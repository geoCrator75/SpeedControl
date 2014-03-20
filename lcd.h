	
#define LCD_PORT PORTB //LCD connected to LCD_PORT
#define LCD_RS 0x10
#define LCD_EN 0x20

char type=0x00;

void LCDreset(void);
void LCDinitialization(void);
void LCDdata(char *data);
void LCDcommand(char data);

void LCDinitialize(void)
{
	DDRB = 0xFF;
	LCD_PORT = 0xFF;
	_delay_ms(20);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(10);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(1);
	LCD_PORT = 0x03+LCD_EN;
	LCD_PORT = 0x03;
	_delay_ms(1);
	LCD_PORT = 0x02+LCD_EN;
	LCD_PORT = 0x02;
	_delay_ms(1);		  
	LCDcommand(0x28);		// 4-bit mode – 2 line – 5x7 font. 
	LCDcommand(0x0C);		// Display on cursor – no blink. 
	LCDcommand(0x06);		// Automatic Increment – No Display shift.
	LCDcommand(0x01);		// Clear Screen
	LCDcommand(0x80);		// Address DDRAM with 0 offset 80h. 

}



void LCDdata(char *data)
{
	type = LCD_RS;
	for(int i=0;data[i]!=0;i++)
	LCDcommand(data[i]);
	type =0x00;
}


void LCDcommand(char data)
{
	LCD_PORT = (((data >> 4) & 0x0F)|LCD_EN|type); 
	LCD_PORT = (((data >> 4) & 0x0F)|type); 
	LCD_PORT = ((data & 0x0F)|LCD_EN|type); 
	LCD_PORT = ((data & 0x0F)|type); 
	_delay_us(200);
}
		

		