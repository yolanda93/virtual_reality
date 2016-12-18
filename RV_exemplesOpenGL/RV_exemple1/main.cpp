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
    QSurfaceFormat::setDefaultFormat(format);

    WidgetOpenGL w;
    w.setWindowTitle("Réalité virtuelle - exemple 2 : openGL 2.2");
    w.show();

    return a.exec();
}
