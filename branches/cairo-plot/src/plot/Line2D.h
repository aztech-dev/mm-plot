/*
 * Line2D.h
 *
 *  Created on: Mar 24, 2010
 *      Author: root
 */

#ifndef LINE2D_H_
#define LINE2D_H_

#include "types.h"
#include "DrawableData.h"

namespace Gtk {

namespace Plot {

class Line2D : public DrawableData<DataPoint2D> {
public:
	Line2D();
	virtual ~Line2D();

	void draw(Cairo::RefPtr<Cairo::Context> cr);
	Gdk::Color* get_color();
	std::valarray<double>* get_dash();
	double*		get_width();
	void		set_color(Gdk::Color color);
	void		set_dash(std::valarray<double> dash);
	void		set_width(double width);
protected:

	Gdk::Color m_color;
	std::valarray<double> m_dash;
	double	   m_width;
};

}

}

#endif /* LINE2D_H_ */
