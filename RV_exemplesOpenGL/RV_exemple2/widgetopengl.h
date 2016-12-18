// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget* parent = 0);
    ~WidgetOpenGL();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void initializeVAO();
    void initializeShader();

private:
    GLint m_programme;          //identifiant du shader program
    GLuint m_vbo;               //identifiant du Vertex Buffer Object
    GLuint m_vao;               //identifiant du Vertex Array Object
    glm::mat4 m_matrix;         //matrice de placement
};

#endif // WIDGETOPENGL_H
