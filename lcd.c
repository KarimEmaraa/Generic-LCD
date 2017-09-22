#include "lcd.h"

/*Helper function*/
static void en_pulse(void);


void lcd_init(void)
{
#if MODE == 8
	LCD_DIR = 0xff;												//LCD PORT is output.
	LCD_PORT = 0x00;
	LCD_CTRL_DIR |= (1 << RS) | (1 << RW) | (1 << EN);			//Set control pins to output.
	LCD_CTRL_PORT &= ~(1 << RS) & ~(1 << RW) & ~(1 << EN);		//Clear RS and RW.
				
	lcd_send_cmd(0x38);
	lcd_send_cmd(0x0c);
	lcd_send_cmd(0x06);
						
#endif
	
#if MODE == 4
	LCD_DIR |= 0xf0 | (1 << RS) | (1 << RW) | (1 << EN);		//LCD port is output
	LCD_PORT &= 0x0f & ~(1 << RS) & ~(1 << RW) & ~(1 << EN);	//clear port pins
	LCD_PORT = 0x30;
	en_pulse();
	en_pulse();	
	en_pulse();												//0x30 is already latched.
	lcd_send_cmd(0x20);
	lcd_send_cmd(0x02);
	lcd_send_cmd(0x28);
	lcd_send_cmd(0x0c);
	lcd_send_cmd(0x06);	
	
#endif	
}

void lcd_send_cmd(const uint8_t cmd)
{
#if MODE == 8
	LCD_PORT = cmd;
	LCD_CTRL_PORT &= ~(1 << RS) & ~(1 << RW);
	en_pulse();
#endif
	
#if MODE == 4
	LCD_PORT &=  ~(1 << RS) & ~(1 << RW);
	LCD_PORT &= 0x0F;
	LCD_PORT |= cmd & 0xf0;
	en_pulse();
	LCD_PORT &= 0x0F;
	LCD_PORT |= (cmd << 4) & 0xf0;
	en_pulse();
#endif
	_delay_ms(2);	
}

void lcd_send_char(const unsigned char data)
{
#if MODE == 8
	LCD_PORT = data;
	LCD_CTRL_PORT |= (1 << RS) & ~(1 << RW);
	en_pulse();
#endif
	
#if MODE == 4
	LCD_PORT |=  (1 << RS) & ~(1 << RW);
	LCD_PORT &= 0x0F;
	LCD_PORT |= data & 0xf0;
	en_pulse();
	LCD_PORT &= 0x0F;
	LCD_PORT |= (data << 4) & 0xf0;
	en_pulse();
#endif
	_delay_us(50);
}

static void en_pulse(void)
{
#if MODE == 8
	LCD_CTRL_PORT |= (1 << EN);
	_delay_us(10);
	LCD_CTRL_PORT &= ~(1 << EN);
	_delay_us(1);
	
#elif MODE == 4
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_us(1);
#endif
}

void lcd_send_string(const unsigned char * str)
{
	while(*str)
	{
		lcd_send_char(*str);
		str++;	
	}
}

uint8_t lcd_send_custom_char(const uint8_t location, const unsigned char * bitmap, const uint8_t size)
{
#if FONT == 8
	if(location > 7 && size < 6) 
		return 1;
		
	lcd_send_cmd(0x40 + location * 8);
	for (uint8_t i = 0; i < size; i++)
	{
		lcd_send_char(bitmap[i]);
	}
	return 0;
	
#elif FONT == 10
	if(location > 3 && size < 10)
		return 1;
	
	lcd_send_cmd(0x40 + location * 16);
	for (uint8_t i = 0; i < size; i++)
	{
		lcd_send_char(bitmap[i]);
	}
	return 0;	

#endif
}

uint8_t lcd_setcursor_to(const uint8_t x, const uint8_t y)
{
	if( x > (COL - 1) || y > (ROW - 1) )
	{
		return 1;
	}
#if COL == 16	
	switch(y)
	{
		case 0:
			lcd_send_cmd(0x80 + x);
			break;
		case 1:
			lcd_send_cmd(0x80 | (0xc0 + x));	
			break;
		case 2:
			lcd_send_cmd(0x80 | (0x90 + x));
			break;	
		case 3:
			lcd_send_cmd(0x80 | (0xd0 + x));
			break;
		default:
			return 1;
	}
#elif COL == 20
	switch(y)
	{
		case 0:
			lcd_send_cmd(0x80 + x);
			break;
		case 1:
			lcd_send_cmd(0x80 | (0xc0 + x));
			break;
		case 2:
			lcd_send_cmd(0x80 | (0x94 + x));
			break;
		case 3:
			lcd_send_cmd(0x80 | (0xd4 + x));
			break;
		default:
			return 1;
	}
#endif						
	return 0;				
}