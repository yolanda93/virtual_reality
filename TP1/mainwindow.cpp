#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSurfaceFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setDepthBufferSize(24);
    format.setVersion(3, 3); // OpenGL 3.3
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);
    setWindowTitle("OpenGL 3.3 with QOpenGL classes");

}

MainWindow::~MainWindow()
{
    delete ui;
}
