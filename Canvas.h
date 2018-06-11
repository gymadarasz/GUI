#ifndef CANVAS_H
#define CANVAS_H

#include <graphics.h>
#include "style.h"
#include "Counted.h"
#include "Cursor.h"

#define CANVASES 40

namespace GUI {


    class Canvas: public Counted {
    private:

        int lastTop;
        int lastLeft;
        int lastWidth;
        int lastHeight;
        
        int top;  // TODO: getter + setter for everything
        int left;
        
        void findNextWidthAndStepCursor(int current);
        
    protected:

        Canvas* parent = {NULL};
        
        int width;
        int height;
        RECT margin;
        RECT padding;
        int bgcolor;
        int brcolor;
        bool disabled;
        bool highlighted;
        bool pushed;
        bool changed;
        
        virtual int calcWidth();
        virtual int calcHeight();

        bool isChanged();
        
    public:
        
//        POINT offset;
        Canvas* canvases[CANVASES] = {NULL};
        Cursor cursor;
        
        Canvas(Canvas* parent = NULL);
        Canvas* setParent(Canvas* canvas);
        Canvas* getParent();
        virtual Canvas* setup(
            int top = GD_AUTOPOSITION,
            int left = GD_AUTOPOSITION,
            int width = GD_CANVAS_WIDTH,
            int height = GD_CANVAS_HEIGHT,
            RECT margin = {
                GD_CANVAS_LMARGIN,
                GD_CANVAS_RMARGIN,
                GD_CANVAS_TMARGIN,
                GD_CANVAS_BMARGIN
            },
            RECT padding = {
                GD_CANVAS_LPADDING,
                GD_CANVAS_RPADDING,
                GD_CANVAS_TPADDING,
                GD_CANVAS_BPADDING
            },
            int bgcolor = GD_CANVAS_BGCOLOR,
            int brcolor = GD_CANVAS_BRCOLOR
        );

        Canvas* add(Canvas* canvas);
        virtual void process();
//        virtual void ticks();
//        virtual bool draws();
        
        virtual void tick();
        virtual bool draw();
        virtual void clear();
        virtual bool inside(POINT point);
        virtual RECT* getRect(RECT* rect);
        virtual int getFullWidth();
        virtual int getFullHeight();
        
        virtual int getTop();
        virtual int getLeft();
        virtual int getWidth();
        virtual int getHeight();
        virtual RECT getMargin();
        virtual RECT getPadding();
        virtual int getBgColor();
        virtual int getBrColor();
        virtual bool getDisabled();
        virtual bool getHighlighted();
        virtual bool getPushed();

        virtual void setTop(int top);
        virtual void setLeft(int left);
        virtual void setWidth(int width);
        virtual void setHeight(int height);
        virtual void setMargin(RECT margin);
        virtual void setPadding(RECT padding);
        virtual void setBgColor(int bgcolor);
        virtual void setBrColor(int brcolor);
        virtual void setDisabled(bool disabled);
        virtual void setHighlighted(bool highlighted);
        virtual void setPushed(bool pushed);
        
        virtual void onTick();
        virtual void onClick(int x, int y);
        virtual void onDblClick(int x, int y);
        virtual void onMouseMove(int x, int y, int prevx, int prevy);
        virtual void onMouseOver(int x, int y);
        virtual void onMouseLeave(int x, int y);
        virtual void onMouseDown(int x, int y);
        virtual void onMouseUp(int x, int y);

        // cursor
        virtual bool isAutoPositioned();
    };

}
#endif
