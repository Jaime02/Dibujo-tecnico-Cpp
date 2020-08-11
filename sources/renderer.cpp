#include "headers/renderer.h"

Renderer::Renderer(MainWindow* parent)
{
}

QSize Renderer::sizeHint() const {
	return QSize(700, 700);
}

void Renderer::resizeEvent(QResizeEvent* event) {
	QOpenGLWidget::resizeEvent(event);
	if (width() > height()) {
		resize(height(), height());
	}
	else {
		resize(width(), width());
	}
}

const char* vertexShaderSource =
"#version 330 core                                                           \n"
"layout(location = 0) in vec3 aPos;                                          \n"
"                                                                            \n"
"uniform mat4 model;                                                         \n"
"uniform mat4 view;                                                          \n"
"uniform mat4 projection;                                                    \n"
"                                                                            \n"
"void main()                                                                 \n"
"{                                                                           \n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0f);              \n"
"}                                                                           \0";

const char* fragmentShaderSource =
"#version 330 core                                  \n"
"out vec4 color;                                    \n"
"void main()                                        \n"
"{                                                  \n"
"    color = vec4(0.5f, 0.5f, 0.2f, 1.0f);          \n"
"}                                                  \0";

const std::vector<double> points{
	 0.5, 0.5, 0.0,
	 0.5, 0.0, 0.0
};

void Renderer::initializeGL() {
	initializeOpenGLFunctions();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	unsigned int vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* DEBUG PURPOSES
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
	}
	// */

	unsigned int shaderProgram{ glCreateProgram() };
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* DEBUG PURPOSES
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
	}
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
	}
	*/
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, std::size(points) * sizeof(double), &points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glPointSize(100);
	glEnable(GL_POINT_SMOOTH);

	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	// pass transformation matrices to the shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
}

void Renderer::drawPoints(const std::vector<double> points, int vec_len) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, vec_len);
}

void Renderer::paintGL() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	Renderer::drawPoints(points, std::size(points));

	update();
}