/*
 * Line2D.cpp
 *
 *  Created on: Mar 24, 2010
 *      Author: root
 */
#include <iostream>
#include <gdkmm-2.4/gdkmm.h>
#include <gdkmm-2.4/gdkmm/general.h>
#include "Line2D.h"

namespace Gtk {

namespace Plot {

Line2D::Line2D() :
		DrawableData<DataPoint2D>(),
		m_color(Gdk::Color("black")),
		m_dash(),
		m_width(1)
{

}

Line2D::~Line2D()
{
}

void Line2D::draw(Cairo::RefPtr<Cairo::Context> cr)
{
	cr->save();
	Gdk::Cairo::set_source_color(cr, m_color);
	cr->set_dash(this->m_dash, 0);
	//std::cout << this->m_dash[0] << std::endl;
	cr->set_line_width(m_width);

	std::deque<DataPoint2D>::iterator it;
	int i = 0;
	for (i = 0; i != (signed)m_data_set.size(); ++i)
	{
		DataPoint2D p = (DataPoint2D) m_data_set[i];
		if (i == 0)
			cr->move_to(p.x, p.y);
		else
			cr->line_to(p.x, p.y);
	}
	cr->stroke();

	for (it = m_data_set.begin(); it != m_data_set.end(); ++it)
	{
		DataPoint2D p = (DataPoint2D) *it;
		//p.draw(cr);
	}
	cr->restore();
}

Gdk::Color* Line2D::get_color()
{
	return &m_color;
}

std::valarray<double>* Line2D::get_dash()
{
	return &m_dash;
}

double* Line2D::get_width()
{
	return &m_width;
}

void Line2D::set_color(Gdk::Color color)
{
	m_color = color;
}

void Line2D::set_dash(std::valarray<double> dash)
{
	this->m_dash = std::valarray<double>(dash);
}

void Line2D::set_width(double width)
{
	if (width > 0)
		m_width = width;
}

}

}
