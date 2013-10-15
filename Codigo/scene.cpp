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
	this->position = glm::vec3(8.0, 0.0, 3.0);
	this->horizontalAngle = 3.14f;
	this->verticalAngle = 0.0f;
	this->initialFoV = 30.0f;
	this->speed = 3.0f; // 3 unidades por segundo
	this->mouseSpeed = 0.005f;

	this->xpos = 0;
	this->ypos = 0;

	cameraPositionX = 8.0;
	cameraPositionY = 0.0;
	cameraPositionZ = 3.0;
	cameraTargetX = 0.0;
	cameraTargetY = 0.0;
	cameraTargetZ = 0.0;
}


// Destructor
Scene::~Scene() { }


// Inicializa la escena.
void Scene::initialize()
{
	this->grado = 0.0f;
	this->ejeCoordenado.create(2);
	this->grid.create(20);
	this->superficie.create();
	this->cangrejo.create();
	this->pez.create();
	this->roca.create();
	this->plantaAcuatica.create();
	// this->test.create(10);


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
	//////////////////////////////

	// this->horizontalAngle += this->mouseSpeed * 0.005f * float(1024/2 - this->xpos);
	// this->verticalAngle += this->mouseSpeed * 0.005f * float(576/2 - this->ypos);

	///////////////////////////////	


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

	// // PERSPECTIVA
	// projection_matrix = glm::perspective(
		
	// 	// The horizontal Field of View, in degrees : the amount of "zoom". 
	// 	// Think "camera lens". Usually between 90° (extra wide) and 30° 
	// 	// (quite zoomed in)
	// 	30.0f,
	
	// 	// Aspect Ratio. Depends on the size of your window. Notice that 
	// 	// 4/3 == 800/600 == 1280/960.
	// 	4.0f / 3.0f,

	// 	// Near clipping plane. Keep as big as possible, or you'll get 
	// 	// precision issues.
	// 	0.1f,

	// 	// Far clipping plane. Keep as little as possible.
	// 	100.0f
	// );


	///////////////////////////////////////////////////////////////////////////
	// OBJETOS DE LA ESCENA
	///////////////////////////////////////////////////////////////////////////

	// Dibujamos el eje coordenado
	glm::mat4 model_matrix_eje_coordenado = glm::mat4 (1.0f);
	model_matrix_eje_coordenado = glm::rotate(model_matrix_eje_coordenado,
		this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->ejeCoordenado.render(model_matrix_eje_coordenado, this->view_matrix, 
		projection_matrix);

	// Drawing Grid
	glm::mat4 model_matrix_grid = glm::mat4(1.0f);
	this->grid.changeObjectColor(128, 128, 128);
	this->grid.render(model_matrix_grid, this->view_matrix, projection_matrix);

	// Dibujamos la superficie
	glm::mat4 mSuperficie = glm::mat4(1.0f);
	this->superficie.render(mSuperficie, this->view_matrix, projection_matrix);

	// Dibujamos cangrejo
	glm::mat4 mCangrejo = glm::mat4(1.0f);
	mCangrejo = glm::translate(mCangrejo, glm::vec3(0.5, -1.0, 0.4));
	mCangrejo = glm::scale(mCangrejo, glm::vec3(0.5, 0.5, 0.5));
	mCangrejo = glm::rotate(mCangrejo, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejo.render(mCangrejo, this->view_matrix, projection_matrix);

	// Dibujamos el pez
	glm::mat4 mPez = glm::mat4(1.0f);
	mPez = glm::translate(mPez, glm::vec3(-0.1, 1.6, 1.0));
	mPez = glm::scale(mPez, glm::vec3(0.8, 0.8, 0.8));
	mPez = glm::rotate(mPez, 15.0f, glm::vec3(0.0, 0.0, 1.0));
	mPez = glm::rotate(mPez, 5.0f, glm::vec3(0.0, 1.0, 0.0));
	this->pez.render(mPez, this->view_matrix, projection_matrix);

	// Dibujamos rocas
	glm::mat4 mRoca = glm::mat4(1.0f);
	mRoca = glm::translate(mRoca, glm::vec3(2.0, 2.0, 0.0));
	mRoca = glm::scale(mRoca, glm::vec3(0.3, 0.3, 0.3));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(1.0, 0.0, 0.3));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(0.0, 1.1, -0.6));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);

	// Dibujamos una planta
	glm::mat4 mPlanta = glm::mat4(1.0f);
	mPlanta = glm::translate(mPlanta, glm::vec3(1.9, 2.3, -0.05));
	mPlanta = glm::rotate(mPlanta, -45.0f, glm::vec3(0.0, 0.0, 1.0));
	this->plantaAcuatica.render(mPlanta, this->view_matrix, projection_matrix);

	// // Drawing TEST
	// glm::mat4 model_matrix_test = glm::mat4(1.0f);
	// this->test.changeObjectColor(255, 0, 0);
	// this->test.render(model_matrix_eje_coordenado, this->view_matrix, projection_matrix);



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

	if(cAscii == '+') 
		this->grado--;
	else if(cAscii == '-') 	
		this->grado++;
}


// Manejador del evento de movimiento de la rueda del mouse
void Scene::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y)
{
	std::cout << nWheelNumber << std::endl;
} 


// Manejador del evento de movimiento del mouse.
void Scene::OnMouseMove(int x, int y)
{
	this->xpos = x;
	this->ypos = y;

	// Mantenemos el cursor en el centro de la ventana
	// glutWarpPointer(1024 / 2, 576 / 2);
}
