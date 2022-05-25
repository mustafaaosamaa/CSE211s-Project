void lcd_4bits_data (unsigned char data) // print 1 char
{
	lcd_write4bits(data & 0xf0 , 1);
	lcd_write4bits(data << 4   , 1);
	delay_micro(40);
}
