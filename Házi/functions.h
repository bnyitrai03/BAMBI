/*
 * functions.h
 *
 *  Created on: Oct 2, 2023
 *      Author: nyiri
 */

#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_

SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS];
SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

typedef struct {
	int minidisplay; //selecting one of the 14segment displays
	char segment; //selecting one of the segment of the chosen minidisplay

}position;

typedef enum {
  RIGHT = 1,
  UP = 2,
  LEFT = 3,
  DOWN = 4
}direction;

void display_position(position* active_body_parts, int length);

void delay(int divider);

void start_init(position* starting_segments, position* starting_food);

int update_direction(direction current_direction, int R0state, int R1state);

void snake_body_position();

void food();

void display_snake_length();

void game_over();

#endif /* SRC_FUNCTIONS_H_ */
