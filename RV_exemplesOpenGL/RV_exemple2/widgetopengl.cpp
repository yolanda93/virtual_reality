// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2016-17

#include "widgetopengl.h"
#include <QMessageBox>

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions_3_3_Core()
{ }

WidgetOpenGL::~WidgetOpenGL()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_programme);
    glDeleteBuffers(1, &m_vbo);
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair

    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    initializeVAO();
    initializeShader();
}

void WidgetOpenGL::initializeShader()
{
    m_programme = glCreateProgram();

    //Vertex Shader
    GLint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vs_source = "#version 330 core\n"
            "layout(location=0) in vec3 pos;\n"
            "layout(location=1) in vec3 col;\n"
            "uniform mat4 u_ModelViewProjectionMatrix;\n"
            "out vec4 color;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);\n"
            "    color = vec4(col, 1);\n"
            "}\n";
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    GLint res;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &res);
    if (res != GL_TRUE)
    {
        QMessageBox msg;
        msg.setText("Echec compilation vertex shader");
        msg.exec();
    }

    glAttachShader(m_programme, vs);

    //Fragment Shader
    GLint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fs_source = "#version 330 core\n"
            "in vec4 color;\n"
            "out vec4 frag_color;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "    frag_color = color.rgba;\n"
            "}\n";
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &res);
    if (res != GL_TRUE)
    {
        QMessageBox msg;
        msg.setText("Echec compilation fragment shader");
        msg.exec();
    }

    glAttachShader(m_programme, fs);

    glLinkProgram(m_programme);
    glGetShaderiv(m_programme, GL_LINK_STATUS, &res);
    if (res != GL_TRUE)
    {
        QMessageBox msg;
        msg.setText("Echec link");
        msg.exec();
    }

    glDetachShader(m_programme, vs);
    glDetachShader(m_programme, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void WidgetOpenGL::initializeVAO()
{
    //Tableau des donnees : 3 sommets puis 3 couleurs
    GLfloat vertex_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    //Generation d'un nom de VBO
    glGenBuffers(1, &m_vbo);

    //Generation du VAO
    glGenVertexArrays(1, &m_vao);

    //Liaison du VAO
    glBindVertexArray(m_vao);

        //Liaison du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        //Ecriture des donnees dans le VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

        //Lien avec les attributs du programme
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(9*sizeof(GLfloat)));

        //Activation des attributs
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        //Libération du VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Libération du VAO
    glBindVertexArray(0);
}



void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Réglages du Shader Program
    glUseProgram(m_programme);

    //Récupération de l'identifiant de la variable uniforme
    GLuint matrice = glGetUniformLocation(m_programme, "u_ModelViewProjectionMatrix");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.33f, 0.1f, 100.0f);
    glm::mat4 vue = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
    glm::mat4 model = glm::mat4(1.0f);

    m_matrix = proj * vue * model;
    m_matrix = glm::transpose(m_matrix);

    //Passage de la valeur de la matrice uniforme
    glUniformMatrix4fv(matrice, 1, GL_FALSE, glm::value_ptr(m_matrix));

    //Activation du VAO
    glBindVertexArray(m_vao);

        //Commande de rendu
        glDrawArrays(GL_TRIANGLES, 0, 3);

    //Désactivation du VAO
    glBindVertexArray(0);
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}
