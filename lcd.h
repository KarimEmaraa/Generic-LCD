/*
 * lcd.h
 *
 * Created: 9/17/2017
 * Author: Karim
 * *****
 * An lcd library for HD44780 controller based LCD modules. Supports 16,20 columns and 2,4 rows.
 *
 * NOTE: CHECK MODE, F_CPU, FONT MACROS.
 * *****		
 */ 


#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
	#warning "Make sure to match F_CPU here and in user code"
	/*Turn off the warning after doing so.*/
	#define F_CPU 16000000UL
#endif	


#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#define MODE 8				/*Select 8-bit or 4-bit interface from here*/
#define FONT 8				/*Select "5x8 = 8" font or "5x10 = 10"*/
#define ROW  4				/*Select how many lines in lcd*/
#define COL  20				/*Select how many displayable char in lcd*/

#define LCD_DIR		DDRD
#define LCD_PORT	PORTD

#define LCD_CTRL_DIR	DDRC	/*Configure those when using 8bit mode. This port for RS RW EN pins*/
#define LCD_CTRL_PORT	PORTC

#define RS	0					/*Select pin numbers*/
#define RW	1
#define EN	2

void lcd_init(void);														//initialize HD44780 based lcd
void lcd_send_cmd(const uint8_t cmd);										//sends a command to lcd
void lcd_send_char(const unsigned char data);								//writes a char to lcd screen
void lcd_send_string(const unsigned char * str);							//writes a string of chars to lcd screen

/*stores custom generated chars to CGRAM, returns 1 when location > 7 (5x8) or location > 4 (5x10).  0 otherwise
Note: use send char to display custom chars*/
/*WARNING ONLY IN 5x10 MULTIPLY location by 2 WHEN DISPLAYING A CUSTOM CHAR.*/
uint8_t lcd_send_custom_char(const uint8_t location, const unsigned char * bitmap, const uint8_t size);	

/*sets the cursor at x , y positions returns 1 for invalid arguments. 0 otherwise. NOTE: first row/column = 0.
Note: rows addresses may vary from the current addresses. change them in the function definition if needed.*/
uint8_t lcd_setcursor_to(const uint8_t x, const uint8_t y);



#endif /* LCD_H_ */