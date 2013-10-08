/*  
 *  CLASS CANGREJO_PINZA
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

#include "object_cangrejo_pinza.h"



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
CangrejoPinza::CangrejoPinza()
{
	this->pinza_index_buffer = NULL;
	this->pinza_vertex_buffer = NULL;
	this->pinza_normal_buffer = NULL;
}


// Destructor
CangrejoPinza::~CangrejoPinza() { }


// Crea un objeto
void CangrejoPinza::create()
{
	// Creamos el eje coordenado
	this->ejeCoordenado.create(1);

	// Creamos la esfera
	this->spiralSphere.create(0.5, 32, 32);

	// Creamos el cubo
	this->cube.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPinza::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);

	glm::mat4 m = glm::mat4(1.0f);
	this->spiralSphere.changeObjectColor(126, 241, 95);

	// Damos forma al objeto y la renderizamos
	glm::mat4 mAntebrazo = glm::mat4(1.0f);
	m = glm::translate(model_matrix, glm::vec3(0.0, -0.35, 0.0));
	mAntebrazo = glm::scale(m, glm::vec3(0.3, 0.7, 0.3));
	this->spiralSphere.render(mAntebrazo, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, -0.25, 0.0));
	m = glm::rotate(m, -40.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mBrazo = glm::mat4(1.0f);
	mBrazo = glm::translate(m, glm::vec3(0.0, -0.425, 0.0));
	mBrazo = glm::scale(mBrazo, glm::vec3(0.3, 0.85, 0.3));
	this->spiralSphere.render(mBrazo, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, -0.75, 0.0));
	m = glm::rotate(m, -30.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mPinzaGrande = glm::mat4(1.0f);
	mPinzaGrande = glm::translate(m, glm::vec3(0.0, -0.25, 0.0));
	mPinzaGrande = glm::scale(mPinzaGrande, glm::vec3(0.5, 0.6, 0.05));
	this->cube.render(mPinzaGrande, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::rotate(m, -30.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mMunieca = glm::mat4(1.0f);
	mMunieca = glm::scale(m, glm::vec3(0.3, 0.3, 0.3));
	this->spiralSphere.render(mMunieca, view_matrix, projection_matrix);

	glm::mat4 mPinzaChica = glm::mat4(1.0f);
	mPinzaChica = glm::translate(m, glm::vec3(0.0, -0.25, 0.05));
	mPinzaChica = glm::scale(mPinzaChica, glm::vec3(0.45, 0.4, 0.05));
	this->cube.render(mPinzaChica, view_matrix, projection_matrix);
}
