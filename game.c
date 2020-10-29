#include <LPC17xx.H> 

#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 

void showcolor (int color);
int delay= 5000;

void delay_ms (uint16_t ms)
{
 uint16_t delay;
 volatile uint32_t i;
 for (delay = ms; delay >0 ; delay--)
  {
  for (i=3500; i >0;i--){};
  }
}

void game(void)
{
	int joystick_prev = 0;
	int joystick_val = 0;
	int color;
	int index;
	int ansnum;
	int ansgot=0;
	int  ans[100];
	int input;
	int level=1;
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Black);
	GLCD_DisplayString (0, 0, 1, "Game: Memorize       ");
	GLCD_DisplayString (1, 0, 1, "Instuction           ");
	GLCD_DisplayString(2, 0, 1, "Memorize the  ");
	GLCD_DisplayString(3, 0, 1, "sequence of color  ");
	GLCD_DisplayString(4, 0, 1, "displayed by the ");
	GLCD_DisplayString(5, 0, 1, "screen ");
	
	delay =30000;
	delay_ms(delay);

	while (1){
		index = 0;
		delay =10000;
		
		while(index <level){
			color = rand()% 4; 
			showcolor(color);
			ans[index] = color;
			GLCD_Clear(White);

			index= index+1;
		}
		GLCD_Clear(White);
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString (0, 0, 1, "Game: Memorize       ");
		GLCD_DisplayString (1, 0, 1, "Left = Blue           ");
		GLCD_DisplayString(2, 0, 1, "Right = Black ");
		GLCD_DisplayString(3, 0, 1, "Down = Yellow");
		GLCD_DisplayString(4, 0, 1, "Up = Red");
		ansnum = 0;
		
		while (ansnum < index){
			ansgot = 0;
			joystick_val = get_button();
			if (joystick_val !=joystick_prev)
			{
				if (joystick_val == KBD_RIGHT)
				{
					input =3;
					ansgot = 1;
				}
				else if (joystick_val== KBD_UP){
					input =0;
					ansgot = 1;
				}
				else if (joystick_val == KBD_DOWN){
					input =2;
					ansgot = 1;
				}
				else if (joystick_val == KBD_LEFT){
					input =1;
					ansgot = 1;
				}
				
				joystick_prev = joystick_val;
			}
			if (ansgot == 1){
				if (ans[ansnum] ==input){ 
					ansnum ++;
				}
				else{
						GLCD_Clear(White);
						GLCD_DisplayString (1, 0, 1, "Game Over");					  
						GLCD_DisplayString(2, 0, 1, "You lose");
					  if (ans[ansnum] == 0)
							GLCD_DisplayString(3, 0, 1, "The color was Red");
						if (ans[ansnum] == 1)
							GLCD_DisplayString(3, 0, 1, "The color was Blue");
						if (ans[ansnum] == 2)
							GLCD_DisplayString(3, 0, 1, "The color was Yellow");
						if (ans[ansnum] == 3)
							GLCD_DisplayString(3, 0, 1, "The color was Black");
						delay_ms(delay);	
					return;
				}
			}
				
		}
		level = level+1;
		GLCD_Clear(White);
	  GLCD_DisplayString (5, 0, 1, "Next Level");
		delay_ms(delay);
	}
}


void showcolor (int color){
	if (color == 0){
		GLCD_Clear(Red);
		delay_ms(delay);
	}
	else if (color == 1){
		GLCD_Clear(Blue);
		delay_ms(delay);
	}
	else if (color == 2){
		GLCD_Clear(Yellow);
		delay_ms(delay);
	}
	else {
		GLCD_Clear(Black);
		delay_ms(delay);
	}
	
}


