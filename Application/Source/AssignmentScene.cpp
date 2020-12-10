#include "AssignmentScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Light.h"
#include "Material.h"
#include "Utility.h"

Assignment::Assignment()
{
}

Assignment::~Assignment()
{
}

void Assignment::Init()
{
	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	/*glEnable(GL_CULL_FACE);*/

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//animation stuff
	translateY = -1.8;
	translateDir = 1;

	rotateAngle = 0;
	rotateDir = -105;

	//Load vertex and fragment shaders


	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	// Use our shader
	glUseProgram(m_programID);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;


	//// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.0, 1.0, 1.0), 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 1.f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 40, 1);

	meshList[GEO_TAIL] = MeshBuilder::GenerateSphere("sphere", Color(0.0, 1.0, 1.0), 40, 40, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 1.0, 1.0), 40, 40, 1);
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("sphere", Color(1, 1.0, 0.5), 40, 40, 1);

	meshList[GEO_TOOTH] = MeshBuilder::GenerateCone("cone", Color(1, 1.0, 1.0),1 , 1);
	meshList[GEO_SNOSE] = MeshBuilder::GenerateCone("cone", Color(0.9, 0.7, 0.0), 1, 1);



	meshList[GEO_IBERG] = MeshBuilder::GenerateCone("cone", Color(1, 1.0, 1.0), 1, 1);

	meshList[GEO_HSPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1.0, 0.5), 40, 40, 1);

	meshList[GEO_EYESL] = MeshBuilder::GenerateHemisphere("hemisphere", Color(0, 0,0 ), 40, 40, 1);
	meshList[GEO_LPUPILS] = MeshBuilder::GenerateCircle("circle", Color(1, 1, 1), 40, 1);
	meshList[GEO_RPUPILS] = MeshBuilder::GenerateCircle("circle", Color(1, 1, 1), 40, 1);

	meshList[GEO_WSPOTS] = MeshBuilder::GenerateCircle("circle", Color(1.0, 1.0, 1.0), 40, 1);

	meshList[GEO_EYESR] = MeshBuilder::GenerateHemisphere("hemisphere", Color(0, 0, 0), 40, 40, 1);

	meshList[GEO_SBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1.0, 1.0), 40, 40, 1);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 40, 40, 1);

	


	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 3.f;

	meshList[GEO_TOOTH]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_TOOTH]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TOOTH]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TOOTH]->material.kShininess = 3.f;

	meshList[GEO_SNOSE]->material.kAmbient.Set(0.9f, 0.7f, 0.0f);
	meshList[GEO_SNOSE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SNOSE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SNOSE]->material.kShininess = 3.f;

	meshList[GEO_IBERG]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_IBERG]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_IBERG]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_IBERG]->material.kShininess = 3.f;

	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kShininess = 3.f;

	meshList[GEO_HSPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HSPHERE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_HSPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HSPHERE]->material.kShininess = 3.f;

	meshList[GEO_EYESL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYESL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_EYESL]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYESL]->material.kShininess = 3.f;

	meshList[GEO_WSPOTS]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_WSPOTS]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_WSPOTS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_WSPOTS]->material.kShininess = 3.f;

	meshList[GEO_LPUPILS]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LPUPILS]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_LPUPILS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LPUPILS]->material.kShininess = 3.f;

	meshList[GEO_SBALL]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_SBALL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SBALL]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SBALL]->material.kShininess = 3.f;

	meshList[GEO_EYESR]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYESR]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_EYESR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYESR]->material.kShininess = 3.f;

	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.8f, 0.8f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 0.1f;

	meshList[GEO_TAIL]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_TAIL ]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TAIL]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TAIL]->material.kShininess = 0.1f;
}

void Assignment::Update(double dt)
{
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(10 * dt);

	camera.Update(dt);

	static const float LSPEED = 20.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);


	if (Application::IsKeyPressed('C')) //on light
		light[0].power = 1;

	if (Application::IsKeyPressed('V')) //off light
		light[0].power = -1;

	if (Application::IsKeyPressed(VK_SPACE)) {
		translateY += (float)(translateDir * 5 * dt);
		rotateAngle += (float)(rotateDir * 5 *  dt);

		if (rotateAngle > 90)
			rotateDir = -180;
		else if (rotateAngle < 0)
			rotateAngle = -180;

		if (translateY >= 0.5)
			translateDir = -1;
		if (translateY <= -1.5)
			translateDir = 1;
	}
		
}

