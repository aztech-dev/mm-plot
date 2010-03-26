/*
 * Line2D.cpp
 *
 *  Created on: Mar 24, 2010
 *      Author: root
 */

#include "Line2D.h"

namespace Gtk {

namespace Plot {

Line2D::Line2D() : DrawableData<DataPoint2D>()
{

}

Line2D::~Line2D()
{
}

void Line2D::draw(Cairo::RefPtr<Cairo::Context> cr)
{
	cr->save();
	cr->set_source_rgb(0.8,0.5,0);
	cr->set_line_width(1);

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

}

}
