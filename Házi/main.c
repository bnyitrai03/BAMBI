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
   position previous_food={};
   direction snake_direction = RIGHT; // 1 = right, 2 = up, 3 = left, 4 = down
  	  	  	  	  	  	             // at the start the snake goes right
   bool dead = false; // checks if the snake is alive

   direction previous_direction = RIGHT; //for testing purposes we inicialize it with something

   position new_head = {};

   position tail = {};


   start_init(active_body_segments, food); //we initialize the snake and the food's starting state


  while (1) {
	  while(!dead){


	  display_position(active_body_segments, snake_length); //display the position of the snake
	  display_position(&food, 1);                  //display the food
	  delay(5);

	  new_head = calculate_new_head(snake_direction, previous_direction, active_body_segments); //update the active_body_segments
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  //according to the previous and current directions

	  tail = move(active_body_segments, snake_length, new_head);

	  snake_length = collision_with_food(active_body_segments, snake_length, food, &previous_food);

	  previous_direction = snake_direction; //after updating, the previously current direction becomes the
	  	  	  	  	  	  	  	  	  	  	//previous direction


	  }

  }
}
