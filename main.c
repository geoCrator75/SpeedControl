#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <lcd.h>

char ADCvalue[4];

int main(void)
{
 
//***********************TEST PROGRAM - SPEED CONTROL****************************
	
	LCDinitialize();
	
	sei(); // Enable Global Interrupts
	
	ADMUX = 0b01100001;
	
	ADCSRA = 0b11001100; //ADEN, ADSC, ADIE, ASPS2
	
	//PWM setup
	
	DDRD = 0b10000000;
	
	TCCR2 = 0b01101001; // WGM20, COM21, WGM21, CS20
	
	TCNT2 = 0b11111111;
	

	LCDcommand(0x01);
	int temp=0;
	int prv=0;
	char pwm[2];
	char change[2];
	
	while(1)
	{
		LCDcommand(0x80);
		LCDdata("ADC=    ");
		LCDcommand(0x80+4); 
		LCDdata(ADCvalue);
		
		LCDcommand(0x80+8);
		LCDdata("PWM%=   ");
		
		LCDcommand(0x80+13);
		temp = 100 * ADCH / 255; 
		itoa(temp,pwm,10);
		LCDdata(pwm);
		
		LCDcommand(0x80+64);
		LCDdata("d/dt=   ");
		
		LCDcommand(0x80+68);
		temp=ADCH - prv, prv=ADCH;
		itoa(temp,change,10); 
		LCDdata(change);
		
		LCDcommand(0x80+72);
		LCDdata("RPS=");
		
	}
	
}	

ISR(ADC_vect)
{
	
	itoa(ADCH,ADCvalue,10);
	
	OCR2 = ADCH;
	
	ADCSRA |= 1<<ADSC;

}




	
	
