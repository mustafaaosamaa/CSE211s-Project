void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		if (i==16)
		{
			lcd_4bits_cmd(0xc0);
		}
		lcd_4bits_data(str[i]);  /* Call LCD data write */
		
		}
				
}
