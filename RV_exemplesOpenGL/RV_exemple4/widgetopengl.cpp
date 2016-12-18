// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions_3_3_Core()
{
    m_programme = new QOpenGLShaderProgram(this);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject(this);
}

WidgetOpenGL::~WidgetOpenGL()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair

    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);


    initializeShader();
    initializeVAO();
}

void WidgetOpenGL::initializeShader()
{
    bool resultat;
    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Link
    resultat = m_programme->link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_programme->log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    m_programme->release();
}

void WidgetOpenGL::initializeVAO()
{
    //Tableau des données : 3 sommets puis 3 couleurs
    GLfloat vertex_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };


    //creation du VA0 et du VBO
    m_vao->create();
    m_vbo->create();

    //Lien du VAO
    m_vao->bind();

        //lien du VBO
        m_vbo->bind();

        //Ecriture des données dans le VBO
        m_vbo->allocate(vertex_data,sizeof(vertex_data));
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        //Lien entre VBO et les variables d'attribut du vertex shader
        m_programme->bind();
            m_programme->setAttributeArray(0, GL_FLOAT, BUFFER_OFFSET(0),3);
            m_programme->setAttributeArray(1, GL_FLOAT, BUFFER_OFFSET(9*sizeof(GLfloat)),3);

            //Activation des attributs
            m_programme->enableAttributeArray(0);
            m_programme->enableAttributeArray(1);
        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();

}



void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.33f, 0.1f, 100.0f);
    glm::mat4 vue = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
    glm::mat4 model = glm::mat4(1.0f);

    m_matrix = proj * vue * model;
    m_matrix = glm::transpose(m_matrix);

    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", QMatrix4x4(glm::value_ptr(m_matrix)));

    m_vao->bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

    m_vao->release();
    m_programme->release();
}


void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}
