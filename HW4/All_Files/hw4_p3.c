/**
 * hw4_p3.c
 *
 * Author: Mosiah Beal (mosiah@pdx.edu)
 * Date:   Nov. 16, 2023
 * 
 * Description:
 * This program tests the iom361 peripheral registers by "hardwiring" switch
 * and RGB LED data and sending it to the peripheral registers.
 * It also tests the temperature and humidity sensor by reading in data from 
 * the sensor and storing it in an array. It then sorts the data and prints
 * it to the console.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "iom361_r2.h"
#include "colors.h"
#include "LinkedList.h"

// typedefs, enums and constants
typedef struct {	// data structure that combines sw and RGB LED data
	uint32_t sw;
	color_t rgb;
} iodata_t;

typedef struct {
	float temp;
	float humidity;

	uint32_t temp_value;
	uint32_t humidity_value;
	
	// (type) timestamp;

} sensor_data_t;

typedef sensor_data_t* sensor_data_t_ptr;

#define MAX_DATA_ITEMS	10
#define NUM_READINGS	8
#define NUM_LEDS		16
#define NUM_SWITCHES	16

#define TEMP_RANGE_LOW	42.0
#define TEMP_RANGE_HI	52.0
#define HUMID_RANGE_LOW	72.6
#define HUMID_RANGE_HI	87.3
  
  
// function prototypes
void print_dir(void);
int random_value(int range);

int populate_data_array(void);
int populate_sensor_data(void);

void write_switch_to_LED(uint32_t reg_value);
void read_sensor(sensor_data_t_ptr reading);

int insert_temp(LinkedListPtr_t sorted, double temp);
int insert_humid(LinkedListPtr_t sorted, double humidity);

uint32_t temp_to_temp_value(float temp);
uint32_t humid_to_humid_value(float humid);

void printSortedTemps(LinkedListPtr_t sorted);
void printSortedHumid(LinkedListPtr_t sorted);



// global variables
uint32_t* io_base;
iodata_t data[MAX_DATA_ITEMS];				// array to hold switch and duty cycle data
sensor_data_t sensor_data[NUM_READINGS];	// array to hold sensor data



// main()
int main() {
	int rtn_code;
	uint32_t reg_value;
	int num_items;
	 
	// greet the user and display the working directory for the application
	printf("Sorting random arrays of temperatures and humidities (mosiah@pdx.edu)\n");
	print_dir();
	 
	// initialize IO module
	printf("Test 1: Initialize and read the I/O registers\n");
	io_base = iom361_initialize(NUM_SWITCHES, NUM_LEDS, &rtn_code);
	if (rtn_code != 0) {
		// initialization failed
		printf("Could not initialize I/O module\n");
		return 1;
	}
	printf("\n");
	 
	// read/display all of the register values
	for (int i = 0; i < NUM_IO_REGS; i++) {
		// The I/O registers are all 32-bits wide, so 4 bytes apart
		reg_value = iom361_readReg(io_base, (i * 4), &rtn_code);
		if (rtn_code == 0) {
			printf("Reading I/O register %d, value: %08X\n",
				i, reg_value);
		}
		else {
			 printf("ERROR: Couldn't read I/O register %d\n", i);
		}
	}
	// get the "hardwired" data
	num_items = populate_data_array();
	
	// Show contents of data array
	if(true) {
		
		// display the contents of the data array
		printf("SHOWING DATA...\n");
		for (int i = 0; i < num_items; i++){
			uint32_t sw;
			uint8_t dcr, dcg, dcb;
			
			// separate and display the data items
			sw = data[i].sw;
			dcr = data[i].rgb.red;
			dcg = data[i].rgb.green;
			dcb = data[i].rgb.blue;
			printf("INFO[main()]:  Retrieved item[%d] sw=%08x, duty cycles= {%d, %d, %d}\n",
					i, sw, dcr, dcg, dcb);
		}
		printf("INFO(main()]: There are %d data items to send to I/O module\n", num_items);
		
		
		printf("\nTest 2: Test the switches and leds\n");
		// sending the data to the iom361 peripheral registers
		for (int i = 0; i < num_items; i++) {
			printf("\nSENDING ITEM %d to I/O MODULE...\n", i);

			// Set switch register
			//printf("\tsetting switches to %08X\n", data[i].sw); 
			write_switch_to_LED(data[i].sw);

			sleep(3);
		}

		// set the duty cycles of the RGB LED
		printf("\nTest 3: Test the RGB LED\n");	
		for (int i = 0; i < num_items; i++) {
			printf("\nSENDING ITEM %d to I/O MODULE...\n", i);

			// Set RGB register
			reg_value = makeRGBLedReg(data[i].rgb, true);
			//printf("\tsetting RGB value to %08X\n", reg_value);
			iom361_writeReg(io_base, RGB_LED_REG, reg_value, &rtn_code);
			if (rtn_code != 0) {
				printf("ERROR(main): Could not write RGB LED register\n");
			}

			sleep(3);
		}
		
	}

	// Sensor Tests
	float temp, humid;
	uint32_t temp_value, humid_value;
	
	// set a new temperature and humidity and display it
	printf("\nTest 4: Test the sensor\n");	 
	_iom361_setSensor1(10.0, 63.0);
	temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
	temp = (temp_value / powf(2,20)) * 200.0 - 50;
	humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
	humid = (humid_value/ pow(2, 20)) * 100;
	printf("Temperature: %3.1fC(%08X), Relative Humidity: %3.1f%%(%08X)\n", 
		temp, temp_value, humid, humid_value);
		
	
	printf("\nTest 5: Test the random sensor value function\n");	 
	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
		temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
	temp = (temp_value / powf(2,20)) * 200.0 - 50;
	humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
	humid = (humid_value/ pow(2, 20)) * 100;
	printf("Temperature: %3.1fC(%08X), Relative Humidity: %3.1f%%(%08X)\n", 
		temp, temp_value, humid, humid_value);

	
	printf("\nTest 5: Try a 2nd set of random numbers\n");	 
	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
	temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
	temp = (temp_value / powf(2,20)) * 200.0 - 50;
	humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
	humid = (humid_value/ pow(2, 20)) * 100;
	printf("Temperature: %3.1fC(%08X), Relative Humidity: %3.1f%%(%08X)\n", 
		temp, temp_value, humid, humid_value);
	

	printf("\nRandom Readings\n");
	LinkedListPtr_t sorted_temps = createLList();	// Linked List to hold sorted temperatures
	LinkedListPtr_t sorted_humid = createLList();	// Linked List to hold sorted humidities
	
	// Now get the sensor data from the iom361 peripheral registers
	int num_readings = populate_sensor_data();
	int temp_node_index;	// index at which the temperature was inserted
	int humid_node_index;	// index at which the humidity was inserted
	
	
	sensor_data_t reading;	// struct to hold the sensor data
	for (int i = 0; i < num_readings; i++){
			reading = sensor_data[i];	// store the reading into the struct
			printf("Retrieved reading[%d] temp=%3.1fC(%08X), humidity=%3.1f%%(%08X)\n",
					i, reading.temp, reading.temp_value, reading.humidity, reading.humidity_value);
			
			// sort the data
			//printf("\nInserting data\n");
			temp_node_index = insert_temp(sorted_temps, reading.temp);
			humid_node_index = insert_humid(sorted_humid, reading.humidity);
			
			//printf("Inserted %3.1lfC at node %d: (of %d)\n", reading.temp, temp_node_index, LListLength(sorted_temps)+1);
			
			//printf("Inserted %lf%% at node %d: (of %d)\n", reading.humidity, humid_node_index, LListLength(sorted_temps)+1);
		}
	
	// Look at sorted lists
	printf("\n\n");
	printf("Sorted Temps: (low to high)\n");
	printSortedTemps(sorted_temps);
	
	printf("\n");
	printf("Sorted Humidities: (low to high)\n");
	printSortedHumid(sorted_humid);

	// Free lists from memory
	deleteLList(sorted_temps);
	deleteLList(sorted_humid);
	
	return 0;
}
 
/**
 * print_dir() - prints the current working directory
 * 
 * This function prints the current working directory to the console.
 *
 */
