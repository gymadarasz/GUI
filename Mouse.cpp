#include "Mouse.h"

namespace GUI {
    
    Mouse::Mouse() {
        lastMouseX = mousex();
        lastMouseY = mousey();
        lbtndown = false;
    }
    
    void Mouse::check() {
        int x, y;

        //MouseEvents mouseEvents = Mouse::events;


        // mouse released (mouse up)?
        events.onMouseUp.happend = false;
        if (ismouseclick(WM_LBUTTONUP)) {
            getmouseclick(WM_LBUTTONUP, x, y);
            events.onMouseUp.happend = true;
            events.onMouseUp.position.x = x;
            events.onMouseUp.position.y = y;
            lbtndown = false;
        }
        
        // any mouse click event (or mouse down - same thing..)?
        events.onMouseDown.happend = false;
        events.onClick.happend = false;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            events.onMouseDown.happend = true;
            events.onMouseDown.position.x = x;
            events.onMouseDown.position.y = y;
            events.onClick.happend = true;
            events.onClick.position.x = x;
            events.onClick.position.y = y;
            lbtndown = true;
        }

        // double click?
        events.onDblClick.happend = false;
        if (ismouseclick(WM_LBUTTONDBLCLK)) {
            getmouseclick(WM_LBUTTONDBLCLK, x, y);
            events.onMouseDown.happend = true;
            events.onMouseDown.position.x = x;
            events.onMouseDown.position.y = y;
            events.onDblClick.happend = true;
            events.onDblClick.position.x = x;
            events.onDblClick.position.y = y;
            events.onClick.happend = true;
            events.onClick.position.x = x;
            events.onClick.position.y = y;
            lbtndown = false;
        }

        // maybe mouse moved or dragged?
        events.onMouseMove.happend = false;
        events.onMouseDrag.happend = false;
        x = mousex();
        y = mousey();
        if (x != lastMouseX || y != lastMouseY) {
            events.onMouseMove.happend = true;
            events.onMouseMove.current.x = x;
            events.onMouseMove.current.y = y;
            events.onMouseMove.previous.x = lastMouseX;
            events.onMouseMove.previous.y = lastMouseY;
            if (lbtndown) {
                events.onMouseDrag.happend = true;
                events.onMouseDrag.current.x = x;
                events.onMouseDrag.current.y = y;
                events.onMouseDrag.previous.x = lastMouseX;
                events.onMouseDrag.previous.y = lastMouseY;
            }
            lastMouseX = x;
            lastMouseY = y;
        }
        
    }

}

