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

#include "config.h"
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

	this->pause = false;

	this->xpos = 0;
	this->ypos = 0;

	cameraPositionX = 8.0;
	cameraPositionY = 0.0;
	cameraPositionZ = 1.0;
	cameraTargetX = 0.0;
	cameraTargetY = 0.0;
	cameraTargetZ = 0.0;

	// Parámetros de movimiento
	this->aceleracionMax = 200;
	this->velocidadMov = 0.07 / this->aceleracionMax;
	this->velocidadGiro = 0.50 / this->aceleracionMax;
	this->movAdelante = false;
	this->movAtras = false;
	this->movDerecha = false;
	this->movIzquierda = false;
	this->movArriba = false;
	this->movAbajo = false;
	this->movGirarDerecha = false;
	this->movGirarIzquierda = false;
	this->aceleracionAdelante = 0;
	this->aceleracionAtras = 0;
	this->aceleracionDerecha = 0;
	this->aceleracionIzquierda = 0;
	this->aceleracionArriba = 0;
	this->aceleracionAbajo = 0;
	this->aceleracionGiroDerecha = 0;
	this->aceleracionGiroIzquierda = 0;

	this->cangrejoPosY = 0.0;
	this->cangrejoPosZ = 0.0;
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
	glClearColor(AMBIENT_COLOR_R, 
				 AMBIENT_COLOR_G, 
				 AMBIENT_COLOR_B, 
				 AMBIENT_COLOR_ALPHA);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}


