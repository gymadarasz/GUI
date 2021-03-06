/*
 * Canvas.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: Gyula
 */

#include "Canvas.h"


namespace gui {

Canvas* Canvas::canvases[CANVASES] = {0};
int Canvas::_canvasDeleted = 0;

// initializers:
void Canvas::initMargin() {
	margin.horizontal = MARGIN_SIZE_HORIZONTAL;
	margin.vertical = MARGIN_SIZE_VERTICAL;
}

void Canvas::initBorder() {
	border.size = BORDER_SIZE;
	border.color = BORDER_COLOR;
	border.colorSelected = BORDER_COLOR_SELECTED;
	border.colorDisabled = BORDER_COLOR_DISABLED;
	border.colorPushed = BORDER_COLOR_PUSHED;
}

void Canvas::initPadding() {
	padding.horizontal = PADDING_SIZE_HORIZONTAL;
	padding.vertical = PADDING_SIZE_VERTICAL;
}

void Canvas::initText() {
	text.label[0] = '\0';
	text.size = TEXT_SIZE;
	text.color = TEXT_COLOR;
	text.colorSelected = TEXT_COLOR_SELECTED;
	text.colorDisabled = TEXT_COLOR_DISABLED;
	text.colorPushed = TEXT_COLOR_PUSHED;
}

void Canvas::initBox() {
	box.top = 0;
	box.left = 0;
	box.width = 0;
	box.height = 0;
	box.color = BOX_COLOR;
	box.colorSelected = BOX_COLOR_SELECTED;
	box.colorDisabled = BOX_COLOR_DISABLED;
	box.colorPushed = BOX_COLOR_PUSHED;
	box.breakLine = false;

	box.fitToText = true;
	box.positioned = false;
}

void Canvas::initCursor() {
	cursor.top = 0;
	cursor.left = 0;
	cursor.lnHeight = 0;
}

void Canvas::cursorReset() {
	cursor.top = 0;
	cursor.left = 0;
	cursor.lnHeight = 0;
}

void Canvas::cursorBreakLine(int lnHeight) {
	cursor.left = 0;
	cursor.top += cursor.lnHeight;
	cursor.lnHeight = lnHeight;
}

void Canvas::cursorStep(int width, int height) {
	cursor.left += width;

	if (height > cursor.lnHeight) {
		cursor.lnHeight = height;
	}
}

CanvasColor Canvas::getClearColor() {
	Canvas* behind = parent ? parent : this;
	CanvasColor color = behind->box.color;
	if (behind->selected) color = behind->box.colorSelected;
	if (behind->pushed) color = behind->box.colorPushed;
	if (behind->disabled) color = behind->box.colorDisabled;
	return color;
}

bool Canvas::select(bool sel) {
	if (!inactive && !disabled && !hidden) {
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i] && canvases[i]->selected) {
				if (canvases[i]->selected) {
					canvases[i]->selected = false;
					canvases[i]->draw();
				}
			}
		}

		selected = sel;
		draw();
	}
	return selected;
}

bool Canvas::push(bool psh) {
	if (!inactive && !disabled && !hidden) {
		if (!switchable) {
			pushed = psh;
		} else if (psh) {
			pushed = !pushed;
		}
		draw();
	}
	return pushed;
}

int Canvas::getSelectedId() {
	for (int i=0; i<CANVASES; i++) {
		if (canvases[i] && canvases[i]->selected) {
			return i;
		}
	}
	return -1;
}

void Canvas::selectNext() {
	int sid = getSelectedId();
	int i = sid + 1 < CANVASES ? sid + 1 : 0;
	for (; i < CANVASES; i++) {
		if (canvases[i] && canvases[i]->select()) {
			break;
		}
	}
}

void Canvas::selectPrev() {
	int sid = getSelectedId();
	int i = sid - 1 >= 0 ? sid - 1 : CANVASES - 1;
	for (; i >= 0; i--) {
		if (canvases[i] && canvases[i]->select()) {
			break;
		}
	}
}

