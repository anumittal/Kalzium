/***************************************************************************
 *   Copyright (C) 2010     by Etienne Rebetez etienne.rebetez@oberwallis.ch    *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "kalziumelementproperty.h"

#include "kalziumdataobject.h"
#include "search.h"

#include "klocale.h"

#include <prefs.h>
#include "qdebug.h"

KalziumElementProperty::KalziumElementProperty()
        : m_mode(0)
{
    m_gradient = KalziumGradientTypeFactory::instance();
    m_scheme = KalziumSchemeTypeFactory::instance();

    m_currentScheme = Prefs::colorschemebox();
    m_currentGradient = Prefs::colorgradientbox();

    if (m_currentGradient > 1) {
        m_mode = GRADIENTVALUE;
    }
}

KalziumElementProperty::~KalziumElementProperty()
{
}

void KalziumElementProperty::setScheme(int newScheme)
{
    m_currentScheme = newScheme;
    Prefs::setColorschemebox(newScheme);
    Prefs::self()->writeConfig();
    propertyChanged();
}

void KalziumElementProperty::setGradient(int newGradient)
{
    m_currentGradient = newGradient;
    Prefs::setColorgradientbox(newGradient);
    Prefs::self()->writeConfig();

    if (m_currentGradient > 1) {
        m_mode = GRADIENTVALUE;
    } else {
        m_mode = NORMAL;
    }

    propertyChanged();
}

void KalziumElementProperty::redrawPse()
{
    propertyChanged();
}

QStringList KalziumElementProperty::schemeList() const
{
    return m_scheme->schemes();
}

QStringList KalziumElementProperty::gradientList() const
{
    QStringList customList;
    customList << i18n("None");
    customList << m_gradient->gradients();
    return customList;
}

KalziumSchemeType* KalziumElementProperty::scheme() const
{
    return m_scheme->build(m_currentScheme);
}

KalziumGradientType* KalziumElementProperty::gradient() const
{
    if (m_currentGradient == NOGRADIENT ) {
        // FIXME Fix the case when no gradient is choosen. gradientwidget or here.
        return m_gradient->build(0);
    }

    return m_gradient->build(m_currentGradient - 1);
}

int KalziumElementProperty::gradientId() const
{
    return m_currentGradient;
}

int KalziumElementProperty::schemeId() const
{
    return m_currentScheme;
}

void KalziumElementProperty::setSliderValue(double slide)
{
    m_slider = slide;
    propertyChanged();
}

double KalziumElementProperty::getValue(int el) const
{
    if (m_currentGradient > 0) {
        return gradient()->value(el);
    }
    return 0;
}

QColor KalziumElementProperty::getElementColor(int el)
{
    QColor elementColor;

    if (m_currentGradient == NOGRADIENT)  {
        elementColor = scheme()->elementBrush(el).color();
    } else {
        // handel Gradient cases
        elementColor = gradientBrushLogic( el );
    }
    return elementColor;
}

QBrush KalziumElementProperty::getElementBrush(int el)
{
    QBrush elementBrush;
    elementBrush.setStyle(Qt::SolidPattern);
    elementBrush.setColor(Qt::transparent);

    // Hide filtered elements from search
    if (!KalziumDataObject::instance()->search()->matches( el ) && KalziumDataObject::instance()->search()->isActive()) {
        return QBrush(Qt::darkGray, Qt::Dense7Pattern);
    }

    //The iconic view is the 3rd view (0,1,2,...). Pixmaps don't make nice gradients.
    if ( m_currentScheme ==  2) {
        elementBrush =  scheme()->elementBrush(el);

    // add a nice gradient
    } else {
        QColor color = getElementColor(el);
        QLinearGradient grad(QPointF(0, 0), QPointF(0, 40));
        grad.setColorAt(0,color);
        qreal h, s, v, a;
        color.getHsvF(&h, &s, &v, &a);
        color.setHsvF(h, s, v*0.7, a);
        grad.setColorAt(1,color);

        elementBrush = QBrush(grad);
    }

    return elementBrush;
}

QColor KalziumElementProperty::getTextColor(int el) const
{
    return scheme()->textColor(el);
}

QColor KalziumElementProperty::getBorderColor(int el) const
{
    // Show sheme color as border when gradients are selected.
    if (m_currentGradient != NOGRADIENT ) {
        return scheme()->elementBrush(el).color();
    }

    // Transparent Borders don't make sens.
    if (getTextColor(el) == QColor(Qt::transparent)) {
        return QColor(Qt::black);
    }

    return getTextColor(el);

}

int KalziumElementProperty::getMode() const
{
    return m_mode;
}

QColor KalziumElementProperty::gradientBrushLogic( int el ) const
{
    QColor gradientColor;
    const double gradientValue = gradient()->value( el );

    // Proof of concept SOM-Widget replacment. TODO make a class or something cool
    if (m_currentGradient == SOMGradientType) {
        const double melting = KalziumDataObject::instance()->element( el )->dataAsVariant( ChemicalDataObject::meltingpoint ).toDouble();
        const double boiling = KalziumDataObject::instance()->element( el )->dataAsVariant( ChemicalDataObject::boilingpoint ).toDouble();

        if ( m_slider < melting ) {
            //the element is solid
            gradientColor = Prefs::color_solid();
        }
        else if ( ( m_slider > melting ) && ( m_slider < boiling ) ) {
            //the element is liquid
            gradientColor = Prefs::color_liquid();
        }
        else if ( ( m_slider >= boiling ) && ( boiling > 0.0 ) ) {
            //the element is vaporous
            gradientColor = Prefs::color_vapor();
        } else {
            gradientColor = Qt::lightGray;
        }
        return gradientColor;
    }

    bool isActiv = true;
    switch ( m_currentGradient ) {

    case DISCOVERYDATE:
        if ( gradientValue > m_slider ) {
            isActiv = false;
        }
        break;

    default: // All other gradients
        if ( gradientValue < m_slider ) {
            isActiv = false;
        }
        break;
    }

    if ( !isActiv && gradientValue != -1) { //FIXME No magic number...
        gradientColor = Qt::transparent;
    } else {
        const double coeff = gradient()->elementCoeff(el);
        gradientColor = gradient()->calculateColor(coeff) ;
    }
    return gradientColor;
}


#include "kalziumelementproperty.moc"
