/**
 * color.c - Source code for the colors struct example
 *
 * @author: Mosiah Beal (mosiah@pdx.edu)
 * @date:	18-Oct-2023
 *
 * This is the source code file for a simple ADT that can be used to create 24-bit color structs and manipulate them.
 * These functions use a struct to hold three 8-bit values (red, green and blue) representing a RGB color (24-bit color)
 */
 
 #include <stdio.h>
 #include "colors.h"
 
 /* makeColor() */
 color_t makeColor( uint8_t redvalue, uint8_t greenvalue, uint8_t bluevalue) {
	color_t new_color;
	new_color.red = redvalue;
	new_color.green = greenvalue;
	new_color.blue = bluevalue;
    return new_color;
 }
 
 /* getColor() */
 uint8_t getColor(thecolors_t whichColor, color_t color) {
	 switch(whichColor)
	 {
	     case 0:    //red
	     return color.red;
	     
	     case 1:    //green
	     return color.green;
	     
	     case 2:    //blue
	     return color.blue;
	     
	     default:   //other
	     printf("Error: Color not found\n");
	 }
	 return (uint8_t) 0;
 }
 
 /* equalColor() */
 bool equalColor(color_t color1, color_t color2) {
	bool equal = 
	(color1.red == color2.red) && 
	(color1.blue == color2.blue) && 
	(color1.green == color2.green);
    return equal;	
 }
 
/* printColor() */
void printColor(color_t c) {
    printf("Color: Red = %d, Green = %d, Blue = %d\n", c.red, c.green, c.blue);
}

 
/* makeRGBLedReg */
uint32_t makeRGBLedReg(color_t s, bool enable){
	uint32_t RGB_register = 0x0;
	uint8_t byte_mask;
	/*
	* enable: bits[31]
	* reserved: bits [30:24] 
	* - OR with 0x80 to set enable, AND with 0x7F to clear enable
	* red byte: bits[16:23]
	* green byte: bits[8:15]
	* blue byte: bits[0:7]
	*/
	
	if (enable)
	{
		RGB_register |= 0x80 << 24;	// set bit 31
	}
	
	//get red value for mask
	byte_mask = getColor(RED, s);
	RGB_register |= byte_mask << 16;
	
	//get green value for mask
	byte_mask = getColor(GREEN, s);
	RGB_register |= byte_mask << 8;
	
	//get blue value for mask
	byte_mask = getColor(BLUE, s);
	RGB_register |= byte_mask;
	
	//printf("Value in RGB_register = %08X\n", RGB_register);
	return RGB_register;
}