void Canvas::clickSelected() {
	for (int i = 0; i<CANVASES; i++) {
		if (canvases[i] && canvases[i]->selected) {
			canvases[i]->onMouseDown(0, 0);
			canvases[i]->onClick(0, 0);
			canvases[i]->onMouseUp(0, 0);
			break;
		}
	}
}

bool Canvas::isInside(CanvasEventPoint eventPoint) {
    int top = realTop;
    int left = realLeft;
    int fullwidth = fullWidth;
    int fullheight = fullHeight;
    int right = left + fullwidth;
    int bottom = top + fullheight;
    return eventPoint.left >= left && eventPoint.left <= right && eventPoint.top >= top && eventPoint.top <= bottom;
}

// public:

Canvas::Canvas(Canvas* parent,
		int width, int height/*,
		CanvasPainter* scr, CanvasKeyboard* kbrd, CanvasMouse* mse*/) {
	this->parent = parent;

	//	this->scr = scr ? scr : (parent ? parent->scr : 0);
	//	this->kbrd = kbrd ? kbrd : (parent ? parent->kbrd : 0);
	//	this->mse = mse ? mse : (parent ? parent->mse : 0);
	this->scr = parent && parent->scr ? parent->scr : new CanvasPainter(width, height);
	this->kbrd = parent && parent->kbrd ? parent->kbrd : new CanvasKeyboard();
	this->mse = parent && parent->mse ? parent->mse : new CanvasMouse();

	for (id=0; id<CANVASES; id++) {
		if (!canvases[id]) {
			canvases[id] = this;
			break;
		}
	}

	initMargin();
	initBorder();
	initBox();
	initPadding();
	initText();

	disabled = false;
	selected = false;
	pushed = false;
	hidden = false;
	inactive = false;
	switchable = false;

	onTickHandler = 0;
	onClickHandler = 0;
	onDblClickHandler = 0;
	onMouseMoveHandler = 0;
	onMouseDragHandler = 0;
	onMouseOverHandler = 0;
	onMouseLeaveHandler = 0;
	onMouseDownHandler = 0;
	onMouseUpHandler = 0;
	onKeyPressHandler = 0;

	realTop = box.top;
	realLeft = box.left;
	setWidth(box.width + (border.size + margin.horizontal)*2);
	setHeight(box.height + (border.size + padding.vertical)*2);
//	fullWidth = box.width + (border.size + margin.horizontal)*2;
//	fullHeight = box.height + (border.size + padding.vertical)*2;

	latestBorderColor = GUI_UNDEFINED;
	latestInnerColor = GUI_UNDEFINED;
	latestTextColor = GUI_UNDEFINED;

	running = false;

	// main screen
	if (!this->parent) {
//		scr->init(width, height);


		setPosition(0, 0);
		setSize(scr->getMaxWidth(), scr->getMaxHeight());
		setMargin(0, 0);
		setBorder(0, NOCOLOR);
		setPadding(0, 0);
		//setColor(4);
	} else {
		this->parent = parent;

		this->parent->inactive = true;
//		if (this->parent->box.width < fullWidth) {
//			this->parent->box.width = fullWidth;
//		}
	}
}

Canvas::~Canvas() {
	clear();
	deleteChildren();
	canvases[id] = 0;
}

void Canvas::setSize(int width, int height) {
	setWidth(width);
	setHeight(height);
}

void Canvas::setHeight(int height) {
	if (box.height != height) {
		box.height = height;
		fullHeight = box.height + (border.size + margin.vertical)*2;
	}
}

void Canvas::setWidth(int width) {
	if (box.width != width) {
		box.width = width;
		fullWidth = box.width + (border.size + margin.horizontal)*2;
		if (parent && parent->box.width < fullWidth) {
			parent->box.width = fullWidth;
		}
	}
}

