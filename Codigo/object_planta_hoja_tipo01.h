/*  
 *  CLASS PLANTA_HOJA
 */  


#ifndef OBJECT_PLANTA_HOJA_TIPO_O1_H
#define OBJECT_PLANTA_HOJA_TIPO_01_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PlantaHojaTipo01 : public ObjectDibujable
{
private:

	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLfloat* object_texture_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_texture_buffer_size;
	unsigned int object_index_buffer_size;

	// Atributos del movimiento
	GLfloat tiempo;

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;				// Niveles que posee el objeto de
									// estiramiento
	float ESPACIADO_ESTIRAMIENTO;	// Espacio entre cada nivel de altura del
									// estiramiento del objeto.
	
public:

	// Constructor
	PlantaHojaTipo01();

	// Destructor
	~PlantaHojaTipo01();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);

	// Permite setear la amplitud de la hoja. Debe setearse antes de crear
	// el objeto.
	void setAmplitud(float amplitud);

	// Permite setear la velocidad de movimiento de la hoja. Debe setearse 
	// antes de crear el objeto.
	void setVelocidad(float velocidad);
};

#endif
