#include "Graph.h"

#include "Canvas.h"

namespace GUI {

    Graph::Graph(int top, int left, Canvas* canvas, const char* title, int bgcolor) {
        
        initwindow(canvas->getWidth(), canvas->getHeight());
        HWND hWnd;
        hWnd = FindWindow(NULL, "Windows BGI");
        SetWindowPos(hWnd, NULL, top, left, canvas->getWidth(), canvas->getHeight(), SWP_SHOWWINDOW);
        SetWindowText(hWnd, title);

        canvas->setBgColor(bgcolor);

        // use in release mode only:
        // ShowWindow(GetConsoleWindow(), SW_HIDE);

        // use for debuging:
        // ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

        // clear
        for (int i=0; i < CANVASES; i++) {
            canvases[i] = NULL;
        }

        canvas->setGraph(this);
        registry(canvas);
    }

    void Graph::box(int top, int left, int width, int height, int color, int fillpattern) {

        int right = left + width;
        int bottom = top + height;

        fillsettingstype fillinfo;
        getfillsettings(&fillinfo);
        int c = getcolor();

        setfillstyle(fillpattern, color);
        setcolor(color);

        rectangle(left, top, right, bottom);
        if (left < right && top < bottom) {
            floodfill(left+1, top+1, color);
        }

        setfillstyle(fillinfo.pattern, fillinfo.color);
        setcolor(c);
    }

    void Graph::text(int top, int left, int color, int bgcolor, const char* txt) {
        int c = getcolor();
        int b = getbkcolor();
        setcolor(color);
        setbkcolor(bgcolor);
        outtextxy(left, top, (char*)txt);
        setcolor(c);
        setbkcolor(b);
    }

    void Graph::registry(Canvas* canvas) {
        for (int i=0; i < CANVASES; i++) {
            if (NULL == canvases[i]) {
                canvases[i] = canvas;
                break;
            }
        }
    }

    void Graph::tick() {
        int x, y;

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
        }

        // mouse released (mouse up)?
        events.onMouseUp.happend = false;
        if (ismouseclick(WM_LBUTTONUP)) {
            getmouseclick(WM_LBUTTONUP, x, y);
            events.onMouseUp.happend = true;
            events.onMouseUp.position.x = x;
            events.onMouseUp.position.y = y;
        }

        // maybe mouse moved?
        events.onMouseMove.happend = false;
        x = mousex();
        y = mousey();
        if (x != lastMouseX || y != lastMouseY) {
            events.onMouseMove.happend = true;
            events.onMouseMove.current.x = x;
            events.onMouseMove.current.y = y;
            events.onMouseMove.previous.x = lastMouseX;
            events.onMouseMove.previous.y = lastMouseY;
            lastMouseX = x;
            lastMouseY = y;
        }

        // for each component..

        for (int i=0; i < CANVASES; i++) {
            if (NULL != canvases[i]) {

                // tick
                canvases[i]->tick();

                // repaint if it's changed..
                if (canvases[i]->isChanged()) {
                    canvases[i]->draw();
                }
            }
        }

    }


    void Graph::run() {
        while(1) {
            tick();
            delay(1);
        }
    }

}


