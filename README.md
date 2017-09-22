# Generic-LCD
Generic menu UI library and driver for HD44780 based LCD modules written in c99 using Atmel Studio 7 and avg-gcc compiler tested with proteus 8.6 and on Arduino UNO REV3.
## Generic Menu UI Library
Uses an exisiting driver to generate a menu with a max of 255 items, each can have a separate menu to navigate to and a call-back function.
### Features
* Supports 2 and 4 lines lcd modules.
* Works fine with 4bit and 8bit modes if your library supports both. (Generic LCD library supports both).
* Underlying driver agnostic as long as you provide the proper definitions for macros in the header file.
* Easy usage only 3 functions are needed to get fully working menu.
* Requires 4 buttons *UP/DOWN/SELECT/BACK*.
* Modifiable arrow shape.
### Usage Instructions
1. Include your library under _LCD_LIB include guard then **disable** the pre-processor warning.
2. Change fuction-like macros defintions with your library functions.
3. Initialize the items and menus **in the proper order i.e main menu first** using the *menuitem_init* and *menu_init*.
4. Call *display_menu* function.
### Detailed Decription
#### Item struct 
* Title string to be shown at the lcd. **Should** be no longer than 16 or 20 depnding on your display. (No checking is included).
* Call-back function is called when *SELECT* button is pressed.
* A pointer to other menu to be displayed when *SELECT* button is pressed.
#### Menu struct
* A pointer to array of items in that menu.
* Number of items in that menu.
* A pointer to previous menu (if exisits) to be displayed when *BACK* button is pressed.
### Screen Shots
More to be uploaded.

## Generic LCD library
Provids primitive functions to interact with LCD modules like sending commands, chars and string.
### Features
* Supports 4bit and 8bit interface modes.
* Supports display with 2 or 4 lines and 16 or 20 displays.
* Generation of 5x8 or 5x10 cgram characters.
### Usage Instructions
* Change *F_CPU*, *MODE*, *FONT*, *ROW*, *COL* macros for the desired configuration.
* *When using 4-bit mode* D3-D7 of the display are assumed to be connected the MSB of the port and RS-RW-EN are bit 0 to bit 2 of the same port. *To be fixed later*.
* *When using 8-bit mode* Change *LCD_CTRL_DIR* *LCD_CTRL_PORT* *RW EN ES* macros to match your connection.
* Call *lcd_init*
#### CGRAM character generation instructions.
* *WHEN FONT == 8* argument *location* of *lcd_send_custom_char* function is from 0 to 7.
* *WHEN FONT == 10* argument *location* of *lcd_send_custom_char* function is from 0 to 3.
#### CGRAM character display instrcutions
* *WHEN FONT == 8* argument *location* of *lcd_send_custom_char* is passed to *lcd_send_char* function.
*  *WHEN FONT == 10* argument *location* of *lcd_send_custom_char* is **x2** then passed to *lcd_send_char* function.


