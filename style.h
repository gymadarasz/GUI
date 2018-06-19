/*
 * style.h
 *
 *  Created on: Jun 15, 2018
 *      Author: Gyula
 */

#ifndef STYLE_H_
#define STYLE_H_

#include <graphics.h>

#define KEY_SPACE 32 // hacky space

#define GUI_NOCOLOR							-1
#define GUI_COLOR							LIGHTGRAY
#define GUI_COLOR_PUSHED					DARKGRAY
#define GUI_BORDER_SIZE						1
#define GUI_BORDER_COLOR					DARKGRAY
#define GUI_BORDER_COLOR_SELECTED			WHITE
#define GUI_DEEP_COLOR						DARKGRAY
#define GUI_DEEP_COLOR_PUSHED				DARKGRAY
#define GUI_MARGIN_SIZE						1
#define GUI_PADDING_SIZE					10

#define GUI_DEFAULT_TEXT					(char*)"text"
#define GUI_DEFAULT_TEXT_ON					(char*)"On"
#define GUI_DEFAULT_TEXT_OFF				(char*)"Off"
#define GUI_DEFAULT_VALUE					0
#define GUI_DEFAULT_MIN_VALUE				0
#define GUI_DEFAULT_MAX_VALUE				100
#define GUI_MINUS_TEXT						(char*)"<"
#define GUI_PLUS_TEXT						(char*)">"
#define GUI_DEFAULT_TEXT_COLOR 				BLACK
#define GUI_DEFAULT_ADJUST					true
#define GUI_DEFAULT_WIDTH					0
#define GUI_DEFAULT_HEIGHT					0
#define GUI_DEFAULT_TOP						0
#define GUI_DEFAULT_LEFT					0

#define GUI_WINDOW_COLOR					GUI_COLOR
#define GUI_WINDOW_COLOR_PUSHED				GUI_COLOR_PUSHED

#define GUI_CANVAS_DEFAULT_ADJUST			GUI_DEFAULT_ADJUST
#define GUI_CANVAS_DEFAULT_WIDTH			GUI_DEFAULT_WIDTH
#define GUI_CANVAS_DEFAULT_HEIGHT			GUI_DEFAULT_HEIGHT
#define GUI_CANVAS_DEFAULT_TOP				GUI_DEFAULT_TOP
#define GUI_CANVAS_DEFAULT_LEFT				GUI_DEFAULT_LEFT
#define GUI_CANVAS_COLOR 					GUI_COLOR
#define GUI_CANVAS_COLOR_PUSHED				GUI_COLOR_PUSHED
#define GUI_CANVAS_BORDER_SIZE				GUI_BORDER_SIZE
#define GUI_CANVAS_BORDER_COLOR				GUI_BORDER_COLOR
#define GUI_CANVAS_BORDER_COLOR_SELECTED	GUI_BORDER_COLOR_SELECTED
#define GUI_CANVAS_MARGIN_SIZE				GUI_MARGIN_SIZE

#define GUI_LABEL_DEFAULT_TEXT 				GUI_DEFAULT_TEXT
#define GUI_LABEL_TEXT_COLOR				GUI_DEFAULT_TEXT_COLOR
#define GUI_LABEL_DEFAULT_ADJUST			GUI_DEFAULT_ADJUST
#define GUI_LABEL_DEFAULT_WIDTH				GUI_DEFAULT_WIDTH
#define GUI_LABEL_DEFAULT_HEIGHT			GUI_DEFAULT_HEIGHT
#define GUI_LABEL_DEFAULT_TOP				GUI_DEFAULT_TOP
#define GUI_LABEL_DEFAULT_LEFT				GUI_DEFAULT_LEFT
#define GUI_LABEL_COLOR						GUI_COLOR
#define GUI_LABEL_COLOR_PUSHED				GUI_COLOR_PUSHED
#define GUI_LABEL_BORDER_SIZE				GUI_BORDER_SIZE
#define GUI_LABEL_BORDER_COLOR				GUI_BORDER_COLOR
#define GUI_LABEL_BORDER_COLOR_SELECTED		GUI_BORDER_COLOR_SELECTED
#define GUI_LABEL_MARGIN_SIZE				GUI_MARGIN_SIZE
#define GUI_LABEL_PADDING_SIZE				GUI_PADDING_SIZE

