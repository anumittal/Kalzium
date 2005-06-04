/***************************************************************************
 *   Copyright (C) 2003 by Carsten Niehaus                                 *
 *   cniehaus@kde.org                                                      *
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
#include "pse.h"
#include "prefs.h"
#include "element.h"

#include <klocale.h>
#include <kdebug.h>
#include <kpixmapeffect.h>
#include <kimageeffect.h>

#include <qimage.h>
#include <qstring.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qcursor.h>
#include <qpainter.h>
#include <qcolor.h>
#include <qrect.h>

PSE::PSE(KalziumDataObject *data, QWidget *parent, const char *name)
  : QWidget(parent, name), table(0), table2(0)
{
	d = data;

	connect( this, SIGNAL( tableClicked( QPoint ) ), this, SLOT( slotUpdatePoint( QPoint ) ) );
	connect( this, SIGNAL( ToolTip( int ) ), this, SLOT( slotToolTip( int ) ) );
	connect(  &HoverTimer, SIGNAL(  timeout() ), this, SLOT(  slotTransientLabel() ) );

	setMouseTracking( true );
  
  //JH: eliminates flicker on redraw
  setBackgroundMode( QWidget::NoBackground );
 
	m_molcalcIsActive = false;
	m_learningMode = false;
	m_showTooltip = true;
	m_timeline = false;
	m_showSOM = false;
	m_showGradient = false;
	
	showLegend( Prefs::showlegend() );

	reloadColours();

	//IUPAC
	m_IUPAClist.append( "IA");
	m_IUPAClist.append( "IIA");
	m_IUPAClist.append( "IIIB");
	m_IUPAClist.append( "IVB");
	m_IUPAClist.append( "VB");
	m_IUPAClist.append( "VIB");
	m_IUPAClist.append( "VIIB");
	m_IUPAClist.append( "VIII");
	m_IUPAClist.append( "VIII");
	m_IUPAClist.append( "VIII");
	m_IUPAClist.append( "IB");
	m_IUPAClist.append( "IIB");
	m_IUPAClist.append( "IIIA");
	m_IUPAClist.append( "IVA");
	m_IUPAClist.append( "VA");
	m_IUPAClist.append( "VIA");
	m_IUPAClist.append( "VIIA");
	m_IUPAClist.append( "VIIIA");

	//oldIUPAC
	m_IUPACOLDlist.append( "1A");
	m_IUPACOLDlist.append( "2A");
	m_IUPACOLDlist.append( "3A");
	m_IUPACOLDlist.append( "4A");
	m_IUPACOLDlist.append( "5A");
	m_IUPACOLDlist.append( "6A");
	m_IUPACOLDlist.append( "7A");
	m_IUPACOLDlist.append( "8");
	m_IUPACOLDlist.append( "8");
	m_IUPACOLDlist.append( "8");
	m_IUPACOLDlist.append( "1B");
	m_IUPACOLDlist.append( "2B");
	m_IUPACOLDlist.append( "3B");
	m_IUPACOLDlist.append( "4B");
	m_IUPACOLDlist.append( "5B");
	m_IUPACOLDlist.append( "6B");
	m_IUPACOLDlist.append( "7B");
	m_IUPACOLDlist.append( "0");

	table = new QPixmap();
	table2 = new QPixmap();

	//JH: Start with a full draw
	doFullDraw = true;
}

void PSE::reloadColours()
{
	color_s = Prefs::block_s();
	color_p = Prefs::block_p();
	color_d = Prefs::block_d();
	color_f = Prefs::block_f();
	color_1 = Prefs::group_1();
	color_2 = Prefs::group_2();
	color_3 = Prefs::group_3();
	color_4 = Prefs::group_4();
	color_5 = Prefs::group_5();
	color_6 = Prefs::group_6();
	color_7 = Prefs::group_7();
	color_8 = Prefs::group_8();
	color_ba = Prefs::beh_basic();
	color_ac = Prefs::beh_acidic();
	color_neu = Prefs::beh_neutral();
	color_amp = Prefs::beh_amphoteric();
	c_alkalie = Prefs::alkalie();
	c_rare = Prefs::rare();
	c_nonmetal = Prefs::nonmetal();
	c_alkaline = Prefs::alkaline();
	c_other_metal = Prefs::other_metal();
	c_halogene = Prefs::halogene();
	c_transition = Prefs::transition();
	c_noble_gas = Prefs::noble_gas();
	c_metalloid = Prefs::metalloid();
}

void PSE::slotToolTip( int number )
{
	if ( !m_showTooltip ) return; //don't update if the table is locked
	m_tooltipElementNumber = number;
	update();
}

PSE::~PSE(){}

void PSE::activateColorScheme( const int nr )
{
	m_currentScheme = nr;
	
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	if ( m_currentScheme == PSE::NOCOLOUR ) //normal view, no colors
	{
		const QColor color = Prefs::noscheme();
		while ( it != itEnd )
		{
			( *it )->setElementColor( color );
			++it;
		}
	}
	else if ( m_currentScheme == PSE::GROUPS ) //groups view
	{

		static QString group;

		while ( it != itEnd )
		{
			group = ( *it )->group();
			
			if (group == QString("1")) {
				( *it )->setElementColor( color_1 );
			}
			if (group == QString("2")){
				( *it )->setElementColor( color_2 );
			}
			if (group == QString("3")){
				( *it )->setElementColor( color_3 );
			}
			if (group == QString("4")){
				( *it )->setElementColor( color_4 );
			}
			if (group == QString("5")){
				( *it )->setElementColor( color_5 );
			}
			if (group == QString("6")){
				( *it )->setElementColor( color_6 );
			}
			if (group == QString("7")){
				( *it )->setElementColor( color_7 );
			}
			if (group == QString("8")){
				( *it )->setElementColor( color_8 );
			}

			++it;
		}
	}
	else if ( m_currentScheme == PSE::BLOCK ) //block view
	{
		static QString block;
		while ( it != itEnd )
		{
			block = (*it)->block();

			if (block == QString("s")) {
				(*it)->setElementColor( color_s );
			}
			if (block == QString("p")) {
				(*it)->setElementColor( color_p );
			}
			if (block == QString("d")) {
				(*it)->setElementColor( color_d );
			}
			if (block == QString("f")) {
				(*it)->setElementColor( color_f );
			}
			++it;
		}
	}
	else if ( m_currentScheme == PSE::ACIDIC ) //acidic beh
	{
		static QString acidicbeh;
		
		while ( it != itEnd )
		{
			acidicbeh = ( *it )->acidicbeh();

			if (acidicbeh == QString("0")) {
				(*it)->setElementColor( color_ac );
			}
			if (acidicbeh == QString("1")){
				(*it)->setElementColor( color_ba );
			}
			if (acidicbeh == QString("2")){
				(*it)->setElementColor( color_neu );
			}
			if (acidicbeh == QString("3")){
				(*it)->setElementColor( color_amp );
			}
			++it;
		}
	}
	else if ( m_currentScheme ==  PSE::FAMILY ) //familiy of the element
	{
		static QString family;

		while ( it != itEnd )
		{
			family = ( *it )->family();

			if ( family == "Noblegas" ){
				(*it)->setElementColor( c_noble_gas );
			}
			if ( family == "Non-Metal" ){
				(*it)->setElementColor( c_nonmetal );
			}
			if ( family == "Rare_Earth" ){
				(*it)->setElementColor( c_rare );
			}
			if ( family == "Alkaline_Earth" ){
				(*it)->setElementColor( c_alkaline );
			}
			if ( family == "Alkali_Earth" ){
				(*it)->setElementColor( c_alkalie );
			}
			if ( family == "Transition" ){
				(*it)->setElementColor( c_transition );
			}
			if ( family == "Other_Metal" ){
				(*it)->setElementColor( c_other_metal );
			}
			if ( family == "Metalloids" ){
				(*it)->setElementColor( c_metalloid );
			}
			if ( family == "Halogene" ){
				(*it)->setElementColor( c_halogene );
			}
			
			++it;
		}
	}
		
}

void PSE::resizeEvent( QResizeEvent * /*e*/ ) 
{
  table->resize( width(), height() );
  table2->resize( width(), height() );
  // XXX: I know it isn't the best way, but otherwise the table won't be redrawn
  // on repaint... Feel *free* to remove these two lines if you foind a better
  // solution...
  doFullDraw = true;
  update();
}

