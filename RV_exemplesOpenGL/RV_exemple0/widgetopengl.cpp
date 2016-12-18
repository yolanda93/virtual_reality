// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include "widgetopengl.h"

#if (defined _WIN32 || defined __linux__)
    #include <GL/glu.h>
#elif defined __APPLE__
    #include <glu.h>
#else
    #error "Environnement non connu"
#endif

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent)
{ }

WidgetOpenGL::~WidgetOpenGL()
{ }

void WidgetOpenGL::initializeGL()
{
    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair

    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Définition de la matrice de placement
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -7.0);

    //définition du triangle (immediate mode)
    glBegin(GL_TRIANGLES);
        glColor3f (0.0f, 0.0f, 1.0f);   //bleu
        glVertex3f(1.0f, 0.0f,0.0f);    //sommet 1
        glVertex3f(0.0f, 1.0f, 0.0f);   //sommet 2
        glColor3f (1.0f, 0.0f, 0.0f);   //rouge
        glVertex3f(-1.0f, 0.0f, 0.0f);  //sommet 3
    glEnd();
    glFlush();

 }

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);

    //transformation de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    //Projection perspective définie par un volume de vue donné par :
    // - angle d'ouverture vertical en degré (fov)
    // - rapport largeur/hauteur (aspect ratio)
    // - plan de fenetrage avant (near clipping plane)
    // - plan de fenetrage arrière (far clipping plane)
    gluPerspective(30,x,1,100);
}
