/*
 * LCD.c
 *
 * Created: 9/17/2017
 * Author : Karim
 */ 

#include <avr/io.h>
//#define F_CPU 16000000UL

#include "lcdmenu.h"
//#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	lcd_init();
	unsigned char t1[] = {"Timer 0"};
	unsigned char t2[] = {"Timer 1"};
	unsigned char t3[] = {"Timer 2"};
	unsigned char t4[] = {"Timer 3"};
	unsigned char t5[] = {"Timer 4"};
	unsigned char t6[] = {"Subitem 1"};	
	unsigned char t7[] = {"Subitem 2"};
		
	Menu mymenu,submenu;	
			
	MenuItem item1,item2,item3,item4,item5,item6,item7, iteeems[5], itemsmenu[2];
	menuitem_init(&item1,t1,0,&submenu);
	menuitem_init(&item2,t2,0,0);
	menuitem_init(&item3,t3,0,0);
	menuitem_init(&item4,t4,0,0);
	menuitem_init(&item5,t5,0,0);
	menuitem_init(&item6,t6,0,0);
	menuitem_init(&item7,t7,0,0);
			
	itemsmenu[0] = item6;
	itemsmenu[1] = item7;
	
	iteeems[0] = item1;
	iteeems[1] = item2;
	iteeems[2] = item3;
	iteeems[3] = item4;
	iteeems[4] = item5;
	
	menu_init(&mymenu, iteeems ,5,0);	
	//unsigned char y[9] = {0x04, 0x0e, 0x0e, 0x1f,0x00, 0x04,0x04,0x04,0x4};
	//unsigned char k[6] = {0x04, 0x0e, 0x0e, 0x1f,0x00, 0x04};
	//unsigned char x[6] = {"Karim"};
	//lcd_send_custom_char(3, y, 9);
	//lcd_setcursor_to(1,11);
    while (1) 
    {
		display_menu();
    }
}

