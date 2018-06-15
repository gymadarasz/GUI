/*
 * GUITest.cpp
 *
 *  Created on: Jun 15, 2018
 *      Author: Gyula
 */

#include "GUITest.h"

namespace GUI {

void GUITest::run() {

    // Is Window draws pixels?
	Window window;
	int color = getpixel(0, 0);
	equ(color, BLACK, "Screen device should be cleared after window initialized.");
	color = getpixel(10, 10);
	equ(color, BLACK, "Screen device should be black after the window initialization.");
	putpixel(10, 10, WHITE);
	color = getpixel(10, 10);
	equ(color, WHITE, "Screen device, should be able to show a pixel.");

    // Is Canvas id incrementing?
    Canvas canvas1;
    equ(canvas1.getId(), 0, "First canvas ID should be 0.");
    Canvas canvas2;
    equ(canvas2.getId(), 1, "Second canvas ID should be 1.");
    Canvas canvas3;
    equ(canvas3.getId(), 2, "Third canvas ID should be 2.");

    // Canvas draws?
    Painter::clear();
    canvas1.setup(100, 100, 20, 20);
    canvas1.draw();
    color = getpixel(20-GUI_CANVAS_BORDER_SIZE, 20-GUI_CANVAS_BORDER_SIZE);
    equ(color, GUI_CANVAS_BORDER_COLOR, "Canvas border should be visible on the screen. (top/left)");
    color = getpixel(20, 20);
    equ(color, GUI_CANVAS_COLOR, "Canvas inner should be visible on the screen. (top/left)");
    color = getpixel(40, 40);
    equ(color, GUI_CANVAS_COLOR, "Canvas border should be visible on the screen. (center somewhere)");
    color = getpixel(20+100+GUI_CANVAS_BORDER_SIZE, 20+GUI_CANVAS_BORDER_SIZE);
    equ(color, GUI_CANVAS_BORDER_COLOR, "Canvas border should be visible on the screen. (top/right)");
    color = getpixel(20+100, 20);
    equ(color, GUI_CANVAS_COLOR, "Canvas inner should be visible on the screen. (top/right)");

    // Canvas auto position
}

} /* namespace GUI */
