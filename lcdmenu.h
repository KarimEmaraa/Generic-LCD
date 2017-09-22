/*
 * lcdmenu.h
 *
 * Created: 9/20/2017
 * Author: Karim
 * Menu interface library for HDD44780 based lcd modules.
 * NOTE: Include your lcd library and modify macros definition with your functions.
 */ 


#ifndef LCDMENU_H_
#define LCDMENU_H_

#ifndef _LCD_LIB
	#warning "Include your lcd library here."
	/*Turn off this warning after including your lcd library.*/
	#define _LCD_LIB
	#include "lcd.h"	/*Include your lcd library here.*/
#endif

#ifndef COL
	#define COL 16
#endif
#ifndef ROW
	#define ROW 4
#endif	

#define BUTTONS_PORT		PINB

#define SELECT_PIN	0				/*Select push buttons pins.*/
#define BACK_PIN	1
#define UP_PIN		2
#define DOWN_PIN	3
#define ARROW		0x7e

/*Change macros definitions with lcd library function names*/ 
#define LCD_INIT()						lcd_init()
#define LCD_SEND_CHAR(CHAR)				lcd_send_char((CHAR))
#define LCD_SEND_CMD(CMD)				lcd_send_cmd((CMD))
#define LCD_SEND_STR(STR)				lcd_send_string((STR))
#define LCD_SEND_CUST_CHAR(CUST)		lcd_send_custom_char((CUST))
#define LCD_SET_CURSOR(X, Y)			lcd_setcursor_to((X), (Y))  /*WARNING: ROWS AND COLUMNS START AT 0*/

struct _menuitem;

typedef struct _menu
{
	const struct _menuitem  * items;	//items to be displayed.
	uint8_t items_num;					//number of items in menu.
	const struct _menu * prev_menu;		//previous menu.
}Menu;


typedef struct _menuitem
{
	unsigned char * title;				//item display string.
	void (*action_func)(void);			//call back function when pressing select button.
	const Menu * next_menu;
}MenuItem;


/*Initializes MenuItem struct members.*/
void menuitem_init(MenuItem * const item, unsigned char * const itemtitle, void (*action)(void), const Menu * const nextmenu );
void menu_init(Menu * const menu, const MenuItem * const menuitmes, const uint8_t num, const Menu * const prev);
void display_menu(void);





#endif /* LCDMENU_H_ */