/*
 * I2C_Device_Detect.c
 *
 * Created: 20-01-2024 21:03:03
 * Author : naval
 */ 

/* This program is created for finding I2C device address connected to I2C bus */


#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <I2CNaval.h>
#include <UARTNaval.h>
#include <string.h>
#include <stdio.h>

#define I2C_7BIT_ADD
//#define I2C_8BIT_ADD



uint8_t count = 0;

int main(void)
{
    /* Replace with your application code */
	
	sei();
	char str1[2];
	uart_init(9600);
	i2c_init();
	uint8_t i2c_status,row=0;
	uint8_t count = 0x00;
    while (1) 
    {
		i2c_start();
		i2c_write(count);
		i2c_status=TWSR&0xF8; 
		if(i2c_status==0x18){
			
			if(count%15 == 0)
			{
				uart_tx('\r');
				sprintf(str1,"%d : ",row);
				uart_txstr(str1);
				memset(str1,'\0',sizeof(str1));
				#ifdef I2C_7BIT_ADD
				sprintf(str1,"%X",count>>1);
				#elif defined I2C_8BIT_ADD
				sprintf(str1,"%X",count);
				#endif
				uart_txstr(str1);
				memset(str1,'\0',sizeof(str1));
				uart_tx(' ');
			}
			
			else{
				uart_tx(' ');
				#ifdef I2C_7BIT_ADD
				sprintf(str1,"%X",count>>1);
				#elif defined I2C_8BIT_ADD
				sprintf(str1,"%X",count);
				#endif
				uart_txstr(str1);
				uart_tx(' ');
				memset(str1,'\0',sizeof(str1));
			}
			
			
		}
		else if(count%15 == 0)
		{
			uart_tx('\r');
			sprintf(str1,"%d : ",row);
			uart_txstr(str1);
			memset(str1,'\0',sizeof(str1));
			uart_txstr("--");
			row++;
		}
		
		else uart_txstr(" -- ");
		
		_delay_ms(10);
		count++;
		
		while(count == 0xff);
		
		
    }
}

