/*   Copyright (C) 2005 by Martin Pfeiffer                                 *
 *   hubipete@gmx.net                                                      *
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

#include "exporter.h"

#include <qpixmap.h>
#include <qpainter.h>

#include <kdebug.h>

Exporter::Exporter()
{
}

Exporter::~Exporter()
{
}

bool Exporter::saveAsPNG( const QWidget* widget, QString fileName, int x, int y, int width, int height )
{
	QPixmap* tmpPixmap = new QPixmap();
	
	if( x != 0 || y != 0 || width != 0 || height != 0 )
	{
		bitBlt( tmpPixmap, 0, 0, widget, x, y, width, height );
		kdDebug() <<"special area" << endl;
	}
	else
		bitBlt( tmpPixmap, 0, 0, widget );

	return tmpPixmap->save( fileName, "PNG" );
	delete tmpPixmap;
}

