/*
 * DrawableData.h
 *
 *  Created on: Mar 24, 2010
 *      Author: root
 */

#ifndef DRAWABLEDATA_H_
#define DRAWABLEDATA_H_

#include <deque>
#include <cairomm-1.0/cairomm/context.h>
#include <cairomm-1.0/cairomm/refptr.h>
#include "types.h"

namespace Gtk {

namespace Plot {

template <typename T>
class DrawableData : public Drawable {
public:
	DrawableData() :
		m_marker_style(MARKER_DEFAULT)
	{
		;
	};
	virtual ~DrawableData() { };

	// Add an item to the stack
	virtual int	 add_data_item(T item);
	// Retrieve an item by its numeric index
	virtual T	 get_data_item(int index);
	// Remove a data item by its numeric index
	virtual T	 remove_data_item(int index);

	// Draw the data
	// Note that that the context object passed to this
	// method should already be prepared (sized, etc)
	// as this method should only handle its own layout.
	virtual void draw(Cairo::RefPtr<Cairo::Context> cr) { };
protected:
	std::deque<T> m_data_set;
	MarkerStyle m_marker_style;

};

template<typename T> inline int Gtk::Plot::DrawableData<T>::add_data_item(T item)
{
	m_data_set.push_back(item);
	return m_data_set.size()-1;
}



template<typename T> inline T Gtk::Plot::DrawableData<T>::get_data_item(int index)
{
	if (index >= 0 && index < (signed)m_data_set.size())
		return m_data_set[index];
	throw std::out_of_range("Index out of range");
}



template<typename T> inline T Gtk::Plot::DrawableData<T>::remove_data_item(int index)
{
	if (index >= 0 && index < (signed)m_data_set.size())
	{
		T item = m_data_set[index];
		m_data_set.erase(m_data_set.begin()+index);
		return item;
	}
	throw std::out_of_range("Index out of range");
}

}

}

#endif /* DRAWABLEDATA_H_ */
