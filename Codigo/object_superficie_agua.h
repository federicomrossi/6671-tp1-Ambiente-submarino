/*  
 *  CLASS SUPERFICIEAGUA
 */  


#ifndef OBJECT_SUPERFICIE_AGUA_H
#define OBJECT_SUPERFICIE_AGUA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class SuperficieAgua : public ObjectDibujable
{
private:

	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLfloat* object_tangent_buffer;
	GLfloat* object_texture_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_tangent_buffer_size;
	unsigned int object_texture_buffer_size;
	unsigned int object_index_buffer_size;

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;		// Niveles que posee el objeto de estiramiento

	// Atributos del movimiento
	GLfloat tiempo;

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	
public:

	// Constructor
	SuperficieAgua();

	// Destructor
	~SuperficieAgua();

	// Crea un objeto
	virtual void create(int ancho);

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
