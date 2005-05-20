#ifndef INFORMATIONDIALOG_IMPL_H
#define INFORMATIONDIALOG_IMPL_H

#include "informationdialog.h"

#include <qtabwidget.h>
#include <qpoint.h>
#include <qdom.h>
#include <qstring.h>
#include <qevent.h>

class PSE;

class InformationWidget : public InformationDialog
{
	Q_OBJECT

	public:
		InformationWidget( PSE *pse );

		void showSOM(){
			tabWidget->setCurrentPage( 1 );
		}

		void showTimeline(){
			tabWidget->setCurrentPage( 2 );
		}

	private:
		///returns the text formated as html
		QString getDesc(QPoint);

		PSE *m_pse;

	public slots:
		void closeEvent(QCloseEvent*e);
		void slotUpdate( QPoint point );

		void slotDate( int );

		void tabSelected( QWidget* );

	signals:
		void closed();
};

class QuizXMLParser
{
	public: 
		QuizXMLParser();

		QString readTasks( QDomDocument &questionDocument, int number );
		bool loadLayout( QDomDocument &questionDocument, const QString& filename );
};

#endif // INFORMATIONDIALOG_IMPL_H