void Assignment::Render()
{	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	modelStack.LoadIdentity();


	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.89, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//yellow body
	modelStack.PushMatrix();
	modelStack.Translate(0.2, 0, 0);
	modelStack.Rotate(40, 0, 0, 1);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_HSPHERE], true);
	modelStack.PopMatrix();

	//left eye
	modelStack.PushMatrix();
	modelStack.Translate(1.5, 2.6, 1);
	modelStack.Rotate(150, 0, 0, 1);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_EYESL], true);
	modelStack.PopMatrix();

	//left pupil
	modelStack.PushMatrix();
	modelStack.Translate(1.7, 2.85, 0.95);
	modelStack.Rotate(150, 0, 0, 1);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[GEO_LPUPILS], true);
	modelStack.PopMatrix();

	//right pupil
	modelStack.PushMatrix();
	modelStack.Translate(1.7, 2.85, -0.95);
	modelStack.Rotate(150, 0, 0, 1);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[GEO_RPUPILS], true);
	modelStack.PopMatrix();

	//right eye
	modelStack.PushMatrix();
	modelStack.Translate(1.5, 2.6, -1);
	modelStack.Rotate(150, 0, 0, 1);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_EYESR], true);
	modelStack.PopMatrix();

	//snowman left eyes
	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 4.6, 17.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_EYESR], true);
	modelStack.PopMatrix();

	//snowman right eyes
	modelStack.PushMatrix();
	modelStack.Translate(-7.9, 4.6, 15.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_EYESR], true);
	modelStack.PopMatrix();

	//blue base body
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//Left mouth
	modelStack.PushMatrix();
	modelStack.Translate(2.5,2.0, -0.8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1, 0.6, 0.5 );
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();
	
	//Right mouth
	modelStack.PushMatrix();
	modelStack.Translate(2.5, 2.0, 0.8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1, 0.6, 0.5);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//Left tooth
	modelStack.PushMatrix();
	modelStack.Translate(3, 1.6, 0.8);
	modelStack.Rotate(230, 0, 0, 1);
	modelStack.Scale(0.4, 0.9, 0.5);
	RenderMesh(meshList[GEO_TOOTH], true);
	modelStack.PopMatrix();

	//Right tooth
	modelStack.PushMatrix();
	modelStack.Translate(3, 1.6, -0.8);
	modelStack.Rotate(230, 0, 0, 1);
	modelStack.Scale(0.4, 0.9, 0.5);
	RenderMesh(meshList[GEO_TOOTH], true);
	modelStack.PopMatrix();

	//left fin
	modelStack.PushMatrix();
	modelStack.Translate(2.0,translateY, 1.5);
	modelStack.Rotate(-85, 0, rotateAngle, 0);
	modelStack.Scale(1.5, 0.5, 0.55);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	////left fin
	//modelStack.PushMatrix();
	//modelStack.Translate(2.0, -1.8, 1.5);
	//modelStack.Rotate(105, 1, 0, 0);
	//modelStack.Scale(1.5, 0.5, 0.25);
	//RenderMesh(meshList[GEO_SPHERE2], true);
	//modelStack.PopMatrix();

	//right fin
	modelStack.PushMatrix();
	modelStack.Translate(2.0, translateY, -1.5);
	modelStack.Rotate(-105, 0, 1, 0);
	modelStack.Scale(1.5, 0.5, 0.55);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0.3, 0, 0);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();*/

	//blue ears
	modelStack.PushMatrix();
	modelStack.Translate(0.115, 2.8, 1.8);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.75,0.375 , 0.75);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//blue ears
	modelStack.PushMatrix();
	modelStack.Translate(0.115, 2.8, -1.8);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.75, 0.375, 0.75);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	//white spots
	modelStack.PushMatrix();
	modelStack.Translate(0.05, 1.20, -2.8);
	modelStack.Rotate(290, 1, 0, 0);
	modelStack.Scale(0.25, 0.25, 0.25);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.95, 0.45, -2.9);
	modelStack.Rotate(290, 1, 0, 0);
	modelStack.Scale(0.25, 0.25, 0.25);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.05, 1.20, 2.8);
	modelStack.Rotate(-290, 1, 0, 0);
	modelStack.Scale(0.25, 0.25, 0.25);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.95, 0.45, 2.9);
	modelStack.Rotate(-290, 1, 0, 0);
	modelStack.Scale(0.25, 0.25, 0.25);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();

	//small white spot
	modelStack.PushMatrix();
	modelStack.Translate(-0.25, 0.5, -3.0);
	modelStack.Rotate(290, 1, 0, 0);
	modelStack.Scale(0.10, 0.10, 0.10);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.25, 0.5, 3.0);
	modelStack.Rotate(-290, 1, 0, 0);
	modelStack.Scale(0.10, 0.10, 0.10);
	RenderMesh(meshList[GEO_WSPOTS], true);
	modelStack.PopMatrix();


	//TAIL
	modelStack.PushMatrix();
	modelStack.Translate(-2, -1.9, -1.5);
	modelStack.Rotate(-130, 0, 1, 0);
	modelStack.Scale(1.2, 0.7, 2);
	RenderMesh(meshList[GEO_TAIL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.5 , -1.9, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.9, 0.7, 2);
	RenderMesh(meshList[GEO_TAIL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2, -1.9, 1.5);
	modelStack.Rotate(130, 0, 1, 0);
	modelStack.Scale(1.2, 0.7, 2);
	RenderMesh(meshList[GEO_TAIL], true);
	modelStack.PopMatrix();

	//ICEBERGS
	modelStack.PushMatrix();
	modelStack.Translate(-15, 4.9, -9.8);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(10.0, 15.0, 15.0);
	RenderMesh(meshList[GEO_IBERG], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20, 4.9, -2.8);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(5.0, 13.0, 10.0);
	RenderMesh(meshList[GEO_IBERG], true);
	modelStack.PopMatrix();

	//Snowman!
	modelStack.PushMatrix();
	modelStack.Translate(-10, 0.2, 16.8);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(3.5, 3.5, 3.5);
	RenderMesh(meshList[GEO_SBALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 4.2, 16.8);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(2.5, 2.5, 2.5);
	RenderMesh(meshList[GEO_SBALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 4.4, 16.4);
	modelStack.Rotate(250, 0, 0, 1);
	modelStack.Scale(0.4, 0.9, 0.5);
	RenderMesh(meshList[GEO_SNOSE], true);
	modelStack.PopMatrix();
}


void Assignment::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}




void Assignment::Exit()
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
