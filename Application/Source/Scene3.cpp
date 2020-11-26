#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{

	rotateAngle = 0;
	rotateAngle2 = 0;
	rotateAngle3 = 0;
	translateX = 0;
	translateX2 = -10;
	scaleAll = 6;
	scaleAll2 = 1.5;
	scaleAll3 = 1;

	rotateDir = 360;
	rotateDir2 = 360;
	rotateDir3 = 360;
	translateDir = 5;
	translateDir2 = 5;
	scaleDir = -1;
	scaleDir2 = 1;
	scaleDir3 = 0.3;

	//Load vertex and fragment shaders
	m_programID = LoadShaders(
		//"Shader//SimpleVertexShader.vertexshader",
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Use our shader
	glUseProgram(m_programID);

	// Init VBO here
	// Set background color to dark blue

	glClearColor(0.9f, 0.7f, 0.0f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// an array of 3 vectors which represents 3 vertices
	//static const GLfloat vertex_buffer_data_1[] =
	//{
	//	-1.0f, 0.0f, 0.0f, // vertex 0 of triangle
	//	0.0f, 1.0f, 0.0f, // vertex 1 of triangle
	//	1.0f, 0.0f, 0.0f, // vertex 2 of triangle
	//};
	// set the current active buffer

	static const GLfloat vertex_buffer_data_1[] = {
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
	};
	

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	// TRANSFER VERTICES TO OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_1), vertex_buffer_data_1, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 verticles
	//static const GLfloat color_buffer_data_1[] = {
	//	0.9f, 0.7f, 0.9f, //color of vertex 0
	//	1.0f, 0.0f, 0.0f, //color of vertex 1 
	//	0.0f, 0.0f, 0.7f, //color of vertex 2
	//};
	static const GLfloat color_buffer_data_1[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);

	
	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_2[] =
	{
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};
	 /*set the current active buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	 /*TRANSFER VERTICES TO OPENGL*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);

	//AN ARRAY OF 3 VECTORS WHICH REPRESENTS THE COLORS OF THE 3 VERTICES
	static const GLfloat (color_buffer_data_2)[] = {
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2), color_buffer_data_2, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data_3[] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	// TRANSFER VERTICES TO OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_3), vertex_buffer_data_3, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 verticles
	//static const GLfloat color_buffer_data_1[] = {
	//	0.9f, 0.7f, 0.9f, //color of vertex 0
	//	1.0f, 0.0f, 0.0f, //color of vertex 1 
	//	0.0f, 0.0f, 0.7f, //color of vertex 2
	//};
	static const GLfloat color_buffer_data_3[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_3), color_buffer_data_3, GL_STATIC_DRAW);

	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_4[] =
	{
		-0.15f, 0.25f, 0.0f,
		0.15f, 0.25f, 0.0f,
		-0.25f, 0.10f, 0.0f,
		0.25f, 0.10f, 0.0f,
		-0.25f, -0.1f, 0.0f,
		0.25f, -0.1f, 0.0f,
		-0.15f, -0.25f, 0.0f,
		0.15f, -0.25f, 0.0f,
	};
	/*set the current active buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	/*TRANSFER VERTICES TO OPENGL*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_4), vertex_buffer_data_4, GL_STATIC_DRAW);

	//AN ARRAY OF 3 VECTORS WHICH REPRESENTS THE COLORS OF THE 3 VERTICES
	static const GLfloat(color_buffer_data_4)[] = {
		1.0f, 1.0f, 0.0f, //color of vertex 0
		1.0f, 1.0f, 0.0f, //color of vertex 1
		1.0f, 1.0f, 0.0f, //color of vertex 2
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_4), color_buffer_data_4, GL_STATIC_DRAW);

	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_5[] =
	{
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};
	/*set the current active buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	/*TRANSFER VERTICES TO OPENGL*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_5), vertex_buffer_data_5, GL_STATIC_DRAW);

	//AN ARRAY OF 3 VECTORS WHICH REPRESENTS THE COLORS OF THE 3 VERTICES
	static const GLfloat(color_buffer_data_5)[] = {
		1.0f, 0.5f, 0.0f, //color of vertex 0
		1.0f, 0.5f, 0.0f, //color of vertex 1
		1.0f, 0.5f, 0.0f, //color of vertex 2
		1.0f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_5), color_buffer_data_5, GL_STATIC_DRAW);

	// an array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_6[] =
	{
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};
	/*set the current active buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
	/*TRANSFER VERTICES TO OPENGL*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_6), vertex_buffer_data_6, GL_STATIC_DRAW);

	//AN ARRAY OF 3 VECTORS WHICH REPRESENTS THE COLORS OF THE 3 VERTICES
	static const GLfloat(color_buffer_data_6)[] = {
		0.0f, 0.0f, 0.1f, //color of vertex 0
		0.0f, 0.0f, 0.4f, //color of vertex 1
		0.0f, 0.0f, 0.4f, //color of vertex 2
		0.0f, 0.0f, 0.1f,
		0.0f, 0.0f, 0.1f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_6), color_buffer_data_6, GL_STATIC_DRAW);

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
}


void Scene3::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE)) 
	{
		rotateAngle += (float)(rotateDir * dt);
		rotateAngle2 += (float)(rotateDir2 * dt);
		translateX += (float)(translateDir * dt);
		translateX2 += (float)(translateDir2 * dt);
		scaleAll += (float)(scaleDir * dt);
		scaleAll2 += (float)(scaleDir2 * dt);
		scaleAll3 += (float)(scaleDir3 * dt);

		if (translateX >= 25)
			translateDir *= -1;
		else if (translateX <= -25)
			translateDir *= -1;

		if (translateX2 >= -10)
			translateDir2 *= 1;
		if (translateX2 >= 10)
			translateX2 = -10;

		if (rotateAngle > 360)
			rotateAngle = -1;
		else if (rotateAngle < 0)
			rotateAngle = -1;

		if (scaleAll >= 7)
			scaleDir *= -1;
		else if (scaleAll <= 6.5)
			scaleDir *= -1;

		if (scaleAll2 >= 2)
			scaleDir2 *= -1;
		else if (scaleAll2 <= 1.5)
			scaleDir2 *= -1;

		if (scaleAll3 >= 1)
			scaleDir3 *= -1;
		else if (scaleAll3 <= -1)
			scaleDir3 *= -1;

		if (rotateAngle2 > 90)
			rotateDir2 *= -1;
		else if (rotateAngle2 < -50)
			rotateDir2 *= -1;

		if (rotateAngle3 > 180)
			rotateDir3 *= -1;
		else if (rotateAngle3 < 100)
			rotateDir3 *= -1;
    }
	
}

void Scene3::Render()
{
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	projection.SetToOrtho(-10, +10, -10, +10, -10, +10); //Our world is a cube defined by these boundaries

	// Render VBO here
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//crane's head
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

	scale.SetToScale(0.5, 0.8, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 0.3 , translateX2 + 0.3 , 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//crane's head
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

	scale.SetToScale(0.5, 0.8, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 3, translateX2 + 3, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//crane's head
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

	scale.SetToScale(0.5, 0.8, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 4, translateX2 - 1.6, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's right wing
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

	scale.SetToScale(0.5, 0.6, 1);
	rotate.SetToRotation(80, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 0.5, translateX2 + 0.1, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's right wing
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

	scale.SetToScale(0.5, 0.6, 1);
	rotate.SetToRotation(80, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 3.1, translateX2 + 2.8, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's right wing
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

	scale.SetToScale(0.5, 0.6, 1);
	rotate.SetToRotation(80, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 4.3, translateX2 - 1.8, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's left wing
	scale.SetToScale(0.7, 0.5, 1);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(translateX2 +0.2,translateX2 -0.2,0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Square
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's left wing
	scale.SetToScale(0.7, 0.5, 1);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 2.8, translateX2 + 2.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Square
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//Crane's left wing
	scale.SetToScale(0.7, 0.5, 1);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(translateX2 + 4, translateX2 - 2.1, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Square
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	scale.SetToScale(scaleAll2, scaleAll2, 0);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(0, 3, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	scale.SetToScale(10, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 0, -2);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_6]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	scale.SetToScale(scaleAll2, scaleAll2, 0);
	rotate.SetToRotation(45, 0, 0, 1);
	translate.SetToTranslation(3, 3, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	
	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);

	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle


	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle 


	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	scale.SetToScale(1.3, 2, 0);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(5, -3, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	scale.SetToScale(1.3, 2, 0);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(6, -2, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);



	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	//glVertexAttribPointer(
	//	0, //attribute 0. Must match the layout in the shader. usually - is for vertex
	//	3, //size
	//	GL_FLOAT, //TYPE
	//	GL_FALSE, //NOMALIZED?
	//	0, // STRIDE
	//	0  // ARRAY BUFFER OFFSET
	////);


	//glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 5); // STARTING FROM VERTEX 0; 3 vertices = 1triangle 

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);

	scale.SetToScale(scaleAll, scaleAll, 1);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-4, 5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, 
		&MVP.a[0]); //update the shader with new MVP


	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	//glVertexAttribPointer(
	//	0, //attribute 0. Must match the layout in the shader. usually - is for vertex
	//	3, //size
	//	GL_FLOAT, //TYPE
	//	GL_FALSE, //NOMALIZED?
	//	0, // STRIDE
	//	0  // ARRAY BUFFER OFFSET
	//);

	//scale.SetToScale(scaleAll, scaleAll, 1);
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToTranslation(-4, -1, 0);
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//	&MVP.a[0]); //update the shader with new MVP


	//glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	//glVertexAttribPointer(
	//	0, //attribute 0. Must match the layout in the shader. usually - is for vertex
	//	3, //size
	//	GL_FLOAT, //TYPE
	//	GL_FALSE, //NOMALIZED?
	//	0, // STRIDE
	//	0  // ARRAY BUFFER OFFSET
	//);

	//scale.SetToScale(scaleAll, scaleAll, 1);
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToTranslation(-5, -2, 0);
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//	&MVP.a[0]); //update the shader with new MVP


	//glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(
		0, //attribute 0. Must match the layout in the shader. usually - is for vertex
		3, //size
		GL_FLOAT, //TYPE
		GL_FALSE, //NOMALIZED?
		0, // STRIDE
		0  // ARRAY BUFFER OFFSET
	);

	scale.SetToScale(scaleAll3, scaleAll3, scaleAll3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-4, 5, 1);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	//glVertexAttribPointer(
	//	0, //attribute 0. Must match the layout in the shader. usually - is for vertex
	//	3, //size
	//	GL_FLOAT, //TYPE
	//	GL_FALSE, //NOMALIZED?
	//	0, // STRIDE
	//	0  // ARRAY BUFFER OFFSET
	//);

	//scale.SetToScale(scaleAll3, scaleAll3, 1);
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToTranslation(-4, -1, 1);
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//	&MVP.a[0]); //update the shader with new MVP
	//glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	//glEnableVertexAttribArray(0); //1st attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	//glVertexAttribPointer(
	//	0, //attribute 0. Must match the layout in the shader. usually - is for vertex
	//	3, //size
	//	GL_FLOAT, //TYPE
	//	GL_FALSE, //NOMALIZED?
	//	0, // STRIDE
	//	0  // ARRAY BUFFER OFFSET
	//);

	//scale.SetToScale(scaleAll3, scaleAll3, 1);
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToTranslation(-5, -2, 1);
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	//	&MVP.a[0]); //update the shader with new MVP
	//glEnableVertexAttribArray(1); //2nd Attribute buffer : colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // STARTING FROM VERTEX 0; 3 vertices = 1triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
