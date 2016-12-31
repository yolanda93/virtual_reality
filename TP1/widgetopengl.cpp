// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include "widgetopengl.h"


#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions_3_3_Core()
{

    m_angleX = 30;
    m_angleY = 30;
    m_angleZ = 0;
    changeAngle=false;
    animate=false;
    m_programme = new QOpenGLShaderProgram(this);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject(this);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(1);//  rate -> 1 ms.


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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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
    glm::vec3 A = glm::vec3(0, 0, 1);
    glm::vec3 B = glm::vec3(1, 0, 1);
    glm::vec3 C = glm::vec3(1, 1, 1);
    glm::vec3 D = glm::vec3(0, 1, 1);
    glm::vec3 E = glm::vec3(0, 0, 0);
    glm::vec3 F = glm::vec3(1, 0, 0);
    glm::vec3 G = glm::vec3(1, 1, 0);
    glm::vec3 H = glm::vec3(0, 1, 0);

    // colors
    glm::vec3 rouge = glm::vec3(1,0,0);
    glm::vec3 vert = glm::vec3(0, 1, 0);
    glm::vec3 bleu = glm::vec3(0,0,1);
    glm::vec3 cyan = glm::vec3(0,1,1);
    glm::vec3 magenta = glm::vec3(1,0,1);
    glm::vec3 jaune = glm::vec3(1,1,0);


    //Tableau des données : 3 sommets puis 3 couleurs
    glm::vec3  vertex_data[] = {
        A, B, C, D,
        B, F, G, C,
        F, E, H, G,
        E, A, D, H,
        D, C, G, H,
        E, F, B, A,
        rouge, rouge, rouge, rouge,
        magenta, magenta, magenta, magenta,
        vert, vert, vert, vert,
        jaune, jaune, jaune, jaune,
        bleu, bleu, bleu, bleu,
        cyan, cyan, cyan, cyan,
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
            m_programme->setAttributeArray(1, GL_FLOAT, BUFFER_OFFSET(24*sizeof(glm::vec3)),3);

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
    glm::mat4 vue = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -4));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5,-0.5,-0.5));
    model =glm::rotate(model, m_angleX, glm::vec3(1.0f, 0.0f, 0.0f))* glm::rotate(model, m_angleY, glm::vec3(0.0f, 1.0f, 0.0f))*  glm::rotate(model, m_angleZ, glm::vec3(0.0f, 0.0f, 1.0f));

    m_matrix = proj * vue * model ;
    m_matrix = glm::transpose(m_matrix);

    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", QMatrix4x4(glm::value_ptr(m_matrix)));

    m_vao->bind();

    glDrawArrays(GL_QUADS,0, 24);
    int i = 0;
    while(i <=20)
    {
      glDrawArrays(GL_TRIANGLE_FAN, i, 4);
      i=i+4;
    }

        glEnd();

    m_vao->release();
    m_programme->release();

}


void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

//  4. Manipulation of the cube with the mouse
void WidgetOpenGL::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent *event)
{

    float dx = ((float)event->x() - lastPos.x())/width();
    float dy = ((float)event->y() - lastPos.y())/height();


       if( event->buttons() == Qt::RightButton)
       {
           m_angleX += dy*180;
           m_angleY += dx*180;

       }else{
           m_angleX += dy*180;
           m_angleZ += dx*180;
       }

       QOpenGLWidget::update();
       lastPos = event->pos();
}

//5. Interaction with the widget OpenGL
void WidgetOpenGL::startAnimation(){

    if(animate){
        animate=false;
    }
    else{
        animate=true;
    }
}

void WidgetOpenGL::changeFov(int angle){
     changeAngle=true;
     m_angleY += angle;
}


void WidgetOpenGL::update()
{
    if(animate){
       m_angleY += 4;
       QOpenGLWidget::update();
    }
    if(changeAngle){
       QOpenGLWidget::update();
       changeAngle=false;
    }

}

void WidgetOpenGL::changeOpacity(int value)
{
    m_programme->setUniformValue("u_opacity", value);
    QOpenGLWidget::update();
}
