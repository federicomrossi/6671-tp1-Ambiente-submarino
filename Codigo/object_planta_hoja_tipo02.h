/*  
 *  CLASS PEZ_ALETA_DORSAL
 */  


#ifndef OBJECT_PLANTA_HOJA_TIPO_O2_H
#define OBJECT_PLANTA_HOJA_TIPO_02_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PlantaHojaTipo02 : public ObjectDibujable
{
private:

	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_index_buffer_size;

	// Puntos de control del movimiento
	float motion_pcx[4];
	float motion_pcy[4];
	float motion_pcz[4];
	float amplitud;
	float velocidad;
	int sentido_motion;		// Señalador que indica el sentido de t

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;		// Niveles que posee el objeto de estiramiento


public:

	// Constructor
	PlantaHojaTipo02();

	// Destructor
	~PlantaHojaTipo02();

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
