/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QTimer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_1_Core>
#include <QInputDialog>
#include <math.h>
#include "../app/app-events.h"

bool GLWidget::m_transparent = false;
QOpenGLExtraFunctions *pGlExtra = NULL;
QOpenGLFunctions_4_1_Core *pGl4 = NULL;

static void ErrMessageBox(const char *pMsg)
{
    QInputDialog::getText(nullptr,"Title","text");
}

struct LibCallbackQt :public pcrlib::LibCallback
{
    void error(const char *pMsg)
    {
        static QTextStream ts( stdout );
        ts<<pMsg;
        ts.flush();
    }
    void message(const char *pMsg)
    {
        static QTextStream ts( stdout );
        ts<<pMsg;
        ts.flush();
    }
};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_pApp(NULL),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
   // QTimer *timer = new QTimer(this);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  //  timer->start(10);

}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup()
{
    makeCurrent(); //makes the widget's rendering context the current OpenGL rendering context
    doneCurrent();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_pApp)  return;
    bool isLeft  = event->buttons() & Qt::LeftButton;
    bool isRight = event->buttons() & Qt::RightButton;
    m_pApp->mouseDownEvent(event->x(), event->y(), isLeft, isRight);
    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
     if(!m_pApp)  return;
     m_pApp->mouseMoveEvent(event->x(), event->y());
     update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!m_pApp)  return;
    bool isLeft  = event->buttons() & Qt::LeftButton;
    bool isRight = event->buttons() & Qt::RightButton;
    m_pApp->mouseUpEvent(isLeft, isRight);
    update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(!m_pApp)  return;
    int delta = (event->angleDelta().y()>0.0f) ? 1:-1;
    m_pApp->mouseWhellEvent(delta);
    update();
}

void GLWidget::runtest()
{
    if(m_pApp) m_pApp->testCloud();
    update();
}

void GLWidget::initializeGL()
{
    pGl4 =  new QOpenGLFunctions_4_1_Core();
    pGl4->initializeOpenGLFunctions();
    pGlExtra = new QOpenGLExtraFunctions();
    pGlExtra->initializeOpenGLFunctions();

    m_pApp = pcrapp::IAppEvents::getAppEvents();
    m_pApp->init(new LibCallbackQt());
}

void GLWidget::resizeGL(int w, int h)
{
    //ErrMessageBox("AAAA");
}
void GLWidget::paintGL()
{
  int h = height();
  int w = width();
  if(m_pApp) m_pApp->paintEvent(w, h);
}
