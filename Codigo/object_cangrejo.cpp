/*  
 *  CLASS CANGREJO
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

#include "object_cangrejo.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/VERT_SHADER_FILENAME.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/FRAG_SHADER_FILENAME.frag";
	
}




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Cangrejo::Cangrejo() { }


// Destructor
Cangrejo::~Cangrejo() { }


// Crea un objeto
void Cangrejo::create()
{
	// Creamos el eje coordenado
	this->ejeCoordenado.create(3);

	// Creamos el cuerpo
	this->cangrejoCuerpo.create();

	// Creamos las patas
	this->cangrejoPata.create();

	// Creamos los ojos
	this->cangrejoOjo.create();

	// Creamos las pinzas
	this->cangrejoPinza.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Cangrejo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);
	

	// Dibujamos el cuerpo
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(0.0, 0.0, 0.2));
	mCuerpo = glm::rotate(mCuerpo, 10.0f,glm::vec3(0.0, 1.0, 0.0));
	this->cangrejoCuerpo.render(mCuerpo, view_matrix, projection_matrix);



	// Dibujamos los ojos
	glm::mat4 mOjoDer = glm::mat4(1.0f);
	mOjoDer = glm::translate(model_matrix, glm::vec3(0.9, -0.3, 0.3));
	mOjoDer = glm::rotate(mOjoDer, 10.0f,glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoOjo.render(mOjoDer, view_matrix, projection_matrix);

	glm::mat4 mOjoIzq = glm::mat4(1.0f);
	mOjoIzq = glm::translate(model_matrix, glm::vec3(0.9, 0.3, 0.3));
	mOjoIzq = glm::rotate(mOjoIzq, -10.0f,glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoOjo.render(mOjoIzq, view_matrix, projection_matrix);



	// Dibujamos las patas derechas
	glm::mat4 mPataDer01 = glm::mat4(1.0f);
	mPataDer01 = glm::translate(model_matrix, glm::vec3(0.4, -0.65, 0.0));
	mPataDer01 = glm::rotate(mPataDer01, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataDer01, view_matrix, projection_matrix);

	glm::mat4 mPataDer02 = glm::mat4(1.0f);
	mPataDer02 = glm::translate(model_matrix, glm::vec3(0.0, -0.60, 0.0));
	mPataDer02 = glm::rotate(mPataDer02, -25.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataDer02 = glm::rotate(mPataDer02, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataDer02, view_matrix, projection_matrix);

	glm::mat4 mPataDer03 = glm::mat4(1.0f);
	mPataDer03 = glm::translate(model_matrix, glm::vec3(-0.4, -0.50, 0.0));
	mPataDer03 = glm::rotate(mPataDer03, -45.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataDer03 = glm::rotate(mPataDer03, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataDer03, view_matrix, projection_matrix);



	// Dibujamos las patas izquierdas
	glm::mat4 mPataIzq01 = glm::mat4(1.0f);
	mPataIzq01 = glm::translate(model_matrix, glm::vec3(0.4, 0.65, 0.0));
	mPataIzq01 = glm::rotate(mPataIzq01, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq01 = glm::rotate(mPataIzq01, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataIzq01, view_matrix, projection_matrix);

	glm::mat4 mPataIzq02 = glm::mat4(1.0f);
	mPataIzq02 = glm::translate(model_matrix, glm::vec3(0.0, 0.60, 0.0));
	mPataIzq02 = glm::rotate(mPataIzq02, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq02 = glm::rotate(mPataIzq02, 25.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq02 = glm::rotate(mPataIzq02, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataIzq02, view_matrix, projection_matrix);

	glm::mat4 mPataIzq03 = glm::mat4(1.0f);
	mPataIzq03 = glm::translate(model_matrix, glm::vec3(-0.4, 0.50, 0.0));
	mPataIzq03 = glm::rotate(mPataIzq03, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq03 = glm::rotate(mPataIzq03, 45.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq03 = glm::rotate(mPataIzq03, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPata.render(mPataIzq03, view_matrix, projection_matrix);



	// Dibujamos las pinzas
	glm::mat4 mPinzaDer = glm::mat4(1.0f);
	mPinzaDer = glm::translate(model_matrix, glm::vec3(0.6, -0.5, 0.35));
	mPinzaDer = glm::scale(mPinzaDer, glm::vec3(0.9, 0.9, 0.9));
	mPinzaDer = glm::rotate(mPinzaDer, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	mPinzaDer = glm::rotate(mPinzaDer, 15.0f, glm::vec3(0.0, 1.0, 0.0));
	mPinzaDer = glm::rotate(mPinzaDer, 15.0f, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejoPinza.render(mPinzaDer, view_matrix, projection_matrix);

	glm::mat4 mPinzaIzq = glm::mat4(1.0f);
	mPinzaIzq = glm::translate(model_matrix, glm::vec3(0.6, 0.5, 0.35));
	mPinzaIzq = glm::scale(mPinzaIzq, glm::vec3(0.9, 0.9, 0.9));
	mPinzaIzq = glm::rotate(mPinzaIzq, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(0.0, 1.0, 0.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejoPinza.render(mPinzaIzq, view_matrix, projection_matrix);
}
