#include "Button1.h"

#include "App1.h"

using namespace GUI;

void Button1::onClick(int x, int y) {
    Button::onClick(x, y);
    App1::label1->setText("button1 clicked");
    printf("button1 clicked.\n");
}
