//============================================================================
// Name        : cairo-plot.cpp
// Author      : Thibaud Fabre
// Version     :
// Copyright   : GNU General Licence v2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm-2.4/gtkmm/main.h>
#include <gtkmm-2.4/gtkmm/window.h>
#include "plot/PlotArea.h"
#include "plot/PlotContainer.h"
using namespace std;
using namespace Gtk::Plot;

int main(int argc, char** argv) {
	   Gtk::Main kit(argc, argv);

	   Gtk::Window win;
	   win.set_default_size(800, 250);

	   Gtk::HBox frame;
	   win.add(frame);

	   Border border;
	   border.color = Gdk::Color("red");

	   Area plot, plot2;
	   Gtk::Label label;

	   label.set_text("Plot area, title outside, centered origin");
	   label.set_line_wrap(true);;
	   plot.show_axes();
	   plot.set_padding(10,10);
	   plot.set_plot_border(border);
	   plot.set_plot_title_position(POSITION_OUTER);
	   plot.set_plot_title(label);


	   plot2.show_axes();
	   plot2.set_padding(10,10);
	   //plot2.set_plot_origin(BOTTOM_LEFT);
	   //plot2.set_default_vector(VECTOR_BOTTOM_LEFT);
	   //plot2.set_plot_title_position(POSITION_INNER);
	   plot2.set_plot_title("Plot area, title outside,\ncenter origin, top-right vector");

	   for (double i = 0; i < 150; i++)
	   {
		   DataPoint2D p = DataPoint2D(5+i, 8+3*i);
		   DataPoint2D p2 = DataPoint2D(10*i,100*sin(i));
		   plot.get_lines()[0]->add_data_item(p);
		   plot2.get_lines()[0]->add_data_item(p2);
	   }

	   plot.get_lines()[0]->set_color(Gdk::Color("red"));
	   plot.get_lines()[0]->set_width(1);
	   plot2.get_lines()[0]->set_color(Gdk::Color("grey"));
	   plot2.get_lines()[0]->set_width(1);
	   std::valarray<double> d = { 5 };
	   plot.get_lines()[0]->set_dash(d);

	   frame.pack_start(plot);
	   frame.pack_end(plot2);

	   plot.show();
	   plot2.show();
	   frame.show();

	   Gtk::Main::run(win);

	   return 0;
}
