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
#include "em_timer.h"
#include "em_core.h"



void display_position(position* active_segments, int length, position tail){

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
		switch(tail.segment){
							case 'a':
								lowerCharSegments[tail.minidisplay].a=0;
								break;
							case 'b' :
								lowerCharSegments[tail.minidisplay].b=0;
								break;
							case 'c' :
								lowerCharSegments[tail.minidisplay].c=0;
								break;
							case 'd' :
								lowerCharSegments[tail.minidisplay].d=0;
								break;
							case 'e' :
								lowerCharSegments[tail.minidisplay].e=0;
								break;
							case 'f' :
								lowerCharSegments[tail.minidisplay].f=0;
								break;
							case 'g' :
								lowerCharSegments[tail.minidisplay].g=0;
								lowerCharSegments[tail.minidisplay].m=0;
								break;
							case 'm' :
								lowerCharSegments[tail.minidisplay].m=0;
								lowerCharSegments[tail.minidisplay].g=0;
								break;

				}



		SegmentLCD_LowerSegments(lowerCharSegments);

	}

}


void delay(int divider) {
   for(int d=0;d<1500000/divider;d++);
}

position G_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch (previous_direction) { //we check where we were going before changing directions
		                case RIGHT:
		                    switch (snake_direction) {//knowing where we were previously, we know where we need to
		                    						// go next given a specific direction
		                        case RIGHT:
		                            new_head.minidisplay = snake[0].minidisplay + 1; //e.g.: if we were going right previously, then we
		                            						//just need to go to the next minidisplay
		                            break;
		                        case UP:
		                            if (snake[0].minidisplay == 6) {//e.g.: if we were going right previously, then
		                            							//if we go up, and we were on G/M then now we have to
		                            							//go to 'f' segment of the next minidisplay
		                            							//here the exception is if we were on the last minidisplay
		                            							//then we have to use the 'b' and 'c' segments too, which we
		                            							//normally wouldnt, so in this case we have to go to the 'b' segment
		                            	new_head.segment ='b';
		                            }
		                            new_head.minidisplay = snake[0].minidisplay + 1;
		                            new_head.segment = 'f';
		                            break;
		                        case DOWN:
		                            if (snake[0].minidisplay == 6) { //e.g.: if we were going right before, and now we are going down
		                            							//then we were on G/M then we have to go to the next minidisplays
		                            							//'e' segment (exception is pretty much the same as the previous one)
		                                new_head.segment = 'c';
		                            }
		                            new_head.minidisplay = snake[0].minidisplay + 1;
		                            new_head.segment = 'e';
		                            break;
		                    }
		                    break;

		                case LEFT:
		                    switch (snake_direction) {
		                        case LEFT:
		                        	new_head.minidisplay = snake[0].minidisplay - 1; //if we were going left previously and we are still going left
		                            						//then we just need to decrease the value of the minidisplay
		                            break;
		                        case UP:
		                            new_head.segment = 'f'; //if we were going left and now we are going up, then we will land on
		                            						//'f' if we were on G/M previously
		                            break;
		                        case DOWN:
		                            new_head.segment = 'e'; //if we were going left and now we are going down, then we will land on
            												//'e' if we were on G/M previously
		                            break;
		                    }
		                    break;							//the rest of these type of direction functions all work in this manner
		            }
	return new_head;
}

position M_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch(previous_direction){

		case RIGHT:
			switch(snake_direction){

				case RIGHT:
					new_head.minidisplay = snake[0].minidisplay + 1;
                    break;
				case UP:
                    if(snake[0].minidisplay==6){
                        new_head.segment='b';
                        }
                    new_head.minidisplay = snake[0].minidisplay + 1;
					new_head.segment='f';
                    break;
				case DOWN:
                    if(snake[0].minidisplay==6){
                        new_head.segment='c';
                        }
                    new_head.minidisplay = snake[0].minidisplay + 1;
					new_head.segment='e';
                    break;
            }
		break;

		case LEFT:
			switch(snake_direction){

				case LEFT:
					new_head.minidisplay = snake[0].minidisplay - 1;
                    break;
				case UP:
					new_head.segment='f';
                    break;
				case DOWN:
					new_head.segment='e';
				    break;


				}
        break;
			}
	return new_head;
}

