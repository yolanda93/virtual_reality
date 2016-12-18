// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QOpenGLWidget>

class WidgetOpenGL : public QOpenGLWidget
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget* parent = 0);
    ~WidgetOpenGL();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

};

#endif // WIDGETOPENGL_H
