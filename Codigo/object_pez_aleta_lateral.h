/*  
 *  CLASS PEZ_ALETA_LATERAL
 */  


#ifndef OBJECT_PEZ_ALETA_LATERAL_H
#define OBJECT_PEZ_ALETA_LATERAL_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PezAletaLateral : public ObjectDibujable
{
private:

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	
	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_index_buffer_size;

	// Atributos del movimiento
	GLfloat tiempo;

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;				// Niveles que posee el objeto de
									// estiramiento
	float ESPACIADO_ESTIRAMIENTO;	// Espacio entre cada nivel de altura del
									// estiramiento del objeto.
	int ORIENTACION_ALETA;	// Atributo que permite establecer la orientación
							// de la aleta, siendo 1 hacia izquierda y -1 
							// hacie la derecha.
	
public:

	// Constructor
	PezAletaLateral();

	// Destructor
	~PezAletaLateral();

	// Crea un objeto
	// PRE: 'orientacion' define si la aleta se curva hacia la derecha (-1) o 
	// hacia la izquierda (1).
	virtual void create(int orientacion);

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
