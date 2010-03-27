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

	/// Gets the line collection storing the data to plot.
	/**
	* @return <tt>std::deque<Line2D*></tt> if the widget has data lines.
	* @exception out_of_range if the index is not found or collection is empty.
	*/
	std::deque<Line2D*> get_lines();
	/// Sets the default vector for the graph.
	/**
	* @param vector (VECTOR_TOP_RIGHT) : the vector direction to use as the default vector.
	* @return void
	*/
	void set_default_vector(DefaultVector vector = VECTOR_TOP_RIGHT);
	/// Sets the mininum size of the plot area, inclusive of margins, padding and so on
	/**
	* @param width : the mininum width of the area in pixels.
	* @param height : the mininum height of the area in pixels.
	* @return void
	*/
	void set_mininum_size(double width, double height);
	/// Sets the mininum/maximum data values to plot.
	/**
	* @param xmin : the mininum x value to plot
	* @param ymin : the mininum y value to plot
	* @param xmax : the maximum x value to plot
	* @param ymax : the maximum y value to plot
	* @return void
	*/
	void set_mininum_range(double xmin, double ymin, double xmax, double ymax);
	/// Sets the padding of the area.
	/**
	* @param x : padding to apply left and right of the plot
	* @param y : padding to apply on top and bottom of the plot
	* @return void
	*/
	void set_padding(double x, double y);
	/// Sets the border of the plot itself (not of the area).
	/*
	* @param border : A <b>Gtk::Plot::Border</b> object to use as the border
	* @return void
	*/
	void set_plot_border(Gtk::Plot::Border border);
	void set_plot_origin(Origin origin);
	void set_plot_title(Gtk::Label& title);
	void set_plot_title(std::string title);
	void set_plot_title_position(Gtk::Plot::LabelPosition pos);
	/// Hides the data axes
	void hide_axes();
	/// Shows the data axes
	void show_axes();

protected:
	//#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
	//Overrides:
	virtual void on_size_request(Gtk::Requisition* requisition);
	virtual void on_size_allocate(Gtk::Allocation& allocation);
	virtual void on_map();
	virtual void on_unmap();
	virtual void on_realize();
	virtual void on_unrealize();
	/**
	* This is where the drawing takes place. You'll likely not want to change this :)
	* @param event : a pointer to the expose event of the widget.
	* @return <tt>true</tt> if success.
	*/
	virtual bool on_expose_event(GdkEventExpose* event);
	//#endif
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
