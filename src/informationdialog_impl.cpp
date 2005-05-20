#include "informationdialog_impl.h"

#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qtextbrowser.h>

#include <klocale.h>
#include <kstandarddirs.h>
#include <kdebug.h>
#include <kfiledialog.h>
#include <kmessagebox.h>
#include <kdebug.h>

#include "pse.h"


InformationWidget::InformationWidget( PSE *pse )
	: InformationDialog( )
{
	m_pse = pse;
	buttonGroup->setButton( 0 );
}

void InformationWidget::closeEvent(QCloseEvent* e)
{
	QWidget::closeEvent(e);
	m_pse->setFullDraw();
	m_pse->setTimeline( false );
	m_pse->activateSOMMode( false );
	emit closed();
}

void InformationWidget::slotUpdate( QPoint point )
{
	kdDebug() << "InformationWidget::slotUpdate" << endl;
	QString appBaseDir = KGlobal::dirs()->findResourceDir("data", "kalzium/data/" );
	appBaseDir.append("kalzium/data/");
	appBaseDir.append("bg.jpg");
	QString htmlcode = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\"><html><body background=\"" ;
	htmlcode.append( appBaseDir );
	htmlcode.append("\">");

	QString content = getDesc( point );

	htmlcode.append( content );

	htmlcode.append( "</body></html>" );

	m_explanation->setText( htmlcode );
}

QString InformationWidget::getDesc( QPoint point )
{
	QString information;
	QString fn;
	int position = 0;
	
	if ( buttonGroup->selectedId() == 0 ){
		fn = "groups.xml";
		position = point.x();
	}
	else
	{
		fn = "periods.xml";
		position = point.y();
	}

	kdDebug() << "Position: " << position << endl;

	QuizXMLParser parser;
	QDomDocument doc(  "periods" );
	
	if ( parser.loadLayout( doc, fn ) )
		information = parser.readTasks( doc, position );

	return information;
}

QuizXMLParser::QuizXMLParser()
{
}

bool QuizXMLParser::loadLayout( QDomDocument &questionDocument, const QString& filename )
{
        KURL url;
        url.setPath( locate("data", "kalzium/data/"));
		url.setFileName( filename );

        QFile layoutFile( url.path() );

        if (!layoutFile.exists())
        {
                KMessageBox::information( 0, i18n("Error"), i18n( "Loading File - Error" ) );
        }

		//TODO really needed?
        if (!layoutFile.open(IO_ReadOnly))
                return false;

        ///Check if document is well-formed
        if (!questionDocument.setContent(&layoutFile))
        {
                kdDebug() << "wrong xml" << endl;
                layoutFile.close();
                return false;
        }
        layoutFile.close();

        return true;
}

QString QuizXMLParser::readTasks( QDomDocument &questionDocument, int number )
{
        QDomNodeList taskList;             //the list of all tasks

		QString html;

        QDomElement taskElement; //a single task

        //read in all tasks
        taskList = questionDocument.elementsByTagName( "unit" );

        for ( uint i = 0; i < taskList.count(); ++i )
        {//iterate through all tasks
                taskElement = ( const QDomElement& ) taskList.item( i ).toElement();
                 if ( taskElement.attributeNode( "number" ).value().toInt() != number )
 					continue;

				QDomNode contentNode = taskElement.namedItem( "content" );
				QDomNode nameNode = taskElement.namedItem( "name" );
				html = contentNode.toElement().text();

				QString headercode = "<h2>";
				headercode.append( nameNode.toElement().text() );
				headercode.append( "</h2>" );
				
				html.prepend( headercode );
        }
        
	return html;
}

void InformationWidget::tabSelected( QWidget* /*w*/ )
{
	if ( tabWidget->currentPageIndex() == 1 )
		m_pse->setTimeline( true );
	else
		m_pse->setTimeline( false );

	if ( tabWidget->currentPageIndex() == 2 )
		m_pse->activateSOMMode( true );
	else
		m_pse->activateSOMMode( false );

	m_pse->setFullDraw();

	kdDebug() << tabWidget->currentPageIndex() << endl;
}

void InformationWidget::slotDate(int date)
{
	kdDebug() << date << endl;
	m_pse->setDate( date );
}
