/**
 * stackADT_LL.c - Starter code for your linked list-based Stack ADT
 *
 * Author: Mosiah Beal (mosiah@pdx.edu)
 * Date:   Nov. 16, 2023
 * 
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

// typedefs, enums and constants
typedef struct {	// data structure that combines sw and RGB LED data
	uint32_t sw;
	color_t rgb;
} iodata_t;

#define MAX_DATA_ITEMS	10
#define NUM_LEDS		16
#define NUM_SWITCHES	16

#define TEMP_RANGE_LOW	42.0
#define TEMP_RANGE_HI	52.0
#define HUMID_RANGE_LOW	72.6
#define HUMID_RANGE_HI	87.3
  
  
//prototypes
void print_dir(void);
int random_value(int range);
int populate_data_array(void);
void write_switch_to_LED(uint32_t reg_value);
void read_sensor(void);


// global variables
uint32_t* io_base;
iodata_t data[MAX_DATA_ITEMS];	// array to hold switch and duty cycle data

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
	if(false) {
		
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
		
		// sending the data to the iom361 peripheral registers
		
		for (int i = 0; i < num_items; i++) {
			// ADD YOUR CODE TO SEND DATA TO iom361 peripheral registers
			printf("\nSENDING ITEM %d to I/O MODULE...\n", i);
			
			// Set switch register
			//printf("\tsetting switches to %08X\n", data[i].sw); 
			write_switch_to_LED(data[i].sw);
			
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

	// set a new temperature and humidity and display it
	printf("\nTest 4: Test the sensor\n");	 
	_iom361_setSensor1(10.0, 63.0);
	read_sensor();
	
	printf("\nTest 5: Test the random sensor value function\n");	 
	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
	read_sensor();
	
	printf("\nTest 5: Try a 2nd set of random numbers\n");	 
	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
	read_sensor();
	 
	return 0;
}
 
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
  * read_sensor() - reads in data from temperature and humidity sensor
  *
  *
  *
  */
void read_sensor() {
	float temp, humid;
	uint32_t temp_value, humid_value;
	temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
	temp = (temp_value / powf(2,20)) * 200.0 - 50;
	humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
	humid = (humid_value/ pow(2, 20)) * 100;
	printf("Temperature: %3.1fC(%08X), Relative Humidity: %3.1f%%(%08X)\n", 
		temp, temp_value, humid, humid_value);
}

 /**
  * write_switch_to_LED() - sets switches and LEDs to value passed in
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
  *
  * This function populates the data array with switch and duty cycle values
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

int random_value(int range){
	return (int) (rand() % range);
}

