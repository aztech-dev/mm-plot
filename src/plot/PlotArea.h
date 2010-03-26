/*
 * Area.h
 *
 *  Created on: Mar 23, 2010
 *      Author: root
 */

#ifndef AREA_H_
#define AREA_H_
#include <deque>
#include <string>
#include <cairomm-1.0/cairomm/matrix.h>
#include <gtk-2.0/gdk/gdkevents.h>
#include <gtk-2.0/gtk/gtkobject.h>
#include <gdkmm-2.4/gdkmm/rectangle.h>
#include <gtkmm-2.4/gtkmm/drawingarea.h>
#include <gtkmm-2.4/gtkmm/widget.h>
#include <gtkmm-2.4/gtkmm/label.h>
#include "types.h"
#include "DrawableData.h"
#include "Line2D.h"

namespace Gtk
{

namespace Plot
{

class Area : public Gtk::Widget {
public:
	Area();
	virtual ~Area();

	std::deque<Line2D*> get_lines();
	void set_default_vector(DefaultVector vector);
	void set_mininum_size(double width, double height);
	void set_mininum_range(double xmin, double ymin, double xmax, double ymax);
	void set_padding(double x, double y);
	void set_plot_border(Gtk::Plot::Border border);
	void set_plot_origin(Origin origin);
	void set_plot_title(Gtk::Label& title);
	void set_plot_title(std::string title);
	void set_plot_title_position(Gtk::Plot::LabelPosition pos);
	void hide_axes();
	void show_axes();
protected:
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
	//Overrides:
	virtual void on_size_request(Gtk::Requisition* requisition);
	virtual void on_size_allocate(Gtk::Allocation& allocation);
	virtual void on_map();
	virtual void on_unmap();
	virtual void on_realize();
	virtual void on_unrealize();
	virtual bool on_expose_event(GdkEventExpose* event);
#endif
	/* GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED */

	Cairo::Matrix get_transform_matrix();
	void 		  translate_context(Cairo::Context* context);

	Glib::RefPtr<Gdk::Window> m_refGdkWindow;
	Border m_border;
	Line m_axes_style;
	Gtk::Allocation m_min_size;
	Gtk::Label * m_title;

	// m_range_rect is use to store mininum x and y values of the graph
	// its width and height are used to determine max x and y vals.
	Gdk::Rectangle m_range_rect;

	Origin m_origin;
	DefaultVector m_def_vector;
	LabelPosition m_label_position;

	std::deque<Line2D*> m_lines;
	int m_padding_x;
	int m_padding_y;
	bool m_show_axes;
};

}

}

#endif /* AREA_H_ */
