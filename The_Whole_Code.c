#include "tm4c123gh6pm.h"
#include "stdlib.h"
#include "stdio.h"

int SW12 = 0;

void SysTick_wait(unsigned long delay)
{
NVIC_ST_CTRL_R = 0;
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R =0;
NVIC_ST_CTRL_R = 0x00000005;
while ((NVIC_ST_CTRL_R &0x00010000)==0){}
}
void delay(unsigned long time)
{
int i;
for(i =0 ; i<time ;i++){
SysTick_wait(16000); // delay for 1msec
}
}
void delay_micro(int n)
{
	int i , j;
	for(i=0;i<n;i++)
	
	{
		for(j=0;j<3;j++)
		{}
	}
}
void delay_milli(int n)
{
	int i , j;
	for(i=0;i<n;i++)
	
	{
		for(j=0;j<3180;j++)
		{}
	}
}
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
unsigned char get_key ()
{
	const unsigned char keypad [4][4]={ {'1','2','3','A'},
																			{'4','5','6','B'},
																			{'7','8','9','C'},
																			{'*','0','#','D'} };
unsigned int row , col ;
	GPIO_PORTE_DATA_R &=~ 0xf;
	col = GPIO_PORTC_DATA_R & 0xf0;
	if (col == 0xf0)
		return 0 ;
	while(1)
	{
		row=0 ;
	  GPIO_PORTE_DATA_R = 0xe;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=1 ;
	  GPIO_PORTE_DATA_R = 0xd;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=2 ;
	  GPIO_PORTE_DATA_R = 0xb;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		row=3 ;
	  GPIO_PORTE_DATA_R = 0x7;
		delay_micro(10);
		col = GPIO_PORTC_DATA_R &0xf0;
		if(col != 0xf0)
			break;
		
		return 0;
	}
	if(col == 0xe0)
		return keypad[row][0];
	
	if(col == 0x0d0)
		return keypad[row][1];
	
	if(col == 0x0b0)
		return keypad[row][2];
	
	if(col == 0x070)
		return keypad[row][3];
	return 0 ;
}

void lcd_data(unsigned char data)
{
		GPIO_PORTA_DATA_R = 0x20 ;
    GPIO_PORTA_DATA_R |= 0x80; // e=1 (pulse) to secure data		
	  GPIO_PORTB_DATA_R = data;
	  
	  delay_micro(10);
	  GPIO_PORTA_DATA_R = 0x00;
		delay_micro(100);
	}

void lcd_write4bits (unsigned char data , unsigned char control)
{
	data     &=0xf0;
	control  &=0x0f;
	GPIO_PORTB_DATA_R = data|control;
	GPIO_PORTB_DATA_R = data|control| 4;
	delay_micro(0);
	GPIO_PORTB_DATA_R  = data;
}
void lcd_4bits_cmd (unsigned char command)
{
	lcd_write4bits(command & 0xf0 , 0);
	lcd_write4bits(command << 4   , 0);
	if (command < 4)
	
		delay_milli(2);
		else
		delay_micro(40);
	}
void lcd_4bits_data (unsigned char data) // print 1 char
{
	lcd_write4bits(data & 0xf0 , 1);
	lcd_write4bits(data << 4   , 1);
	delay_micro(40);
}
	


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

void sw12_Init()
{
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R & 0x20) == 0);
GPIO_PORTF_LOCK_R |= GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |= 0x11;
GPIO_PORTF_AFSEL_R &= ~0x11;
GPIO_PORTF_PCTL_R &= ~0x000F000F;
GPIO_PORTF_AMSEL_R &= ~0x11;
GPIO_PORTF_DEN_R |= 0x11;
GPIO_PORTF_DIR_R &= ~0x11;
GPIO_PORTF_PUR_R |= 0x11;
//GPIO_PORTF_DATA_R |= 0x11;
GPIO_PORTF_IS_R &= ~0x11;
GPIO_PORTF_IBE_R &= ~0x11;
GPIO_PORTF_IEV_R &= ~0x11;
GPIO_PORTF_ICR_R &= ~0x11;
GPIO_PORTF_IM_R |= 0x11;
NVIC_EN0_R = 0x40000000;
NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000 ;
}

void sw3_Init()
{
//using port A7
SYSCTL_RCGCGPIO_R |= 0x01;
while((SYSCTL_PRGPIO_R &0x01)==0) ;
GPIO_PORTA_DIR_R &= ~0x80;
GPIO_PORTA_DEN_R |=0x80;
GPIO_PORTA_CR_R |=0x80;
GPIO_PORTA_AMSEL_R &= ~0x80;
GPIO_PORTA_PCTL_R &= ~0xF0000000;
GPIO_PORTA_AFSEL_R &=~0x80;
GPIO_PORTA_PDR_R |=0x80;
GPIO_PORTA_IS_R &= ~0x80;
GPIO_PORTA_IBE_R &= ~0x80;
GPIO_PORTA_IEV_R &= ~0x80;
GPIO_PORTA_ICR_R &= ~0x80;
GPIO_PORTA_IM_R |= 0x80;
NVIC_EN0_R = 0x00000001;
NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x00000040 ;
}


void Buzzer_Init()
{ 
//using port D0
SYSCTL_RCGCGPIO_R |= 0x08;
while ((SYSCTL_PRGPIO_R & 0x08) == 0){}
GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTD_CR_R |= 0x80;
GPIO_PORTD_AFSEL_R &= ~0x80;
GPIO_PORTD_PCTL_R &= ~0xF0000000;
GPIO_PORTD_AMSEL_R &= ~0x80;
GPIO_PORTD_DEN_R |= 0x80;
GPIO_PORTD_DIR_R |= 0x80;
GPIO_PORTD_DATA_R &= ~0x80;
}

void Leds_Init()
{
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R & 0x20) == 0);
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTF_DIR_R |= 0x0E;
GPIO_PORTF_DATA_R &= ~0x0E;
}
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

unsigned char sw12_input()
{
	return (GPIO_PORTF_DATA_R & 0x11);
}

void blink_led()
{
	GPIO_PORTF_DATA_R =GPIO_PORTF_DATA_R ^ 0x0E;// change the light on or off
}

void Buzzer_OnOff()
{
	GPIO_PORTD_DATA_R =GPIO_PORTD_DATA_R ^ 0x80;
}

void Welcome()
{
		GPIO_PORTF_DATA_R |= 0x11;
		LCD_String("Enter a choice  to begin cooking");
		delay(1000);
		lcd_4bits_cmd(0x1);
		lcd_4bits_cmd(0x80);
}

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

int Beef(char weight)
{
	int a,x,y,z;
	x = weight - '0';
	x *= 30;
	y = x / 60;
	z = x % 60;
	a = y * 100 + z;
	return a;
}
int Chicken(char weight)
{
	int a,x,y,z;
	x = weight - '0';
	x *= 12;
	y = x / 60;
	z = x % 60;
	a = y * 100 + z;
	return a;
}

void GPIOF_Handler(void)
{
if(GPIO_PORTF_MIS_R&&0x10 == 0x10){
GPIO_PORTF_ICR_R = 0x10;
SW12=1;
}
if(GPIO_PORTF_MIS_R&&0x10 == 0x10){
GPIO_PORTF_ICR_R = 0x01;
SW12=2;
}
}

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