void PSE::paintEvent( QPaintEvent * /*e*/ )
{
	QPainter p;

  //JH: I have split the drawing into two pixmaps: table and table2.
  //table contains the "static" PSE table, and does not change very often.
  //table2 contains the tooltips and any other dynamic overlays.
  //Usually, we can skip the code which renders the table, and just use the 
  //image stored in table...when doFullDraw==false, the rendering code is skipped.
  if ( doFullDraw ) 
  {
	  //DEBUG
	  kdDebug() << "Drawing full table" << endl;

	  p.begin( table );
	  p.fillRect( 0, 0, width(), height(), paletteBackgroundColor() ); 

	  drawNumeration( &p );
	  
	  if ( m_timeline ){ //use timeline
		  drawTimeLine(& p );
		  p.end();

		  *table2 = *table;
		  bitBlt( this, 0, 0, table2 );
		  return;
	  }
	  if ( som() ){//use state of matter
		  drawSOMPSE(& p );
		  p.end();

		  *table2 = *table;
		  bitBlt( this, 0, 0, table2 );
		  return;
	  }
	  if ( gradient() ){//show a gradient
		  calculateGradient(& p );
		  p.end();

		  *table2 = *table;
		  bitBlt( this, 0, 0, table2 );
		  return;
	  }
	  if ( m_currentScheme == CRYSTAL ){//show the crystal structure
		  drawCrystal(& p );
		  p.end();

		  *table2 = *table;
		  bitBlt( this, 0, 0, table2 );
		  return;
	  }
	  drawPSE( &p );

	  if ( m_showLegend )
		  drawLegend( &p );
	  
	  if ( !showTooltip() ){
		paintCurrentSelection( &p );
	  }
	  

	  p.end();

	  doFullDraw = false;
  }

  //JH: Ok, now table contains the static PSE table, and we may need to draw
  //a tooltip on it.  However, we don't want to ruin the stored table pixmap, 
  //so let's copy it to table2 and add the tooltip there.
  *table2 = *table;
 
  if ( m_showTooltip )
  {
    if ( m_tooltipElementNumber < 112 && m_tooltipElementNumber > 0 )
    {
      QPainter p2;
      p2.begin( table2 );
      Element *e = d->element( m_tooltipElementNumber );
      drawToolTip( &p2, e );
      p2.end();
    }
  }
		
  //JH: Finally, bitBlt the table2 pixmap to the widget
  bitBlt( this, 0, 0, table2 );
}

