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
"uniform mat4 view;                                                          \n"
"uniform mat4 projection;                                                    \n"
"                                                                            \n"
"void main()                                                                 \n"
"{                                                                           \n"
"	gl_Position = projection * view * vec4(aPos, 1.0f);                      \n"
"}                                                                           \0";

const char* fragmentShaderSource =
"#version 330 core                                  \n"
"out vec4 color;                                    \n"
"void main()                                        \n"
"{                                                  \n"
"    color = vec4(0.5f, 0.5f, 0.2f, 1.0f);          \n"
"}                                                  \0";

const std::vector<float> points {
	0.5, 0.5, 0.0,
	0.0, 0.0, 0.0,
	-0.5, 0.5, -1.0,
	0.0, 0.5, 1.0,
};

void Renderer::initializeGL() {
	initializeOpenGLFunctions();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/* DEBUG PURPOSES
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
	}
	*/

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* DEBUG PURPOSES

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
	}
	*/

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* DEBUG PURPOSES
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
	}
	*/
	
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glPointSize(100);
	glEnable(GL_POINT_SMOOTH);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
}

void Renderer::drawPoints(const std::vector<float> points, int vec_len, const float* data) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vec_len * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, vec_len);
}

void Renderer::paintGL() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	Renderer::drawPoints(points, points.size(), points.data());
	update();
}