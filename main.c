/*
 * main.c
 *
 *  Created on: May 25, 2022
 *      Author: ahmed
 */

#include"sensor.h"
#include"lcd.h"
#include"avr/io.h"
#include"util/delay.h"
int main(void){
//var to store in it the distance
volatile uint16 distance=0;

//enable global intterupts
SREG=(1<<7);

//initiate the LCD, Ultrasonic and ICU
LCD_init();
Ultrasonic_init();

//display at the beginning Distance then go to the below line and display cm

LCD_moveCursor(0,3);
LCD_displayString("Distance");
LCD_moveCursor(1,7);
LCD_displayString("cm");

//move the cursor of the LCD to the location where the distance will be displayed.
LCD_moveCursor(1,3);


/* 1- we call the sensor function that measure the distance and trigger the sensor
 * 2- display the value on LCD
 * delay 61 ms as according to the datasheet we should wait this time before triggering again
 * the sensor to generate 8 pulses to prevent trigger signal to the echo signal.
 */

while(1){
	distance=Ultrasonic_readDistance();
	 LCD_intgerToString(distance);

	 /*the below two lines control the dispaly as if the number is bigger than 100 and returns
	  * again to less than 100 cm will remove the last number stored in LCD which we don't
	  * need it
	  */

	 LCD_displayCharacter(' ');
	 LCD_moveCursor(1,3);
	 _delay_ms(61);

}
}