void PSE::paintCurrentSelection( QPainter *p )
{
	int x = m_currentPoint.x()-1;
	int y = m_currentPoint.y();

	QPen pen;
	pen.setStyle( DotLine );
	pen.setWidth( 4 );
	pen.setColor( Qt::blue );
	p->setPen( pen );
	p->drawEllipse( x*ELEMENTSIZE-10,y*ELEMENTSIZE-10,ELEMENTSIZE+20,ELEMENTSIZE+20 );
	pen.setWidth( 3 );
	pen.setColor( Qt::red );
	p->setPen( pen );
	p->drawEllipse( x*ELEMENTSIZE-5,y*ELEMENTSIZE-5,ELEMENTSIZE+10,ELEMENTSIZE+10 );
}

void PSE::drawToolTip( QPainter* p, Element *e )
{
	if ( !e ) return;

	if(!m_showTooltip) return;
	
	const int x1 = mapFromGlobal( QCursor::pos() ).x();
	const int y1 = mapFromGlobal( QCursor::pos() ).y();

	static const int padding = 3;

	QFont fB = KGlobalSettings::generalFont();
	fB.setPointSize( fB.pointSize() + 4 );
	p->setFont( fB );
	
	QString text = i18n( "Name: %1\n"
	                     "Number: %2\n"
	                     "Mass: %3 u")
	               .arg( e->elname().utf8(),
	                     QString::number( e->number() ),
	                     QString::number( e->mass() ) );

	QRect bRect( 0, 0, 1000, 1000 );
	bRect = p->boundingRect( bRect, AlignLeft|AlignTop, text );
	bRect.moveBy( x1, y1 );
	QRect bRectExt = bRect;
	bRect.moveBy( padding, padding );
	bRectExt.setWidth( bRectExt.width() + 2 * padding );
	bRectExt.setHeight( bRectExt.height() + 2 * padding );

	bool vertflipped = false;
	if ( bRectExt.bottom() > height() )
	{
		bRectExt.moveBy( 0, - bRectExt.height() );
		bRect.moveBy( 0, - bRect.height() - 2 * padding );
		vertflipped = true;
	}
	if ( bRectExt.right() > width() )
	{
		bRectExt.moveBy( - bRectExt.width(), 0 );
		bRect.moveBy( - bRect.width() - 2 * padding, 0 );
	}
	else if ( !vertflipped )
	{
		bRectExt.moveBy( 15, 0 );
		bRect.moveBy( 15, 0 );
	}

	p->setBrush(Qt::SolidPattern);
//	p->setBrush( Qt::yellow );
	p->setBrush( QColor( 255, 255, 220 ) );
	p->drawRect( bRectExt );

	p->setBrush( Qt::black );
	p->setBrush(Qt::NoBrush);

	p->drawText( bRect, AlignLeft|AlignTop, text );
}

