#include "Scene5.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
{	

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Use our shader
	glUseProgram(m_programID);
	
	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 0), 1.f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 40, 4.2);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 40, 40 ,4.2);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 1.f);
}

void Scene5::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(10 * dt);

	camera.Update(dt);
}

void Scene5::Render()
{
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	//Mtx44 translate, rotate, scale;
	//Mtx44 MVP;

	//These will be replaced by matrix stack soon
	//Mtx44 model;
	//Mtx44 view;
	//Mtx44 projection;

	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	//Set all matrices to identity
	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();
	//model.SetToIdentity();

	//Set view matrix using camera settings
	//view.SetToLookAt(
		//camera.position.x, camera.position.y, camera.position.z,
		//camera.target.x, camera.target.y, camera.target.z,
		//camera.up.x, camera.up.y, camera.up.z
					//);


	//Set projection matrix to perspective mode
	//projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane

	//model.SetToIdentity();
	//MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_AXES]->Render();

	//translate.SetToIdentity();
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//scale.SetToIdentity();
	//model = translate * rotate * scale;
	//MVP = projection * view * model;
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	//meshList[GEO_CUBE]->Render();

	//earth
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Translate(22, 10, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	//earth
	modelStack.PushMatrix();
	modelStack.Rotate(-rotateAngle, 0, 1, 0);
	modelStack.Translate(-22, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	//earth
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Translate(30, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	//earth
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Translate(-22, 0, 0);
	modelStack.Scale(1, 1, 1);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();
	
	// square
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle + 90, 0, 1, 0);
	modelStack.Translate(12, 0, 0);
	modelStack.Scale(2, 2, 2);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_CUBE]->Render();
	modelStack.PopMatrix();
	
	// ring
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle + 90, 0, 1, 0);
	modelStack.Translate(12, 0, 0);
	modelStack.Scale(0.4, 0.6, 0.4);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_CIRCLE]->Render();
	modelStack.PopMatrix();

	//earth
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(1, 1, 1);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_SPHERE]->Render();
	

	// ring
	modelStack.PushMatrix();
	modelStack.Translate(-22, 0, 0);
	modelStack.Scale(2, 2, 1);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	meshList[GEO_CIRCLE]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	
}

void Scene5::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
