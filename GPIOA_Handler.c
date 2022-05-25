void GPIOA_Handler(void)
{
GPIO_PORTF_DATA_R |= 0x11;
GPIO_PORTA_ICR_R = 0x80;
while(1){
	if((GPIO_PORTA_DATA_R & 0x80) == 0x80){
	
	}
	else if ((GPIO_PORTF_DATA_R & 0x10) == 0x00)
	{
		main();
	}
	else if((GPIO_PORTF_DATA_R & 0x01) == 0x00)
	{
		break;
	}
	GPIO_PORTF_DATA_R ^= 0x0E;
	delay(300);
}
}
