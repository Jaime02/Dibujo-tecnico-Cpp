#include "headers/renderer.h"
#include <QMainWindow>
#include <iostream>

Renderer::Renderer(QMainWindow *parent)
{
    this->parent = parent;
}

QSize Renderer::sizeHint() const {
    return QSize(700, 700);
}

void Renderer::resizeEvent(QResizeEvent *event){
    if (this->width() > this->height()){
        this->resize(this->height(), this->height());
    } else {
        this->resize(this->width(), this->width());
    }
}

const char *vertexShaderSource =
    "#version 330 core                                      \n"
    "layout (location = 0) in vec3 aPos;                    \n"
    "void main()                                            \n"
    "{                                                      \n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);   \n"
    "}                                                      \0";

const char *fragmentShaderSource =
    "#version 330 core                                  \n"
    "out vec4 FragColor;                                \n"
    "void main()                                        \n"
    "{                                                  \n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);      \n"
    "}                                                  \0";

void Renderer::initializeGL(){
    initializeOpenGLFunctions();
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
}

void Renderer::paintGL(){
    initializeOpenGLFunctions();
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    const float vertices[] = {
        0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, sizeof(vertices)/sizeof(float));

    GLint dims[2];
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dims);
    std::cout << "dimenson x:" << dims[0] << " dimenson y:" << dims[1] << std::endl;

    this->update();
}