void print_dir(void) {
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer to hold the path   
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");
}

/**
 * random_value() - generates a random value between 0 and range
 * 
 * @param range: the upper bound of the random value
 * @return the random value
 * 
 * This function takes an upper bound and generates a random value between 0 and
 * the upper bound.
 *
 */
int random_value(int range){
	return (int) (rand() % range);
}

/**
 * temp_to_temp_value() - converts a temperature value to a temperature register value
 * 
 * @param temp: the temperature value to convert
 * @return the temperature register value
 * 
 * This function takes a temperature value and converts it back to a temperature register
 * value
 *
 */
uint32_t temp_to_temp_value(float temp) {
    uint32_t temp_value = (temp + 50) / 200.0 * powf(2,20);
    return temp_value;
}

/**
 * humid_to_humid_value() - converts a humidity value to a humidity register value
 * 
 * @param humid: the humidity value to convert
 * @return the humidity register value
 * 
 * This function takes a humidity value and converts it back to a humidity register
 * value
 *
 */
uint32_t humid_to_humid_value(float humid) {
    uint32_t humid_value = humid / 100.0 * powf(2,20);
    return humid_value;
}

 /**
  * read_sensor() - reads in data from temperature and humidity sensor
  * @param reading: a pointer to the sensor_data_t struct to store the reading
  * 
  * This function reads in data from the temperature and humidity sensor and
  * stores it in the sensor_data_t struct passed in.
  *
  */
