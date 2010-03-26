/*
 * Container.h
 *
 *  Created on: Mar 23, 2010
 *      Author: root
 */

#ifndef PLOT_CONTAINER_H_
#define PLOT_CONTAINER_H_
#include <gtk-2.0/gtk/gtkobject.h>
#include <gtkmm-2.4/gtkmm/container.h>
#include <gtkmm-2.4/gtkmm/widget.h>
#include "PlotArea.h"

namespace Gtk
{

namespace Plot
{


class Container : public Gtk::Container
{
public:
	Container();
	virtual ~Container();

	void set_plot_widget(Area& p_widget);

protected:
	Gtk::Widget * m_plot;

	virtual GType child_type_vfunc() const;
	virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);

	virtual void on_add(Area* child);
	virtual void on_remove(Area* child);
	virtual void on_size_allocate(Gtk::Allocation& allocation);
	virtual void on_size_request(Gtk::Requisition* requisition);
};

}

}

#endif /* PLOT_CONTAINER_H_ */
