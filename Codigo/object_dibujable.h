/*  
 *  CLASS OBJECTDIBUJABLE
 */  


#ifndef OBJECT_DIBUJABLE_H
#define OBJECT_DIBUJABLE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class ObjectDibujable
{
protected:

	GLuint programHandle;				// Program shader
	GLuint vertShader;					// Vertex shader
	GLuint fragShader;					// Fragment shader
	GLuint texture_id;					// ID de la textura
	GLuint normalmap_id;				// ID de la textura de mapa de normales

	unsigned char* image_buffer;
	int image_witdh;
	int image_height;
	int image_channels;

	unsigned char* normalmap_buffer;
	int normalmap_witdh;
	int normalmap_height;
	int normalmap_channels;

	// Colores que definen al objeto en formato RGB
	int R, G, B;

	// Carga los shaders
	void loadShaderPrograms(std::string vertShaderFile, 
		std::string fragShaderFile);

	// Carga e inicia la textura
	void loadAndInitTexture(const char* filename);

	// Carga e inicia la textura y el mapa de normales
	void loadAndInitTexture(const char* filename, const char* normalmap);

public:

	// Constructor
	ObjectDibujable();

	// Destructor
	~ObjectDibujable();

	// Crea un objeto.
	void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix,
		glm::mat4 &projection_matrix) = 0;

	// Cambia el color del objeto
	// PRE: 'r', 'g' y 'b' corresponden al color en RGB, es decir, a un valor
	// entre 0 y 255.
	void changeObjectColor(int r, int g, int b);
};

#endif
