/*  
 *  CLASS EJECOORDENADO
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

#include "object_eje_coordenado.h"



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
EjeCoordenado::EjeCoordenado() { }


// Destructor
EjeCoordenado::~EjeCoordenado() { }


// Crea un objeto
void EjeCoordenado::create(int size) 
{
	// Guardamos el tamaño del eje
	this->size = size;

	// Creamos objetos
	this->sphere.create(1.0, 32, 32);
	this->cube.create();
}


// Renderiza el cubo (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void EjeCoordenado::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// CENTRO DEL EJE
	glm::mat4 mCentro = glm::mat4(1.0f);
	mCentro = glm::scale(model_matrix, glm::vec3(0.05f, 0.05f, 0.05f));
	this->sphere.changeObjectColor(1.0, 1.0, 1.0);
	this->sphere.render(mCentro, view_matrix, projection_matrix);


	GLfloat axisSize = this->size * 0.5f;

	// EJE X (Rojo)
	glm::mat4 mX = glm::mat4(1.0f);
	mX = glm::translate(model_matrix, glm::vec3(axisSize / 2.0, 0.0, 0.0));
	mX = glm::scale(mX, glm::vec3(axisSize, 
		axisSize * 0.02f, axisSize * 0.02f));
	this->cube.changeObjectColor(1.0, 0.0, 0.0);
	this->cube.render(mX, view_matrix, projection_matrix);

	// EJE Y (Verde)
	glm::mat4 mY = glm::mat4 (1.0f);
	mY = glm::translate(model_matrix, glm::vec3(0.0, axisSize / 2.0, 0.0));
	mY = glm::rotate(mY, -90.0f, glm::vec3(0.0, 0.0, 1.0));
	mY = glm::scale(mY, glm::vec3(axisSize, 
		axisSize * 0.02f, axisSize * 0.02f));
	this->cube.changeObjectColor(0.0, 1.0, 0.0);
	this->cube.render(mY, view_matrix, projection_matrix);

	// EJE Z (Azul)
	glm::mat4 mZ = glm::mat4 (1.0f);
	mZ = glm::translate(model_matrix, glm::vec3(0.0, 0.0, axisSize / 2.0));
	mZ = glm::rotate(mZ, -90.0f, glm::vec3(0.0, 1.0, 0.0));
	mZ = glm::scale(mZ, glm::vec3(axisSize, 
		axisSize * 0.02f, axisSize * 0.02f));
	this->cube.changeObjectColor(0.0, 0.0, 1.0);
	this->cube.render(mZ, view_matrix, projection_matrix);
}