void Canvas::setColor(int color, int colorSelected, int colorDisabled, int colorPushed) {
	if (box.color != color) {
		box.color = color;
	}
	if (colorSelected != GUI_UNDEFINED) {
		setColorSelected(colorSelected);
	}
	if (colorDisabled != GUI_UNDEFINED) {
		setColorDisabled(colorSelected);
	}
	if (colorPushed != GUI_UNDEFINED) {
		setColorPushed(colorSelected);
	}
}

void Canvas::setColorSelected(int colorSelected) {
	if (box.colorSelected != colorSelected) {
		box.colorSelected = colorSelected;
	}
}

void Canvas::setColorDisabled(int colorDisabled) {
	if (box.colorDisabled != colorDisabled) {
		box.colorDisabled = colorDisabled;
	}
}

void Canvas::setColorPushed(int colorPushed) {
	if (box.colorPushed != colorPushed) {
		box.colorPushed = colorPushed;
	}
}

void Canvas::setTextf(const char* format, ...) {
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);
    setText(dest);
}

void Canvas::setText(const char* str, int size) {
	setText((char*)str, size);
}

void Canvas::setText(char* str, int size) {
	bool redraw = false;
	int i = 0;
	while(str[i]) {
		if (text.label[i] != str[i]) {
			redraw = true;
		}
		text.label[i] = str[i];
		i++;
	}
	text.label[i] = 0;

	if (size != GUI_UNDEFINED && text.size != size) {
		setTextSize(size);
		redraw = true;
	}

	if (redraw) {
		int textWidth = scr->getTextWidth(text.label, text.size);
		int textHeight = scr->getTextHeight(text.label, text.size);
		if (box.fitToText || box.width < textWidth + padding.horizontal*2) {
			setWidth(textWidth + padding.horizontal*2);
		}
		if (box.fitToText || box.height < textHeight + padding.vertical*2) {
			setHeight(textHeight + padding.vertical*2);
		}
//		if (isRunning()) {
//			draw();
//		}
	}

}

void Canvas::setTextColor(int color, int colorSelected, int colorDisabled, int colorPushed) {
	if (text.color != color) {
		text.color = color;
	}
	if (colorSelected != GUI_UNDEFINED) {
		setTextColorSelected(colorSelected);
	}
	if (colorDisabled != GUI_UNDEFINED) {
		setTextColorDisabled(colorSelected);
	}
	if (colorPushed != GUI_UNDEFINED) {
		setTextColorPushed(colorSelected);
	}
}

void Canvas::setTextColorSelected(int colorSelected) {
	if (text.colorSelected != colorSelected) {
		text.colorSelected = colorSelected;
	}
}

void Canvas::setTextColorDisabled(int colorDisabled) {
	if (text.colorDisabled != colorDisabled) {
		text.colorDisabled = colorDisabled;
	}
}

void Canvas::setTextColorPushed(int colorPushed) {
	if (text.colorPushed != colorPushed) {
		text.colorPushed = colorPushed;
	}
}

void Canvas::setTextSize(int size) {
	if (text.size != size) {
		text.size = size;
	}
}

void Canvas::setBreakLine(bool br) {
	if (box.breakLine != br) {
		box.breakLine = br;
	}
}

void Canvas::setPosition(int top, int left, bool positioned) {
	if (box.top != top || box.left != left) {
		box.top = top;
		box.left = left;
		box.positioned = positioned;
	}
}


void Canvas::setMargin(int horizontal, int vertical) {
	if (margin.horizontal != horizontal || margin.vertical != vertical) {
		margin.horizontal = horizontal;
		margin.vertical = vertical;
	}
}

void Canvas::setMarginVertical(int vertical) {
	if (margin.vertical != vertical) {
		margin.vertical = vertical;
	}
}

void Canvas::setPadding(int horizontal, int vertical) {
	if (padding.horizontal != horizontal || padding.vertical != vertical) {
		padding.horizontal = horizontal;
		padding.vertical = vertical;
	}
}

