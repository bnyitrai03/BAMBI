/*
 * functions.c
 *
 *  Created on: Oct 2, 2023
 *      Author: nyiri
 */

#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"


void display_snake(snake_position* active_body_segments, int length){

	for(int i=0;i<length;i++){

		int active_disp = active_body_segments[i].minidisplay;

		switch(active_body_segments[i].segment){
		case 'a':
			lowerCharSegments[active_disp].a=1;
			break;
		case 'b' :
			lowerCharSegments[active_disp].b=1;
			break;
		case 'c' :
			lowerCharSegments[active_disp].c=1;
			break;
		case 'd' :
			lowerCharSegments[active_disp].d=1;
			break;
		case 'e' :
			lowerCharSegments[active_disp].e=1;
			break;
		case 'f' :
			lowerCharSegments[active_disp].f=1;
			break;
		case 'g' :
			lowerCharSegments[active_disp].g=1;
			lowerCharSegments[active_disp].m=1;
			break;
		case 'm' :
			lowerCharSegments[active_disp].m=1;
			lowerCharSegments[active_disp].g=1;
			break;
		}
		SegmentLCD_LowerSegments(lowerCharSegments);



	}

	}


void delay(int divider) {
   for(int d=0;d<1500000/divider;d++);
}

void start_init() {

	lowerCharSegments[0].g=1;
	lowerCharSegments[0].m=1;
	SegmentLCD_LowerSegments(lowerCharSegments);
}

void move(){

}

void snake_body_position(){


}

void food(){

}

void display_snake_length(){

}

void game_over(){

}


