#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"
#include "em_rmu.h"
#include "em_cmu.h"


void move() {
	for(int i=0; i<7;i++){
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
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  //Enable LCD module
  SegmentLCD_Init(false);

  int snake_length = 1;
  position active_body_segments[37]={}; //6*5+7 on the first 6 minidisplays only 5 segments can be active
  //on the last one however there can be 7
  position active_food[1]={}; //stores the position of the food



  start_init(active_body_segments, active_food); //we initialize the snake and the food's starting state

  while (1) {
	  //move();
	  display_position(active_body_segments, snake_length);

  }
}