void Canvas::setPaddingVertical(int vertical) {
	if (padding.vertical != vertical) {
		padding.vertical = vertical;
	}
}

void Canvas::setBorder(int size, int color) {
	if (border.size != size) {
		border.size = size;
	}
	if (border.color != color) {
		border.color = color;
	}
}

void Canvas::setBorderSize(int size) {
	if (border.size != size) {
		border.size = size;
	}
}

void Canvas::setBorderColor(int color, int colorSelected, int colorDisabled, int colorPushed) {
	if (border.color != color) {
		border.color = color;
	}
	if (colorSelected != GUI_UNDEFINED) {
		setBorderColorSelected(colorSelected);
	}
	if (colorDisabled != GUI_UNDEFINED) {
		setBorderColorDisabled(colorSelected);
	}
	if (colorPushed != GUI_UNDEFINED) {
		setBorderColorPushed(colorSelected);
	}
}

void Canvas::setBorderColorSelected(int colorSelected) {
	if (border.colorSelected != colorSelected) {
		border.colorSelected = colorSelected;
	}
}

void Canvas::setBorderColorDisabled(int colorDisabled) {
	if (border.colorDisabled != colorDisabled) {
		border.colorDisabled = colorDisabled;
	}
}

void Canvas::setBorderColorPushed(int colorPushed) {
	if (border.colorPushed != colorPushed) {
		border.colorPushed = colorPushed;
	}
}

void Canvas::setSwitch(bool switchable) {
	this->switchable = switchable;
}

Canvas* Canvas::getParent() {
	return parent;
}

int Canvas::getFullWidth() {
	return fullWidth;
}

bool Canvas::isPushed() {
	return pushed;
}

bool Canvas::isRunning() {
	if (running || (parent && parent->isRunning())) {
		return true;
	}
	return false;
}


void Canvas::enable() {
	if (disabled) {
		disabled = false;
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
				canvases[i]->enable();
			}
		}
		if (isRunning()) {
			draw();
		}
	}
}

void Canvas::disable() {
	if (!disabled) {
		disabled = true;
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
				canvases[i]->disable();
			}
		}
		if (isRunning()) {
			draw();
		}
	}
}

void Canvas::show() {
	if (hidden) {
		hidden = false;
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
				canvases[i]->show();
			}
		}
		draw();
	}
}

void Canvas::hide() {
	if (!hidden) {
		hidden = true;
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
				canvases[i]->hide();
			}
		}
		draw();
	}
}


void Canvas::activate() {
	this->inactive = false;
}

void Canvas::inactivate() {
	this->inactive = true;
}

void Canvas::calc() {

	// calculate size (may it's already calculated... if not use setSize(), setWidth() or setHeight())
	fullWidth = box.width + (border.size + margin.horizontal)*2;
	fullHeight = box.height + (border.size + margin.vertical)*2;

	// calculate real (on screen) position
	int parentCursorRealTop = 0;
	int parentCursorRealLeft = 0;
	if (!hidden && !box.positioned && parent) {
		parentCursorRealTop = parent->realTop;
		parentCursorRealLeft = parent->realLeft;

		if (box.breakLine || parent->cursor.left + fullWidth > parent->box.width) {
			parent->cursorBreakLine(fullHeight);
		}

		parentCursorRealTop += parent->cursor.top;
		parentCursorRealLeft += parent->cursor.left;

	}
	realTop = parentCursorRealTop + box.top + margin.vertical + border.size;
	realLeft = parentCursorRealLeft + box.left + margin.horizontal + border.size;

	// calc children
	cursorReset();
	for (int i=0; i<CANVASES; i++) {
		if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
			canvases[i]->calc();
		}
	}

	// height fit to cursor (maybe children push down the size?)
	if (cursor.top + cursor.lnHeight > box.height) {
		box.height = cursor.top + cursor.lnHeight;
		fullHeight = box.height + (border.size + margin.vertical)*2;
	}

	if (!hidden && !box.positioned && parent) {
		parent->cursorStep(fullWidth, fullHeight);
	}

}

