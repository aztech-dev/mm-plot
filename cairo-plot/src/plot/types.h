/*
 * types.h
 *
 *  Created on: Mar 24, 2010
 *      Author: root
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <gdkmm-2.4/gdkmm/color.h>
#include <gtkmm-2.4/gtkmm/enums.h>
#include <cairomm-1.0/cairomm/context.h>
#include <cairomm-1.0/cairomm/refptr.h>

namespace Gtk
{

namespace Plot
{

class Drawable
{
public:
	Drawable() {}
	virtual ~Drawable() {}
	// draw() expects context to be set up. As a general rule,
	// draw() does not perform any layout, and will draw to
	// whatever coordinate system is setup.
	virtual void draw(Cairo::RefPtr<Cairo::Context> context) = 0;
};

struct Border
{
	int width;
	Gdk::Color color;
	Border()
	{
		this->width = 1;
	};
	Border(uint width, Gdk::Color color)
	{
		this->width = width;
		this->color = color;
	};
};

typedef Border Line;

typedef struct PlotLineDataStruct2D : Drawable
{
	double x;
	double y;
	PlotLineDataStruct2D(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	void draw(Cairo::RefPtr<Cairo::Context> context)
	{
		context->save();
		double l_w = context->get_line_width();
		context->move_to(x, y);
		context->rectangle(x-0.5*l_w, y-0.5*l_w,l_w,l_w);
		context->stroke();
		context->restore();
	}
} DataPoint2D;

enum LabelPosition
{
	POSITION_INNER = 0,
	POSITION_OUTER = 1,
	POSITION_DEFAULT = 1
};

enum MarkerStyle
{
	MARKER_NONE = 0,
	MARKER_DOT = 1,
	MARKER_TRIANGLE = 2,
	MARKER_SQUARE = 3,
	MARKER_CIRCLE = 4,
	MARKER_CROSSHAIR = 5,
	MARKER_DEFAULT = MARKER_NONE
};

enum Origin
{
	TOP_LEFT = Gtk::CORNER_TOP_LEFT,
	BOTTOM_LEFT = Gtk::CORNER_BOTTOM_LEFT,
	BOTTOM_RIGHT = Gtk::CORNER_BOTTOM_RIGHT,
	TOP_RIGHT = Gtk::CORNER_TOP_RIGHT,
	CENTER = 10,
	CAIRO_DEFAULT = TOP_LEFT
};

enum DefaultVector
{
	VECTOR_TOP_LEFT = Gtk::CORNER_TOP_LEFT,
	VECTOR_BOTTOM_LEFT = Gtk::CORNER_BOTTOM_LEFT,
	VECTOR_BOTTOM_RIGHT = Gtk::CORNER_BOTTOM_RIGHT,
	VECTOR_TOP_RIGHT = Gtk::CORNER_TOP_RIGHT
};

}

}

#endif /* TYPES_H_ */
