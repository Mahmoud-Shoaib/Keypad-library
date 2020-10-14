/*
 * Keypad.c
 *
 * Created: 2020-10-14 1:07:41 AM
 * Author : Mahmoud Shoaib
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define portA 1
#define portB 2
#define portC 3
#define portD 4

void Make_pin_input(uint8_t port,uint8_t pin);
void Make_pin_output(uint8_t port,uint8_t pin);
void Set_pin(uint8_t port,uint8_t pin);
void Reset_pin(uint8_t port,uint8_t pin);
int IsPressed_pin(uint8_t port,uint8_t pin);
int Keypad();
void init_Keypad();
void init_display();

int num;

int main(void)
{
    /* Replace with your application code */
	init_Keypad();
	init_display();
	
	while (1) 
    {	
		num = Keypad();
		PORTA = num == 50 ? PORTA: num;	
    }
}

void Make_pin_input(uint8_t port,uint8_t pin){
	
	switch (port)
	{
		case 1: DDRA &= ~(1<<pin); break;
		case 2: DDRB &= ~(1<<pin); break;
		case 3: DDRC &= ~(1<<pin); break;
		case 4: DDRD &= ~(1<<pin); break;
		default: break;
	}
}

void Make_pin_output(uint8_t port,uint8_t pin){
	
	switch (port)
	{
		case 1: DDRA |= (1<<pin); break;
		case 2: DDRB |= (1<<pin); break;
		case 3: DDRC |= (1<<pin); break;
		case 4: DDRD |= (1<<pin); break;
		default: break;
	}
}

void Set_pin(uint8_t port,uint8_t pin){
	
	switch (port)
	{
		case 1: PORTA |= (1<<pin); break;
		case 2: PORTB |= (1<<pin); break;
		case 3: PORTC |= (1<<pin); break;
		case 4: PORTD |= (1<<pin); break;
		default: break;
	}
}

void Reset_pin(uint8_t port,uint8_t pin){
	
	switch (port)
	{
		case 1: PORTA &= ~(1<<pin); break;
		case 2: PORTB &= ~(1<<pin); break;
		case 3: PORTC &= ~(1<<pin); break;
		case 4: PORTD &= ~(1<<pin); break;
		default: break;
	}
}

int IsPressed_pin(uint8_t port,uint8_t pin){
	
	switch (port)
	{
		case 1: if(PINA & (1<<pin)) {return 1;}
		else { return 0; } break;
		
		case 2: if(PINB & (1<<pin)) {return 1;}
		else { return 0; } break;
		
		case 3: if(PINC & (1<<pin)) {return 1;}
		else { return 0; } break;
			
		case 4: if(PIND & (1<<pin)) {return 1;}
		else { return 0; } break;
			
		default: return 0; break;
	}
}

int Keypad()
{
	Set_pin(portD,0);
	Set_pin(portD,1);
	Set_pin(portD,2);
	
	if (IsPressed_pin(portD,3))
	{
		Reset_pin(portD,0);
		Reset_pin(portD,1);
		
		if (IsPressed_pin(portD,3)) 
		{
			return 1;
			_delay_ms(20);
		}
		
		else {
			Reset_pin(portD,0);
			Reset_pin(portD,2);
			Set_pin(portD,1);
			
			if (IsPressed_pin(portD,3)) {
				return 2;
				_delay_ms(20);
			}
			else
			{
				Reset_pin(portD,1);
				Reset_pin(portD,2);
				Set_pin(portD,0);
				
				if (IsPressed_pin(portD,3)) {
					return 3;
					_delay_ms(20);
				}
			}
		}
	}
	else if (IsPressed_pin(portD,4)){
		Reset_pin(portD,0);
		Reset_pin(portD,1);
		
		if (IsPressed_pin(portD,4)) 
		{
			return 4;
			_delay_ms(20);
		}
		else {
			Reset_pin(portD,0);
			Reset_pin(portD,2);
			Set_pin(portD,1);
			
			if (IsPressed_pin(portD,4)) 
			{
				return 5;
				_delay_ms(20);
			}
			else 
			{
				Reset_pin(portD,1);
				Reset_pin(portD,2);
				Set_pin(portD,0);
				
				if (IsPressed_pin(portD,4)) {
					return 6;
					_delay_ms(20);
				}
			}
		}
	}
	
	else if (IsPressed_pin(portD,5))
	{
		Reset_pin(portD,0);
		Reset_pin(portD,1);
		
		if (IsPressed_pin(portD,5)) {
			return 7;
			_delay_ms(20);
		}
		else {
			Reset_pin(portD,0);
			Reset_pin(portD,2);
			Set_pin(portD,1);
			if (IsPressed_pin(portD,5)) {
				return 8;
				_delay_ms(20);
			}
			else 
			{ 
				Reset_pin(portD,1);
				Reset_pin(portD,2);
				Set_pin(portD,0);
				
				if (IsPressed_pin(portD,5)) {
					return 9;
					_delay_ms(20);
				}
			}
		}
	}
	
	else if (IsPressed_pin(portD,6))
	{
		return 0;
		_delay_ms(20);
	}
			
		return 50;
}

void init_Keypad()
{
	Make_pin_output(portD,0);
	Make_pin_output(portD,1);
	Make_pin_output(portD,2);
	Make_pin_input(portD,3);
	Make_pin_input(portD,4);
	Make_pin_input(portD,5);
	Make_pin_input(portD,6);
}

void init_display()
{
	Make_pin_output(portA,0);
	Make_pin_output(portA,1);
	Make_pin_output(portA,2);
	Make_pin_output(portA,3);
}
