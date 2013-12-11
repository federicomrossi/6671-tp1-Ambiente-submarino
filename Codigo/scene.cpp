/*  
 *  CLASS SCENE
 */


#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "scene.h"




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Scene::Scene()
{
	this->position = glm::vec3(4.0, 0.0, 0.0);
	this->horizontalAngle = 3.14f;
	this->verticalAngle = 0.0f;
	this->initialFoV = 30.0f;
	this->speed = 3.0f; // 3 unidades por segundo
	this->mouseSpeed = 0.005f;

	this->xpos = 0;
	this->ypos = 0;

	cameraPositionX = 8.0;
	cameraPositionY = 0.0;
	cameraPositionZ = 1.0;
	cameraTargetX = 0.0;
	cameraTargetY = 0.0;
	cameraTargetZ = 0.0;

	this->cangrejoPosY = 0.0;
	this->cangrejoSentido = 1;

	this->pezGradoRotacion = 0.0;
}


// Destructor
Scene::~Scene() { }


// Inicializa la escena.
void Scene::initialize()
{
	// Creamos los objetos
	this->grado = 0.0f;
	// this->ejeCoordenado.create(4);
	// this->grid.create(20);
	this->superficie.create(80);
	this->superficieAgua.create(80);
	this->cangrejo.create();
	this->roca.create();
	this->pez.create();
	this->plantaAcuatica.create();

	// Establecemos un color inicial para la escena
	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}


