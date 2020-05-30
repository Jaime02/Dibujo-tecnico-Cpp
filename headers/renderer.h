#pragma once
#include <QOpenGLWidget>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLExtraFunctions>

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    QMainWindow *parent;

public:
    Renderer(QMainWindow *parent);
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *event) override;
    void paintGL() override;
    void initializeGL() override;

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
};

