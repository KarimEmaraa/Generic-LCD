/*
 * lcdmenu.c
 *
 * Created: 9/20/2017 
 *  Author: Karim
 */

#include "lcdmenu.h"
#include <stdbool.h>

static void menu_draw(void);
static void select_event(void);
static void back_event(void);
static void up_event(void);
static void down_event(void);

static const Menu * currentMenu;
static uint8_t arrow_pos;
static uint8_t first_item;
static bool menu_changed = false;


static void menu_draw(void)
{
	LCD_SEND_CMD(0x01);
	LCD_SET_CURSOR(0, arrow_pos);	
	LCD_SEND_CHAR(ARROW);	
	
	for (uint8_t i = 0; i < ROW; i++)
	{
		LCD_SET_CURSOR(1, i);
		
		if(first_item + i < currentMenu->items_num)
			LCD_SEND_STR( currentMenu->items[first_item + i].title );	
	}
		
}

void menuitem_init(MenuItem * const item, unsigned char * const itemtitle, void (*action)(void), const Menu * const nextmenu )
{
	if(!item)
		return;	
	item->title = itemtitle;
	item->next_menu = nextmenu;
	item->action_func = action;
}

void menu_init(Menu * const menu, const MenuItem * const menuitmes, const uint8_t num, const Menu * const prev)
{
	if (!menu)
	{
		return;
	}
	menu->items = menuitmes;
	menu->items_num = num;
	menu->prev_menu = prev;
	if (!currentMenu)
	{	
		currentMenu = menu;
		menu_changed = true;
	}

}

void display_menu(void)
{
	if(menu_changed)
	{
		menu_draw();
		menu_changed = false;
	}
	else if( !(BUTTONS_PORT & 1 << SELECT_PIN))
	{
		while(!(BUTTONS_PORT & 1 << SELECT_PIN));
		select_event();
	}
	else if ( !(BUTTONS_PORT & 1 << BACK_PIN))
	{
		while(!(BUTTONS_PORT & 1 << BACK_PIN));
		back_event();
	}
	else if ( !(BUTTONS_PORT & 1 << UP_PIN))
	{
		while(!(BUTTONS_PORT & 1 << UP_PIN));
		up_event();
	}
	else if ( !(BUTTONS_PORT & 1 << DOWN_PIN))
	{
		while(!(BUTTONS_PORT & 1 << DOWN_PIN));
		down_event();
	}	
}

static void select_event(void)
{
	if (currentMenu->items[first_item + arrow_pos].next_menu)
	{
		currentMenu = currentMenu->items[first_item + arrow_pos].next_menu;
		first_item = 0;
		arrow_pos = 0;
		menu_changed = true;
	}
	else if(currentMenu->items[first_item + arrow_pos].action_func)
	{
		currentMenu->items[first_item + arrow_pos].action_func();
	}
}

static void back_event(void)
{
	if (currentMenu->prev_menu)
	{
		currentMenu = currentMenu->prev_menu;
		first_item = 0;
		menu_changed = true;
	}
}

static void up_event(void)
{
	if (arrow_pos > 0)
	{
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(' ');
		arrow_pos--;
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(ARROW);
	}
	else if(arrow_pos == 0 && first_item > 0)
	{
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(' ');
		arrow_pos = ROW - 1;
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(ARROW);
#if ROW == 2
		if ((first_item - 2) < 0 )
			first_item--;
		else
			first_item -= 2;		
#elif ROW == 4
		first_item -= 4;		
#endif
		menu_changed = true;
	}
}

static void down_event(void)
{
	if (arrow_pos < (ROW - 1) && (arrow_pos + first_item) < (currentMenu->items_num - 1))
	{			
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(' ');
		arrow_pos++;
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(ARROW);
	}
	else if (arrow_pos == (ROW - 1) && first_item < currentMenu->items_num)
	{
#if ROW == 2
		if ((first_item + 2) == currentMenu->items_num)
		{
			return;
		}
#elif ROW == 4
		if ((first_item + 4) == currentMenu->items_num)
		{
			return;
		}			
#endif				
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(' ');
		arrow_pos = 0;
		LCD_SET_CURSOR(0, arrow_pos);
		LCD_SEND_CHAR(ARROW);
#if ROW == 2		
		if(first_item + 2 > currentMenu->items_num)
			first_item += 1;
		else
			first_item += 2;	
#elif ROW == 4
		if(first_item + 4 > currentMenu->items_num)
			first_item += 1;
		else
			first_item += 4;
#endif	
		menu_changed = true;			
	}

}

