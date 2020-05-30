#pragma once
#include <QOpenGLWidget>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLExtraFunctions>
#include <headers/mainwindow.h>

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    MainWindow *parent;

public:
    Renderer(MainWindow *paarent);
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *event) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
};
