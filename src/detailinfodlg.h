/***************************************************************************

        detailedinfodlg.h  -  description
                             -------------------
    begin                : Tue Apr 2 20:43:44 2002 UTC
    copyright            : (C) 2003, 2004 by Carsten Niehaus
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

#ifndef _DETAILINFODLG_H_
#define _DETAILINFODLG_H_

#include <kdialogbase.h>

class DetailedGraphicalOverview;
class Element;
class KalziumDataObject;
class OrbitsWidget;

class QMouseEvent;
class QFrame;
class QVBoxLayout;

/**
 * @short The dialog which shows all available information
 * @author Carsten Niehaus
 */
class DetailedInfoDlg : public KDialogBase
{
    Q_OBJECT
    
	public:
        DetailedInfoDlg( KalziumDataObject* data, Element *el , QWidget *parent=0, const char *name=0);
 
	    void setElement(Element *el);

		enum DATATYPE
		{
			CHEMICAL = 0,
			MISC,
			ENERGY
		};
	
	private:
		KalziumDataObject  *m_data;
		Element            *m_element;

		QString isotopeTable();
		QString isotopeRow( const QString& str );
		
		QFrame *m_pOverviewTab,
			*m_pPictureTab,
			*m_pModelTab;
		
		QLabel *piclabel;

		QVBoxLayout *miscLayout, 
					*mainLayout,
					*overviewLayout;

		///holds the pointers to all pages of the dialog
		QValueList<QFrame*> m_pages;

		DetailedGraphicalOverview *dTab;

		OrbitsWidget *wOrbits;

		/**
		 * create the tabs.
		 */
		void createContent( Element *e );

		QString getHtml(DATATYPE);

		QString m_baseHtml;

		/**
		 * @param htmlcode The code which will be displayed
		 * @param title The title of the tab, appears above the htmlview
		 * @param icontext The name of the tab, appears belov or instead of the icon
		 * @param iconname The name of the icon
		 */
		void addTab( const QString& htmlcode, const QString& title, const QString icontext, const QString iconname );
	
	protected slots:
		virtual void slotUser1();
		virtual void slotUser2();

	protected:
		virtual void wheelEvent (  QWheelEvent * ev );
};
#endif