void PSE::drawTimeLine( QPainter* p )
{
	if ( !p ) return;
	kdDebug() << "PSE::drawTimeLine: " << m_date << endl;
	
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	/**
	 * this loop iterates through all elements. The Elements
	 * draw themselfs, the PSE only tells them to do so
	 */
	while ( it != itEnd )
	{
		if ( ( *it )->date() <= m_date )
			( *it )->drawSelf( p );
		++it;
	}
}

void PSE::drawLegend( QPainter* p )
{
	if ( !p ) return;

	/*
	 * The legend is drawn in the big gap of the table. The gap has
	 * this size:
	 * 
	 * width: ELEMENTSIZE * 10
	 * hight: ELEMENTSIZE * 3
	 *
	 * We need to spare a few pixels on every side so that the legend
	 * does not collide with the elements
	 */
	
	QFont legendFont = KGlobalSettings::generalFont();
	legendFont.setPointSize( legendFont.pointSize() + 1 );
	p->setFont( legendFont );

	/*
	 * one field is allowed to be half the gap minus 10 pixel
	 */
	int fieldsize = ELEMENTSIZE*5-10;

	/*
	 * one field is a maximum of half the size of an element
	 */
	int fieldheight = ELEMENTSIZE/2;  

	int x1 = ELEMENTSIZE*2+45;
	int x2 = ELEMENTSIZE*7+45;

	const int square_w = 20;
	const int square_h = 20;
	
	switch ( m_currentScheme ) {
		//No Legend to be drawn as only one colour is used
		case PSE::NOCOLOUR:
			break;
		case PSE::BLOCK:
			{
				p->fillRect(x1-25, fieldheight*2, square_w, square_h, color_s ); 
				p->fillRect(x2-25, fieldheight*2, square_w, square_h, color_p ); 
				p->fillRect(x1-25, fieldheight*3, square_w, square_h, color_d ); 
				p->fillRect(x2-25, fieldheight*3, square_w, square_h, color_f ); 
				p->drawText(x1, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("s-Block") ); 
				p->drawText(x2, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("p-Block") ); 
				p->drawText(x1, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("d-Block") ); 
				p->drawText(x2, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("f-Block") ); 
				break;
			}
		case PSE::GROUPS:
			{
				p->fillRect( x1-25, fieldheight*2, square_w, square_h, color_1); 
				p->fillRect( x2-25, fieldheight*2, square_w, square_h, color_2); 
				p->fillRect( x1-25, fieldheight*3, square_w, square_h, color_3); 
				p->fillRect( x2-25, fieldheight*3, square_w, square_h, color_4); 
				p->fillRect( x1-25, fieldheight*4, square_w, square_h, color_5); 
				p->fillRect( x2-25, fieldheight*4, square_w, square_h, color_6); 
				p->fillRect( x1-25, fieldheight*5, square_w, square_h, color_7); 
				p->fillRect( x2-25, fieldheight*5, square_w, square_h, color_8 ); 
				p->drawText( x1 , fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 1") ); 
				p->drawText( x2 , fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 2")); 
				p->drawText( x1 , fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 3")); 
				p->drawText( x2 , fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 4")); 
				p->drawText( x1 , fieldheight*4, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 5")); 
				p->drawText( x2 , fieldheight*4, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 6")); 
				p->drawText( x1 , fieldheight*5, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 7")); 
				p->drawText( x2 , fieldheight*5, fieldsize, fieldheight, Qt::AlignLeft, i18n("Group 8")); 
				break;
			}
		case PSE::ACIDIC:
			{
				p->fillRect(x1-25, fieldheight*2, square_w, square_h, color_ba ); 
				p->fillRect(x2-25, fieldheight*2, square_w, square_h, color_ac ); 
				p->fillRect(x1-25, fieldheight*3, square_w, square_h, color_neu ); 
				p->fillRect(x2-25, fieldheight*3, square_w, square_h, color_amp ); 
				p->drawText(x1, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Basic") ); 
				p->drawText(x2, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Acidic") ); 
				p->drawText(x1, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("Neutral") ); 
				p->drawText(x2, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("both acidic and basic behaviour","Amphoteric") ); 
				break;
			}
		case PSE::FAMILY:
			{
				p->fillRect( x1-25, fieldheight*2, square_w, square_h, c_alkaline ); 
				p->fillRect( x2-25, fieldheight*2, square_w, square_h, c_rare ); 
				p->fillRect( x1-25, fieldheight*3, square_w, square_h, c_nonmetal ); 
				p->fillRect( x2-25, fieldheight*3, square_w, square_h, c_alkalie ); 
				p->fillRect( x1-25, fieldheight*4, square_w, square_h, c_other_metal ); 
				p->fillRect( x2-25, fieldheight*4, square_w, square_h, c_halogene ); 
				p->fillRect( x1-25, fieldheight*5, square_w, square_h, c_transition ); 
				p->fillRect( x2-25, fieldheight*5, square_w, square_h, c_noble_gas ); 
				p->fillRect( x1-25, fieldheight*6, square_w, square_h, c_metalloid ); 

				p->drawText( x1 , fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Alkaline") ); 
				p->drawText( x2 , fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Rare Earth")); 
				p->drawText( x1 , fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("Non-Metals")); 
				p->drawText( x2 , fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("Alkalie-Metals")); 
				p->drawText( x1 , fieldheight*4, fieldsize, fieldheight, Qt::AlignLeft, i18n("Other Metal")); 
				p->drawText( x2 , fieldheight*4, fieldsize, fieldheight, Qt::AlignLeft, i18n("Halogene")); 
				p->drawText( x1 , fieldheight*5, fieldsize, fieldheight, Qt::AlignLeft, i18n("Transition Metal")); 
				p->drawText( x2 , fieldheight*5, fieldsize, fieldheight, Qt::AlignLeft, i18n("Noble Gas")); 
				p->drawText( x1 , fieldheight*6, fieldsize, fieldheight, Qt::AlignLeft, i18n("Metalloid")); 
				break;
			}
	}
}

void PSE::drawNumeration( QPainter* p )
{
	if ( !p ) return;

	switch(m_num){
		case PSE::NO:
			return;
		case PSE::CAS:
			for(int i = 0; i < 18 ; ++i )
			{
				p->drawText( i*ELEMENTSIZE,0 ,ELEMENTSIZE,ELEMENTSIZE, Qt::AlignCenter, QString::number(i+1));
			}
			break;
		case PSE::IUPAC:
			for(int i = 0; i < 18 ; ++i )
			{
				p->drawText( i*ELEMENTSIZE,0 ,ELEMENTSIZE,ELEMENTSIZE, Qt::AlignCenter, m_IUPAClist[i]);
			}
			break;
		case PSE::IUPACOLD:
			for(int i = 0; i < 18 ; ++i )
			{
				p->drawText( i*ELEMENTSIZE,0 ,ELEMENTSIZE,ELEMENTSIZE, Qt::AlignCenter, m_IUPACOLDlist[i]);
			}
			break;
	}
}

	
void PSE::drawSOMPSE( QPainter* p )
{
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	while ( it != itEnd )
	{
		( *it )->drawStateOfMatter( p, m_temperature );
		++it;
	}

}

void PSE::slotTransientLabel( void )
{
	int X = mapFromGlobal( QCursor::pos() ).x()/ELEMENTSIZE;
	int Y = ( mapFromGlobal( QCursor::pos() ).y( )-ELEMENTSIZE)/ELEMENTSIZE;
	
	X += 1;
	Y += 1;

	QPoint point( X,Y );

	const int num = ElementNumber( X, Y );
	if ( num )
		emit ToolTip( num );
}

void PSE::mouseMoveEvent( QMouseEvent * /*mouse*/ )
{
  //JH: only update() if we were showing a tooltip
  if ( m_tooltipElementNumber ) {
  	m_tooltipElementNumber = 0; //this invalidates the number. If the mouse
	                            //is moved, the number is invalid. 
  	update();       
  }
  
  HoverTimer.start(  2000, true ); //JH: true = run timer once, not continuously
}

void PSE::mouseReleaseEvent( QMouseEvent *mouse )
{
	///first: find out the position
	int X = mouse->x()/ELEMENTSIZE;
	
	//for the y-position I need to substract ELEMENTSIZE pixel because
	//the whole table doesn't start at (0,0) but at (0,ELEMENTSIZE)
	int Y = ( mouse->y()-ELEMENTSIZE)/ELEMENTSIZE;
		
	X += 1;
	Y += 1;

	QPoint point( X,Y );
	emit tableClicked( point );
	
	const int num = ElementNumber( X, Y );

	//If no element was clicked ElementNumber() will return 0
	if ( num )
		emit ElementClicked( num );
}

int PSE::ElementNumber( int X, int Y )
{
	//from this on I can use X and Y. Both contain the position of an element in the
	//complete PSE. Eg, He is 1,18 and Na is 2,1
	
	CList::ConstIterator it = d->CoordinateList.begin();

	int counter = 1;
	while ( it != d->CoordinateList.end() )
	{//iterate through the list of coordinates and compare the x/y values.
	 //finally, if the 20'es iterator has the same coordinates Element 20
	 //has been clicked.
	
		coordinate c = *it;
		if ( c.x == X )
		{
			if ( c.y == Y )
			{//coordinates match. Return the number of the element.
				return counter;
			}
		}
		++it;
		++counter;
	}

	return 0;
}

void PSE::slotLock()
{
	setShowTooltip(false);
}

void PSE::slotUnlock()
{
	setShowTooltip(true);
}

void PSE::slotLock(bool locked)
{
	if(locked){
		setShowTooltip(false);
	}
	else{
		setShowTooltip(true);
	}

	setFullDraw();
	update();
}

void PSE::slotUpdatePoint( QPoint point )
{
	kdDebug() << "PSE::slotUpdatePoint()" << endl;
		
	m_currentPoint = point;

	kdDebug() << m_currentPoint.x() << endl;
	kdDebug() << m_currentPoint.y() << endl;

	update();
}

void PSE::drawCrystal( QPainter* p )
{
	kdDebug() << "PSE::drawCrystal()" << endl;
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	/**
	 * this loop iterates through all elements. The Elements
	 * draw themselfs, the PSE only tells them to do so
	 */
	while ( it != itEnd )
	{
		( *it )->drawCrystalstructure( p );
		++it;
	}
	QFont legendFont = KGlobalSettings::generalFont();
	legendFont.setPointSize( legendFont.pointSize() + 1 );
	p->setFont( legendFont );

	/*
	 * one field is allowed to be half the gap minus 10 pixel
	 */
	int fieldsize = ELEMENTSIZE*5-10;

	/*
	 * one field is a maximum of half the size of an element
	 */
	int fieldheight = ELEMENTSIZE/2;  

	int x1 = ELEMENTSIZE*2+45;
	int x2 = ELEMENTSIZE*7+45;

	const int square_w = 20;
	const int square_h = 20;

	p->fillRect(x1-25, fieldheight*2, square_w, square_h, Qt::blue ); 
	p->fillRect(x2-25, fieldheight*2, square_w, square_h, Qt::red ); 
	p->fillRect(x1-25, fieldheight*3, square_w, square_h, Qt::yellow ); 
	p->fillRect(x2-25, fieldheight*3, square_w, square_h, Qt::green ); 
	p->fillRect(x2-25, fieldheight*4, square_w, square_h, Qt::white ); 
	p->drawText(x1, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("Own") ); 
	p->drawText(x2, fieldheight*2, fieldsize, fieldheight, Qt::AlignLeft, i18n("bbc, body-centred cubic lattice") ); 
	p->drawText(x1, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("hdp, hexagonal") ); 
	p->drawText(x2, fieldheight*3, fieldsize, fieldheight, Qt::AlignLeft, i18n("ccp, cubic close packed") ); 
	p->drawText(x2, fieldheight*4, fieldsize, fieldheight, Qt::AlignLeft, i18n("Unknown") ); 
}

void PSE::drawPSE( QPainter* p )
{
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	/**
	 * this loop iterates through all elements. The Elements
	 * draw themselfs, the PSE only tells them to do so
	 */
	while ( it != itEnd )
	{
		( *it )->drawSelf( p );
		++it;
	}
}

//CN This is called for *every* drawing of the table. This means
//a lot overload... I would be better to chache the values in
//member variables an only check if they need an update. 
void PSE::calculateGradient( QPainter *p )
{
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	QValueList<double> tmpList;
	switch ( m_gradientType )
	{
		case Element::ATOMICRADIUS:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->getRadius(Element::ATOMIC) );
			}
			break;
		case Element::COVALENTRADIUS:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->getRadius(Element::COVALENT) );
			}
			break;
		case Element::VDWRADIUS:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->getRadius(Element::VDW) );
			}
			break;
		case Element::MASS:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->mass() );
			}
			break;
		case Element::DENSITY:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->density() );
			}
			break;
		case Element::BOILINGPOINT:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->boiling() );
			}
			break;
		case Element::MELTINGPOINT:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->melting() );
			}
			break;
		case Element::EN:
			for (; it != itEnd; ++it )
			{
				tmpList.append( ( *it )->electroneg() );
			}
			break;
	}

	QValueList<double>::iterator dit = tmpList.begin();
	const QValueList<double>::iterator ditEnd = tmpList.end();

	double tmpMin = *dit;
	double tmpMax = *dit;
	for ( ; dit != ditEnd; ++dit )
	{
		if ((  *dit ) == 0 ) continue;
		if ( ( *dit ) < tmpMin )
			tmpMin = *dit;
		if ( ( *dit ) > tmpMax )
			tmpMax = *dit;
	}
	
	//now draw the gradient-table
	drawGradientPSE( p, tmpMin, tmpMax );
}



