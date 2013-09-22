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
	// Inicializamos atributos de movimiento
	this->modoMovimiento = 1;

	this->gradoHombro = 0.0f;
	this->gradoBrazo = 45.0f;
	this->gradoCodo = 0.0f;
	this->gradoAntebrazo = 45.0f;
	this->gradoMano = 45.0f;

	// View (camera) Matrix
	this->view_matrix = glm::lookAt(glm::vec3 ( 8.0, 0.0, 5.0 ),
									glm::vec3 ( 0.0, 0.0, 0.0 ),
									glm::vec3 ( 0.0, 0.0, 1.0 ));
}


// Destructor
Scene::~Scene() { }


// Inicializa la escena.
void Scene::initialize()
{
	this->grid.create(10);							// Grilla
	this->spiralSphere.create(1.0, 32, 32);			// Esfera
	this->cube.create();							// Cubo    

	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}


// Renderiza la escena.
// POST: previo a realizar el primer renderizado debe invocarse al método
// initialize().
void Scene::render(GLuint height, GLuint width)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection Matrix
	glm::mat4 projection_matrix = glm::mat4 ( 1.0f );
	projection_matrix = glm::infinitePerspective( 52.0f , 
		(float)width / (float)height, 0.1f);


	///////////////////////////////////////////////////////////////////////////
	// OBJETOS DE LA ESCENA
	///////////////////////////////////////////////////////////////////////////
	
	// Drawing Grid
	glm::mat4 model_matrix_grid = glm::mat4 ( 1.0f );

	// Cambiamos el color de la grilla
	this->grid.changeObjectColor(0.5, 0.5, 0.5);
	this->grid.render(model_matrix_grid, this->view_matrix, projection_matrix);

	// ARM
	glm::mat4 model_matrix = glm::mat4 ( 1.0f );

	// Rotacion del HOMBRO
	model_matrix = glm::rotate (model_matrix, this->gradoHombro, 
		glm::vec3(0.0, 0.0, 1.0));

	this->dibujarHombro(model_matrix, projection_matrix);


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
	if(cAscii == '6') 
	{
		if(this->modoMovimiento == 1)
			this->gradoHombro += 1.0f;
		else if(this->modoMovimiento == 2)
			this->gradoCodo += 1.0f;
		else if(this->modoMovimiento == 3)
			this->gradoMunieca += 3.0f;
	}
	else if(cAscii == '4')
	{
		if(this->modoMovimiento == 1)
			this->gradoHombro -= 1.0f;
		else if(this->modoMovimiento == 2)
			this->gradoCodo -= 1.0f;
		else if(this->modoMovimiento == 3)
			this->gradoMunieca -= 3.0f;
	}
	else if(cAscii == '2')
	{	
		if(this->modoMovimiento == 1)
			this->gradoBrazo += 1;
		else if(this->modoMovimiento == 2)
			this->gradoAntebrazo += 1;
	}
	else if(cAscii == '8')
	{
		if(this->modoMovimiento == 1)
			this->gradoBrazo -= 1;
		else if(this->modoMovimiento == 2)
			this->gradoAntebrazo -= 1;
	}
	// Abrir pinzas
	else if(cAscii == '+')
	{
		this->gradoMano += 1;
	}
	// Cerrar pinzas
	else if(cAscii == '-')
	{
		this->gradoMano -= 1;
	}


	// Selección de movimiento del HOMBRO
	else if(cAscii == 'a' || cAscii == 'A')
		this->modoMovimiento = 1;
	// Selección de movimiento del CODO
	else if(cAscii == 's' || cAscii == 'S')
		this->modoMovimiento = 2;
	// Selección de movimiento del MUÑECA
	else if(cAscii == 'd' || cAscii == 'D')
		this->modoMovimiento = 3;
}






// METODOS PRIVADOS
// ################


void Scene::dibujarHombro(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Renderizamos esfera que representa el hombro
	glm::mat4 mHombro = glm::mat4 ( 1.0f );
	mHombro = glm::rotate (m, this->gradoBrazo, glm::vec3(1.0, 0.0, 0.0));
	
	// Cambiamos el color del objeto
	this->spiralSphere.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->spiralSphere.render(mHombro, this->view_matrix, projection_matrix);

	// Posicionamos el inicio del brazo
	glm::mat4 mBrazo = glm::mat4 ( 1.0f );
	mBrazo = glm::translate(mHombro , glm::vec3(0.0, 0.0, 0.5) );

	// Dibujamos brazo
	this->dibujarBrazo(mBrazo, projection_matrix);
}


