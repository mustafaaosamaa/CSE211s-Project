void lcd_init()
{
	SYSCTL_RCGCGPIO_R |= 0x2;
  while((SYSCTL_PRGPIO_R &= 0x2)==0) ;
//	SYSCTL_RCGCGPIO_R |= 0x1;
//  while((SYSCTL_PRGPIO_R &= 0x1)==0) ;
//	GPIO_PORTA_DIR_R |= 0xe0;
//	GPIO_PORTA_DEN_R |=0xe0;
	GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_DEN_R |=0xff;
//	GPIO_PORTA_PCTL_R &=~ 0xffffffff;
	GPIO_PORTB_PCTL_R &=~ 0xffffffff;
//	GPIO_PORTA_LOCK_R=0x4C4F434B;
	GPIO_PORTB_LOCK_R=0x4C4F434B;
	
	
	lcd_4bits_cmd(0x28);
	lcd_4bits_cmd(0x06);
	lcd_4bits_cmd(0x01);
	lcd_4bits_cmd(0x0f);
  
}
