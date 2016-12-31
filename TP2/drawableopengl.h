#ifndef DRAWABLEOPENGL_H
#define DRAWABLEOPENGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <camera.h>


class DrawableOpenGL  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    DrawableOpenGL();
    void setCamera();

protected:
    void initializeShader(QString vs, QString fs);
    void initializeVAO();


private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;
    camera* m_camera;
    glm::vec3 m_position;
    GLfloat m_roulis, m_tangage, m_lacet;


};

#endif // DRAWABLEOPENGL_H
