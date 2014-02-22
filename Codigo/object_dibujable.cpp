/*  
 *  CLASS OBJECTDIBUJABLE
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
#include "SOIL.h"

#include "object_dibujable.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
ObjectDibujable::ObjectDibujable() { }


// Destructor
ObjectDibujable::~ObjectDibujable() { }
	

// Crea un objeto.
void ObjectDibujable::create() { }


// Cambia el color del objeto
// PRE: 'r', 'g' y 'b' corresponden al color en RGB, es decir, a un valor
// entre 0 y 255.
void ObjectDibujable::changeObjectColor(int r, int g, int b)
{
	this->R = r;
	this->G = g;
	this->B = b;

	
	glm::vec3 diffuse_reflectivity = glm::vec3(r/255.0, g/255.0, b/255.0);

	GLuint location_diffuse_reflectivity = glGetUniformLocation(
		this->programHandle, "Kd");

	if(location_diffuse_reflectivity >= 0) 
		glUniform3fv(location_diffuse_reflectivity, 1, 
			&diffuse_reflectivity[0]); 
}


// Carga los shaders
void ObjectDibujable::loadShaderPrograms(std::string vertShaderFile, 
	std::string fragShaderFile)
{
	// ********************************************
	// Compiling the shader programms
	// ********************************************

	// Do your GLEW experiments here:
	if (GLEW_ARB_shading_language_100) 
	{ 
		// std::cout << "GLEW_ARB_shading_language_100" << std::endl;
		const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
		
		if (glGetError() != GL_INVALID_ENUM)
		{
			std::string version((char*)sVersion);
			// std::cout << version.c_str() << std::endl;
		}

		// Load vertex Shader
		this->vertShader = glCreateShader (GL_VERTEX_SHADER);
		
		// if (0 == this->vertShader)
		// 	std::cout << "Error creating vertex shader" << std::endl;

		std::ifstream v_shader_file(vertShaderFile.c_str(), std::ifstream::in);
		std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), 
			std::istreambuf_iterator<char>());
		const char* vs_code_array[] = {v_str.c_str()};

		glShaderSource(this->vertShader, 1, vs_code_array, NULL);

		// Compilar el shader
		glCompileShader(this->vertShader);

		// Verificar resultado de la compilacion
		GLint vs_compilation_result;
		glGetShaderiv(this->vertShader, GL_COMPILE_STATUS, 
			&vs_compilation_result);

		if(GL_FALSE == vs_compilation_result)
		{
			// Informe de error por salida estandar
			std::cout << "Vertex shader compilation failed!\n" << std::endl;
			
			GLint logLen;
			glGetShaderiv( this->vertShader, GL_INFO_LOG_LENGTH, &logLen );
			
			if(logLen > 0)
			{
				char * log = (char *) malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(vertShader, logLen, &written, log);
				std::cout << "Shader log: " << log << std::endl;
				free(log);
			}
		}

		 // Load fragment Shader
		this->fragShader = glCreateShader (GL_FRAGMENT_SHADER);

		// Informe de error por salida estandar
		if(0 == this->fragShader)
			std::cout << "Error creating fragment shader" << std::endl;

		std::ifstream f_shader_file(fragShaderFile.c_str(), std::ifstream::in);
		std::string f_str((std::istreambuf_iterator<char>(f_shader_file)),
			std::istreambuf_iterator<char>());
		const char* fs_code_array[] = {f_str.c_str()};

		glShaderSource(this->fragShader, 1, fs_code_array, NULL);

		// Compilar el shader
		glCompileShader(this->fragShader);

		// verificar resultado de la compilacion
		GLint fs_compilation_result;
		glGetShaderiv( this->fragShader, GL_COMPILE_STATUS, 
			&fs_compilation_result );

		if(GL_FALSE == fs_compilation_result)
		{
			// Informe de error por salida estandar
			std::cout << "Fragment shader compilation failed!\n" << std::endl;
			
			GLint logLen;
			glGetShaderiv( this->fragShader, GL_INFO_LOG_LENGTH, &logLen );
			
			if(logLen > 0)
			{
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog( this->fragShader, logLen, &written, log);
				std::cout << "Shader log: " << log << std::endl;
				free(log);
			}
		}
	
		// *******************************************


		// *******************************************
		// Linking the shader programms
		// *******************************************

		this->programHandle = glCreateProgram();
		
		if (0 == this->programHandle)
		{
			// Informe de error por salida estandar
			std::cout << "Error creating program object" << std::endl;
		}
		else
		{
			glAttachShader(this->programHandle, this->vertShader);
			glAttachShader(this->programHandle, this->fragShader);
			glLinkProgram(this->programHandle);

			GLint status;
			glGetProgramiv( this->programHandle, GL_LINK_STATUS, &status );
			
			if(GL_FALSE == status)
			{
				// Informe de error por salida estandar
				std::cout << "Failed to link shader program!\n" << std::endl;
				
				GLint logLen;
				glGetProgramiv(this->programHandle, GL_INFO_LOG_LENGTH, 
					&logLen);
				
				if(logLen > 0)
				{
					char * log = (char *) malloc(logLen);
					GLsizei written;
					glGetProgramInfoLog(programHandle, logLen, &written, log);
					std::cout << "Program log: \n%s" << std::endl;
					free(log);
				}
			}

		}
	}
}


// Carga e inicia las texturas
void ObjectDibujable::loadAndInitTexture(const char* filename)
{
	// Load texture file
	this->image_buffer  = SOIL_load_image(filename, &this->image_witdh, &this->image_height, &this->image_channels, SOIL_LOAD_RGBA);

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image_witdh, this->image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// Carga e inicia las texturas
void ObjectDibujable::loadAndInitTexture(const char* filename, 
	const char* normalmap)
{
	// Load texture file
	this->image_buffer  = SOIL_load_image(filename, &this->image_witdh, &this->image_height, &this->image_channels, SOIL_LOAD_RGBA);

	GLuint texIDs[2];

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(2, texIDs);
	this->texture_id = texIDs[0];
	this->normalmap_id = texIDs[1];

	glBindTexture(GL_TEXTURE_2D, this->texture_id);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image_witdh, this->image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// Load normalmap texture file
	this->normalmap_buffer  = SOIL_load_image(normalmap, 
		&this->normalmap_witdh, &this->normalmap_height, 
		&this->normalmap_channels, SOIL_LOAD_RGBA);

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalmap_id);  

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->normalmap_witdh, 
		this->normalmap_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		this->normalmap_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


// Carga e inicia la textura, el mapa de normales y el mapa esférico
void ObjectDibujable::loadAndInitTexture(const char* filename, const char* normalmap,
		const char* spheremap)
{
	GLuint texIDs[3];
	
	// Load texture file
	this->image_buffer  = SOIL_load_image(filename, &this->image_witdh, &this->image_height, &this->image_channels, SOIL_LOAD_RGBA);

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(3, texIDs);
	this->texture_id = texIDs[0];
	this->normalmap_id = texIDs[1];
	this->spheremap_id = texIDs[2];

	glBindTexture(GL_TEXTURE_2D, this->texture_id);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image_witdh, this->image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// Load normalmap texture file
	this->normalmap_buffer  = SOIL_load_image(normalmap, 
		&this->normalmap_witdh, &this->normalmap_height, 
		&this->normalmap_channels, SOIL_LOAD_RGBA);

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalmap_id);  

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->normalmap_witdh, 
		this->normalmap_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		this->normalmap_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// Load spheremap texture file
	this->spheremap_buffer  = SOIL_load_image(spheremap, 
		&this->spheremap_witdh, &this->spheremap_height, 
		&this->spheremap_channels, SOIL_LOAD_RGBA);

	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->spheremap_id);  

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->spheremap_witdh, 
		this->spheremap_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		this->spheremap_buffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	// glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	// glEnable(GL_TEXTURE_GEN_S);
	// glEnable(GL_TEXTURE_GEN_T);
}
