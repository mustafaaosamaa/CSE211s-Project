void counter(int time)
{
	int i;
	char a,b,c,d;
	d = (time % 10)+'0';
	c = (( time % 100 ) / 10)+'0';
	b = (( time % 1000 ) / 100)+'0';
	a = (time / 1000)+'0';

	for(i=0; i < 1+(60*(time/100))+time%100; i++)
	{
		GPIO_PORTF_DATA_R |= 0x0E;
		if(SW12==1)
			{
				SW12=0;
				while(1)
					{
					
						if(SW12==2)
							{
								SW12=0;
								break;
							}
						if(SW12==1)
							{
								SW12=0;
								lcd_4bits_cmd(0x01);
								GPIO_PORTF_DATA_R&=~0x0E;
								main();
							}
							GPIO_PORTF_DATA_R ^= 0x0E;
						delay(300);
					}
			}
		lcd_4bits_data(a);
		lcd_4bits_data(b);
		lcd_4bits_data(':');
		lcd_4bits_data(c);
		lcd_4bits_data(d);
		delay(1000);
		//lcd_4bits_cmd(0x1); //clear
		lcd_4bits_cmd(0x80);
		d--;
        if(d=='/')
        {
            c--;
            d='9';
        }
        if(c=='/')
        {
            b--;
            c='5';
        }
        if(b=='/')
        {
            a--;
            b='9';
        }
	}
	for(i=0; i<3; i++)  // blink and buzz
	{
		Buzzer_OnOff();
		delay(1000);
		Buzzer_OnOff();
		blink_led();
		delay(1000);
		blink_led();
	}
	blink_led();
	
}
