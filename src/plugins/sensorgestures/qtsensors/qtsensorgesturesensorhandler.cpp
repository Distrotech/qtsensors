/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QDebug>

#include "qtsensorgesturesensorhandler.h"

QtSensorGestureSensorHandler::QtSensorGestureSensorHandler(QObject *parent) :
    QObject(parent),
    accel(0), orientation(0), proximity(0), irProx(0),tapSensor(0)
{
}

QtSensorGestureSensorHandler* QtSensorGestureSensorHandler::instance()
{
    static QtSensorGestureSensorHandler *instance = 0;
    if (!instance) {
        instance = new QtSensorGestureSensorHandler;
    }
    return instance;
}

void QtSensorGestureSensorHandler::accelChanged()
{
    Q_EMIT accelReadingChanged(accel->reading());
}

void QtSensorGestureSensorHandler::orientationChanged()
{
    Q_EMIT orientationReadingChanged(orientation->reading());
}

void QtSensorGestureSensorHandler::proximityChanged()
{
    Q_EMIT proximityReadingChanged(proximity->reading());
}

void QtSensorGestureSensorHandler::irProximityChanged()
{
    Q_EMIT irProximityReadingChanged(irProx->reading());
}

void QtSensorGestureSensorHandler::doubletap()
{
    Q_EMIT dTabReadingChanged(tapSensor->reading());
}

bool QtSensorGestureSensorHandler::startSensor(SensorGestureSensors sensor)
{
    bool ok = true;
    switch (sensor) {
    case Accel:
        //accel
        if (accel == 0x0) {
            accel = new QAccelerometer(this);
            ok = accel->connectToBackend();
            qoutputrangelist outputranges = accel->outputRanges();

            if (outputranges.count() > 0)
                accelRange = (int)(outputranges.at(0).maximum *2);//39
            else
                accelRange = 39; //this should never happen
            connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
        }
        if (ok && !accel->isActive())
            accel->start();
        break;
    case Orientation:
        //orientation
        if (orientation == 0x0) {
            orientation = new QOrientationSensor(this);
            ok = orientation->connectToBackend();
            connect(orientation,SIGNAL(readingChanged()),this,SLOT(orientationChanged()));
        }
        if (ok && !orientation->isActive())
            orientation->start();
        break;
    case Proximity:
        //proximity
        if (proximity == 0x0) {
            proximity = new QProximitySensor(this);
            ok = proximity->connectToBackend();
            connect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
        }
        if (ok && !proximity->isActive())
            proximity->start();
        break;
    case IrProximity:
        //irproximity
        if (irProx == 0x0) {
            irProx = new QIRProximitySensor(this);
            ok = irProx->connectToBackend();
            connect(irProx,SIGNAL(readingChanged()),this,SLOT(irProximityChanged()));
        }
        if (ok && !irProx->isActive())
            irProx->start();
        break;
    case Tap:
        //dtap
        if (tapSensor == 0x0) {
            tapSensor = new QTapSensor(this);
            ok = tapSensor->connectToBackend();
            connect(tapSensor,SIGNAL(readingChanged()),this,SLOT(doubletap()));
        }
        if (ok && !tapSensor->isActive())
            tapSensor->start();
        break;
    };
    int val = usedSensorsMap.value(sensor);
    usedSensorsMap.insert(sensor,++val);

    return ok;
}

void QtSensorGestureSensorHandler::stopSensor(SensorGestureSensors sensor)
{
    //  qDebug() << __FUNCTION__ << sensor;
    if (usedSensorsMap.value(sensor) == 0)
        return;
    int val = usedSensorsMap.value(sensor);
    usedSensorsMap.insert(sensor,--val);
    switch (sensor) {
    case Accel:
        //accel
        if (usedSensorsMap.value(sensor) == 0) {
            accel->stop();
        }
        break;
    case Orientation:
        if (usedSensorsMap.value(sensor) == 0) {
            orientation->stop();
        }
        //orientation
        break;
    case Proximity:
        if (usedSensorsMap.value(sensor) == 0) {
            proximity->stop();
        }
        //proximity
        break;
    case IrProximity:
        if (usedSensorsMap.value(sensor) == 0) {
            irProx->stop();
        }
        //irproximity
        break;
    case Tap:
        if (usedSensorsMap.value(sensor) == 0) {
            tapSensor->stop();
        }
        //dtap
        break;
    };
}
