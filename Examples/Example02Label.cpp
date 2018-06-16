/*
 * Example02Label.cpp
 *
 *  Created on: Jun 16, 2018
 *      Author: Gyula
 */

#include "Example02Label.h"

#include "../Label.h"

Example02Label::Example02Label() {
	Window window;

	(new Label(window.getCanvas()))->setup("Hello World!");
	(new Label(window.getCanvas()))->setup("This is a Label.");
	(new Label(window.getCanvas()))->setup("This label in new line.")->setLineBreak(true);

	window.run();
}

Example02Label::~Example02Label() {
	// TODO Auto-generated destructor stub
}

