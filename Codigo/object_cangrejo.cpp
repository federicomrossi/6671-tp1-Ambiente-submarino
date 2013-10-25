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
#include "lib_matematica.h"
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
	// this->ejeCoordenado.create(3);

	// Creamos el cuerpo
	this->cangrejoCuerpo.create();

	// Creamos las patas
	this->cangrejoPataDer01.create(1);
	this->cangrejoPataDer02.create(1);
	this->cangrejoPataDer02.setDelay(50.0);
	this->cangrejoPataDer03.create(1);
	this->cangrejoPataIzq01.create(1);
	this->cangrejoPataIzq02.create(1);
	this->cangrejoPataIzq02.setDelay(50.0);
	this->cangrejoPataIzq03.create(1);

	// Creamos los ojos
	this->cangrejoOjo.create();

	// Creamos las pinzas
	this->cangrejoPinza.create();


	// Movimiento
	this->cuerpoPosZ = 0.0; 	// Posicion inicial
	this->parametro = 0.0;
	this->sentidoParametro = 1;
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Cangrejo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);
	
	// Calculamos movimiento del cuerpo
	// Puntos de control
	float mov_cuerpo_pc0x = 0.0;
	float mov_cuerpo_pc0y = -0.2;

	float mov_cuerpo_pc1x = 1.0;
	float mov_cuerpo_pc1y = 0.1;

	float mov_cuerpo_pc2x = 9.0;
	float mov_cuerpo_pc2y = 0.1;

	float mov_cuerpo_pc3x = 10.0;
	float mov_cuerpo_pc3y = -0.2;

	float mov_cuerpo_pcy[] = {mov_cuerpo_pc0y, mov_cuerpo_pc1y, mov_cuerpo_pc2y, mov_cuerpo_pc3y};

	
	this->parametro += 0.0081;

	if(this->parametro > 1.0) this->parametro = 0.0;

	// Calculamos la curva de bezier que da forma al esqueleto superior
	this->cuerpoPosZ = Matematica::curvaBezier(this->parametro,mov_cuerpo_pcy);


	// Dibujamos el cuerpo
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(0.0, 0.0, 
		this->cuerpoPosZ));
	// mCuerpo = glm::rotate(mCuerpo, 10.0f,glm::vec3(0.0, 1.0, 0.0));
	mCuerpo = glm::scale(mCuerpo, glm::vec3(1.1, 1.1, 1.1));
	this->cangrejoCuerpo.changeObjectColor(178,178,179);
	this->cangrejoCuerpo.render(mCuerpo, view_matrix, projection_matrix);



	// Dibujamos los ojos
	glm::mat4 mOjoDer = glm::mat4(1.0f);
	mOjoDer = glm::translate(model_matrix, glm::vec3(0.9, -0.3, 0.3 + this->cuerpoPosZ));
	mOjoDer = glm::rotate(mOjoDer, 10.0f,glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoOjo.render(mOjoDer, view_matrix, projection_matrix);

	glm::mat4 mOjoIzq = glm::mat4(1.0f);
	mOjoIzq = glm::translate(model_matrix, glm::vec3(0.9, 0.3, 0.3 + this->cuerpoPosZ));
	mOjoIzq = glm::rotate(mOjoIzq, -10.0f,glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoOjo.render(mOjoIzq, view_matrix, projection_matrix);


	// Escalamos la matriz inicial para las patas
	glm::mat4 mPata = glm::mat4(1.0f);
	mPata = glm::scale(model_matrix, glm::vec3(0.6, 0.6, 0.6));

	// Dibujamos las patas derechas
	glm::mat4 mPataDer01 = glm::mat4(1.0f);
	mPataDer01 = glm::translate(mPata, glm::vec3(0.9, -0.75, -0.8));
	mPataDer01 = glm::rotate(mPataDer01, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataDer01.render(mPataDer01, view_matrix, projection_matrix);

	glm::mat4 mPataDer02 = glm::mat4(1.0f);
	mPataDer02 = glm::translate(mPata, glm::vec3(0.5, -0.70, -0.8));
	mPataDer02 = glm::rotate(mPataDer02, -25.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataDer02 = glm::rotate(mPataDer02, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataDer02.render(mPataDer02, view_matrix, projection_matrix);

	glm::mat4 mPataDer03 = glm::mat4(1.0f);
	mPataDer03 = glm::translate(mPata, glm::vec3(0.1, -0.60, -0.8));
	mPataDer03 = glm::rotate(mPataDer03, -45.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataDer03 = glm::rotate(mPataDer03, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataDer03.render(mPataDer03, view_matrix, projection_matrix);



	// Dibujamos las patas izquierdas
	glm::mat4 mPataIzq01 = glm::mat4(1.0f);
	mPataIzq01 = glm::translate(mPata, glm::vec3(0.9, 0.75, -0.8));
	mPataIzq01 = glm::rotate(mPataIzq01, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq01 = glm::rotate(mPataIzq01, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataIzq01.render(mPataIzq01, view_matrix, projection_matrix);

	glm::mat4 mPataIzq02 = glm::mat4(1.0f);
	mPataIzq02 = glm::translate(mPata, glm::vec3(0.5, 0.70, -0.8));
	mPataIzq02 = glm::rotate(mPataIzq02, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq02 = glm::rotate(mPataIzq02, 25.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq02 = glm::rotate(mPataIzq02, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataIzq02.render(mPataIzq02, view_matrix, projection_matrix);

	glm::mat4 mPataIzq03 = glm::mat4(1.0f);
	mPataIzq03 = glm::translate(mPata, glm::vec3(0.1, 0.60, -0.8));
	mPataIzq03 = glm::rotate(mPataIzq03, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq03 = glm::rotate(mPataIzq03, 45.0f, glm::vec3(0.0, 0.0, 1.0));
	mPataIzq03 = glm::rotate(mPataIzq03, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	this->cangrejoPataIzq03.render(mPataIzq03, view_matrix, projection_matrix);



	// Dibujamos las pinzas
	glm::mat4 mPinzaDer = glm::mat4(1.0f);
	mPinzaDer = glm::translate(model_matrix, glm::vec3(0.6, -0.5, 0.2 + this->cuerpoPosZ));
	mPinzaDer = glm::scale(mPinzaDer, glm::vec3(0.4, 0.4, 0.4));
	mPinzaDer = glm::rotate(mPinzaDer, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	mPinzaDer = glm::rotate(mPinzaDer, 15.0f, glm::vec3(0.0, 1.0, 0.0));
	mPinzaDer = glm::rotate(mPinzaDer, 15.0f, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejoPinza.render(mPinzaDer, view_matrix, projection_matrix);

	glm::mat4 mPinzaIzq = glm::mat4(1.0f);
	mPinzaIzq = glm::translate(model_matrix, glm::vec3(0.6, 0.5, 0.2 + this->cuerpoPosZ));
	mPinzaIzq = glm::scale(mPinzaIzq, glm::vec3(0.4, 0.4, 0.4));
	mPinzaIzq = glm::rotate(mPinzaIzq, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(1.0, 0.0, 0.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(0.0, 1.0, 0.0));
	mPinzaIzq = glm::rotate(mPinzaIzq, -15.0f, glm::vec3(0.0, 0.0, 1.0));
	this->cangrejoPinza.render(mPinzaIzq, view_matrix, projection_matrix);
}