void Canvas::draw(CanvasColor clearColor) {

	int borderColor = border.color;
	int innerColor = box.color;
	int textColor = text.color;

	if (selected) {
		borderColor = border.colorSelected;
		innerColor = box.colorSelected;
		textColor = text.colorSelected;
	}

	if (pushed) {
		borderColor = border.colorPushed;
		innerColor = box.colorPushed;
		textColor = text.colorPushed;
	}

	if (disabled) {
		borderColor = border.colorDisabled;
		innerColor = box.colorDisabled;
		textColor = text.colorDisabled;
	}


	if (hidden) {
		clearColor = getClearColor();
	}
	if (clearColor != GUI_UNDEFINED) {
		borderColor = clearColor;
		innerColor = clearColor;
		textColor = clearColor;
	}


	if (latestBorderColor != borderColor) {
		// draw border
		scr->rect(
				realTop + margin.vertical + border.size,
				realLeft + margin.horizontal + border.size,
				box.width,
				box.height,
				borderColor,
				border.size);
		latestBorderColor = borderColor;
	}

	bool redrawText = false;
	if (latestInnerColor != innerColor) {
		// draw inner box
		scr->fillrect(
				realTop + margin.vertical + border.size,
				realLeft + margin.horizontal + border.size,
				box.width,
				box.height,
				innerColor);
		redrawText = true;
		latestInnerColor = innerColor;
	}

	if (latestTextColor != textColor || redrawText) {
		// draw text
		scr->putText(
				realTop + margin.vertical + border.size + padding.vertical,
				realLeft + margin.horizontal + border.size + padding.horizontal,
				text.label,
				textColor,
				innerColor,
				text.size);
		latestTextColor = textColor;
	}

	// draw children
	for (int i=0; i<CANVASES; i++) {
		if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
			canvases[i]->draw();
		}
	}

}

void Canvas::clear() {
	draw(getClearColor());
}

void Canvas::redraw() {
	calc();
	draw();
}

void Canvas::deleteChildren() {
	for (int i=0; i<CANVASES; i++) {
		if (canvases[i] && canvases[i]->parent && canvases[i]->parent->id == id) {
			canvases[i]->deleteChildren();
			delete canvases[i];
			canvases[i] = 0;
			_canvasDeleted++;
		}
	}
}


void Canvas::run(CanvasLoop loop) {
	calc();
	draw();

	mse->reset();

	running = true;
	while (running) {
		mse->check();

		if (kbrd->check()) {

			switch (kbrd->getKeypress().key) {

			case KEY_LEFT:
				selectPrev();
				break;
			case KEY_RIGHT:
				selectNext();
				break;

			case KEY_ENTER:
			case KEY_SPACE:
				clickSelected();
				break;
			}

		}

		_canvasDeleted = false;
		for (int i=0; i<CANVASES; i++) {
			if (canvases[i]) {
				canvases[i]->tick();
				if (_canvasDeleted) {
					break;
				}
			}
		}

		if (loop) {
			loop();
		}
		delay(1);
	}
}

//--events

