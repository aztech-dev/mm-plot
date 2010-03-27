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

	/**
	 * @brief Pushes a data item onto the drawable stack
	 * @param item : item to push.
	 */
	virtual int	 add_data_item(T item);
	/**
	 * @brief Retrieves a data item from the drawable stack
	 * @param index : the item's index on the stack as returned
	 * by the add() method.
	 * @return T : a data object of type T, as specified in constructor.
	 * * @exception out_of_range if item was not found.
	 */
	virtual T	 get_data_item(int index);
	/**
	 * @brief Removes a data item from the drawable stack
	 * @param index : the item's index on the stack as returned
	 * by the add() method.
	 * @return T : a data object of type T, as specified in constructor, if remove was successfull
	 * @exception out_of_range if item was not found.
	 */
	virtual T	 remove_data_item(int index);

	/**
	 * @brief Draw the data
	 * @details Note that that the context object passed to this
	 * method should already be prepared (sized, etc)
	 * as this method should only handle its own layout.
	 * @param cr : the cairo context to draw with.
	 */
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
