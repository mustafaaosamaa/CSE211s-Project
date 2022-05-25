void keypad_init ()
{
	SYSCTL_RCGCGPIO_R |= 0x4;
  while((SYSCTL_PRGPIO_R &= 0x4)==0) ; //port c
	
	SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R &= 0x10)==0) ; //porte
	
	GPIO_PORTE_DIR_R |=0xf;
	GPIO_PORTE_DEN_R |=0xf;
	GPIO_PORTE_ODR_R |=0XF;
	
	GPIO_PORTC_DIR_R &=~ 0xf0;
	GPIO_PORTC_DEN_R |= 0xf0;
	GPIO_PORTC_PUR_R |= 0xf0;
	
}
