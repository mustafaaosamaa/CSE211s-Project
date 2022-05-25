void lcd_data(unsigned char data)
{
		GPIO_PORTA_DATA_R = 0x20 ;
    GPIO_PORTA_DATA_R |= 0x80; // e=1 (pulse) to secure data		
	  GPIO_PORTB_DATA_R = data;
	  
	  delay_micro(10);
	  GPIO_PORTA_DATA_R = 0x00;
		delay_micro(100);
	}