void PSE::drawGradientPSE( QPainter *p, const double min, const double max )
{
	QString title = QString::null;
	
	const double var = max-min;
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	/**
	 * this loop iterates through all elements. The Elements
	 * draw themselfs, the PSE only tells them to do so
	 */
	it = d->ElementList.begin();
	switch ( m_gradientType )
	{
		case Element::ATOMICRADIUS:
			title = i18n( "Gradient: Atomic Radius" );
			while ( it != d->ElementList.end() )
			{
				double value = ( *it )->getRadius( Element::ATOMIC );
				double coeff = ( value - min )/var;

				drawGradientButton( p, *it, coeff, value, min );
				
				++it;
			}
			break;
		case Element::VDWRADIUS:
			title = i18n( "Gradient: van der Walls Radius" );
			while ( it != d->ElementList.end() )
			{
				double value = ( *it )->getRadius( Element::VDW );
				double coeff = ( value - min )/var;
				
				drawGradientButton( p, *it, coeff, value, min );

				++it;
			}
			break;
		case Element::COVALENTRADIUS:
			title = i18n( "Gradient: Covalent Radius" );
			while ( it != d->ElementList.end() )
			{
				double value = ( *it )->getRadius( Element::COVALENT );
				double coeff = ( (*it)->getRadius(Element::COVALENT) - min )/var;
				
				drawGradientButton( p, *it, coeff, value, min );

				++it;
			}
			break;
		case Element::MASS:
			title = i18n( "Gradient: Atomic Mass" );
			while ( it != d->ElementList.end() )
			{
				double coeff = ( (*it)->mass() - min )/var;
				drawGradientButton( p, *it, coeff, ( *it )->mass(), min );

				++it;
			}
			break;
		case Element::DENSITY:
			title = i18n( "Gradient: Atomic Density" );
			while ( it != d->ElementList.end() )
			{
				double coeff = ( (*it)->density() - min )/var;

				drawGradientButton( p, *it, coeff, ( *it )->density(), min );
				++it;
			}
			break;
		case Element::BOILINGPOINT:
			title = i18n( "Gradient: Boiling point" );
			while ( it != d->ElementList.end() )
			{
				double coeff = ( (*it)->boiling() - min )/var;
				drawGradientButton( p, *it, coeff, ( *it )->boiling(), min );

				++it;
			}
			break;
		case Element::MELTINGPOINT:
			title = i18n( "Gradient: Melting point" );
			while ( it != d->ElementList.end() )
			{
				double coeff = ( (*it)->melting() - min )/var;
				drawGradientButton( p, *it, coeff, ( *it )->melting(), min );

				++it;
			}
			break;
		case Element::EN:
			title = i18n( "Gradient: Electronegativity" );
			while ( it != d->ElementList.end() )
			{
				double coeff = ( (*it)->electroneg() - min )/var;
				drawGradientButton( p, *it, coeff, ( *it )->electroneg(), min );

				++it;
			}
			break;
	}
	//now draw the gradientwidget:
	int x,y,w,h;
	x = ELEMENTSIZE*2+5;
	y= 5;
	w = ELEMENTSIZE*10-5;
	h = ELEMENTSIZE*4-5;
	QSize s( ELEMENTSIZE*7,20 );
	QImage img = KImageEffect::gradient ( s, Qt::white, Qt::red, KImageEffect::HorizontalGradient );
	QPixmap pm( img );
	p->drawText( x+5,y+50,ELEMENTSIZE*7,20, Qt::AlignCenter, title ); 
	p->drawPixmap( x+50,y+80, pm );
	p->drawText(   x+50,y+100,ELEMENTSIZE*7,20, Qt::AlignRight, QString::number(  max ) ); 
	p->drawText(   x+50,y+100,ELEMENTSIZE*7,20, Qt::AlignLeft, QString::number( min ) ); 
}

