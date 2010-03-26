/*
 * Container.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: root
 */

#include "PlotContainer.h"

namespace Gtk
{

namespace Plot
{

Container::Container()
{
	m_plot = new Area;
}

Container::~Container()
{
	set_flags(Gtk::NO_WINDOW);
	set_redraw_on_allocate(false);
}

void Container::set_plot_widget(Area & p_widget)
{
	m_plot = &p_widget;
	m_plot->set_parent(*this);
}

void Container::on_add(Area* child)
{
	if (!m_plot)
	{
		m_plot = child;
		m_plot->set_parent(*this);
	}
}

void Container::on_remove(Area* child)
{
	if (child)
	{
		const bool visible = child->get_visible();
		if(child == m_plot)
		{
			m_plot = 0;
			child->unparent();
			if(visible)
				queue_resize();
		}
	}
}

GType Container::child_type_vfunc() const
{
	if (!m_plot)
		return Area::get_type();
	else
	{
		return G_TYPE_NONE;
	}
}

void Container::forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data)
{
	if(m_plot)
		callback(m_plot->gobj(), callback_data);
}

void Container::on_size_allocate(Gtk::Allocation & allocation)
{
	m_plot->size_allocate(allocation);
}

void Container::on_size_request(Gtk::Requisition* requisition)
{
	//Initialize the output parameter:
	*requisition = Gtk::Requisition();

	Gtk::Requisition plot_requisition = {0, 0};
	if(m_plot && m_plot->get_visible())
	{
		plot_requisition = m_plot->size_request();
	}

	requisition->height = plot_requisition.height;
	requisition->width = plot_requisition.width;
}

}

}