position A_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch(previous_direction){

			case RIGHT:
				switch(snake_direction){

					case RIGHT:
						new_head.minidisplay = snake[0].minidisplay + 1;
                        break;
					case UP:
                        if(snake[0].minidisplay==6){
                            new_head.segment='c';
                            }
                        new_head.minidisplay = snake[0].minidisplay + 1;
						new_head.segment='e';
                        break;
					case DOWN:
                        if(snake[0].minidisplay==6){
                            new_head.segment='b';
                            }
                        new_head.minidisplay = snake[0].minidisplay + 1;
						new_head.segment='f';
					    break;
                }
            break;

			case LEFT:
				switch(snake_direction){

					case LEFT:
						new_head.minidisplay = snake[0].minidisplay - 1;
                        break;
					case UP:
						new_head.segment='e';
                        break;
					case DOWN:
						new_head.segment='f';
					    break;


					}
            break;

				}
	return new_head;
}
//case d and a works the same way , but because the way switch case works, i have to repeat it
position D_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch(previous_direction){

			case RIGHT:
				switch(snake_direction){

					case RIGHT:
						new_head.minidisplay = snake[0].minidisplay + 1;
                        break;
					case UP:
                        if(snake[0].minidisplay==6){
                            new_head.segment='c';
                            }
                        new_head.minidisplay = snake[0].minidisplay + 1;
						new_head.segment='e';
                        break;
					case DOWN:
                        if(snake[0].minidisplay==6){
                            new_head.segment='b';
                            }
                        new_head.minidisplay = snake[0].minidisplay + 1;
						new_head.segment='f';
					    break;
                }
            break;

			case LEFT:
				switch(snake_direction){

					case LEFT:
						new_head.minidisplay = snake[0].minidisplay - 1;
                        break;
					case UP:
						new_head.segment='e';
                        break;
					case DOWN:
						new_head.segment='f';
					    break;


					}
            break;

			}
	return new_head;
}

position F_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch(previous_direction){

			case UP:
				switch(snake_direction){

					case RIGHT:
						new_head.segment='a';
                        break;
					case UP:
						new_head.segment='e';
                        break;
                    case LEFT:
                    	new_head.minidisplay = snake[0].minidisplay - 1;
                        new_head.segment='a';
                }
            break;

			case DOWN:
				switch(snake_direction){

					case RIGHT:
						new_head.minidisplay = snake[0].minidisplay - 1;
                        new_head.segment='g';
                        break;
					case LEFT:
						new_head.segment='g';
                        break;
					case DOWN:
						new_head.segment='e';
					    break;


					}
            break;

		}
return new_head;

}

position E_snake_direction(direction snake_direction, direction previous_direction , position* snake){

	position new_head = snake[0];
	switch(previous_direction){

			case UP:
				switch(snake_direction){

					case RIGHT:
						new_head.segment='g';
                        break;
					case UP:
						new_head.segment='f';
                        break;
                    case LEFT:
                    	new_head.minidisplay = snake[0].minidisplay - 1;
                        new_head.segment='g';
                }
            break;

			case DOWN:
				switch(snake_direction){

					case RIGHT:
						new_head.minidisplay = snake[0].minidisplay - 1;
                        new_head.segment='d';
                        break;
					case LEFT:
						new_head.segment='d';
                        break;
					case DOWN:
						new_head.segment='f';
					    break;


					}
            break;


		}
	return new_head;
}

position calculate_new_head(direction snake_direction, direction previous_direction , position* snake){
	//we only need to check the head of the snake,
	//which is the first item in the active_body_segments array

	//first we look at where we are currently, and then make a decision about where to move next
	//in the light of the current direction that we are moving in

	direction snake_direction_ = snake_direction;
	direction previous_direction_ = previous_direction;
	position* snake_=snake;
	position new_head = snake[0];


	 switch (snake[0].segment) { //first we look at where we are, depending on which segment we are on, we
	 	 	 	 	 	 	 	 //have to make different decisions regarding where to move next
	 	 	 	 	 	 	 	 //we also have to use different logic depending on which direction were we
	 	 	 	 	 	 	 	 //moving previously, which is handled in a function in every case
	 	 	 	 	 	 	 	 //There is also some comments about the inner workings of these functions at the start of
	 	 	 	 	 	 	 	 //the G_snake_direction function, they all work in the same manner
	        case 'g':

	        	new_head = G_snake_direction(snake_direction_,previous_direction_ ,snake_);
	            break;

	        case 'm' :

	        	new_head = M_snake_direction(snake_direction_,previous_direction_ ,snake_);
	        	break;

	        case 'a':

	        	new_head = A_snake_direction(snake_direction_,previous_direction_ ,snake_);
	        	break;

	        case 'd':

	        	new_head = D_snake_direction(snake_direction_,previous_direction_ ,snake_);
	        	break;

	        case 'f':

	        	new_head = F_snake_direction(snake_direction_,previous_direction_ ,snake_);
	        	break;
	        case 'e':


	        	new_head = E_snake_direction(snake_direction_,previous_direction_ ,snake_);
	        	break;

	}
	//if we go out of one side of the minidisplays, we have to come back in on the other side
    if (new_head.minidisplay==7)
    {
        new_head.minidisplay=0;
    }
    else if (new_head.minidisplay==-1)
    {
        new_head.minidisplay=6;
    }

   return new_head;
}

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
                      |
                      2
             LEFT <-3   1 -> RIGHT
                      4
                      |
                     DOWN
pressing R0 the snake rotates left, which increases current_direction's value
pressing R1 the snake rotates right, which decreases current_direction's value
 */
int update_direction(direction previous_direction, int R0state, int R1state){
	int new_direction = previous_direction;   // if there weren't any button presses, the snake keeps going in the same direction
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
	return new_direction; //give the previous direction back with a pointer too
}


void display_snake_length(){

}

void game_over(){

}
