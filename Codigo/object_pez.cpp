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
	// // Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

	// Creamos el cuerpo del pez;
	this->pezCuerpo.create();

	// Creamos el ojo del pez;
	this->pezOjoIzq.create(1.0, 16, 16);
	this->pezOjoDer.create(1.0, 16, 16);

	// Creamos la aleta trasera
	this->pezAletaTrasera.create();

	// Creamos la aleta dorsal
	this->pezAletaDorsal.create();

	// Creamos las aletas laterales
	this->pezAletaLateralDer.create(-1);
	this->pezAletaLateralIzq.create(1);
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Pez::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// // Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, 
	// 	projection_matrix);

	// Renderizamos el cuerpo del pez
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::scale(model_matrix, glm::vec3(1.3, 1.3, 1.3));
	this->pezCuerpo.render(mCuerpo, view_matrix, projection_matrix);

	// Renderizamos los ojos del pez
	glm::mat4 mOjoDer = glm::mat4(1.0f);
	glm::mat4 mOjoIzq = glm::mat4(1.0f);
	mOjoDer = glm::translate(model_matrix, glm::vec3(1.3, 0.06, 0.25));
	mOjoIzq = glm::translate(model_matrix, glm::vec3(1.3, -0.06, 0.25));
	mOjoDer = glm::scale(mOjoDer, glm::vec3(0.13, 0.13, 0.13));
	mOjoIzq = glm::scale(mOjoIzq, glm::vec3(0.13, 0.13, 0.13));
	// mOjoDer = glm::rotate(mOjoDer, 180.0f, glm::vec3(0.0, 1.0, 0.0));
	// mOjoDer = glm::rotate(mOjoDer, 270.0f, glm::vec3(0.0, 0.0, 1.0));
	mOjoIzq = glm::rotate(mOjoIzq, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezOjoDer.render(mOjoDer, view_matrix, projection_matrix);
	this->pezOjoIzq.render(mOjoIzq, view_matrix, projection_matrix);

	// Renderizamos la aleta trasera del pez
	glm::mat4 mAletaTrasera = glm::mat4(1.0f);
	mAletaTrasera = glm::translate(model_matrix, glm::vec3(-1.9, 0.0, 0.0));
	mAletaTrasera = glm::scale(mAletaTrasera, glm::vec3(1.3, 1.3, 1.3));
	mAletaTrasera = glm::rotate(mAletaTrasera, 90.0f, 
		glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaTrasera.changeObjectColor(33, 59, 200);
	// this->pezAletaTrasera.changeObjectColor(166, 214, 38);
	this->pezAletaTrasera.render(mAletaTrasera, view_matrix, projection_matrix);

	// Renderizamos la aleta dorsal del pez
	glm::mat4 mAletaDorsal = glm::mat4(1.0f);
	mAletaDorsal = glm::translate(model_matrix, glm::vec3(0.0, 0.0, 1.16));
	mAletaDorsal = glm::rotate(mAletaDorsal, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaDorsal.changeObjectColor(33, 59, 200);
	this->pezAletaDorsal.render(mAletaDorsal, view_matrix, projection_matrix);

	// Renderizamos las aletas laterales del pez
	glm::mat4 mAletaLateralIzq = glm::mat4(1.0f);
	mAletaLateralIzq = glm::translate(model_matrix, 
		glm::vec3(0.7, 0.26, 0.0));
	mAletaLateralIzq = glm::scale(mAletaLateralIzq, glm::vec3(0.5, 0.5, 0.5));
	mAletaLateralIzq = glm::rotate(mAletaLateralIzq, 
		90.0f, glm::vec3(0.0, 0.0, 1.0));
	// mAletaLateralIzq = glm::rotate(mAletaLateralIzq, 
	// 	10.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaLateralIzq.render(mAletaLateralIzq, view_matrix, projection_matrix);

	glm::mat4 mAletaLateralDer = glm::mat4(1.0f);
	mAletaLateralDer = glm::translate(model_matrix, glm::vec3(0.7, -0.26, 0.0));
	mAletaLateralDer = glm::scale(mAletaLateralDer, glm::vec3(0.5, 0.5, 0.5));
	mAletaLateralDer = glm::rotate(mAletaLateralDer, 
		90.0f, glm::vec3(0.0, 0.0, 1.0));
	this->pezAletaLateralDer.render(mAletaLateralDer, view_matrix, projection_matrix);
}
