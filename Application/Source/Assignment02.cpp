#include "Assignment02.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Light.h"
#include "Material.h"
#include "Utility.h"
#include "LoadTGA.h"

AssignmentTwo::AssignmentTwo()
{
}

AssignmentTwo::~AssignmentTwo()
{
}

void AssignmentTwo::Init()
{

	tentEntered = false;
	sphealAppear = true;


	FPS = 1;
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
	glEnable(GL_CULL_FACE);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders


	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
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
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	// Use our shader
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f); // CHANGES SPOT LIGHT DIRECTION

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 20, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f); // CHANGES SPOT LIGHT DIRECTION
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	


	//// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_TENT] = MeshBuilder::GenerateOBJMTL("tent", "OBJ//tent_smallOpen.obj", "OBJ//tent_smallOpen.mtl");

	meshList[GEO_GRASS] = MeshBuilder::GenerateOBJMTL("model7",
		"OBJ//grass_leafsLarge.obj", "OBJ//grass_leafsLarge.mtl"); //cottage_diffuse

	meshList[GEO_SHAND] = MeshBuilder::GenerateOBJMTL("model7",
		"OBJ//tree_oak.obj", "OBJ//tree_oak.mtl"); //cottage_diffuse
	//meshList[GEO_SHAND]->textureID =
	//	LoadTGA("Image//tree_texture.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front",
		Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//SKYBOXfront.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left",
		Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//SKYBOXleft.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right",
		Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//SKYBOXright.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top",
		Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//SKYBOXtop.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom",
		Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//SKYBOXbtm.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back",
		Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//SKYBOXback.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.1, 0.3, 0.5), 1.f);
	//meshList[GEO_QUAD]->textureID = LoadTGA("Image//sidm.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 1.f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 40, 1);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 1.0, 1.0), 40, 40, 1);
	
	meshList[GEO_TAIL] = MeshBuilder::GenerateSphere("sphere", Color(0.0, 1.0, 1.0), 40, 40, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 1.0, 1.0), 40, 40, 1);
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("sphere", Color(1, 1.0, 0.5), 40, 40, 1);

	meshList[GEO_TOOTH] = MeshBuilder::GenerateCone("cone", Color(1, 1.0, 1.0), 1, 1);

	meshList[GEO_HSPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1.0, 0.5), 40, 40, 1);

	meshList[GEO_HSPHERE2] = MeshBuilder::GenerateHemisphere("hemisphere", Color(0, 1.0, 1.0), 40, 40, 1);

	meshList[GEO_EYESL] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 40, 40, 1);
	meshList[GEO_LPUPILS] = MeshBuilder::GenerateCircle("circle", Color(1, 1, 1), 40, 1);

	meshList[GEO_WSPOTS] = MeshBuilder::GenerateCircle("circle", Color(1.0, 1.0, 1.0), 40, 1);

	meshList[GEO_SBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1.0, 1.0), 40, 40, 1);

	//meshList[GEO_MODELCHAIR] = MeshBuilder::GenerateOBJ("chair", "OBJ//chair.obj");
	//meshList[GEO_MODELCHAIR]->textureID = LoadTGA("Image//chair.tga");

	//meshList[GEO_MODELDMAN] = MeshBuilder::GenerateOBJ("doorman", "OBJ//doorman.obj");
	//meshList[GEO_MODELDMAN]->textureID = LoadTGA("Image//doorman.tga");

	//meshList[GEO_MODELDART] = MeshBuilder::GenerateOBJ("dart", "OBJ//dart.obj");
	//meshList[GEO_MODELDART]->textureID = LoadTGA("Image//dart.tga");

	//meshList[GEO_MODELDBOARD] = MeshBuilder::GenerateOBJ("dboard", "OBJ//dartboard.obj");
	//meshList[GEO_MODELDBOARD]->textureID = LoadTGA("Image//dartboard.tga");

	//meshList[GEO_MODELSHOE] = MeshBuilder::GenerateOBJ("shoe", "OBJ//shoe.obj");
	//meshList[GEO_MODELSHOE]->textureID = LoadTGA("Image//shoe.tga");

	//meshList[GEO_MODELWINE] = MeshBuilder::GenerateOBJ("wine", "OBJ//winebottle.obj");
	//meshList[GEO_MODELWINE]->textureID = LoadTGA("Image//winebottle.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 40, 40, 1);

	meshList[GEO_GRASS]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_GRASS]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_GRASS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_GRASS]->material.kShininess = 3.f;

	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 3.f;

	meshList[GEO_TOOTH]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_TOOTH]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TOOTH]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TOOTH]->material.kShininess = 3.f;



	meshList[GEO_SPHERE2]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE2]->material.kShininess = 3.f;

	meshList[GEO_HSPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HSPHERE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_HSPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HSPHERE]->material.kShininess = 3.f;

	meshList[GEO_HSPHERE2]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_HSPHERE2]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_HSPHERE2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HSPHERE2]->material.kShininess = 3.f;

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

	meshList[GEO_SHAND]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_SHAND]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SHAND]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SHAND]->material.kShininess = 1.f;

	meshList[GEO_TENT]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_TENT]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TENT]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TENT]->material.kShininess = 1.f;

	meshList[GEO_TAIL]->material.kAmbient.Set(0.1f, 0.1f, 0.3f);
	meshList[GEO_TAIL]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TAIL]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TAIL]->material.kShininess = 0.1f;

	meshList[GEO_TEXT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TEXT]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_TEXT]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TEXT]->material.kShininess = 0.1f; 
}

