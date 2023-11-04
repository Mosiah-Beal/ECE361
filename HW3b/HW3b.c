/**
 * hw3_prob2_starter - starter code for IO application
 *
 * @file:	hw3_prob2_starter.c
 * @author:	Mosiah Beal (mosiah@pdx.edu)
 * @date:	30 Oct. 2023
 *
 * Populates array with switch and RGB color data in the application.  Uses iom361
 * to copy switch data to the LEDs and to set the duty cycles of the RGB LED.
 * This problem does not use the AHT20 registers or the RESERVED registers.  
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

#include "longestLineHelper.h"
#include "colors.h"
#include "iom361.h"

// constants, enums and typedef
#define MAX_DATA_ITEMS	10
#define NUM_LEDS		16
#define NUM_SWITCHES	16

typedef struct {	// data structure that combines sw and RGB LED data
	uint32_t sw;
	color_t rgb;
} iodata_t;
  
// global variables
uint32_t* io_base;	// base address of iom361
iodata_t data[MAX_DATA_ITEMS];	// array to hold switch and duty cycle data

// helper function prototypes
int populate_data_array(void);
void print_dir(void);

// main()
int main() {
	int rtn_code;
	uint32_t reg_value;
	int num_items;
		 
	// greet the user and display the working directory for the application
    printf("Trial Run (mosiah@pdx.edu)\n");
    print_dir();
	 
	// ADD YOUR CODE TO INITIALIZE iom361
	io_base = iom361_initialize(NUM_SWITCHES, NUM_LEDS, &rtn_code);
	//add error checking to see if initilization was successful
	
	// get the "hardwired" data
	num_items = populate_data_array();
	
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
				num_items, sw, dcr, dcg, dcb);
	}
	printf("INFO(main()]: There are %d data items to send to I/O module\n", num_items);
	
	// sending the data to the iom361 peripheral registers
	for (int i = 0; i < num_items; i++) {
		// ADD YOUR CODE TO SEND DATA TO iom361 peripheral registers
		
		// Set switch register
		printf("\tsetting switches to %8X\n", data[i].sw); 
		_iom361_setSwitches(reg_value);
		reg_value = iom361_readReg(io_base, SWITCHES_REG, NULL);
		iom361_writeReg(io_base, LEDS_REG, reg_value, NULL);
		
		
		sleep(3);
	}
	return 0;
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
	
	return num_items; 	
}

void print_dir(void)
{
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