// Renderiza la escena.
// POST: previo a realizar el primer renderizado debe invocarse al método
// initialize().
void Scene::render(GLuint height, GLuint width)
{
	// The position of your camera, in world space
	glm::vec3 cameraPosition = glm::vec3(
		this->cameraPositionX,
		this->cameraPositionY,
		this->cameraPositionZ
	);


	// Where you want to look at, in world space
	glm::vec3 cameraTarget = glm::vec3(
		this->cameraTargetX,
		this->cameraTargetY,
		this->cameraTargetZ
	);

	// Probably glm::vec3(0,1,0), but (0,,0) would make you looking 
	// upside-down, which can be great too
	glm::vec3 upVector = glm::vec3(0.0, 0.0, 1.0);

	// View (camera) Matrix
	this->view_matrix = glm::lookAt(
		cameraPosition,
		cameraTarget,
		upVector
	);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// PERSPECTIVA INFINITA
	glm::mat4 projection_matrix = glm::infinitePerspective(
		30.0f,
		(float)width / (float)height,
		0.1f
	);


	///////////////////////////////////////////////////////////////////////////
	// OBJETOS DE LA ESCENA
	///////////////////////////////////////////////////////////////////////////


	// Dibujamos el eje coordenado
	// glm::mat4 model_matrix_eje_coordenado = glm::mat4 (1.0f);
	// model_matrix_eje_coordenado = glm::rotate(model_matrix_eje_coordenado,
	// 	this->grado, glm::vec3(0.0, 0.0, 1.0));
	// this->ejeCoordenado.render(model_matrix_eje_coordenado, this->view_matrix, 
	// 	projection_matrix);

	// Drawing Grid
	// glm::mat4 model_matrix_grid = glm::mat4(1.0f);
	// this->grid.changeObjectColor(128, 128, 128);
	// this->grid.render(model_matrix_grid, this->view_matrix, projection_matrix);

	// Dibujamos la superficie
	glm::mat4 mSuperficie = glm::mat4(1.0f);
	mSuperficie = glm::translate(mSuperficie, glm::vec3(-30.0, 0.0, 0.0));
	// mSuperficie = glm::rotate(mSuperficie, this->grado, glm::vec3(0.0, 1.0, 0.0));
	this->superficie.render(mSuperficie, this->view_matrix, projection_matrix);

	// Dibujamos la superficie de agua
	glm::mat4 mSupAgua = glm::mat4(1.0f);
	mSupAgua = glm::translate(mSupAgua, glm::vec3(-30.0, 0.0, 5.0));
	// mSupAgua = glm::rotate(mSupAgua, this->grado, glm::vec3(0.0, 1.0, 0.0));
	this->superficieAgua.render(mSupAgua, this->view_matrix, projection_matrix);



	// Dibujamos cangrejo

	// // Movimiento
	// if(this->cangrejoSentido == 1 && this->cangrejoPosY < 4.0)
	// 	this->cangrejoPosY += 0.003;
	// else if(this->cangrejoSentido == -1 && this->cangrejoPosY > 0.0)
	// 	this->cangrejoPosY -= 0.003;

	// if(this->cangrejoPosY <= 0.0) this->cangrejoSentido = 1;
	// else if(this->cangrejoPosY >= 4.0) this->cangrejoSentido = -1;

	glm::mat4 mCangrejo = glm::mat4(1.0f);
	mCangrejo = glm::translate(mCangrejo, glm::vec3(0.5, -this->cangrejoPosY, 0.45));
	mCangrejo = glm::scale(mCangrejo, glm::vec3(0.3, 0.3, 0.3));
	mCangrejo = glm::rotate(mCangrejo, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejo.render(mCangrejo, this->view_matrix, projection_matrix);

	// Dibujamos el pez

	// Movimiento del pez

	// Rotación para efecto de delantamiento
	float dosPi = 6.283185307;
	this->pezGradoRotacion += 0.02;
	if(this->pezGradoRotacion >= dosPi) this->pezGradoRotacion = 0.0;
	float radio = 7.5;

	this->pezPosX = radio * cos(this->pezGradoRotacion);
	this->pezPosY = radio * sin(this->pezGradoRotacion);
	this->pezPosZ = 1.5;

	glm::mat4 mPez = glm::mat4(1.0f);
	mPez = glm::translate(mPez, glm::vec3(this->pezPosX - 3.0, this->pezPosY, this->pezPosZ));
	mPez = glm::scale(mPez, glm::vec3(0.8, 0.8, 0.8));
	mPez = glm::rotate(mPez, 90.0f + this->pezGradoRotacion * 360.0f / dosPi, 
		glm::vec3(0.0, 0.0, 1.0));
	mPez = glm::rotate(mPez, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->pez.render(mPez, this->view_matrix, projection_matrix);

	// Dibujamos rocas
	glm::mat4 mRoca = glm::mat4(1.0f);
	mRoca = glm::translate(mRoca, glm::vec3(2.3, 2.0, -0.1));
	mRoca = glm::scale(mRoca, glm::vec3(0.7, 0.6, 0.5));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::scale(mRoca, glm::vec3(0.7, 0.8, 0.7));
	mRoca = glm::translate(mRoca, glm::vec3(-1.0, -0.5, -0.05));
	// mRoca = glm::rotate(mRoca, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(-1.5, -2.5, 0.1));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(-9.0, -8.0, -0.1));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);

	// Dibujamos una planta
	glm::mat4 mPlanta = glm::mat4(1.0f);
	mPlanta = glm::translate(mPlanta, glm::vec3(1.9, 2.3, -0.05));
	// mPlanta = glm::rotate(mPlanta, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	// mPlanta = glm::rotate(mPlanta, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->plantaAcuatica.render(mPlanta, this->view_matrix, projection_matrix);

	mPlanta = glm::mat4(1.0f);
	mPlanta = glm::translate(mPlanta, glm::vec3(1.3, 1.8, -0.05));
	mPlanta = glm::rotate(mPlanta, -30.0f, glm::vec3(0.0, 0.0, 1.0));
	// mPlanta = glm::rotate(mPlanta, this->grado, glm::vec3(0.0, 0.0, 1.0));
	mPlanta = glm::scale(mPlanta, glm::vec3(1.0, 0.7, 0.6));
	this->plantaAcuatica.render(mPlanta, this->view_matrix, projection_matrix);

	glm::mat4 mPlanta1 = glm::mat4(1.0f);
	glm::mat4 mPlanta2 = glm::mat4(1.0f);
	mPlanta1 = glm::translate(mPlanta1, glm::vec3(-1.0, -1.5, -0.05));
	mPlanta1 = glm::scale(mPlanta1, glm::vec3(0.7, 0.7, 0.7));
	this->plantaAcuatica.render(mPlanta1, this->view_matrix, projection_matrix);


	///////////////////////////////////////////////////////////////////////////

	glutSwapBuffers();
}


// Redimensiona la escena.
void Scene::resize(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
}


// Establece la posicion de la camara de la escena.
void Scene::setCameraPosition()
{

}


// Devuelve la posicion de la camara de la escena.
void Scene::getCameraPosition()
{

}


// Manejador del evento de tecla presionada.
void Scene::onKeyDown(int nKey, char cAscii)
{
	// MANEJO DE LA CAMARA

	// Adelante
	if(cAscii == 'w')
	{
		this->cameraPositionX -= 0.07;
		this->cameraTargetX -= 0.07;
	}
	// Atras
	else if(cAscii == 's')
	{
		this->cameraPositionX += 0.07;
		this->cameraTargetX += 0.07;
	}

	// Derecha
	else if(cAscii == 'd')
	{
		this->cameraPositionY += 0.07;
		this->cameraTargetY += 0.07;
	}
	// Izquierda
	else if(cAscii == 'a')
	{
		this->cameraPositionY -= 0.07;
		this->cameraTargetY -= 0.07;
	}
	// Subir
	else if(cAscii == 'i')
	{
		this->cameraPositionZ += 0.07;
		this->cameraTargetZ += 0.07;
	}
	// Subir
	else if(cAscii == 'k')
	{
		this->cameraPositionZ -= 0.07;
		this->cameraTargetZ -= 0.07;
	}

	if(cAscii == '+') 
		this->grado--;
	else if(cAscii == '-') 	
		this->grado++;
}


// Manejador del evento de movimiento de la rueda del mouse
void Scene::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y)
{

} 


// Manejador del evento de movimiento del mouse.
void Scene::OnMouseMove(int x, int y)
{
	this->xpos = x;
	this->ypos = y;

	// Mantenemos el cursor en el centro de la ventana
	// glutWarpPointer(1024 / 2, 576 / 2);
}
