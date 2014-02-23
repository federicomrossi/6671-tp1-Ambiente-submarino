/*  
 *  CLASS CANGREJOPATA
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
#include "object_cangrejo_pata.h"



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
CangrejoPata::CangrejoPata() { }


// Destructor
CangrejoPata::~CangrejoPata() { }


// Crea un objeto
void CangrejoPata::create(int direccion)
{
	this->direccion = direccion;

	
	this->maxGradoMuslo = 110.0;
	this->minGradoMuslo = 70.0;
	if(direccion == 1) {
		this->gradoMuslo = 70.0;
		this->gradoRotacion = 0;
	}
	else if(direccion == -1) {
		this->gradoMuslo = 110.0;
		this->gradoRotacion = 360;
	}
	this->sentidoMuslo = 1;

	this->maxGradoPierna = 180.0;
	this->minGradoPierna = 35.0;
	this->gradoPierna = 35.0;
	if(direccion == 1) this->gradoPierna = 35.0;
	else if(direccion == -1) this->gradoPierna = 180.0;

	this->maxGradoPie = 70.0;
	this->minGradoPie = 40.0;
	this->gradoPie = 40.0;
	if(direccion == 1) this->gradoPie = 40.0;
	else if(direccion == -1) this->gradoPie = 70.0;


	// Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

	// Creamos el muslo
	this->muslo.create();

	// Creamos la pierna
	this->pierna.create();

	// Creamos el pie
	this->pie.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPata::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);

	this->gradoRotacion += 30.0;

	// if(direccion == 1)
	// {
	// 	// Rotación para efecto de delantamiento
	// 	this->gradoRotacion += 0.045;
	// 	if(this->gradoRotacion >= 360.0) this->gradoRotacion = 0.0;

	// 	// Calculo de posiciones para el movimiento
	// 	if(this->sentidoMuslo == 1 && this->gradoMuslo < maxGradoMuslo)
	// 	{
	// 		if(this->gradoMuslo < maxGradoMuslo - 5.0)
	// 		{
	// 			this->gradoMuslo += 0.65;
				
	// 		}
	// 		else 
	// 		{
	// 			this->gradoMuslo += 0.3;
				
	// 			this->gradoPierna += 0.65;
	// 			if(this->gradoPierna > this->maxGradoPierna)
	// 				this->gradoPierna = this->maxGradoPierna;

	// 			this->gradoPie += 0.65;
	// 			if(this->gradoPie > this->maxGradoPie)
	// 				this->gradoPie = this->maxGradoPie;
	// 		}
	// 	}
	// 	else if(this->sentidoMuslo == -1 && this->gradoMuslo > minGradoMuslo)
	// 	{
	// 		if(this->gradoMuslo > minGradoMuslo + 5.0)
	// 		{
	// 			this->gradoMuslo -= 0.65;
	// 		}
	// 		else
	// 		{
	// 			this->gradoMuslo -= 0.3;	
				
	// 			this->gradoPierna -= 0.65;
	// 			if(this->gradoPierna < this->minGradoPierna)
	// 				this->gradoPierna = this->minGradoPierna;

	// 			this->gradoPie -= 0.65;
	// 			if(this->gradoPie < this->minGradoPie)
	// 				this->gradoPie = this->minGradoPie;
	// 		}
	// 	}
	// }
	// else if(direccion == -1)
	// {
	// 	// Rotación para efecto de delantamiento
	// 	this->gradoRotacion -= 0.045;
	// 	if(this->gradoRotacion <= 0.0) this->gradoRotacion = 360.0;

	// 	// Calculo de posiciones para el movimiento
	// 	if(this->sentidoMuslo == 1 && this->gradoMuslo < maxGradoMuslo)
	// 	{
	// 		if(this->gradoMuslo < maxGradoMuslo - 5.0)
	// 		{
	// 			this->gradoMuslo += 0.65;
				
	// 		}
	// 		else 
	// 		{
	// 			this->gradoMuslo += 0.3;
				
	// 			this->gradoPierna += 0.65;
	// 			if(this->gradoPierna > this->maxGradoPierna)
	// 				this->gradoPierna = this->maxGradoPierna;

	// 			this->gradoPie += 0.65;
	// 			if(this->gradoPie > this->maxGradoPie)
	// 				this->gradoPie = this->maxGradoPie;
	// 		}
	// 	}
	// 	else if(this->sentidoMuslo == -1 && this->gradoMuslo > minGradoMuslo)
	// 	{
	// 		if(this->gradoMuslo > minGradoMuslo + 5.0)
	// 		{
	// 			this->gradoMuslo -= 0.65;
	// 		}
	// 		else
	// 		{
	// 			this->gradoMuslo -= 0.3;	
				
	// 			this->gradoPierna -= 0.65;
	// 			if(this->gradoPierna < this->minGradoPierna)
	// 				this->gradoPierna = this->minGradoPierna;

	// 			this->gradoPie -= 0.65;
	// 			if(this->gradoPie < this->minGradoPie)
	// 				this->gradoPie = this->minGradoPie;
	// 		}
	// 	}
	// }

	// Verificamos el sentido
	if(this->sentidoMuslo == 1 && this->gradoMuslo >= maxGradoMuslo)
		this->sentidoMuslo = -1;
	else if(this->sentidoMuslo == -1 && this->gradoMuslo <= minGradoMuslo)
		this->sentidoMuslo = 1;


	// Coloreamos objetos
	this->muslo.changeObjectColor(126, 241, 95);
	this->pierna.changeObjectColor(0, 0, 0);
	this->pie.changeObjectColor(126, 241, 95);

	// Matriz de traslasión
	glm::mat4 m = glm::mat4(1.0f);

	// Damos forma al objeto y la renderizamos
	glm::mat4 mMuslo = glm::mat4(1.0f);
	m = glm::rotate(model_matrix, 100.0f, glm::vec3(1.0, 0.0, 0.0));
	// m = glm::rotate(model_matrix, this->gradoMuslo * 1.0f, 
	// 	glm::vec3(1.0, 0.0, 0.0));
	// m = glm::translate(m, glm::vec3(0.0, 0.05 * cos(this->gradoRotacion), 
	// 	0.05 * sin(this->gradoRotacion)));
	this->muslo.render(m, view_matrix, projection_matrix);

	// // Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, 0.0, 1.6));
	m = glm::rotate(m, this->gradoPierna * 1.0f, glm::vec3(1.0, 0.0, 0.0));

	// // // Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	this->pierna.render(m, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, 0.1, 1.8));
	m = glm::rotate(m, this->gradoPie * 1.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mPie = glm::mat4(1.0f);
	mPie = glm::translate(m, glm::vec3(0.0, 0.0, 2.0));
	// mPie = glm::scale(mPie, glm::vec3(0.9, 0.9, 0.9));
	mPie = glm::rotate(mPie, -180.0f, glm::vec3(1.0, 0.0, 0.0));
	this->pie.render(mPie, view_matrix, projection_matrix);
}


// Permite establecer un delay en el movimientoi
void CangrejoPata::setDelay(float delay)
{
	this->gradoMuslo += delay;
}