void Scene::dibujarBrazo(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Transformamos para posicionar y formar el brazo
	glm::mat4 mBrazo = glm::mat4 ( 1.0f );
	mBrazo = glm::scale(m, glm::vec3 (0.6f, 0.6f, 3.0f) );
	mBrazo = glm::translate(mBrazo , glm::vec3(0.0, 0.0, 0.5) );

	// Cambiamos el color del objeto
	this->cube.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos el brazo
	this->cube.render(mBrazo, this->view_matrix, projection_matrix);

	// Posicionamos el codo respecto del brazo
	glm::mat4 mCodo = glm::mat4 ( 1.0f );
	mCodo = glm::translate(m, glm::vec3(0.0, 0.0, 3.0) );

	// Dibujamos codo
	this->dibujarCodo(mCodo, projection_matrix);
}


void Scene::dibujarCodo(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Renderizamos esfera que representa el codo
	glm::mat4 mCodo = glm::mat4 ( 1.0f );
	mCodo = glm::rotate (m, this->gradoCodo, glm::vec3(0.0, 0.0, 1.0));
	mCodo = glm::scale(mCodo, glm::vec3(0.5f, 0.5f, 0.5));

	// Cambiamos el color del objeto
	this->spiralSphere.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->spiralSphere.render(mCodo, this->view_matrix, projection_matrix);

	// Posicionamos el inicio del antebrazo
	glm::mat4 mAntebrazo = glm::mat4 ( 1.0f );
	mAntebrazo = glm::rotate (m, this->gradoCodo, glm::vec3(0.0, 0.0, 1.0));
	mAntebrazo = glm::rotate (mAntebrazo, this->gradoAntebrazo, 
		glm::vec3(1.0, 0.0, 0.0));
	// mAntebrazo = glm::translate(mAntebrazo, glm::vec3(0.0, 0.0, 0.5) );

	// Dibujamos antebrazo
	this->dibujarAntebrazo(mAntebrazo, projection_matrix);
}


void Scene::dibujarAntebrazo(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Transformamos para posicionar y formar el brazo
	glm::mat4 mAntebrazo = glm::mat4 ( 1.0f );
	mAntebrazo = glm::scale(m, glm::vec3 (0.4f, 0.4f, 1.5f) );
	mAntebrazo = glm::translate(mAntebrazo , glm::vec3(0.0, 0.0, 0.5) );

	// Cambiamos el color del objeto
	this->cube.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->cube.render(mAntebrazo, this->view_matrix, projection_matrix);

	// Posicionamos la muñeca respecto del antebrazo
	glm::mat4 mMunieca = glm::mat4 ( 1.0f );
	mMunieca = glm::rotate (m, this->gradoMunieca, glm::vec3( 0.0, 0.0, 1.0));
	mMunieca = glm::translate(mMunieca, glm::vec3(0.0, 0.0, 1.5) );

	// Dibujamos muñeca
	this->dibujarMunieca(mMunieca, projection_matrix);
}


void Scene::dibujarMunieca(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Renderizamos esfera que representa la muñeca
	glm::mat4 mMunieca = glm::mat4 ( 1.0f );
	mMunieca = glm::scale(m, glm::vec3(0.3f, 0.3f, 0.3));
	
	// Cambiamos el color del objeto
	this->spiralSphere.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->spiralSphere.render(mMunieca, this->view_matrix, projection_matrix);

	// Dibujamos mano
    this->dibujarMano(m, projection_matrix);
}


void Scene::dibujarMano(glm::mat4 m, glm::mat4 &projection_matrix)
{
	// Transformamos para posicionar y formar
	glm::mat4 mGarraDerecha = glm::mat4 ( 1.0f );
	mGarraDerecha = glm::rotate(m, (-1) * this->gradoMano, 
		glm::vec3( 1.0, 0.0, 0.0));
	mGarraDerecha = glm::scale(mGarraDerecha, glm::vec3 (0.3f, 0.1f, 0.7f) );
	mGarraDerecha = glm::translate(mGarraDerecha , glm::vec3(0.0, 0.0, 0.5) );

	// Cambiamos el color del objeto
	this->cube.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->cube.render(mGarraDerecha, this->view_matrix, projection_matrix);

	// Transformamos para posicionar y formar
	glm::mat4 mGarraIzquierda = glm::mat4 ( 1.0f );
	mGarraIzquierda = glm::rotate(m, this->gradoMano, 
		glm::vec3( 1.0, 0.0, 0.0));
	mGarraIzquierda = glm::scale(mGarraIzquierda, 
		glm::vec3 (0.3f, 0.1f, 0.7f) );
	mGarraIzquierda = glm::translate(mGarraIzquierda , 
		glm::vec3(0.0, 0.0, 0.5) );

	// Cambiamos el color del objeto
	this->cube.changeObjectColor(0.796, 0.65, 0.6);
	// Renderizamos
	this->cube.render(mGarraIzquierda, this->view_matrix, projection_matrix);
}
