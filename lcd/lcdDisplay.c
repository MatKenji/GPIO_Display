/*
 * LCD1602.c
 *
 *  Created on: 21-Jan-2020
 *      Author: Controllerstech
 */

#include "lcdDisplay.h"


void delay (lcd_t *lcd, uint16_t us)
{
	uint32_t ticks = lcd->_ticksForUs*us;

	while (ticks > 0){
		ticks--;
	}
}

/****************************************************************************************************************************************************************/

void send_to_lcd (lcd_t *lcd, char data, int rs)
{
	HAL_GPIO_WritePin(lcd->gpios[LCD_RS].GPIO, lcd->gpios[LCD_RS].pin, rs);  // rs = 1 for data, rs=0 for command
	delay(lcd, 5);
	/* write the data to the respective pin */
	HAL_GPIO_WritePin(lcd->gpios[LCD_D7].GPIO, lcd->gpios[LCD_D7].pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(lcd->gpios[LCD_D6].GPIO, lcd->gpios[LCD_D6].pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(lcd->gpios[LCD_D5].GPIO, lcd->gpios[LCD_D5].pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(lcd->gpios[LCD_D4].GPIO, lcd->gpios[LCD_D4].pin, ((data>>0)&0x01));

	/* Toggle EN PIN to send the data
	 * if the HCLK > 100 MHz, use the  20 us delay
	 * if the LCD still doesn't work, increase the delay to 50, 80 or 100..
	 */
	HAL_GPIO_WritePin(lcd->gpios[LCD_E].GPIO, lcd->gpios[LCD_E].pin, 1);
	delay(lcd, 20);
	HAL_GPIO_WritePin(lcd->gpios[LCD_E].GPIO, lcd->gpios[LCD_E].pin, 0);
	delay(lcd, 20);
}

void lcd_send_cmd (lcd_t *lcd, char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(lcd, datatosend,0);  // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(lcd, datatosend, 0);
}

void lcd_send_data (lcd_t *lcd, char data)
{
	char datatosend;

	/* send higher nibble */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(lcd, datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data)&0x0f);
	send_to_lcd(lcd, datatosend, 1);
}

void lcd_clear (lcd_t *lcd)
{
	lcd_send_cmd(lcd, 0x01);
	HAL_Delay(2);
}

void lcd_put_cur(lcd_t *lcd, int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
        case 2:
        	col |= 0x94;
        	break;
        case 3:
        	col |= 0xD4;
        	break;
    }

    lcd_send_cmd (lcd, col);
}

/**
 * Publics
 */

void lcd_init (lcd_t *lcd)
{
	uint32_t sysclk = HAL_RCC_GetSysClockFreq();

	lcd->_ticksForUs = (sysclk)/(2E6);

	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (lcd, 0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (lcd, 0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (lcd, 0x30);
	HAL_Delay(10);
	lcd_send_cmd (lcd, 0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (lcd, 0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (lcd, 0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (lcd, 0x01);  // clear display
	HAL_Delay(2);
	lcd_send_cmd (lcd, 0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (lcd, 0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (lcd_t *lcd, char *str)
{
	while (*str) lcd_send_data (lcd, *str++);
}
