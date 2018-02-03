#include "CubemapFBO.h"
#include <QOpenGLFramebufferObjectFormat>
#include <QDebug>
#include <CubemapFboRender.h>

const float floatEpsilon = 0.00001;


CubemapQuickRender::CubemapQuickRender() : QQuickFramebufferObject(),
    m_scheme(Scheme::VerticalLine)
{
    connect(this, &CubemapQuickRender::schemeChanged, [this](Scheme _scheme){
       qDebug() << "scheme changed";
    });
}

CubemapQuickRender::Renderer * CubemapQuickRender::createRenderer() const
{
    CubemapFboRender * render = new CubemapFboRender;

    connect(this, &CubemapQuickRender::imageLoaded, render, &CubemapFboRender::setImage, Qt::QueuedConnection);
    connect(this, &CubemapQuickRender::yRotationChanged, render, &CubemapFboRender::setYRotation, Qt::QueuedConnection);
    connect(render, &CubemapFboRender::imageReady, this, &CubemapQuickRender::cubemapReady, Qt::QueuedConnection);
    //connect(this, &CubemapQuickRender::schemeChanged, render, &CubemapFboRender::setScheme, Qt::QueuedConnection);

    return render;
}

void CubemapQuickRender::cubemapReady(QImage img)
{
    m_cubemapImage = img;
}

void CubemapQuickRender::saveToFileCubemap(QString fileName)
{
    qDebug() << "save to file" << fileName;
    if(!m_cubemapImage.isNull())
        m_cubemapImage.save(fileName);
}

void CubemapQuickRender::loadFromFileEquRectMap(QString fileName)
{
    qDebug() << "load from file" << fileName;
    QImage img(fileName);
    emit imageLoaded(img);
    update(); //enforce render updating and process it's queued signals
}



void CubemapQuickRender::setScheme(Scheme _scheme)
{
    if(m_scheme != _scheme){
        m_scheme = _scheme;
        emit schemeChanged(m_scheme);
    }
}

void CubemapQuickRender::setYRotation(float _yRotation)
{
    if(fabs(m_yRotation - _yRotation) > floatEpsilon){
        qDebug() << "set rotation" << _yRotation;
        m_yRotation = _yRotation; //% 360.0;
        emit yRotationChanged(m_yRotation);
        update();
    }
}

CubemapQuickRender::Scheme CubemapQuickRender::scheme() const
{
    return m_scheme;
}

float CubemapQuickRender::yRotation() const
{
    return m_yRotation;
}




