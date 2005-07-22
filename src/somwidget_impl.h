#ifndef SOMWIDGET_IMPL_H
#define SOMWIDGET_IMPL_H
/***************************************************************************
    copyright            : (C) 2005 by Carsten Niehaus
    email                : cniehaus@kde.org
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "somwidget.h"

class Element;

/**
 * @class SOMWidgetIMPL
 * @author Carsten Niehaus
 * @author Pino Toscana
 *
 * The SOMWidgetIMPL provides a QSlider. When this slider ist moved
 * it will display which elements have similat boiling- and 
 * meltingoints (compared to the temperature the user entered using 
 * the slider )
 */
class SOMWidgetIMPL : public SOMWidget
{
	Q_OBJECT

	public:
		/**
		 * @param parent The parent of this widget
		 * @param name The name of this widget
		 */
		SOMWidgetIMPL( QWidget *parent = 0, const char* name = 0 );

	private:
		QValueList<Element*> m_list;
		QString m_htmlBegin;
		QString m_htmlEnd;

	private slots:
		/**
		 * in this slot the elements will be compared with 
		 * the given temperature. The content of the html
		 * will be generated
		 */
		void slotTemp( int temp );
};
#endif // SOMWIDGET_IMPL_H
