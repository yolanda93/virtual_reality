// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QAbstractSlider>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/glm.hpp"
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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;

    glm::mat4 m_matrix;    //matrice de placement

private slots:
    void update();
    void startAnimation();
    void changeFov(int angle);
    void changeOpacity(int value);

private:
    QTimer* m_timer;
    GLfloat m_angleX;
    GLfloat m_angleY;
    GLfloat m_angleZ;
    QPoint lastPos;
    bool animate;
    bool changeAngle;
};

#endif // WIDGETOPENGL_H