// Renderiza la escena.
// POST: previo a realizar el primer renderizado debe invocarse al método
// initialize().
void Scene::render(GLuint height, GLuint width)
{
	// Pausamos el movimiento	
	if(this->pause) return;

	///////////////////////
	// Movimiento de cámara

	if(this->movAdelante)
	{
		if(this->aceleracionAdelante < this->aceleracionMax)
			this->aceleracionAdelante++;

		this->cameraPositionX -= this->aceleracionAdelante * this->velocidadMov;
		this->cameraTargetX -= this->aceleracionAdelante * this->velocidadMov;
	}
	else if(!this->movAdelante && this->aceleracionAdelante > 0)
	{
		this->aceleracionAdelante--;

		this->cameraPositionX -= this->aceleracionAdelante * this->velocidadMov;
		this->cameraTargetX -= this->aceleracionAdelante * this->velocidadMov;
	}

	if(this->movAtras)
	{
		if(this->aceleracionAtras < this->aceleracionMax)
			this->aceleracionAtras++;

		this->cameraPositionX += this->aceleracionAtras * this->velocidadMov;
		this->cameraTargetX += this->aceleracionAtras * this->velocidadMov;
	}
	else if(!this->movAtras && this->aceleracionAtras > 0)
	{
		this->aceleracionAtras--;

		this->cameraPositionX += this->aceleracionAtras * this->velocidadMov;
		this->cameraTargetX += this->aceleracionAtras * this->velocidadMov;
	}

	if(this->movDerecha)
	{
		if(this->aceleracionDerecha < this->aceleracionMax)
			this->aceleracionDerecha++;

		this->cameraPositionY += this->aceleracionDerecha * this->velocidadMov;
		this->cameraTargetY += this->aceleracionDerecha * this->velocidadMov;
	}
	else if(!this->movDerecha && this->aceleracionDerecha > 0)
	{
		this->aceleracionDerecha--;

		this->cameraPositionY += this->aceleracionDerecha * this->velocidadMov;
		this->cameraTargetY += this->aceleracionDerecha * this->velocidadMov;
	}

	if(this->movIzquierda)
	{
		if(this->aceleracionIzquierda < this->aceleracionMax)
			this->aceleracionIzquierda++;

		this->cameraPositionY -= this->aceleracionIzquierda * this->velocidadMov;
		this->cameraTargetY -= this->aceleracionIzquierda * this->velocidadMov;
	}
	else if(!this->movIzquierda && this->aceleracionIzquierda > 0)
	{
		this->aceleracionIzquierda--;

		this->cameraPositionY -= this->aceleracionIzquierda * this->velocidadMov;
		this->cameraTargetY -= this->aceleracionIzquierda * this->velocidadMov;
	}

	if(this->movArriba)
	{
		if(this->aceleracionArriba < this->aceleracionMax)
			this->aceleracionArriba++;

		this->cameraPositionZ += this->aceleracionArriba * this->velocidadMov;
		this->cameraTargetZ += this->aceleracionArriba * this->velocidadMov;
	}
	else if(!this->movArriba && this->aceleracionArriba > 0)
	{
		this->aceleracionArriba--;

		this->cameraPositionZ += this->aceleracionArriba * this->velocidadMov;
		this->cameraTargetZ += this->aceleracionArriba * this->velocidadMov;
	}

	if(this->movAbajo)
	{
		if(this->aceleracionAbajo < this->aceleracionMax)
			this->aceleracionAbajo++;

		this->cameraPositionZ -= this->aceleracionAbajo * this->velocidadMov;
		this->cameraTargetZ -= this->aceleracionAbajo * this->velocidadMov;
	}
	else if(!this->movArriba && this->aceleracionAbajo > 0)
	{
		this->aceleracionAbajo--;

		this->cameraPositionZ -= this->aceleracionAbajo * this->velocidadMov;
		this->cameraTargetZ -= this->aceleracionAbajo * this->velocidadMov;
	}

	if(this->movGirarDerecha)
	{
		if(this->aceleracionGiroDerecha < this->aceleracionMax)
			this->aceleracionGiroDerecha++;

		this->grado -= this->aceleracionGiroDerecha * this->velocidadGiro;
	}
	else if(!this->movGirarIzquierda && this->aceleracionGiroDerecha > 0)
	{
		this->aceleracionGiroDerecha--;

		this->grado -= this->aceleracionGiroDerecha * this->velocidadGiro;
	}


	if(this->movGirarIzquierda)
	{
		if(this->aceleracionGiroIzquierda< this->aceleracionMax)
			this->aceleracionGiroIzquierda++;

		this->grado += this->aceleracionGiroIzquierda * this->velocidadGiro;
	}
	else if(!this->movGirarDerecha && this->aceleracionGiroIzquierda > 0)
	{
		this->aceleracionGiroIzquierda--;

		this->grado += this->aceleracionGiroIzquierda * this->velocidadGiro;
	}

	// FIN Movimiento de la camara
	//////////////////////////////



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

	glm::mat4 mGeneral = glm::mat4(1.0f);
	mGeneral = glm::rotate(mGeneral, this->grado, glm::vec3(0.0, 0.0, 1.0));

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
	mSuperficie = glm::translate(mGeneral, glm::vec3(10.0, 0.0, 0.0));
	// mSuperficie = glm::rotate(mSuperficie, this->grado, glm::vec3(0.0, 1.0, 0.0));
	this->superficie.render(mSuperficie, this->view_matrix, projection_matrix);

	// Dibujamos la superficie de agua
	glm::mat4 mSupAgua = glm::mat4(1.0f);
	mSupAgua = glm::translate(mGeneral, glm::vec3(-10.0, 0.0, 3.5));
	// mSupAgua = glm::rotate(mSupAgua, this->grado, glm::vec3(0.0, 1.0, 0.0));
	this->superficieAgua.render(mSupAgua, this->view_matrix, projection_matrix);



	// Dibujamos cangrejo

	// Movimiento
	if(this->cangrejoSentido == 1 && this->cangrejoPosY < 1.5)
	{
		this->cangrejoPosY += 0.0015;
		this->cangrejoPosZ += 0.0003;
	}
	else if(this->cangrejoSentido == -1 && this->cangrejoPosY > 0.0)
	{
		this->cangrejoPosY -= 0.0015;
		this->cangrejoPosZ -= 0.0003;
	}

	if(this->cangrejoPosY <= 0.0) this->cangrejoSentido = 1;
	else if(this->cangrejoPosY >= 1.5) this->cangrejoSentido = -1;

	glm::mat4 mCangrejo = glm::mat4(1.0f);
	mCangrejo = glm::translate(mGeneral, glm::vec3(0.5, -this->cangrejoPosY, 0.40 - this->cangrejoPosZ));
	// mCangrejo = glm::translate(mCangrejo, glm::vec3(0.0, 0.0, 1.0));
	mCangrejo = glm::scale(mCangrejo, glm::vec3(0.2, 0.2, 0.2));
	mCangrejo = glm::rotate(mCangrejo, 10.0f, glm::vec3(1.0, 0.0, 0.0));
	// mCangrejo = glm::rotate(mCangrejo, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejo.render(mCangrejo, this->view_matrix, projection_matrix);

	// Dibujamos el pez

	// Movimiento del pez

	// Rotación para efecto de delantamiento
	float dosPi = 6.283185307;
	this->pezGradoRotacion += 0.01;
	if(this->pezGradoRotacion >= dosPi) this->pezGradoRotacion = 0.0;
	float radio = 7.5;

	this->pezPosX = radio * cos(this->pezGradoRotacion);
	this->pezPosY = radio * sin(this->pezGradoRotacion);
	this->pezPosZ = 1.5;

	glm::mat4 mPez = glm::mat4(1.0f);
	mPez = glm::translate(mGeneral, glm::vec3(this->pezPosX - 3.0, this->pezPosY, this->pezPosZ));
	// mPez = glm::translate(mPez, glm::vec3(0.0, 0.0, 1.5));
	// mPez = glm::scale(mPez, glm::vec3(0.8, 0.8, 0.8));
	mPez = glm::rotate(mPez, 90.0f + this->pezGradoRotacion * 360.0f / dosPi, 
		glm::vec3(0.0, 0.0, 1.0));
	// mPez = glm::rotate(mPez, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->pez.render(mPez, this->view_matrix, projection_matrix);

	// Dibujamos rocas
	glm::mat4 mRoca = glm::mat4(1.0f);
	mRoca = glm::translate(mGeneral, glm::vec3(2.3, 2.0, -0.1));
	mRoca = glm::scale(mRoca, glm::vec3(0.7, 0.6, 0.5));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::scale(mRoca, glm::vec3(0.3, 0.8, 0.7));
	mRoca = glm::translate(mRoca, glm::vec3(-1.0, -0.5, 0.4));
	// mRoca = glm::rotate(mRoca, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(-1.5, -2.5, 0.1));
	mRoca = glm::rotate(mRoca, 10.0f, glm::vec3(1.0, 0.0, 0.0));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);
	mRoca = glm::translate(mRoca, glm::vec3(-9.0, -8.0, 0.45));
	mRoca = glm::scale(mRoca, glm::vec3(0.6, 1.0, 1.0));
	mRoca = glm::rotate(mRoca, -25.0f, glm::vec3(1.0, 0.0, 0.0));
	this->roca.render(mRoca, this->view_matrix, projection_matrix);

	// Dibujamos una planta
	glm::mat4 mPlanta = glm::mat4(1.0f);
	mPlanta = glm::translate(mGeneral, glm::vec3(1.9, 2.3, -0.05));
	// mPlanta = glm::rotate(mPlanta, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	// mPlanta = glm::rotate(mPlanta, this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->plantaAcuatica.render(mPlanta, this->view_matrix, projection_matrix);

	mPlanta = glm::mat4(1.0f);
	mPlanta = glm::translate(mGeneral, glm::vec3(1.3, 1.8, 0.25));
	mPlanta = glm::rotate(mPlanta, -30.0f, glm::vec3(0.0, 0.0, 1.0));
	// mPlanta = glm::rotate(mPlanta, this->grado, glm::vec3(0.0, 0.0, 1.0));
	mPlanta = glm::scale(mPlanta, glm::vec3(0.3, 0.3, 0.3));
	this->plantaAcuatica.render(mPlanta, this->view_matrix, projection_matrix);

	glm::mat4 mPlanta1 = glm::mat4(1.0f);
	glm::mat4 mPlanta2 = glm::mat4(1.0f);
	mPlanta1 = glm::translate(mGeneral, glm::vec3(-1.0, -1.5, -0.05));
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
		this->movAdelante = true;
	}
	// Atras
	else if(cAscii == 's')
	{
		this->movAtras = true;
	}
	// Derecha
	else if(cAscii == 'd')
	{
		this->movDerecha = true;
	}
	// Izquierda
	else if(cAscii == 'a')
	{
		this->movIzquierda = true;
	}
	// Subir
	else if(cAscii == 'i')
	{
		this->movArriba = true;
	}
	// Bajar
	else if(cAscii == 'k')
	{
		this->movAbajo = true;
	}
	else if(cAscii == '+')
	{
		this->movGirarDerecha = true;
	}
	else if(cAscii == '-')
	{
		this->movGirarIzquierda = true;
	}
	else if(cAscii == 'p')
	{
		if(this->pause)
			this->pause = false;
		else
			this->pause = true;
	}

	// // DEBUG
	// if(cAscii == '+') 
	// 	this->grado -= 2;
	// else if(cAscii == '-') 	
	// 	this->grado += 2;
	// // END DEBUG
}

// Manejador del evento de tecla liberada.
void Scene::onKeyUp(int nKey, char cAscii)
{
	// Adelante
	if(cAscii == 'w')
	{
		this->movAdelante = false;
	}
	// Atras
	else if(cAscii == 's')
	{
		this->movAtras = false;
	}
	// Derecha
	else if(cAscii == 'd')
	{
		this->movDerecha = false;
	}
	// Izquierda
	else if(cAscii == 'a')
	{
		this->movIzquierda = false;
	}
	// Subir
	else if(cAscii == 'i')
	{
		this->movArriba = false;
	}
	// Bajar
	else if(cAscii == 'k')
	{
		this->movAbajo = false;
	}
	else if(cAscii == '+')
	{
		this->movGirarDerecha = false;
	}
	else if(cAscii == '-')
	{
		this->movGirarIzquierda = false;
	}
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
