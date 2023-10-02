#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"


/*void move() {
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
}  */
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  SegmentLCD_Init(false);

  int snake_length = 3;
  snake_position active_body_segments[37]={}; //6*5+7
  active_body_segments[0].minidisplay=1; //the head is the first value in the array
  active_body_segments[0].segment='g';	//thats the starting position

  active_body_segments[1].minidisplay=1;
  active_body_segments[1].segment='f';

  active_body_segments[2].minidisplay=1;
  active_body_segments[2].segment='a';






  //start_init();

  while (1) {
	  //move();

	  display_snake(active_body_segments,snake_length);
  }
}
