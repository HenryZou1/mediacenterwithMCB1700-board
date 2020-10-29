                 
#include <LPC17xx.H> 
#include "photo_gallery.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

extern unsigned char lena[];
extern unsigned char angel[];
extern unsigned char girl[];

void image_view(void)
{
	int joystick_prev = 0;
	int joystick_val = 0;
	int seq = 0;
	int exit = 0;
	GLCD_Clear(White);
	GLCD_SetBackColor(Black);
  GLCD_SetTextColor(Yellow);
	GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
	GLCD_DisplayString (1, 0, 1, "    Photo Gallery   ");
	GLCD_DisplayString (2, 0, 1, "   Select to quit   ");
	while(!exit){
		joystick_val = get_button();
		if (joystick_val !=joystick_prev)
		{
			if (joystick_val == KBD_RIGHT)
			{
				seq +=1;
				if (seq == 3)
			  seq = 0;
			}
			else if (joystick_val == KBD_LEFT)
			{
				seq -=1;
				if (seq < 0)
					seq = 2;
			}
			else if (joystick_val == KBD_SELECT)
			{
				exit =1;
			}
			joystick_prev = joystick_val;
		}
	if (seq == 0){
		GLCD_Bitmap(80, 80, 150, 150, lena);
	} else if(seq == 1){
		GLCD_Bitmap(80, 80, 150, 150, angel);
	} else if(seq == 2){
		GLCD_Bitmap(80, 80, 150, 150, girl);
	}	
	}
}





