/*
 * Area.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: root
 */

#include <vector>
#include <cairomm-1.0/cairomm/context.h>
#include <cairomm-1.0/cairomm/refptr.h>
#include <gdkmm-2.4/gdkmm.h>
#include <gdkmm-2.4/gdkmm/general.h>
#include <pangomm-1.4/pangomm/fontdescription.h>
#include <pangomm-1.4/pangomm/layout.h>
#include <pangomm-1.4/pangomm/types.h>
#include "PlotArea.h"
#include "Line2D.h"

namespace Gtk
{

namespace Plot
{

Area::Area() :
	Glib::ObjectBase("GtkPlotArea"),
	Gtk::Widget(),
	m_border(1, Gdk::Color("black")),
	m_min_size(0,0,250,250),
	m_title(new Gtk::Label()),
	m_range_rect(0,0,1,1),
	m_origin(CENTER),
	m_def_vector(VECTOR_TOP_RIGHT),
	m_label_position(POSITION_OUTER),
	m_lines(),
	m_padding_x(10),
	m_padding_y(10)
{
	// TODO Auto-generated constructor stub
	set_flags(Gtk::NO_WINDOW);
	m_title->set_text("Plot area");
	Line2D* line = new Line2D;
	m_lines.push_back(line);
}

Area::~Area() {
	// TODO Auto-generated destructor stub
}

//#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

void Area::on_unmap()
{
	Gtk::Widget::on_unmap();
}

void Area::on_size_request(Gtk::Requisition *requisition)
{
	*requisition = Gtk::Requisition();
	int h = (m_label_position == POSITION_INNER) ? 0 : m_title->size_request().height;
	h += m_min_size.get_height();
	int w = MAX(m_title->get_width(), m_min_size.get_width());
	requisition->height = h + m_border.width;
	requisition->width = w + m_border.width;
}

void Area::on_unrealize()
{
	m_refGdkWindow.clear();
	Gtk::Widget::on_unrealize();
}

void Area::on_size_allocate(Gtk::Allocation & allocation)
{
	set_allocation(allocation);

	if(m_refGdkWindow)
	{
		m_refGdkWindow->move_resize( allocation.get_x(), allocation.get_y(),
				allocation.get_width(), allocation.get_height() );
	}
}

void Area::on_map()
{
	Gtk::Widget::on_map();
}

void Area::on_realize()
{
	Gtk::Widget::on_realize();

	if(!m_refGdkWindow)
	{
		//Create the GdkWindow:

		GdkWindowAttr attributes;
		memset(&attributes, 0, sizeof(attributes));

		Gtk::Allocation allocation = get_allocation();

		//Set initial position and size of the Gdk::Window:
		attributes.x = allocation.get_x();
		attributes.y = allocation.get_y();
		attributes.width = allocation.get_width();
		attributes.height = allocation.get_height();

		attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK;
		attributes.window_type = GDK_WINDOW_CHILD;
		attributes.wclass = GDK_INPUT_OUTPUT;


		m_refGdkWindow = Gdk::Window::create(get_window() /* parent */, &attributes,
				GDK_WA_X | GDK_WA_Y);
		unset_flags(Gtk::NO_WINDOW);
		set_window(m_refGdkWindow);

		//set colors
		modify_bg(Gtk::STATE_NORMAL , get_style()->get_bg(Gtk::STATE_NORMAL));
		modify_fg(Gtk::STATE_NORMAL , Gdk::Color("white"));

		//make the widget receive expose events
		m_refGdkWindow->set_user_data(gobj());
	}
}

bool Area::on_expose_event(GdkEventExpose *event)
{
	if(m_refGdkWindow)
	{
		Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
		if(event)
		{
			// clip to the area that needs to be re-exposed so we don't draw any
			// more than we need to.
			cr->rectangle(event->area.x, event->area.y,
					event->area.width, event->area.height);
			cr->clip();
		}

		// paint the background
		Gdk::Cairo::set_source_color(cr, get_style()->get_bg(Gtk::STATE_NORMAL));
		cr->paint();

		double width = (double) get_allocation().get_width();
		double height = (double) get_allocation().get_height();
		int t_height, t_width;

		m_title->set_alignment(ALIGN_CENTER, ALIGN_CENTER);
		m_title->set_justify(Gtk::JUSTIFY_CENTER);
		Glib::RefPtr<Pango::Layout> pangoLayout = m_title->get_layout();
		pangoLayout->get_pixel_size(t_width, t_height);

		cr->save();

		if (m_label_position == Gtk::Plot::POSITION_OUTER)
		{
			cr->rectangle(m_padding_x+m_border.width, m_padding_y+t_height,
					width-(2*m_padding_x)-2*m_border.width, height-(2*m_padding_y)-t_height-m_border.width);
			switch (m_origin)
			{
				case TOP_LEFT:
					cr->translate(m_padding_x,m_padding_y+t_height);
					break;
				case BOTTOM_LEFT:
					cr->translate(m_padding_x, height-m_padding_y);
					break;
				case BOTTOM_RIGHT:
					cr->translate(width-m_padding_x, height-m_padding_y);
					break;
				case TOP_RIGHT:
					cr->translate(width-m_padding_x,m_padding_y+t_height);
					break;
				case CENTER:
					cr->translate((width/2)-m_padding_x, m_padding_y+(height/2));
			}
		}
		else
		{
			cr->rectangle(m_padding_x+m_border.width, m_padding_y+m_border.width,
					width-(2*m_padding_x)-2*m_border.width, height-(2*m_padding_y)-2*m_border.width);
			switch (m_origin)
			{
				case TOP_LEFT:
					cr->translate(m_padding_x, m_padding_y);
					break;
				case BOTTOM_LEFT:
					cr->translate(m_padding_x, height-m_padding_y);
					break;
				case BOTTOM_RIGHT:
					cr->translate(width-m_padding_x, height-m_padding_y);
					break;
				case TOP_RIGHT:
					cr->translate(width-m_padding_x,m_padding_y);
					break;
				case CENTER:
					cr->translate((width/2)-m_padding_x, m_padding_y+((height)/2)-0.5*t_height);
			}
		}

		Cairo::Matrix m = get_transform_matrix();
		cr->transform(m);

		if (m_border.width > 0)
		{
			Gdk::Cairo::set_source_color(cr, m_border.color);
			cr->set_line_width(m_border.width);
			cr->stroke_preserve();
		}
		Gdk::Cairo::set_source_color(cr, get_style()->get_fg(Gtk::STATE_NORMAL));
		cr->clip();
		cr->paint();

		if (m_show_axes)
		{
			cr->save();
			cr->set_source_rgb(0,0,0);
			cr->set_line_width(1);
			std::valarray<double> d = { 5 };
			cr->set_dash(d, 0);
			cr->move_to(-1000,-0.5);
			cr->line_to(1000,-0.5);
			cr->move_to(-0.5, -1000);
			cr->line_to(-0.5, 1000);
			cr->stroke();
			cr->restore();
		}

		// draw equivalent of vector(+1,+1) to check origin and direction
		std::deque<Line2D*>::iterator it;
		for (it = m_lines.begin(); it != m_lines.end(); ++it)
		{
			Line2D* p = (Line2D*) *it;
			p->draw(cr);
		}

		cr->restore();

		// draw plot title
		Gdk::Cairo::set_source_color(cr, Gdk::Color("black"));
		m_title->set_alignment(0.5, 0);
		cr->move_to(.5*width-0.5*t_width,m_padding_y);
		pangoLayout->update_from_cairo_context(cr);
		pangoLayout->add_to_cairo_context(cr);
		cr->fill();



		/*
		context->save();
		context->set_width(border_width);
		context->set_source_rgb(border_color.get_red(), border_color.get_green(),
				border_color.get_blue());

		context->stroke_preserve();
		context->set_source_rgb(fill_color.get_red(), fill_color.get_green(),
				fill_color.get_blue());
		context->fill();
		context->restore();

		// Prepare the context for line drawing.
		// We want to be sure that the context is set up so that the lines
		// get drawn within the plot area, do not overflow, and that x and y
		// values get correctly plotted (by default, cairo origin is top-left corner
		// in a plotting environment, it is generally bottom-left.
		context->save();

		// TODO Improve this ugly piece of...

		// Iterate over lists and get min/max values to scale context.
		double max_x = std::numeric_limits<double>::min();
		double max_y = std::numeric_limits<double>::min();
		double min_x = std::numeric_limits<double>::max();
		double min_y = std::numeric_limits<double>::max();

		std::list<PlotLine2D>::iterator it;
		for (it = lines.begin(); it  != lines.end(); ++it)
		{
			PlotLine2D r_line = (PlotLine2D) *it;
			double r_max_x = r_line.get_max_x();
			double r_max_y = r_line.get_max_y();
			double r_min_x = r_line.get_min_x();
			double r_min_y = r_line.get_min_y();

			if (r_max_x > max_x) max_x = r_max_x;
			if (r_max_y > max_y) max_y = r_max_y;
			if (r_min_x < min_x) min_x = r_min_x;
			if (r_min_y < min_y) min_y = r_min_y;
		}

		// Set origin to plot area boundaries
		context->translate(position.left+0.5*border_width, size.height+position.top-0.5*border_width);
		std::cout << "height : " << size.height << " ; width : " << size.width << std::endl;

		// Flip y axis
		Cairo::Matrix m = Cairo::Matrix(1.0, 0.0,
				0.0, -1.0,
				0.0, 0.0);
		context->transform(m);

		// Clip the region to prevent drawing outside of area
		context->set_width(1.0);
		context->set_source_rgb(1,0,0);
		context->rectangle(0, 0, (size.width-border_width)*9/10, (size.height-border_width)*9/10);
		context->stroke();
		//context->clip();

		// Scale the context
		if (lines.max_size() > 0)
		{
			double scale_x = floor(10*((size.width*0.9)/(max_x-min_x)))/10;
			double scale_y = floor(10*((size.height*0.9)/(max_y-min_y)))/10;

			if (scale_x != 0 && scale_y != 0)
			{
				context->scale(scale_x, scale_y);
			}
			context->translate(-min_x, -min_y);

			// Call draw for method for each line in this area
			// This is done outside of the save/restore pair, since lines (normally) call save/restore
			// on their own.
			for (it = lines.begin(); it  != lines.end(); ++it)
			{
				PlotLine2D r_line = (PlotLine2D) *it;
				r_line.draw(context);
			}
		}
		context->restore();
		*/
	}
	return true;
}

std::deque<Line2D*> Area::get_lines()
{
	return m_lines;
}

Cairo::Matrix Area::get_transform_matrix()
{
	// FIXME for now this function prepares the transformation
	// regardless of the vector direction.
	Cairo::Matrix matrix;
	switch (m_def_vector)
	{
		case VECTOR_TOP_LEFT:
			matrix = Cairo::Matrix(-1.0, 0.0,
					0.0, -1.0,
					0.0, 0.0);
			break;
		case VECTOR_BOTTOM_LEFT:
			matrix = Cairo::Matrix(-1.0, 0.0,
					0.0, 1.0,
					0.0, 0.0);
			break;
		case VECTOR_BOTTOM_RIGHT:
			matrix = Cairo::Matrix(1.0, 0.0,
					0.0, 1.0,
					0.0, 0.0);
			break;
		case VECTOR_TOP_RIGHT:
			matrix = Cairo::Matrix(1.0, 0.0,
					0.0, -1.0,
					0.0, 0.0);
			break;
	}
	return matrix;
}

void Area::set_default_vector(DefaultVector vector)
{
	m_def_vector = vector;
}

void Area::set_mininum_size(double width, double height)
{
	m_min_size.set_height(height);
	m_min_size.set_width(width);
}

void Area::set_padding(double x, double y)
{
	m_padding_x = x;
	m_padding_y = y;
}

void Area::set_plot_border(Border border)
{
	m_border = border;
}

void Area::set_plot_origin(Origin origin)
{
	m_origin = origin;
}

void Area::set_plot_title(Gtk::Label& title)
{
	m_title = &title;
}

void Area::set_plot_title(std::string title)
{
	m_title->set_text(title);
}

void Area::set_plot_title_position(Gtk::Plot::LabelPosition pos)
{
	m_label_position = pos;
}

void Area::hide_axes()
{
	m_show_axes = false;
}

void Area::show_axes()
{
	m_show_axes = true;
}

//#endif

}

}

