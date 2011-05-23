/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtapsensor.h"
#include "qtapsensor_p.h"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING(QTapReading)

/*!
    \class QTapReading
    \ingroup sensors_reading
    \inmodule QtSensors
    \since 1.0

    \brief The QTapReading class represents one reading from the
           tap sensor.

    \section2 QTapReading Units
    The tap sensor registers tap events along the 3 axes that originate from the phone.
    The axes are arranged as follows.

    \image sensors-coordinates2.jpg

    By default it returns only double tap events. The QTapSensor::returnDoubleTapEvents property
    must be set to false to return individual tap events.
*/

/*!
    \enum QTapReading::TapDirection

    The tap direction is indicated using flags. Applications should check for the presence of
    a particular flag as multiple flags may be set at once.

    The X, Y and Z flags allow an app to check for taps along an axis without caring about the
    direction.

    \code
    if (reading->tapDirection()&QTapReading::X) {
        ...
    }
    \endcode

    The *_Pos and *_Neg flags allow checking for taps in a specific direction. Note that some
    devices cannot determine the direction of a tap and will set both the _Pos and _Neg flag for
    the detected axis. Previous versions of the API did not allow this. Applications that check
    for the _Pos and _Neg flags as values should be updated so they can work with all devices.

    \oldcode
    if (reading->tapDirection() == QTapReading::X_Pos) {
        ...
    }
    \newcode
    if (reading->tapDirection()&QTapReading::X_Pos) {
        ...
    }
    \endcode

    \value Undefined This value means that the direction is unknown.
    \value X     This flag is set if the tap was along the X axis.
    \value Y     This flag is set if the tap was along the Y axis.
    \value Z     This flag is set if the tap was along the Z axis.
    \value X_Pos This flag is set if the tap was towards the positive X direction.
    \value Y_Pos This flag is set if the tap was towards the positive Y direction.
    \value Z_Pos This flag is set if the tap was towards the positive Z direction.
    \value X_Neg This flag is set if the tap was towards the negative X direction.
    \value Y_Neg This flag is set if the tap was towards the negative Y direction.
    \value Z_Neg This flag is set if the tap was towards the negative Z direction.
    \value X_Both Equivalent to \c{X_Pos|X_Neg}. Returned by devices that cannot detect the direction of a tap.
    \value Y_Both Equivalent to \c{Y_Pos|Y_Neg}. Returned by devices that cannot detect the direction of a tap.
    \value Z_Both Equivalent to \c{Z_Pos|Z_Neg}. Returned by devices that cannot detect the direction of a tap.
*/

/*!
    \property QTapReading::tapDirection
    \brief the direction of the tap.

    \sa {QTapReading Units}
*/

QTapReading::TapDirection QTapReading::tapDirection() const
{
    return static_cast<QTapReading::TapDirection>(d->tapDirection);
}

/*!
    Sets the tap direction to \a tapDirection.
*/
void QTapReading::setTapDirection(QTapReading::TapDirection tapDirection)
{
    switch (tapDirection) {
        case X_Pos:
        case Y_Pos:
        case Z_Pos:
        case X_Neg:
        case Y_Neg:
        case Z_Neg:
        case X_Both:
        case Y_Both:
        case Z_Both:
            d->tapDirection = tapDirection;
            break;
        default:
            d->tapDirection = Undefined;
            break;
    }
}

/*!
    \property QTapReading::doubleTap
    \brief a value indicating if there was a single or double tap.

    \list
    \o true - double tap
    \o false - single tap
    \endlist
    \sa {QTapReading Units}
*/

bool QTapReading::isDoubleTap() const
{
    return d->doubleTap;
}

/*!
    Sets the double tap status of the reading to \a doubleTap.
*/
void QTapReading::setDoubleTap(bool doubleTap)
{
    d->doubleTap = doubleTap;
}

// =====================================================================

/*!
    \class QTapFilter
    \ingroup sensors_filter
    \inmodule QtSensors

    \brief The QTapFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to QTapReading
    instead of QSensorReading.
*/

/*!
    \fn QTapFilter::filter(QTapReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

char const * const QTapSensor::type("QTapSensor");

/*!
    \class QTapSensor
    \ingroup sensors_type
    \inmodule QtSensors

    \brief The QTapSensor class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a QTapReading instead of a QSensorReading.

    For details about how the sensor works, see \l QTapReading.

    \sa QTapReading
*/

/*!
    \fn QTapSensor::QTapSensor(QObject *parent)

    Construct the sensor as a child of \a parent.
*/

/*!
    \fn QTapSensor::~QTapSensor()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*!
    \fn QTapSensor::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

/*!
    \property QTapSensor::returnDoubleTapEvents
    \brief a value indicating if double tap events should be reported.

    Set to true (the default) to have the sensor report only on double tap events.
    Set to false to have the sensor report only on individual tap events.

    It is not possible to have the sensor report both single and double tap events.
    If both are needed the app should create 2 sensor objects.

    Note that you must access this property via QObject::property() and QObject::setProperty().
    The property must be set before calling start().
*/

#include "moc_qtapsensor.cpp"
QT_END_NAMESPACE
