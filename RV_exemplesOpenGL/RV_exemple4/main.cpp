// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include <QApplication>
#include "widgetopengl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);          // cible OpenGL 3.3
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    WidgetOpenGL w;
    w.setWindowTitle("Exemple 4 : OpenGL 3.3 avec classes QOpenGL");
    w.show();

    return a.exec();
}
