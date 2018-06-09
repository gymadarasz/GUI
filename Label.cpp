#include "Label.h"

#include "App.h"

namespace GUI {

    Label::Label(
        int top, int left, const char* text, int width, int height,
        int bgcolor, int txcolor, int brcolor):
            Canvas(top, left, width, height, bgcolor, brcolor) {
        this->txcolor = txcolor;
        this->text = NULL;
        setText(text);
        changed = true;
    }

    bool Label::draw() {
        if(Canvas::draw()) {
            int w = textwidth((char*)getText());
            int h = textheight((char*)getText());
            App::painter.text(top + (getHeight()-h)/2, left + (getWidth()-w)/2,
                txcolor, getBgColor(), getText());
            return true;
        }
        return false;
    }

//    void Label::clearText() {
//        int w = textwidth((char*)getText());
//        int h = textheight((char*)getText());
//        App::painter.text(top + (getHeight()-h)/2, left + (getWidth()-w)/2,
//            container->getBgColor(), container->getBgColor(), getText());
//    }
    
    const char* Label::getText() {
        return text;
    }

    void Label::setText(const char* text) {
        // clear first if text already set because maybe text changes the size
        if (NULL != getText()) {
//            clearText();
//            if (width == GD_AUTO || height == GD_AUTO) {
                clear();
//            }
        }
        this->text = text;
        changed = true;
    }

    void Label::onMouseOver(int x, int y) {}

    void Label::onMouseLeave(int x, int y) {}

    // ---- protected

    int Label::calcWidth() {
        return textwidth((char*)getText()) + GD_LBL_WPADDING*2;  // todo: use class variable instead constants for paddings (here and buttons also!)
    }

    int Label::calcHeight() {
        return textheight((char*)getText()) + GD_LBL_HPADDING*2;
    }
    
}
