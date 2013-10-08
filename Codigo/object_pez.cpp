/*  
 *  CLASS PEZ_CUERPO
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

#include "object_pez.h"



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
Pez::Pez() { }


// Destructor
Pez::~Pez() { }


// Crea un objeto
void Pez::create()
{
	// Creamos el eje coordenado
	this->ejeCoordenado.create(3);

	// Creamos el cuerpo del pez;
	this->pezCuerpo.create();

	// Creamos el ojo del pez;
	this->pezOjo.create();

	// Creamos la aleta trasera
	this->pezAletaTrasera.create();

	// Creamos la aleta dorsal
	this->pezAletaDorsal.create();

	// Creamos las aletas laterales
	this->pezAletaLateralDer.create();
	this->pezAletaLateralIzq.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Pez::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	this->ejeCoordenado.render(model_matrix, view_matrix, 
		projection_matrix);

	// Renderizamos el cuerpo del pez
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::scale(model_matrix, glm::vec3(2.0, 2.0, 2.0));
	this->pezCuerpo.render(mCuerpo, view_matrix, projection_matrix);

	// Renderizamos los ojos del pez
	glm::mat4 mOjoDer = glm::mat4(1.0f);
	glm::mat4 mOjoIzq = glm::mat4(1.0f);
	mOjoDer = glm::translate(model_matrix, glm::vec3(1.6, 0.06, 0.25));
	mOjoIzq = glm::translate(model_matrix, glm::vec3(1.6, -0.06, 0.25));
	mOjoDer = glm::scale(mOjoDer, glm::vec3(0.07, 0.07, 0.07));
	mOjoIzq = glm::scale(mOjoIzq, glm::vec3(0.07, 0.07, 0.07));
	this->pezOjo.render(mOjoDer, view_matrix, projection_matrix);
	this->pezOjo.render(mOjoIzq, view_matrix, projection_matrix);

	// Renderizamos la aleta trasera del pez
	glm::mat4 mAletaTrasera = glm::mat4(1.0f);
	mAletaTrasera = glm::translate(model_matrix, glm::vec3(-2.0, 0.0, 0.0));
	this->pezAletaTrasera.render(mAletaTrasera, view_matrix, projection_matrix);

	// Renderizamos la aleta dorsal del pez
	glm::mat4 mAletaDorsal = glm::mat4(1.0f);
	mAletaDorsal = glm::translate(model_matrix, glm::vec3(0.0, 0.0, 0.9));
	this->pezAletaDorsal.render(mAletaDorsal, view_matrix, projection_matrix);

	// Renderizamos las aletas laterales del pez
	glm::mat4 mAletaLateralDer = glm::mat4(1.0f);
	mAletaLateralDer = glm::translate(model_matrix, glm::vec3(0.8, -0.15, 0.0));
	mAletaLateralDer = glm::rotate(mAletaLateralDer, 
		10.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaLateralDer.render(mAletaLateralDer, view_matrix, projection_matrix);

	glm::mat4 mAletaLateralIzq = glm::mat4(1.0f);
	mAletaLateralIzq = glm::translate(model_matrix, glm::vec3(0.8, 0.15, 0.0));
	mAletaLateralIzq = glm::rotate(mAletaLateralIzq, 
		-10.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaLateralIzq.render(mAletaLateralIzq, view_matrix, projection_matrix);
}