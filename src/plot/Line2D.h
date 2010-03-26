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
};

}

}

#endif /* LINE2D_H_ */
