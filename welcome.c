void Welcome()
{
		GPIO_PORTF_DATA_R |= 0x11;
		LCD_String("Enter a choice  to begin cooking");
		delay(1000);
		lcd_4bits_cmd(0x1);
		lcd_4bits_cmd(0x80);
}