void AssignmentTwo::Update(double dt)
{
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if (Application::IsKeyPressed('5'))
	{
		//to do: switch light type to POINT and pass the information to shader
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		light[1].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		light[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		light[1].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}	
	FPS = 1.0f / dt;
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

	if (Application::IsKeyPressed('R')) {
		sphealAppear = true;
		tentEntered = false;
		camera.position.x = 0;
		camera.position.y = 0;
		camera.position.z = 0;
	}


	if (Application::IsKeyPressed('C')) //on light
		light[0].power = 1;

	if (Application::IsKeyPressed('V')) //off light
		light[0].power = -1;

	if (((camera.position.x <= 254) && (camera.position.x >= 252)) && ((camera.position.z <= -231) && (camera.position.z >= -238)) && (sphealAppear == true))
	{
		
		sphealAppear = false;
		
	}

	if (((camera.position.x <= 185) && (camera.position.x >= 184)) && ((camera.position.z <= 292) && (camera.position.z >= 267)) && (sphealAppear == false))
	{
		Vector3 view = (camera.target - camera.position).Normalized();
		camera.position.x = 184;
		camera.target = view + camera.position;
	}

	if (((camera.position.x <= 213) && (camera.position.x >= 186)) && ((camera.position.z <= 264) && (camera.position.z >= 262)) && (sphealAppear == false))
	{
		Vector3 view = (camera.target - camera.position).Normalized();
		camera.position.z = 261;
		camera.target = view + camera.position;
	}

	if (((camera.position.x <= 213) && (camera.position.x >= 211)) && ((camera.position.z <= 292) && (camera.position.z >= 268)) && (sphealAppear == false))
	{
		Vector3 view = (camera.target - camera.position).Normalized();
		camera.position.x = 212;
		camera.target = view + camera.position;
	}

	if (((camera.position.x <= 203) && (camera.position.x >= 192)) && ((camera.position.z <= 282) && (camera.position.z >= 280)) && (sphealAppear == false) && (tentEntered == false))
	{
	
		tentEntered = true;
	
	}

	//animation stuff
	translateY = -1.8;
	translateDirY = 1;
	translateY2 = 2.2;
	translateDirY2 = 1;

	translateX = 0;
	translateDirX = 1;

	translateZ = 1.0;
	translateDirZ = 0.1;

	rotateAngle = 0;
	rotateDir = 30;

	rotateAngle2 = 0;
	rotateDir2 = 0.2;

	rotateAngle3 = 0;
	rotateDir3 = 180;

	scaleAll = 0.5;
	scaleDir = -1;

	scaleAll2 = 0.5;
	scaleDir2 = -1.5;

	scaleAll3 = 1;
	scaleDir3 = -0.4;

}

void AssignmentTwo::Render()
{	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

	modelStack.LoadIdentity();
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	RenderSkybox();
	RenderMesh(meshList[GEO_AXES], false);


	modelStack.PushMatrix();
	modelStack.Translate(0, -2.69, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(10000, 10000, 10000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();


	if (sphealAppear == true) {
		modelStack.PushMatrix(); //start of spheal
		modelStack.Rotate(rotateAngle, 1, 0, 0);
		modelStack.Translate(244, 0, -230.5);
		modelStack.Rotate(rotateAngle2, 0, 0, 1);
		modelStack.Scale(scaleAll3, scaleAll3, scaleAll3);

		//blue base body
		modelStack.PushMatrix();
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_SPHERE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Rotate(0, 0, 0, 1);
		modelStack.Scale(scaleAll, scaleAll, scaleAll);
		RenderMesh(meshList[GEO_SBALL], true);
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
		RenderMesh(meshList[GEO_LPUPILS], true);
		modelStack.PopMatrix();

		//right eye
		modelStack.PushMatrix();
		modelStack.Translate(1.5, 2.6, -1);
		modelStack.Rotate(150, 0, 0, 1);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_EYESL], true);
		modelStack.PopMatrix();



		//Left mouth
		modelStack.PushMatrix();
		modelStack.Translate(2.5, 2.0, -0.8);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1, 0.6, 0.5);
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
		modelStack.Translate(2.0, translateY, 1.5);
		modelStack.Rotate(rotateAngle, 1, 0, 0);
		modelStack.Scale(1.5, 0.5, 0.55);
		RenderMesh(meshList[GEO_SPHERE2], true);
		modelStack.PopMatrix();


		//right fin
		modelStack.PushMatrix();
		modelStack.Translate(2.0, translateY, -1.5);
		modelStack.Rotate(rotateAngle, 1, 0, 0);
		modelStack.Scale(1.5, 0.5, 0.55);
		RenderMesh(meshList[GEO_SPHERE2], true);
		modelStack.PopMatrix();

		//blue ears
		modelStack.PushMatrix();
		modelStack.Translate(0.115, 2.8, 1.8);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Scale(0.75, 0.375, 0.75);
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
		modelStack.Translate(-2.5, -1.9, 0);
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

		modelStack.PopMatrix(); //END of spheal
	RenderTextOnScreen(meshList[GEO_TEXT], "Find Spheal!", Color(0, 1, 0), 4, 0, 0);
	}

	if ((sphealAppear == false) && (tentEntered == false)) {
		modelStack.PushMatrix();
		modelStack.Translate(198, -2, 280.4);
		modelStack.Scale(40, 40, 40);
		RenderMesh(meshList[GEO_TENT], true);
		modelStack.PopMatrix();

		RenderTextOnScreen(meshList[GEO_TEXT], "Find Tent!", Color(0, 1, 0), 4, 0, 0);
	}

	if ((sphealAppear == false) && (tentEntered == true)) {
		RenderTextOnScreen(meshList[GEO_TEXT], "Congrats!", Color(0, 1, 0), 4, 10, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "R to Restart!", Color(0, 1, 0), 2, 50, 0);
	}

	modelStack.PushMatrix();
	modelStack.Translate(71.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(70.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(31.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(136.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(146.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(219.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(240.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(30.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(45, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(59, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(178, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(185, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(85, -2, 19.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(98, -2, 19.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(108, -2, 19.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(121.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(120.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(161.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(160.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-201.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-200.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(201.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(261.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(71, -2, 250.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(70.4, -2, 250.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30.4, -2, 190.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30.4, -2, 190.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10.4, -2, 130.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10.4, -2, 130.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(160.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(160.4, -2, 20.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-201.4, -2, -120.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-200.4, -2, -120.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(201, -2, -180.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(200, -2, -180.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(261, -2, -220.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260, -2, -220.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(320, -2, -280.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(320, -2, -280.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(320, -2, -280.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(360, -2, -320.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(361, -2, -320.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(9, -2, 147.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(14, -2, 167.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(33, -2, 178.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(49, -2, 227.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_SHAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(37, -2, 219.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30, -2, 208);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(55, -2, 239);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(46, -2, 230);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(222.4, -2, -182.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(232.4, -2, -192.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(242, -2, -207.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(252, -2, -219.4);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();



	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: " + std::to_string(FPS), Color(0, 1, 0), 4, 0, 3);
	//RenderTextOnScreen(meshList[GEO_TEXT], "X:" + std::to_string(camera.position.x), Color(0, 1, 0), 3, 35, 25);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + std::to_string(camera.position.y), Color(0, 1, 0), 3, 35, 20);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + std::to_string(camera.position.z), Color(0, 1, 0), 3, 35, 15);

	/*modelStack.PushMatrix();
	modelStack.Translate(0, 2, 0);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	modelStack.PopMatrix();*/
	
}


void AssignmentTwo::RenderMesh(Mesh* mesh, bool enableLight)
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

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void AssignmentTwo::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

	//front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -500);
	modelStack.Rotate(180, 1, 0, 1);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	//back
	modelStack.PushMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 500);
	modelStack.Rotate(180, 1, 0, 1);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1);
	RenderMesh(meshList[GEO_BACK], false);
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	//left
	modelStack.PushMatrix();
	modelStack.Translate(-500, 0, 0);
	modelStack.Rotate(-180, 1, 0, 1);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	//right
	modelStack.PushMatrix();
	modelStack.Translate(500, 0, 0);
	modelStack.Rotate(180, 1, 0, 1);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//top
	modelStack.PushMatrix();
	modelStack.Translate(0, 500, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	//bottom
	modelStack.PushMatrix();
	modelStack.Translate(0, -500, 0);
	modelStack.Rotate(180, 1, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(20, 20, 1);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();*/
	
	modelStack.PopMatrix();
}

void AssignmentTwo::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	//glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
}

void AssignmentTwo::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 1.0f, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void AssignmentTwo::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(40, 30, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(10, 10, 10);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void AssignmentTwo::Exit()
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
