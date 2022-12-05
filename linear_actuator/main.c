/*
 * Servo_Motor.c
 *
 * Created: 2022-11-19 오후 3:19:22
 * Author : donghyun
 */ 


#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

unsigned char ch;

ISR(USART0_RX_vect){
	ch = UDR0;
}

ISR(USART0_TX_vect){
	UDR0 = ch;
}

void Init_USART0(void){			// 블루투스 초기화
	UCSR0A = 0x00;
	UCSR0B = (1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN0) | (1<<TXEN0);
	UCSR1C = (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0C &= ~(1<<UMSEL0);
	
	UBRR0H = 0;
	UBRR0L = 95;
}

int main(void)
{
	DDRB|=0x60;		//PB5,6
	PORTB|=0x60;

	TCCR1A=0xA2;
	TCCR1B=0x1b;
	ICR1=4999;     //TOP
	OCR1A=375;     //0도
	OCR1B=375;
	
	Init_USART0();
	sei();
	LCD_Init();
	LCD_Clear();
	LCD_Pos(0,0);
	while(1)
	{
		OCR1B = 250;
		_delay_ms(1000);
		OCR1B = 375;
		_delay_ms(1000);
		OCR1B = 500;
		_delay_ms(1000);
		if(ch == '1'){
			LCD_Pos(0,0);
			LCD_Str("1st Floor");
			OCR1A=250;     //-90도	1층	
			ch = '0';
		}
		else if(ch == '2'){
			LCD_Pos(0,0);
			LCD_Str("2nd Floor");
			OCR1A=333;		// 2층
			ch = '0';
		}
		else if(ch == '3'){
			LCD_Pos(0,0);
			LCD_Str("3rd Floor");
			OCR1A = 416;		// 3층
			ch = '0';
		}
		else if(ch == '4'){
			//LCD_Clear();
			LCD_Pos(0,0);
			LCD_Str("4th Floor");
			OCR1A=500;     //90도	4층
			ch = '0';
		}
		else{
			//LCD_Clear();
			LCD_Pos(0,0);
			LCD_Str("Enter 1to4 floor");
		}
	}
}