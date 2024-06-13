/*
 * lcd1602.h
 *
 *  Created on: Jan 21, 2020
 *      Author: Controllerstech
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_


#include <stdint.h>
/**
 * Uncomment the include here the stm32 main library, example:
 */
//#include "stm32f1xx.h"
//#include "stm32f2xx.h"
#include "stm32f4xx.h"
//#include "stm32g0xx.h"
// ..you can add another if wasn't inserted here

/*
 * Enumerates
 */
typedef enum{
	LCD_RS,
	LCD_RW,
	LCD_E,
	LCD_D4,
	LCD_D5,
	LCD_D6,
	LCD_D7,

	LCD_PIN_QTD
}lcd_pin_e;

typedef struct{
	GPIO_TypeDef *GPIO;
	uint32_t pin;
}gpio_t;

typedef struct{
	gpio_t gpios[LCD_PIN_QTD];
	uint32_t columns;
	uint32_t rows;
	// please, do not customize this values
	uint32_t _ticksForUs;
}lcd_t;

/*
 * Function Prototypes
 */

void lcd_init (lcd_t *lcd);   // initialize lcd

void lcd_send_cmd (lcd_t *lcd, char cmd);  // send command to the lcd

void lcd_send_data (lcd_t *lcd, char data);  // send data to the lcd

void lcd_send_string (lcd_t *lcd, char *str);  // send string to the lcd

void lcd_put_cur(lcd_t *lcd, int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_clear (lcd_t *lcd);

#endif /* INC_LCD1602_H_ */
