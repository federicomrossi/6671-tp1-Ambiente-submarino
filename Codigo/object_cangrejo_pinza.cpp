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
	// this->ejeCoordenado.create(1);

	// Creamos el antebrazo
	this->antebrazo.create();

	// Creamos el brazo
	this->brazo.create();

	// Creamos la munieca
	this->munieca.create(0.2, 32, 32);

	// Creamos la garra superior
	this->garraSup.create();

	// Creamos la garra Inferior
	this->garraInf.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPinza::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);


	// Coloreamos objetos
	this->antebrazo.changeObjectColor(126, 241, 95);
	this->brazo.changeObjectColor(126, 241, 95);
	this->munieca.changeObjectColor(126, 241, 95);
	this->garraSup.changeObjectColor(178,178,179);
	this->garraInf.changeObjectColor(178,178,179);

	// Matriz de traslasión
	glm::mat4 m = glm::mat4(1.0f);


	// Damos forma al objeto y la renderizamos
	glm::mat4 mAntebrazo = glm::mat4(1.0f);
	mAntebrazo = glm::rotate(model_matrix, 90.0f, glm::vec3(1.0, 0.0, 0.0));
	this->antebrazo.render(mAntebrazo, view_matrix, projection_matrix);


	// Reposicionamos
	m = glm::translate(model_matrix, glm::vec3(0.0, -2.0, -0.3));
	m = glm::rotate(m, 40.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mBrazo = glm::mat4(1.0f);
	this->brazo.render(m, view_matrix, projection_matrix);


	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, 0.0, 2.0));
	// m = glm::rotate(m, -30.0f, glm::vec3(1.0, 0.0, 0.0));

	glm::mat4 mMunieca = glm::mat4(1.0f);
	this->munieca.render(m, view_matrix, projection_matrix);


	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);


	glm::mat4 mGarraSup = glm::mat4(1.0f);
	mGarraSup = glm::translate(m, glm::vec3(0.0, 0.0, 0.0));
	mGarraSup = glm::scale(mGarraSup, glm::vec3(0.8, 0.8, 0.8));
	this->garraSup.render(mGarraSup, view_matrix, projection_matrix);


	glm::mat4 mGarraInf = glm::mat4(1.0f);
	mGarraInf = glm::translate(m, glm::vec3(0.0, 0.0, 0.0));
	mGarraInf = glm::scale(mGarraInf, glm::vec3(0.8, 0.8, 0.8));
	mGarraInf = glm::rotate(mGarraInf, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	this->garraInf.render(mGarraInf, view_matrix, projection_matrix);
}
