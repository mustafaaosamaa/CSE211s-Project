void lcd_write4bits (unsigned char data , unsigned char control)
{
	data     &=0xf0;
	control  &=0x0f;
	GPIO_PORTB_DATA_R = data|control;
	GPIO_PORTB_DATA_R = data|control| 4;
	delay_micro(0);
	GPIO_PORTB_DATA_R  = data;
}
