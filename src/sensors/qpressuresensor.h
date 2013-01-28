/****************************************************************************
**
** Copyright (C) 2013 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QPRESSURESENSOR_H
#define QPRESSURESENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

QT_MODULE(QtSensors)

class QPressureReadingPrivate;

class Q_SENSORS_EXPORT QPressureReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal pressure READ pressure)
    DECLARE_READING(QPressureReading)
public:
    qreal pressure() const;
    void setPressure(qreal pressure);
};

class Q_SENSORS_EXPORT QPressureFilter : public QSensorFilter
{
public:
    virtual bool filter(QPressureReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) Q_DECL_OVERRIDE
        { return filter(static_cast<QPressureReading*>(reading)); }
};

class Q_SENSORS_EXPORT QPressureSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QPressureSensor(QObject *parent = 0);
    ~QPressureSensor();
    QPressureReading *reading() const { return static_cast<QPressureReading*>(QSensor::reading()); }
    static char const * const type;

private:
    Q_DISABLE_COPY(QPressureSensor)
};

QT_END_NAMESPACE

#endif
