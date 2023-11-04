#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"
#include "em_rmu.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_gpio.h"
#include "em_core.h"

// we check if the snake ate itself
bool collision_with_snake(position* snake, int length){
	bool is_dead = false; // flag checks if the snake has collided with itself

	for(int i = 1; i < length; i++){ // we skip the collision comparison for the head with itself
		if(snake[0].minidisplay == snake[i].minidisplay && snake[0].segment == snake[i].segment)
			is_dead = true;
	}
	return is_dead;
}

// we check if the snake has collided with the food
int collision_with_food(position* snake, int snake_length, position* food){
	int length = snake_length;
	if(snake[0].minidisplay == food->minidisplay && snake[0].segment == food->segment){ // check if the snake ate the food
	    	snake[length].minidisplay = food->minidisplay; // food makes the snake longer by attaching a segment to it's tail
			snake[length].segment = food->segment;
	    	length ++; // snake becomes longer
	    }
	return length;
}

position move(position* snake, int snake_length, position snake_head){

	position new_snake[37]={};
	position tail; //we give this back so that we can turn it off in the display function
	tail = snake[snake_length-1];

	for(int i=1; i<=snake_length; i++){

			new_snake[i].minidisplay = snake[i-1].minidisplay;
			new_snake[i].segment = snake[i-1].segment;
		}


	new_snake[0].minidisplay = snake_head.minidisplay;
	new_snake[0].segment = snake_head.segment;

	for(int i=0; i<37;i++){
		snake[i].minidisplay = 0;
		snake[i].segment =0;
	}

	for(int i=0; i<snake_length; i++){
		snake[i].minidisplay = new_snake[i].minidisplay;
		snake[i].segment = new_snake[i].segment;
	}


	return tail;

}

int main(void)
{
  CHIP_Init();

   //*********************************************
   // CMU configuration *
   //*********************************************
   // enable clock signals
   //CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable);
   CMU_ClockEnable(cmuClock_GPIO, true);
   CMU_ClockEnable(cmuClock_TIMER0, true);

   // *******************************
   // * TIMER config *
   // *******************************
   TIMER_Init_TypeDef TIMER0_init = TIMER_INIT_DEFAULT;
   TIMER0_init.prescale = timerPrescale1; // no prescale
   TIMER_Init(TIMER0, &TIMER0_init);
   TIMER_Enable(TIMER0, true); //timer starts counting


    // *******************************
    // * Initialize R0 and R1 *
    // *******************************
    //  NVIC_EnableIRQ();

   //Enable LCD module
   SegmentLCD_Init(false);

   int snake_length = 1;
   position active_body_segments[37]={}; //6*5+7 on the first 6 minidisplays only 5 segments can be active
                                        //on the last one however there can be 7
   position food[1]={}; //stores the position of the food
   direction snake_direction = RIGHT; // 1 = right, 2 = up, 3 = left, 4 = down
  	  	  	  	  	  	             // at the start the snake goes right
   bool dead = false; // checks if the snake is alive

   direction previous_direction = RIGHT; //for testing purposes we inicialize it with something

   position new_head = {};

   position tail = {};


   start_init(active_body_segments, food); //we initialize the snake and the food's starting state


  while (1) {
	  while(!dead){


	  display_position(active_body_segments, snake_length, tail); //display the position of the snake and the food

	  new_head = calculate_new_head(snake_direction, previous_direction, active_body_segments); //update the active_body_segments
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  //according to the previous and current directions

	  tail = move(active_body_segments, snake_length, new_head);

	  snake_length = collision_with_food(active_body_segments, snake_length, food);

	  previous_direction = snake_direction; //after updating, the previously current direction becomes the
	  	  	  	  	  	  	  	  	  	  	//previous direction


	  }

  }
}
