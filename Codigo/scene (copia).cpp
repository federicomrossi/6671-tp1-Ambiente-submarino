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
	this->grid.create(10);
	this->pez.create();
	// this->test.create(10);

	// this->cangrejo.create();

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

	this->horizontalAngle += this->mouseSpeed * 0.005f * float(1024/2 - this->xpos);
	this->verticalAngle += this->mouseSpeed * 0.005f * float(576/2 - this->ypos);

	///////////////////////////////	


	// The position of your camera, in world space
	glm::vec3 cameraPosition = glm::vec3(
		this->cameraPositionX,
		this->cameraPositionY,
		this->cameraPositionZ
	);


	// // Where you want to look at, in world space
	// glm::vec3 cameraTarget = glm::vec3(
	// 	this->cameraTargetX,
	// 	this->cameraTargetY,
	// 	this->cameraTargetZ
	// );

	// Where you want to look at, in world space
	this->cameraTarget = glm::vec3(
		cos(this->verticalAngle) * sin(this->horizontalAngle),
		sin(this->verticalAngle),
		cos(this->verticalAngle) * cos(this->horizontalAngle)
	);


	// Right vector
	this->right = glm::vec3(
		sin(this->horizontalAngle - 3.14f/2.0f),
		0,
		cos(this->horizontalAngle - 3.14f/2.0f)
	);

	// Probably glm::vec3(0,1,0), but (0,,0) would make you looking 
	// upside-down, which can be great too
	glm::vec3 upVector = glm::vec3(0.0, 0.0, 1.0);
	// glm::vec3 upVector = glm::cross(this->right, this->cameraTarget);

	// // View (camera) Matrix
	// this->view_matrix = glm::lookAt(
	// 	cameraPosition,
	// 	cameraTarget,
	// 	upVector
	// );

	// View (camera) Matrix
	this->view_matrix = glm::lookAt(
		this->position,
		this->position + this->cameraTarget,
		upVector
	);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Matriz de projeccion
	glm::mat4 projection_matrix = glm::mat4 (1.0f);
	projection_matrix = glm::perspective(
		30.0f,
		(float)width / (float)height,
		0.1f,
		100.0f
	);

	// // PERSPECTIVA INFINITA
	// projection_matrix = glm::infinitePerspective(
	// 	30.0f,
	// 	(float)width / (float)height,
	// 	0.1f
	// );

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
	this->grid.changeObjectColor(0.5, 0.5, 0.5);
	this->grid.render(model_matrix_grid, this->view_matrix, projection_matrix);


	// Dibujamos el pez
	glm::mat4 mPez = glm::mat4(1.0f);
	mPez = glm::translate(mPez, glm::vec3(0.0, 0.0, 1.0) );
	mPez = glm::rotate(mPez, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->pez.render(mPez, this->view_matrix, projection_matrix);

	// // Drawing TEST
	// glm::mat4 model_matrix_test = glm::mat4(1.0f);
	// this->test.changeObjectColor(1.0, 0.0, 0.0);
	// this->test.render(model_matrix_eje_coordenado, this->view_matrix, projection_matrix);


	// // Dibujamos cangrejo
	// glm::mat4 model_matrix_cangrejo = glm::mat4(1.0f);

	// // Cambiamos el color de la grilla
	// this->cangrejo.changeObjectColor(0.796, 0.65, 0.6);
	// this->cangrejo.render(model_matrix_cangrejo, this->view_matrix, 
	// 	projection_matrix);


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
		// this->cameraPositionX -= 0.5;
		this->position += this->cameraTarget * 0.05f * this->speed;

	// Atras
	else if(cAscii == 's')
		// this->cameraPositionX += 0.5;
		this->position -= this->cameraTarget * 0.05f * this->speed;

	// Derecha
	else if(cAscii == 'd')
		// this->cameraPositionY += 0.5;
		this->position += this->right * 0.05f * this->speed;

	// Izquierda
	else if(cAscii == 'a')
		// this->cameraPositionY -= 0.5;
		this->position -= this->right * 0.05f * this->speed;

	std::cout << "Se movio" << std::endl;

	// if(cAscii == '+') 
	// 	this->grado--;
	// else if(cAscii == '-') 	
	// 	this->grado++;
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
