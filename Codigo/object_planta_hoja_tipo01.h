/*  
 *  CLASS PEZ_ALETA_DORSAL
 */  


#ifndef OBJECT_PLANTA_HOJA_TIPO_O1_H
#define OBJECT_PEZ_ALETA_DORSAL_H


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
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_index_buffer_size;

	// Puntos de control del movimiento
	float motion_pcx[4];
	float motion_pcy[4];
	float motion_pcz[4];
	int sentido_motion;		// Señalador que indica el sentido de t

	// Caracteristicas del objeto
	float ESTIRAMIENTO;		// Niveles que posee el objeto de estiramiento


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
};

#endif
