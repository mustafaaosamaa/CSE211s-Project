int main()
{
	char value;
	Leds_Init();
	Buzzer_Init();
	sw12_Init();
	sw3_Init();
	lcd_init();
	keypad_init(); 
	lcd_4bits_cmd(0x1);
	lcd_4bits_cmd(0x80);
	while(1)
	{
LW:	Welcome();
		do
		{
			value = get_key();
		}while(value==0);
    delay(100);
		if(value >= 'A' && value <= 'D')
		{
			lcd_4bits_data(value);
			delay(1000);
			lcd_4bits_cmd(0x1); //clear
			lcd_4bits_cmd(0x80);
		}			
			
		if(value < 'A' || value > 'D')
		{
			LCD_String("Err");
			delay(2000);
			lcd_4bits_cmd(0x1); //clear
			lcd_4bits_cmd(0x80);
			goto LW;
		}
		if(value=='A') // POOOOOP COOOOOORN
		{
			LCD_String("Popcorn");
			delay(1000);
			while(1)
			{
				while(sw12_input()  == 0x10)
				{
					lcd_4bits_cmd(0x1); //clear
					lcd_4bits_cmd(0x80);
					counter(100);
					goto LW;
				}
			}
		}
		
		
		else if(value=='B')  // BEEEEEEEEEEEEEEEEEEEEEEEF
		{
LB:		LCD_String("Beef weight?");
			delay(1000);
			lcd_4bits_cmd(0x1); //clear
			lcd_4bits_cmd(0x80);
			do{
					value = get_key();
				}while(value==0);
			delay(100);	
			if(value < '1' || value > '9')
			{
				LCD_String("Err");
				delay(2000);
				lcd_4bits_cmd(0x1); //clear
				lcd_4bits_cmd(0x80);
				goto LB;
			}
			lcd_4bits_data(value);
			while(1)
			{
				if(sw12_input() == 0x01)
				{
					lcd_4bits_cmd(0x1); //clear
					lcd_4bits_cmd(0x80);
					goto LB;
				}
				if(sw12_input() == 0x10)
				{
					delay(2000);
					lcd_4bits_cmd(0x1); //clear
					lcd_4bits_cmd(0x80);
					counter(Beef(value));
					goto LW;
				}
			}
		}
		
		else if(value=='C') //  CHIIIIICCCCKKKKEEEEEEEEEEEEEN
		{
LC:		LCD_String("Chicken weight?");
			delay(1000);
			lcd_4bits_cmd(0x1); //clear
			lcd_4bits_cmd(0x80);
			do{
					value = get_key();
				}while(value==0);
			delay(100);
			if(value < '1' || value > '9')
			{
				LCD_String("Err");
				delay(2000);
				lcd_4bits_cmd(0x1); //clear
				lcd_4bits_cmd(0x80);
				goto LC;
			}
			lcd_4bits_data(value);
			while(1)
			{
				if(sw12_input() == 0x01)
				{
					lcd_4bits_cmd(0x1); //clear
					lcd_4bits_cmd(0x80);
					goto LC;
				}
				if(sw12_input() == 0x10)
				{
					delay(2000);
					lcd_4bits_cmd(0x1); //clear
					lcd_4bits_cmd(0x80);
					counter(Chicken(value));
					goto LW;
				}
			}
		}
		
		
		else if(value=='D') // OOOOTTTHHHEEEEEEEEERSSS
		{
			int i, button;
			char arrayOfTime[4];
LD:		LCD_String("Cooking Time?");
			arrayOfTime[0] = '0';
			arrayOfTime[1] = '0';
			arrayOfTime[2] = '0';
			arrayOfTime[3] = '0';
			delay(2000);
			lcd_4bits_cmd(0x1);
			lcd_4bits_cmd(0x80);
			LCD_String("00:00");
			
			while(1)
			{
				for(i=0; i<4; i++)
				{
					do{
							value = get_key();
							button = sw12_input();
						}while((value==0) & (sw12_input()==0x11));
				
					if(button == 0x11 && value >= '0' && value <='9')
					{
						lcd_4bits_cmd(0x80);	
						arrayOfTime[0] = arrayOfTime[1];
						arrayOfTime[1] = arrayOfTime[2];
						arrayOfTime[2] = arrayOfTime[3];
						arrayOfTime[3] = value;
						delay(350);
						lcd_4bits_data(arrayOfTime[0]);
						lcd_4bits_data(arrayOfTime[1]);
						lcd_4bits_data(':');
						lcd_4bits_data(arrayOfTime[2]);
						lcd_4bits_data(arrayOfTime[3]);
					}
					else if(button == 0x01)
					{
						GPIO_PORTF_DATA_R |= 0x11;
						lcd_4bits_cmd(0x1); //clear
						lcd_4bits_cmd(0x80);
						goto LD;
					}
					else if(button == 0x10)
					{
						GPIO_PORTF_DATA_R |= 0x11;
						delay(2000);
						lcd_4bits_cmd(0x1); //clear
						lcd_4bits_cmd(0x80);
						counter(atoi(arrayOfTime));
						goto LW;
					}
					else
					{
						lcd_4bits_cmd(0x1); //clear
						lcd_4bits_cmd(0x80);
						LCD_String("Err");
						delay(2000);
						lcd_4bits_cmd(0x1); //clear
						lcd_4bits_cmd(0x80);
						goto LD;
					}
				}
			}
		}
		break;
	}
}