void PSE::drawGradientButton( QPainter *p, Element* e, double coeff, double value, double minValue )
{
	if ( value >= minValue )
	{
		QColor c = calculateColor( coeff );
		e->drawGradient( p, QString::number( value ), c );
	}
	else
		e->drawGradient( p, i18n("It means: Not Available. Translators: keep it as short as you can!", "N/A"), Qt::white );
}

QColor PSE::calculateColor( const double coeff )
{
	const QColor color2 = Qt::white;
	const QColor color1 = Qt::red;

	int red = (int)( (color1.red() - color2.red()) * coeff + color2.red() );
	int green = (int)( (color1.green() - color2.green()) * coeff + color2.green() );
	int blue = (int)( (color1.blue() - color2.blue()) * coeff + color2.blue() );

	return QColor( red, green, blue );
}

void PSE::setLook( PSE::SCHEMETYPE type, int which )
{
	m_currentScheme = type;
	
	EList::Iterator it = d->ElementList.begin();
	const EList::Iterator itEnd = d->ElementList.end();

	switch ( type )
	{
		case NOCOLOUR:
		{
			const QColor color = Prefs::noscheme();
			while ( it != itEnd )
			{
				( *it )->setElementColor( color );
				++it;
			}
			setGradient( false );
			break;
		}
		case PSE::GROUPS:  // group view
		{
			QString group;

			while ( it != itEnd )
			{
				group = ( *it )->group();
				
				if (group == QString("1")) {
					( *it )->setElementColor( color_1 );
				}
				if (group == QString("2")){
					( *it )->setElementColor( color_2 );
				}
				if (group == QString("3")){
					( *it )->setElementColor( color_3 );
				}
				if (group == QString("4")){
					( *it )->setElementColor( color_4 );
				}
				if (group == QString("5")){
					( *it )->setElementColor( color_5 );
				}
				if (group == QString("6")){
					( *it )->setElementColor( color_6 );
				}
				if (group == QString("7")){
					( *it )->setElementColor( color_7 );
				}
				if (group == QString("8")){
					( *it )->setElementColor( color_8 );
				}

				++it;
			}
			setGradient( false );
			break;
		}
		case PSE::BLOCK: //block view
		{
			static QString block;
			while ( it != itEnd )
			{
				block = (*it)->block();
	
				if (block == QString("s")) {
					(*it)->setElementColor( color_s );
				}
				if (block == QString("p")) {
					(*it)->setElementColor( color_p );
				}
				if (block == QString("d")) {
					(*it)->setElementColor( color_d );
				}
				if (block == QString("f")) {
					(*it)->setElementColor( color_f );
				}
				++it;
			}
			setGradient( false );
			break;
		}
		case PSE::ACIDIC: //acidic beh
		{
			static QString acidicbeh;
			while ( it != itEnd )
			{
				acidicbeh = ( *it )->acidicbeh();

				if (acidicbeh == QString("0")) {
					(*it)->setElementColor( color_ac );
				}
				if (acidicbeh == QString("1")){
					(*it)->setElementColor( color_ba );
				}
				if (acidicbeh == QString("2")){
					(*it)->setElementColor( color_neu );
				}
				if (acidicbeh == QString("3")){
					(*it)->setElementColor( color_amp );
				}
				++it;
			}
			setGradient( false );
			break;
		}
		case PSE::FAMILY: //familiy of the element
		{
			static QString family;

			while ( it != itEnd )
			{
				family = ( *it )->family();

				if ( family == "Noblegas" ){
					(*it)->setElementColor( c_noble_gas );
				}
				if ( family == "Non-Metal" ){
					(*it)->setElementColor( c_nonmetal );
				}
				if ( family == "Rare_Earth" ){
					(*it)->setElementColor( c_rare );
				}
				if ( family == "Alkaline_Earth" ){
					(*it)->setElementColor( c_alkaline );
				}
				if ( family == "Alkali_Earth" ){
					(*it)->setElementColor( c_alkalie );
				}
				if ( family == "Transition" ){
					(*it)->setElementColor( c_transition );
				}
				if ( family == "Other_Metal" ){
					(*it)->setElementColor( c_other_metal );
				}
				if ( family == "Metalloids" ){
					(*it)->setElementColor( c_metalloid );
				}
				if ( family == "Halogene" ){
					(*it)->setElementColor( c_halogene );
				}
			
				++it;
			}
			setGradient( false );
			break;
		}
		case CRYSTAL:
		{
			setGradient( false );
			break;
		}
		case GRADIENT:
		{
			setGradient( true );
			setGradientType( which );
			break;
		}
		default:
			;
	}

	Prefs::setColorschemebox( type );
	Prefs::writeConfig();

	//JH: redraw the full table next time
	setFullDraw();
	update();
}


#include "pse.moc"
