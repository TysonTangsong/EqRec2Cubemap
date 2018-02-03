#ifndef CUBEMAPFBORENDER_H
#define CUBEMAPFBORENDER_H

#include <QObject>
#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QImage>


struct SchemeDataElement
{
    QVector3D screenPos, cubemapCoords;
};

class CubemapFboRender : public QObject, public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    CubemapFboRender(QObject *parent=Q_NULLPTR);
    void render();
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);

signals:
    void imageReady(QImage);

public slots:
    void setImage(QImage img);
    void setYRotation(float _yRotation);
    //void setScheme(QImage);

private:
    void initDataBuffer();
    void drawGeometry();
    QOpenGLShaderProgram m_shaderProgram;
    int m_vertexAttribId, m_cubemapCoordsAttribId;
    int m_matrixUniformId;
    int m_textureSamplerId;
    int m_yRotationUniformId;

    float m_yRotation;

    QVector<SchemeDataElement> m_schemeData;
    QOpenGLTexture m_equrectangleMap;
};

#endif // CUBEMAPFBORENDER_H