#define GUI_BUTTON_DEFAULT_TEXT				GUI_DEFAULT_TEXT
#define GUI_BUTTON_TEXT_COLOR				GUI_DEFAULT_TEXT_COLOR
#define GUI_BUTTON_DEFAULT_ADJUST			GUI_DEFAULT_ADJUST
#define GUI_BUTTON_DEFAULT_WIDTH			GUI_DEFAULT_WIDTH
#define GUI_BUTTON_DEFAULT_HEIGHT			GUI_DEFAULT_HEIGHT
#define GUI_BUTTON_DEFAULT_TOP				GUI_DEFAULT_TOP
#define GUI_BUTTON_DEFAULT_LEFT				GUI_DEFAULT_LEFT
#define GUI_BUTTON_COLOR					GUI_COLOR
#define GUI_BUTTON_COLOR_PUSHED				GUI_COLOR_PUSHED
#define GUI_BUTTON_BORDER_SIZE				GUI_BORDER_SIZE
#define GUI_BUTTON_BORDER_COLOR				GUI_BORDER_COLOR
#define GUI_BUTTON_BORDER_COLOR_SELECTED	GUI_BORDER_COLOR_SELECTED
#define GUI_BUTTON_MARGIN_SIZE				GUI_MARGIN_SIZE
#define GUI_BUTTON_PADDING_SIZE				GUI_PADDING_SIZE

#define GUI_SWITCH_DEFAULT_TEXT_OFF			GUI_DEFAULT_TEXT_OFF
#define GUI_SWITCH_DEFAULT_TEXT_ON			GUI_DEFAULT_TEXT_ON
#define GUI_SWITCH_TEXT_COLOR				GUI_DEFAULT_TEXT_COLOR
#define GUI_SWITCH_DEFAULT_ADJUST			GUI_DEFAULT_ADJUST
#define GUI_SWITCH_DEFAULT_WIDTH			GUI_DEFAULT_WIDTH
#define GUI_SWITCH_DEFAULT_HEIGHT			GUI_DEFAULT_HEIGHT
#define GUI_SWITCH_DEFAULT_TOP				GUI_DEFAULT_TOP
#define GUI_SWITCH_DEFAULT_LEFT				GUI_DEFAULT_LEFT
#define GUI_SWITCH_COLOR					GUI_COLOR
#define GUI_SWITCH_COLOR_PUSHED				GUI_COLOR_PUSHED
#define GUI_SWITCH_BORDER_SIZE				GUI_BORDER_SIZE
#define GUI_SWITCH_BORDER_COLOR				GUI_BORDER_COLOR
#define GUI_SWITCH_BORDER_COLOR_SELECTED	GUI_BORDER_COLOR_SELECTED
#define GUI_SWITCH_MARGIN_SIZE				GUI_MARGIN_SIZE
#define GUI_SWITCH_PADDING_SIZE				GUI_PADDING_SIZE

#define GUI_SCROLL_DEFAULT_VALUE			GUI_DEFAULT_VALUE
#define GUI_SCROLL_DEFAULT_MIN_VALUE		GUI_DEFAULT_MIN_VALUE
#define GUI_SCROLL_DEFAULT_MIN_VALUE		GUI_DEFAULT_MIN_VALUE
#define GUI_SCROLL_MINUS_TEXT				GUI_MINUS_TEXT
#define GUI_SCROLL_PLUS_TEXT				GUI_PLUS_TEXT
#define GUI_SCROLL_DEFAULT_ADJUST			GUI_DEFAULT_ADJUST
#define GUI_SCROLL_DEFAULT_WIDTH			GUI_DEFAULT_WIDTH
#define GUI_SCROLL_DEFAULT_HEIGHT			GUI_DEFAULT_HEIGHT
#define GUI_SCROLL_DEFAULT_TOP				GUI_DEFAULT_TOP
#define GUI_SCROLL_DEFAULT_LEFT				GUI_DEFAULT_LEFT
#define GUI_SCROLL_COLOR					GUI_COLOR
#define GUI_SCROLL_COLOR_PUSHED				GUI_COLOR_PUSHED
#define GUI_SCROLL_BORDER_SIZE				GUI_BORDER_SIZE
#define GUI_SCROLL_BORDER_COLOR				GUI_BORDER_COLOR
#define GUI_SCROLL_BORDER_COLOR_SELECTED	GUI_BORDER_COLOR_SELECTED
#define GUI_SCROLL_MARGIN_SIZE				GUI_MARGIN_SIZE
#define GUI_SCROLL_AREA_COLOR				GUI_DEEP_COLOR
#define GUI_SCROLL_AREA_COLOR_PUSHED		GUI_DEEP_COLOR_PUSHED
#define GUI_SCROLL_HANDLER_COLOR			GUI_COLOR
#define GUI_SCROLL_HANDLER_COLOR_PUSHED		GUI_COLOR

#endif /* STYLE_H_ */
