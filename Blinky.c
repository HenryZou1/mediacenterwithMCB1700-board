/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "usbdmain.h"
#include "photo_gallery.h"
#include "game.h"


extern int audio_main (void);


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) 
{  	/* Main Program                       */
	int selector = 1; //selector to see which program is user the choosing
										//'1' for photo viewer, '2' for audio file, '3' for game
	int joystick_val = 0;   //track the current joystick value
	int joystick_prev = 0;  //track the previous value for the joystick
	
	KBD_Init();

  LED_Init ();
  GLCD_Init();

  GLCD_Clear  (White);
  SysTick_Config(SystemCoreClock/100); 
	GLCD_SetBackColor(Red);
  GLCD_SetTextColor(White);
	GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
	GLCD_DisplayString (1, 0, 1, "                    ");
	GLCD_DisplayString (2, 0, 1, "Choose with up/down ");
	GLCD_DisplayString (3, 0, 1, "   right to select  ");

  for (;;)	
	{
			joystick_val = get_button();
			
			if (joystick_val !=joystick_prev)	
			  {
					if (joystick_val == KBD_DOWN)
						{
							selector +=1;
							if (selector >=4)
									selector = 1;
						}
					else if (joystick_val == KBD_UP)
						{
							selector -=1;
							if (selector <=0)
									selector = 3;
						}
					else if(joystick_val == KBD_RIGHT)
							{
								if (selector == 1)
								{
									image_view();
									GLCD_Clear(White);
									GLCD_SetTextColor(Red);
									GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
									GLCD_DisplayString (1, 0, 1, "   Photo Gallery    ");		
									selector = 1;
								}
								else if (selector == 2)
								{
									audio_main();
									GLCD_Clear(White);
									GLCD_SetTextColor(Red);
									GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
									GLCD_DisplayString (1, 0, 1, "        MP3         ");						
									selector =1;
								}
								else if (selector == 3)
								{
									game();
									GLCD_Clear(White);
									GLCD_SetTextColor(Red);
									GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
									GLCD_DisplayString (1, 0, 1, "       Game         ");	
									selector = 1;
								}
							}
					joystick_prev = joystick_val;
			}
			
			if (selector == 1){
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
						GLCD_DisplayString (5, 0, 1, "Photo Gallery       ");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (6, 0, 1, "MP3                 ");
						GLCD_DisplayString (7, 0, 1, "Game                ");
						
				} else if(selector == 2){
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (5, 0, 1, "Photo Gallery       ");
					  GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
						GLCD_DisplayString (6, 0, 1, "MP3                 ");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (7, 0, 1, "Game                ");
				} else if(selector == 3){
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (5, 0, 1, "Photo Gallery       ");
						GLCD_DisplayString (6, 0, 1, "MP3                 ");
					  GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
						GLCD_DisplayString (7, 0, 1, "Game                ");
				} else{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Red);
						GLCD_DisplayString (5, 0, 1, "Photo Gallery       ");
						GLCD_DisplayString (6, 0, 1, "MP3                 ");
						GLCD_DisplayString (7, 0, 1, "Game                ");
				}
	GLCD_SetBackColor(Red);
  GLCD_SetTextColor(White);
	GLCD_DisplayString (0, 0, 1, "COE718 Media Center ");
	GLCD_DisplayString (1, 0, 1, "        Menu        ");
	GLCD_DisplayString (2, 0, 1, "Choose with up/down ");
	GLCD_DisplayString (3, 0, 1, "   right to select  ");
	}
}