void read_sensor(sensor_data_t_ptr reading) {
	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
	reading->temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
	reading->temp = (reading->temp_value / powf(2,20)) * 200.0 - 50;
	reading->humidity_value = iom361_readReg(io_base, HUMID_REG, NULL);
	reading->humidity = (reading->humidity_value/ pow(2, 20)) * 100;

	//printf("Temperature: %3.1fC(%08X), Relative Humidity: %3.1f%%(%08X)\n", 
	//	reading->temp, reading->temp_value, reading->humidity, reading->humidity_value);
}

 /**
  * write_switch_to_LED() - sets switches and LEDs to value passed in
  * @param reg_value: the value to set the switches and LEDs to
  *
  * This function takes a uint32 value and writes it to the switches register.
  * It then reads the switches register and writes the value read in to the
  * LED register.
  *
  */
void write_switch_to_LED(uint32_t reg_value) {
	printf("\tsetting switches to %8X\n", reg_value); 
	_iom361_setSwitches(reg_value);
	reg_value = iom361_readReg(io_base, SWITCHES_REG, NULL);
	iom361_writeReg(io_base, LEDS_REG, reg_value, NULL);
}

 /**
  * populate_data_array() - "hardwires" switch and RGB duty cycle data
  * @return: the number of items in the data array
  *
  * This function populates the data array with switch and duty cycle values
  * to be sent to the iom361 peripheral registers.
  *
  */
int populate_data_array(void) {
	int num_items = 0;
	data[0].sw = 0x0000A5A5;
	data[0].rgb.red = 25; data[0].rgb.green = 102; data[0].rgb.blue = 128;
	++num_items;
	
	data[1].sw = 0x00005A5A;
	data[1].rgb.red = 128; data[1].rgb.green = 128; data[1].rgb.blue = 128;
	++num_items;
	
	data[2].sw = 0x0000FFFF;
	data[2].rgb.red = 255; data[2].rgb.green = 255; data[2].rgb.blue = 255;
	++num_items;
	
	data[3].sw = 0x00000000;
	data[3].rgb.red = 0; data[3].rgb.green = 0; data[3].rgb.blue = 0;
	++num_items;
	
	data[4].sw = 0x0000ECE3;
	data[4].rgb.red = 30; data[4].rgb.green = 60; data[4].rgb.blue = 90;
	++num_items;
	
	// ADD YOUR TEST CASES HERE
	srand(time(NULL));   // Initializing random number generator
	while(num_items < MAX_DATA_ITEMS) {
		uint32_t random_switch = (uint32_t) rand();		//random uint32 value
		data[num_items].sw = random_switch & 0xFFFF;	//mask lower 2 bytes
		
		data[num_items].rgb.red = random_value(256); 
		data[num_items].rgb.green = random_value(256); 
		data[num_items].rgb.blue = random_value(256);
		++num_items;
	}
	
	return num_items; 	
}

 /**
  * populate_sensor_data() - "hardwires" sensor data
  * @return: the number of items in the sensor_data array
  *
  * This function populates the sensor_data array with temperature and humidity
  * values to be sorted.
  *
  */
int populate_sensor_data(void) {
	int num_items = 0;
	
	// ADD YOUR TEST CASES HERE
	srand(time(NULL));   // Initializing random number generator
	while(num_items < NUM_READINGS) {
		read_sensor(&sensor_data[num_items++]);	//store the reading into the struct at current index
	}
	
	return num_items; 	
}

/**
  * insert_temp() - inserts a temperature reading into a sorted linked list
  * @param sorted: a pointer to the sorted linked list
  * @param temp: the temperature reading to insert
  * @return: the index at which the reading was inserted
  * 
  * This function takes a pointer to a sorted linked list and a temperature
  * reading and inserts the reading into the list in sorted order. It returns
  * the index at which the reading was inserted.
  *
  */
