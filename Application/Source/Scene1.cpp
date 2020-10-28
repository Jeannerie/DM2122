#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);

	// Use our shader
	glUseProgram(m_programID);

	// Init VBO here
	// Set background color to dark blue

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_1[] =
	{
		-1.0f, 0.0f, 0.0f, // vertex 0 of triangle
		0.0f, 1.0f, 0.0f, // vertex 1 of triangle
		1.0f, 0.0f, 0.0f, // vertex 2 of triangle
	};
	// set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// TRANSFER VERTICES TO OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_1), vertex_buffer_data_1, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 verticles
	static const GLfloat color_buffer_data_1[] = {
		0.9f, 0.7f, 0.9f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1 
		0.0f, 0.0f, 0.7f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);

	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_2[] =
	{
		0.0f, 1.0f, 0.0f, // vertex 0 of triangle
		1.0f, 0.0f, 1.0f, // vertex 1 of triangle
		0.0f, 0.0f, 0.0f, // vertex 2 of triangle
	};
	// set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	// TRANSFER VERTICES TO OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);

	//AN ARRAY OF 3 VECTORS WHICH REPRESENTS THE COLORS OF THE 3 VERTICES
	static const GLfloat (color_buffer_data_2)[] = {
		0.0f, 0.0f, 1.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2), color_buffer_data_2, GL_STATIC_DRAW);
}


void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
