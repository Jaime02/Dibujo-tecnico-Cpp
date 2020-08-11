#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLExtraFunctions>
#include <headers/mainwindow.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
public:
	Renderer(MainWindow* parent);
	QSize sizeHint() const override;
	void resizeEvent(QResizeEvent* event) override;
	void paintGL() override;
	void initializeGL() override;

	void drawPoints(const std::vector<double> points, int vec_len);

private:
	unsigned int VAO;
	unsigned int VBO;
	int shaderProgram;
};
