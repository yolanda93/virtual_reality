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
    glDeleteBuffers(1, &m_ibo);

}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair

    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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
            "uniform mat4 u_ModelViewProjectionMatrix;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);\n"
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
            "out vec4 frag_color;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "    frag_color = vec4(0.9, 0.2, 0.2, 1);\n"
            "}\n";
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &res);
    if (res != GL_TRUE)
    {
        QMessageBox msg;
        msg.setText("Echec compilation index shader");
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
    //Tableau des donnees : 4 sommets
    GLfloat vertex_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };

    GLuint index_data[] = {
        0, 1, 2, 0, 1, 3, 1, 2, 3, 0, 2, 3
    };

    //Generation d'un nom de VBO
    glGenBuffers(1, &m_vbo);
    //Generation d'un nom de IBO
    glGenBuffers(1, &m_ibo);

    //Generation du VAO
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

        //Liaison du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        //Ecriture des donnees dans le VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

        //Liaison du IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        //Ecriture des donnees dans le IBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

        //Lien avec les attributs du programme
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}



void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.33f, 0.1f, 100.0f);
    glm::mat4 vue = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
    glm::mat4 model = glm::mat4(1.0f);

    m_matrix = proj * vue * model;
    m_matrix = glm::transpose(m_matrix);

    glUseProgram(m_programme);

        //Réglages du Shader Program
        GLuint matrice = glGetUniformLocation(m_programme, "u_ModelViewProjectionMatrix");
        glUniformMatrix4fv(matrice, 1, GL_FALSE, glm::value_ptr(m_matrix));

        glBindVertexArray(m_vao);

            //Commande de rendu
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

    glUseProgram(0);
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}