void Canvas::tick() {

	onTick();

    if (disabled || hidden) {
        return ;
    }

    int top = realTop;
    int left = realLeft;

	// mouse down?
	if (mse->getEvents().mouseDown.happend && isInside(mse->getEvents().mouseDown.position)) {
		onMouseDown(mse->getEvents().mouseDown.position.left-left, mse->getEvents().mouseDown.position.top-top);
	}

	// click?
	if (mse->getEvents().click.happend && isInside(mse->getEvents().click.position)) {
		onClick(mse->getEvents().click.position.left-left, mse->getEvents().click.position.top-top);
	}

	// dblclick?
	if (mse->getEvents().dblClick.happend && isInside(mse->getEvents().dblClick.position)) {
		onDblClick(mse->getEvents().dblClick.position.left-left, mse->getEvents().dblClick.position.top-top);
	}

	// mouse move, over, leave?
	if (mse->getEvents().mouseMove.happend) {
		if (isInside(mse->getEvents().mouseMove.current) && isInside(mse->getEvents().mouseMove.previous)) {
			onMouseMove(
				mse->getEvents().mouseMove.current.left-left, mse->getEvents().mouseMove.current.top-top,
				mse->getEvents().mouseMove.previous.left-left, mse->getEvents().mouseMove.previous.top-top
			);
		} else if (isInside(mse->getEvents().mouseMove.current)) {
			onMouseOver(mse->getEvents().mouseMove.current.left-left, mse->getEvents().mouseMove.current.top-top);
		} else if (isInside(mse->getEvents().mouseMove.previous)) {
			onMouseLeave(mse->getEvents().mouseMove.previous.left-left, mse->getEvents().mouseMove.previous.top-top);
		}
	}

	if (mse->getEvents().mouseDrag.happend) {
		if (isInside(mse->getEvents().mouseDrag.current) && isInside(mse->getEvents().mouseDrag.previous)) {
			onMouseDrag(
				mse->getEvents().mouseDrag.current.left-left, mse->getEvents().mouseDrag.current.top-top,
				mse->getEvents().mouseDrag.previous.left-left, mse->getEvents().mouseDrag.previous.top-top
			);
		}
	}

	// mouse up?
	if (mse->getEvents().mouseUp.happend && isInside(mse->getEvents().mouseUp.position)) {
		onMouseUp(mse->getEvents().mouseUp.position.left-left, mse->getEvents().mouseUp.position.top-top);
	}

    if (selected) {
    	CanvasEventKeypress keypress = kbrd->getKeypress();
    	if (keypress.happened) {
    		onKeyPress(keypress.key);
    	}
    }
}


void Canvas::onTick() {
    if (onTickHandler) {
        onTickHandler(this);
    }
}

void Canvas::onClick(int mouseLeft, int mouseTop) {
	if (onClickHandler) {
		onClickHandler(this, mouseLeft, mouseTop);
	}
}

void Canvas::onDblClick(int mouseLeft, int mouseTop) {
	if (onDblClickHandler) {
		onDblClickHandler(this, mouseLeft, mouseTop);
	}
}

void Canvas::onMouseMove(int mouseLeftFrom, int mouseTopFrom, int mouseLeftCurrent, int mouseTopCurrent) {
	if (onMouseMoveHandler) {
		onMouseMoveHandler(this, mouseLeftFrom, mouseTopFrom, mouseLeftCurrent, mouseTopCurrent);
	}
}

void Canvas::onMouseOver(int mouseLeft, int mouseTop) {
	select();

	if (onMouseOverHandler) {
		onMouseOverHandler(this, mouseLeft, mouseTop);
	}
}

void Canvas::onMouseLeave(int mouseLeft, int mouseTop) {
	select(false);

	if (onMouseLeaveHandler) {
		onMouseLeaveHandler(this, mouseLeft, mouseTop);
	}
}

void Canvas::onMouseDrag(int mouseLeftFrom, int mouseTopFrom, int mouseLeftCurrent, int mouseTopCurrent) {
	if (onMouseDragHandler) {
		onMouseDragHandler(this, mouseLeftFrom, mouseTopFrom, mouseLeftCurrent, mouseTopCurrent);
	}
}

void Canvas::onMouseDown(int mouseLeft, int mouseTop) {
	push();

	if (onMouseDownHandler) {
		onMouseDownHandler(this, mouseLeft, mouseTop);
	}
}

void Canvas::onMouseUp(int mouseLeft, int mouseTop) {
	push(false);

	if (onMouseUpHandler) {
		onMouseUpHandler(this, mouseLeft, mouseTop);
	}
}


void Canvas::onKeyPress(int key) {

	if (onKeyPressHandler) {
		onKeyPressHandler(this, key);
	}
}


} /* namespace gui */