int insert_temp(LinkedListPtr_t sorted, double temp) {
	int list_len = LListLength(sorted);
	
	if(list_len == 0) {
		// if the list is empty, insert the reading at the head
		insertNodeInLList(sorted, temp, 1);
		return 1;
	}

	int i = 1;
	// find the index to insert the reading
	
	//printf("list_len: %d\n", list_len);
	//printf("temp: %lf\n", temp);
	
	//while (not at end of list)
	while(i <= list_len) {
	
	double current_temp = getNodeDataInLList(sorted, i);
	//printf("current_temp: %lf\n", current_temp);
	

	// if temp > temp at current index, increment index
	if (temp >= current_temp) {
		//printf("%lf >= sorted[%d]: %lf\n", temp, i, getNodeDataInLList(sorted, i));
		i++;
		continue;
	}
	// else insert temp at current index
	  else {
		//printf("\n%lf < sorted[%d]: %lf\n", temp, i, getNodeDataInLList(sorted, i));
		//printf("Inserted %lfC at index %d\n", temp, i);
		insertNodeInLList(sorted, temp, i);
		return i;
	}
	}
	
	// At end of list, insert temp at end
	//printf("%lfC > sorted[%d]: %lf\n", temp, i, getNodeDataInLList(sorted, i-1));
	insertNodeInLList(sorted, temp, i);
	return i;
}

/**
  * insert_humid() - inserts a humidity reading into a sorted linked list
  * @param sorted: a pointer to the sorted linked list
  * @param humidity: the humidity reading to insert
  * @return: the index at which the reading was inserted
  *
  * This function takes a pointer to a sorted linked list and a humidity
  * reading and inserts the reading into the list in sorted order. It returns
  * the index at which the reading was inserted.
  *
  */
int insert_humid(LinkedListPtr_t sorted, double humidity) {
	int list_len = LListLength(sorted);
	
	if(list_len == 0) {
		// if the list is empty, insert the reading at the head
		insertNodeInLList(sorted, humidity, 1);
		return 1;
	}

	int i = 1;
	// find the index to insert the reading
	
	//printf("list_len: %d\n", list_len);
	//printf("humidity: %lf\n", humidity);
	
	//while (not at end of list)
	while(i <= list_len) {
	
	double current_humidity = getNodeDataInLList(sorted, i);
	//printf("current_humidity: %lf\n", current_humidity);
	

	// if humidity > humidity at current index, increment index
	if (humidity >= current_humidity) {
		//printf("%lf >= sorted[%d]: %lf\n", humidity, i, getNodeDataInLList(sorted, i));
		i++;
		continue;
	}
	// else insert humidity at current index
	  else {
		//printf("\n%lf < sorted[%d]: %lf\n", humidity, i, getNodeDataInLList(sorted, i));
		//printf("Inserted %lf%% at index %d\n", humidity, i);
		insertNodeInLList(sorted, humidity, i);
		return i;
	}
	}
	
	// At end of list, insert humidity at end
	//printf("%lf%% > sorted[%d]: %lf\n", humidity, i, getNodeDataInLList(sorted, i-1));
	insertNodeInLList(sorted, humidity, i);
	return i;
}

/**
  * printSortedTemps() - prints the sorted temperatures
  * @param sorted: a pointer to the sorted linked list
  *
  * This function takes a pointer to a sorted linked list and prints the
  * temperatures in the list.
  * It also prints the average temperature.
  *
  */
void printSortedTemps(LinkedListPtr_t sorted) {
	int list_len = LListLength(sorted);
	double avg_temp = 0;
	//printf("len = %d\n", list_len);
	for(int i = 0; i < list_len; i++) {
		double temp = getNodeDataInLList(sorted, i+1);
		printf("\tT[%d] = %3.1lfC ", i, temp);
		printf("(%08X)\n", temp_to_temp_value(temp));
		avg_temp += temp;
	}
	printf("Average Temperature = %gC\n", (double) avg_temp / list_len);
}

/**
  * printSortedHumid() - prints the sorted humidities
  * @param sorted: a pointer to the sorted linked list
  *
  * This function takes a pointer to a sorted linked list and prints the
  * humidities in the list.
  * It also prints the average humidity.
  *
  */
void printSortedHumid(LinkedListPtr_t sorted) {
	int list_len = LListLength(sorted);
	double avg_humid = 0;
	//printf("len = %d\n", list_len);
	for(int i = 0; i < list_len; i++) {
		double humid = getNodeDataInLList(sorted, i+1);
		printf("\tH[%d] = %3.1lf%% ", i, humid);
		printf("(%08X)\n", humid_to_humid_value(humid));
		avg_humid += humid;
	}
	printf("Average Humidity = %g%%\n", (double) avg_humid / list_len);
}
