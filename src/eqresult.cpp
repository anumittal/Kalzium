/***************************************************************************
 *   Copyright (C) 2004 by Thomas Nagy                                     *
 *   tnagy2^8@yahoo.fr                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qtimer.h>
#include <qpainter.h>
#include <qsimplerichtext.h>
#include <qcolor.h>

#include <kdebug.h>

#include "eqresult.h"

// inspired by speedcrunch

class questionitem : public QListBoxItem
{
    public:
	questionitem( QListBox*, const QString&, QColor bg );
    protected:
	void paint( QPainter* p );
	int width( const QListBox* ) const;
	int height( const QListBox* ) const;
    private:
	QString m_msg;
	QColor m_bgcolor;
};

class answeritem : public QListBoxItem
{
    public:
	answeritem(  QListBox*, const QString&, const QString&, QColor bg );
	~answeritem() { delete m_richtext; }
	void checkSize();
    protected:
	void paint( QPainter* p );
	int width( const QListBox* ) const;
	int height( const QListBox* ) const;
    private:
	QString m_msg;
	QString m_origmsg;
	QColor m_bgcolor;
	QSimpleRichText * m_richtext;
};

questionitem::questionitem( QListBox* listBox, const QString& e, QColor bg ):
QListBoxItem ( listBox )
{
    m_msg = e;
    m_bgcolor = bg;
}

answeritem::answeritem( QListBox* listBox, const QString& e, const QString &r, QColor bg ):
QListBoxItem ( listBox )
{
    m_msg = "<p align=\"right\">"+r+"</p>";
    m_origmsg = e;
    m_bgcolor = bg;
    m_richtext = new QSimpleRichText(m_msg, listBox->font());
    m_richtext->setWidth( listBox->width() );
}

void questionitem::paint( QPainter* painter )
{
    int tf = Qt::NoAccel | Qt::SingleLine | Qt::AlignVCenter;

    QRect r ( 0, 0, listBox()->contentsWidth(), height( listBox() ) );
    painter->fillRect( r, m_bgcolor );
    painter->drawText( r, tf, m_msg );
}

void answeritem::paint( QPainter* painter )
{
    checkSize();

    QRect r ( 0, 0, listBox()->contentsWidth(), height( listBox() ) );
    painter->fillRect( r, m_bgcolor );

    QColorGroup cg = listBox()->colorGroup();
    cg.setColor( QColorGroup::Background, m_bgcolor );

    m_richtext->draw(painter, 0, 0, r, cg );
}

int questionitem::width( const QListBox*lb ) const
{
    QFont font = lb->font();
    return QFontMetrics( font ).width( m_msg );
}

int questionitem::height( const QListBox*lb ) const
{
    QFont font = lb->font();
    return QFontMetrics( font ).height() + 4;
}

int answeritem::width( const QListBox* ) const
{
    return m_richtext->width();
}

int answeritem::height( const QListBox* ) const
{
    return m_richtext->height();
}

void answeritem::checkSize()
{
    QFont font = listBox()->font();
    int t1 = QFontMetrics( font ).width( m_origmsg+"padding" );
    int t2 = listBox()->width() - 20;

    // take the maximum
    m_richtext->setWidth(   (t1>t2)?t1:t2   );
}

eqresult::eqresult(QWidget *parent) : QListBox(parent)
{
    m_alternate_color = false;
    setMinimumWidth(140);
}

eqresult::~eqresult()
{
}

void eqresult::add(const QString & question, const QString & answer)
{
    QColor bgcolor = colorGroup().base();

    if ( m_alternate_color )
	bgcolor = bgcolor.dark( 120 );

    m_alternate_color = !m_alternate_color;

    new questionitem( this, question, bgcolor );
    new answeritem( this, question, answer, bgcolor );

    QTimer::singleShot( 100, this, SLOT( scrollToEnd() ) );
}

void eqresult::scrollToEnd()
{
    ensureVisible( 0, contentsHeight()-1 );
}

void eqresult::resizeEvent( QResizeEvent* )
{
    triggerUpdate( true );
}

#include "eqresult.moc"
