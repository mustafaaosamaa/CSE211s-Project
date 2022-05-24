unsigned char get_key ()
{
	const unsigned char keypad [4][4]={ {'1','2','3','A'},
																			{'4','5','6','B'},
																			{'7','8','9','C'},
																			{'*','0','#','D'} };
unsigned int row , col ;
	GPIO_PORTE_DATA_R &=~ 0xf;
	col = GPIO_PORTC_DATA_R & 0xf0;
	if (col == 0xf0)
		return 0 ;
	while(1)
	{
		row=0 ;
	  GPIO_PORTE_DATA_R = 0xe;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=1 ;
	  GPIO_PORTE_DATA_R = 0xd;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=2 ;
	  GPIO_PORTE_DATA_R = 0xb;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=3 ;
	  GPIO_PORTE_DATA_R = 0x7;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		return 0;
	}
	if(col == 0xe0)
		return keypad[row][0];
	
	if(col == 0x0d0)
		return keypad[row][1];
	
	if(col == 0x0b0)
		return keypad[row][2];
	
	if(col == 0x070)
		return keypad[row][3];
	return 0 ;
}
