#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"
#include "em_rmu.h"
#include "em_cmu.h"


/*void move(int button_state, position* active_body_segments) {

	switch(button_state)
	{
	case 0: //Right
	for(int i=0; i<7;i++){
		lowerCharSegments[i].g=1;
		lowerCharSegments[i].m=1;

		active_body_segments[0].minidisplay=i;
		active_body_segments[0].segment='g';

		display_position(active_body_segments, 1);
		delay(2);
		lowerCharSegments[i].g=0;
		lowerCharSegments[i].m=0;

		active_body_segments=0;


		delay(5);
		}
	case 1: //Left
	for(int i=6; i>=0; i--){
		lowerCharSegments[i].g=1;
		lowerCharSegments[i].m=1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		delay(2);
		lowerCharSegments[i].g=0;
		lowerCharSegments[i].m=0;
		SegmentLCD_LowerSegments(lowerCharSegments);
		delay(5);
		}
	}
}*/


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

// takes the calculated direction and moves the snake there
// we need not just the head but the previous body part as well
void move(direction snake_direction, position* snake){
	switch(snake_direction){
	case 'RIGHT':

		break;
	case '2': //snake goes up
		//  E -> F
		//  F -> E
		//  we are fucked
		//
		break;
	}
}

// after this we check for collisions (snake eating itself or the apple)
// after that we do the displaying

int main(void)
{
  CHIP_Init();
  //Enable LCD module
  SegmentLCD_Init(false);

  int snake_length = 1;
  position active_body_segments[37]={}; //6*5+7 on the first 6 minidisplays only 5 segments can be active
                                        //on the last one however there can be 7
  position food[1]={}; //stores the position of the food
  direction snake_direction = RIGHT; // 1 = right, 2 = up, 3 = left, 4 = down
  	  	  	  	  	  	             // at the start the snake goes right
  bool dead = false; // checks if the snake is alive

  start_init(active_body_segments, food); //we initialize the snake and the food's starting state

  while (1) {
	  while(!dead){

	  //move(0, active_body_segments);
	  //display_position(active_body_segments, snake_length);

	  }

  }
}
