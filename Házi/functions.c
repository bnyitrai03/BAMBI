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
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/*
 snake_postion-t át kéne nevezni position-re
 display_snake-t meg simán snake-re
 !!!
 */



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


//void move(){

//}

void snake_body_position(){


}

char convert_int_to_char(int randsegment)
{
	char randchar;

	switch (randsegment)
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

void generate_food(position* foodptr)
{
	// srand nem ad random számokat :(
	//srand(time(NULL));						 // initialize the random number generator function

	// memória szemét se lesz random
	int randsegment;

	int rand_minidisplay = (rand() % 7); // choose a random minidisplay (from 1 to 7)

	if (rand_minidisplay == 6)
	{ // if the last minidisplay gets chosen, we can get one of the 7 segments selected
		randsegment = (rand() % 7);  // choose a random segment (from 1 to 7)
	}
	else
	{ // otherwise we can only choose from 5 different segments
		randsegment = (rand() % 5);     // choose a random segment (from 1 to 5)
	}

	// we need to convert the randsegment to char
	foodptr->minidisplay = rand_minidisplay % 7;
	foodptr->segment = convert_int_to_char(randsegment % 5);
}

void start_init(position* starting_segments, position* starting_food) {

	starting_segments[0].minidisplay=0; //the head is the first value in the array
	starting_segments[0].segment='g';	//thats the starting position

	generate_food(starting_food);

	if(starting_food->minidisplay == 1 && starting_food->segment == 'g' ) //if the starting_food is in the same starting position as the snake, put the food elsewhere
		starting_food->minidisplay = (rand() % 5)+1; // some random place (random number between 2 and 6)
	display_position(starting_food, 1);          //display food at the start in a random position
}


void display_snake_length(){

}

void game_over(){

}
