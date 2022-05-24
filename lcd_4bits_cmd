void lcd_4bits_cmd (unsigned char command)
{
	lcd_write4bits(command & 0xf0 , 0);
	lcd_write4bits(command << 4   , 0);
	if (command < 4)
	
		delay_milli(2);
		else
		delay_micro(40);
	}
