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
#include "em_timer.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>



void display_position(position* active_segments, int length){

	for(int i=0;i<length;i++){
		//first we choose which minidisplay is active, then we display the given segment in the
		//active minidisplay
		int active_disp = active_segments[i].minidisplay; //checks the current position's minidisplay value

		//we check which segment is active, and then display it
		switch(active_segments[i].segment){
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

char convert_int_to_char(int randsegment)
{
	char randchar;

	switch (randsegment) //we get a random number from 0 to 7
	{
	case 0:
		randchar = 'a';
		break;
	case 1:
		randchar = 'f';
		break;
	case 2:
		randchar = 'g';
		break;
	case 3:
		randchar = 'e';
		break;
	case 4:
		randchar = 'd';
		break;
	case 5:
		randchar = 'a';
		break;
	case 6:
		randchar = 'b';
		break;
	case 7:
		randchar = 'c';
		break;
	default:
		randchar = '0';
	}

	return randchar;
}

void generate_food(position* food, position* snake)
{
	int randsegment;
	int rand_minidisplay = (TIMER_CounterGet(TIMER0) % 7); // choose a random minidisplay (from 1 to 7)
														   // we get the random seed from TIMER0

	if (rand_minidisplay == 6)
	{ // if the last minidisplay gets chosen, we can get one of the 7 segments selected
		randsegment = (TIMER_CounterGet(TIMER0) % 7);  // choose a random segment (from 1 to 7)
	}
	else
	{ // otherwise we can only choose from 5 different segments
		randsegment = (TIMER_CounterGet(TIMER0) % 5);     // choose a random segment (from 1 to 5)
	}

	// we need to convert the randsegment to char
	food->minidisplay = rand_minidisplay;
	food->segment = convert_int_to_char(randsegment);

	if(food->minidisplay == snake->minidisplay && food->segment == snake->segment)
	 generate_food(food,snake); // if the apple spawns inside the snake, we generate a new one
}

void start_init(position* starting_segment, position* starting_food) {

	starting_segment[0].minidisplay=0; //the head is the first value in the array
	starting_segment[0].segment='g';	//thats the starting position

	generate_food(starting_food, starting_segment);
}



/* calculate the new direction where the snake will go
					  UP
                      ↑
                      2
             LEFT ← 3   1 → RIGHT
                      4
                      ↓
                     DOWN
pressing R0 the snake rotates left, which increases current_direction's value
pressing R1 the snake rotates right, which decreases current_direction's value
 */
int update_direction(direction current_direction, int R0state, int R1state){
	int new_direction = current_direction;   // if there weren't any button presses, the snake keeps going in the same direction
	if (R0state){
		new_direction ++;
		if(new_direction == 5)
			new_direction = 1;
	}

	if (R1state){
	   new_direction --;
	    if(new_direction == 0)
		   new_direction = 4;
		}
	return new_direction;
}


void display_snake_length(){

}
