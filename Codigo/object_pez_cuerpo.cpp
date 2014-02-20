/*  
 *  CLASS PEZ
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

#include "object_pez_cuerpo.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/PezCuerpoVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/PezCuerpoFShader.frag";
}







/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
PezCuerpo::PezCuerpo()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_tangent_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
PezCuerpo::~PezCuerpo() { }


// Crea un objeto
void PezCuerpo::create()
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/pez-cuerpo-texture-01.jpg", 
		"textures/pez-cuerpo-normalmap-texture-01.png",
		"textures/water-texture-03.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Puntos de control de la CURVA DE ESQUELETO SUPERIOR

	float superior_pc0x = 0.0;
	float superior_pc0y = 0.15;

	float superior_pc1x = 9.0;
	float superior_pc1y = 1.0;

	float superior_pc2x = 10.0;
	float superior_pc2y = 1.5;

	float superior_pc3x = 10.0;
	float superior_pc3y = 0.0;

	float superior_pcx[] = {superior_pc0x, superior_pc1x, superior_pc2x, superior_pc3x};
	float superior_pcy[] = {superior_pc0y, superior_pc1y, superior_pc2y, superior_pc3y};


	// Puntos de control de la CURVA DE ESQUELETO INFERIOR

	float inferior_pc0x = 10.0;
	float inferior_pc0y = 0.15;

	float inferior_pc1x = 9.0;
	float inferior_pc1y = 0.5;

	float inferior_pc2x = 0.1;
	float inferior_pc2y = 1.0;

	float inferior_pc3x = 0.0;
	float inferior_pc3y = 0.001;

	float inferior_pcx[] = {inferior_pc0x, inferior_pc1x, inferior_pc2x, inferior_pc3x};
	float inferior_pcy[] = {inferior_pc0y, inferior_pc1y, inferior_pc2y, inferior_pc3y};



	// Puntos de control de la CURVA DE ANCHO DEL ESQUELETO

	float ancho_pc0x = 0.0;
	float ancho_pc0y = 0.0;

	float ancho_pc1x = 2.0;
	float ancho_pc1y = 0.3;

	float ancho_pc2x = 8.0;
	float ancho_pc2y = 0.3;

	float ancho_pc3x = 10.0;
	float ancho_pc3y = 0.0;

	float ancho_pcx[] = {ancho_pc0x, ancho_pc1x, ancho_pc2x, ancho_pc3x};
	float ancho_pcy[] = {ancho_pc0y, ancho_pc1y, ancho_pc2y, ancho_pc3y};




	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;
	// Cantidad de curvas que compondran la curva general
	int CANT_CURVAS = 4;

	// Valores para cálculos (no modificar)
	this->ESTIRAMIENTO = 16;
	this->CANT_PUNTOS = CANT_CURVAS * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESPACIADO_ESTIRAMIENTO = 0.2;
	int DIMENSIONES_TEXTURA = 2;




	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_texture_buffer_size = DIMENSIONES_TEXTURA * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO; 
	this->object_texture_buffer = new GLfloat[this->object_vertex_buffer_size];


	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];

	this->object_tangent_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_tangent_buffer = new GLfloat[this->object_tangent_buffer_size];


	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;



	int i = 0;
	int y = 0;
	int w = 0;
	int z = 0;

	// Vector tangente correspondiente al barrido
	float t_barrido[3];
	t_barrido[0] = 0.0;
	t_barrido[1] = 0.0;
	t_barrido[2] = 1.0;


	// Iteramos sobre cada nivel del objeto
	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		// Calculamos la curva de bezier que da forma al esqueleto superior
		float distancia_sup = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	superior_pcy);

		// Calculamos la curva de bezier que da forma al esqueleto inferior
		float distancia_inf = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	inferior_pcy);

		// Calculamos la curva de bezier que da el ancho del cuerpo
		float ancho = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1), ancho_pcy);


		// Puntos de control
		float pc0x = 1.0  * distancia_inf;
		float pc0y = -1.0 * ancho;
		float pc0z = 0.0;

		float pc1x = -1.0 * distancia_sup;
		float pc1y = -1.0 * ancho;
		float pc1z = 0.0;

		float pc2x = -1.0 * distancia_sup;
		float pc2y = 1.0 * ancho;
		float pc2z = 0.0;

		float pc3x = 1.0  * distancia_inf;
		float pc3y = 1.0 * ancho;
		float pc3z = 0.0;

		// Armamos arreglos para los trozos que conforman la curva
		float pcx012[] = {pc0x, pc1x, pc2x};
		float pcx123[] = {pc1x, pc2x, pc3x};
		float pcx230[] = {pc2x, pc3x, pc0x};
		float pcx301[] = {pc3x, pc0x, pc1x};

		float pcy012[] = {pc0y, pc1y, pc2y};
		float pcy123[] = {pc1y, pc2y, pc3y};
		float pcy230[] = {pc2y, pc3y, pc0y};
		float pcy301[] = {pc3y, pc0y, pc1y};

		float pcz012[] = {pc0z, pc1z, pc2z};
		float pcz123[] = {pc1z, pc2z, pc3z};
		float pcz230[] = {pc2z, pc3z, pc0z};
		float pcz301[] = {pc3z, pc0z, pc1z};

		float punto_cierre_x;
		float punto_cierre_y;
		float punto_cierre_z;



		// Segmento 0-1-2 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx012);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy012);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx012, pcy012, pcz012, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t_barrido, t);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			this->object_texture_buffer[y++] = (q * 1.0) / this->ESTIRAMIENTO;
			this->object_texture_buffer[y++] = j / 8.0;
		}

		// Segmento 1-2-3 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx123);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy123);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx123, pcy123, pcz123, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t_barrido, t);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			this->object_texture_buffer[y++] = (q * 1.0) / this->ESTIRAMIENTO;
			this->object_texture_buffer[y++] = j / 8.0 + (this->CANT_PUNTOS / CANT_CURVAS);
		}

		// Segmento 2-3-0 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx230);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy230);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx230, pcy230, pcz230, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t_barrido, t);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			this->object_texture_buffer[y++] = (q * 1.0) / this->ESTIRAMIENTO;
			this->object_texture_buffer[y++] = j / 8.0 + 2 * (this->CANT_PUNTOS / CANT_CURVAS);
		}

		// Segmento 3-0-1 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx301);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy301);
			float ppz = q * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			// Calculamos el vector tangente a la curva en el punto
			float t[3];
			Matematica::vectorTangenteCurvaBSpline(j * PASO, pcx301, pcy301, pcz301, t);

			// Cargamos las coordenadas del vector tangente en el buffer
			this->object_tangent_buffer[z++] = t[0];
			this->object_tangent_buffer[z++] = t[1];
			this->object_tangent_buffer[z++] = t[2];

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t_barrido, t);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;

			this->object_texture_buffer[y++] = (q * 1.0) / this->ESTIRAMIENTO;
			this->object_texture_buffer[y++] = j / 8.0 + 3 * (this->CANT_PUNTOS / CANT_CURVAS);
		}
	}



	int sentido = 1;
	int k = 0;

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++)
	{
		if(sentido == 1)
		{
			for(int j=0; j <= (this->CANT_PUNTOS-1); j++) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = -1;
		}
		else if(sentido == -1)
		{
			for(int j=(this->CANT_PUNTOS-1); j >= 0; j--) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = 1;
		}
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezCuerpo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);
	
	// Ponemos el objeto en el centro del eje coordenado
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(-1.5, 0.0, 0.0));
	mCuerpo = glm::rotate(mCuerpo, 90.0f, glm::vec3(0.0, 1.0, 0.0));


	///////////////////////////////////////////
	// Bind View Matrix
	GLuint location_view_matrix = glGetUniformLocation(this->programHandle,
		"ViewMatrix"); 

	if(location_view_matrix >= 0) 
		glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, 
			&view_matrix[0][0]); 

	// Bind Projection Matrix
	GLuint location_projection_matrix = glGetUniformLocation(
		this->programHandle, "ProjectionMatrix"); 

	if(location_projection_matrix >= 0) 
		glUniformMatrix4fv( location_projection_matrix, 1, GL_FALSE,
			&projection_matrix[0][0]); 
	//
	///////////////////////////////////////////


	//////////////////////////////////////
	// Bind Light Settings

	glm::vec3 light_intensity = glm::vec3(0.8f, 0.8f, 1.0f);
	glm::vec4 light_position = glm::vec4(10.0f, 0.0f, 4.0f, 1.0f);
	// glm::vec3 light_intensity = glm::vec3(0.0f, 0.0f, -5.0f);
	// glm::vec4 light_position = glm::vec4(0.0f, 0.0f, 6.0f, 0.0f);
	glm::vec3 La = glm::vec3(0.1f, 0.1f, 0.2f);
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ka = glm::vec3(8 / 255.0f,
							 72 / 255.0f, 
							 56 / 255.0f);
	this->changeObjectColor(166, 224, 246);
	glm::vec3 Kd = glm::vec3(this->R / 255.0f,
							 this->G / 255.0f, 
							 this->B / 255.0f);
	glm::vec3 Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	float Shininess = 20.0;


	// Fog
	GLfloat FogMinDist = 3.0;
	GLfloat FogMaxDist = 15.0;
	glm::vec3 FogColor = glm::vec3(0.0f / 255.0, 
								   36.0f / 255.0,
								   60.0f / 255.0);


	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(
		this->programHandle, "LightIntensity");

	if(location_light_intensity >= 0) 
		glUniform3fv(location_light_intensity, 1, &light_intensity[0]); 

	// Light Position
	GLuint location_light_position = glGetUniformLocation(
		this->programHandle, "LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	// // La
	// GLuint location_la = glGetUniformLocation(
	// 	this->programHandle, "La");

	// if(location_la >= 0) 
	// 	glUniform3fv( location_la, 1, &La[0]); 
	
	// // Ld
	// GLuint location_ld = glGetUniformLocation(
	// 	this->programHandle, "Ld");

	// if(location_ld >= 0) 
	// 	glUniform3fv( location_ld, 1, &Ld[0]); 

	// // Ls
	// GLuint location_ls = glGetUniformLocation(
	// 	this->programHandle, "Ls");

	// if(location_ls >= 0) 
	// 	glUniform3fv( location_ls, 1, &Ls[0]); 


	// Ka
	GLuint location_ka = glGetUniformLocation(
		this->programHandle, "Ka");

	if(location_ka >= 0) 
		glUniform3fv( location_ka, 1, &Ka[0]); 
	
	// // Kd
	// GLuint location_kd = glGetUniformLocation(
	// 	this->programHandle, "Kd");

	// if(location_kd >= 0) 
	// 	glUniform3fv( location_kd, 1, &Kd[0]); 

	// Ks
	GLuint location_ks = glGetUniformLocation(
		this->programHandle, "Ks");

	if(location_ks >= 0) 
		glUniform3fv( location_ks, 1, &Ks[0]); 


	// Shininess
	GLfloat location_shininess = glGetUniformLocation(this->programHandle,
		"Shininess");

	if(location_shininess >= 0)
		glUniform1f(location_shininess, Shininess); 


	// FogMaxDist
	GLfloat location_fogMaxDist = glGetUniformLocation(this->programHandle,
		"FogMaxDist");

	if(location_fogMaxDist >= 0)
		glUniform1f(location_fogMaxDist, FogMaxDist);


	// FogMinDist
	GLfloat location_fogMinDist = glGetUniformLocation(this->programHandle,
		"FogMinDist");

	if(location_fogMinDist >= 0)
		glUniform1f(location_fogMinDist, FogMinDist); 


	// FogColor
	GLuint location_FogColor = glGetUniformLocation(
		this->programHandle, "FogColor");

	if(location_FogColor >= 0) 
		glUniform3fv(location_FogColor, 1, &FogColor[0]); 

	//
	///////////////////////////////////////////


	// Normal Matrix
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mCuerpo)));

	// Bind Normal MAtrix
	GLuint location_normal_matrix = glGetUniformLocation(this->programHandle, 
		"NormalMatrix"); 
	if( location_normal_matrix >= 0 ) 
		glUniformMatrix3fv( location_normal_matrix, 1, GL_FALSE, 
			&normal_matrix[0][0]); 

	// Bind Model Matrix
	GLuint location_model_matrix = glGetUniformLocation(this->programHandle, 
		"ModelMatrix"); 
	if(location_model_matrix >= 0)
		glUniformMatrix4fv( location_model_matrix, 1, GL_FALSE, 
			&mCuerpo[0][0]);


	// Set the Texture sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Texture");
	if(loc >= 0) glUniform1i(loc, 0);
	else fprintf(stderr, "Uniform variable TexPezCuerpo not found!\n");


	// Set the NormalMapTex sampler uniform to refer to texture unit 1
	int locNM = glGetUniformLocation(this->programHandle, "NormalMapTex");
	if(locNM >= 0) glUniform1i(locNM, 1);
	else fprintf(stderr, "Uniform variable NormalMapTexPezCuerpo not found!\n");


	// Set the SphereMapTex sampler uniform to refer to texture unit 2
	int locSM = glGetUniformLocation(this->programHandle, "SphereMapTex");
	if(locSM >= 0) glUniform1i(locSM, 2);
	else fprintf(stderr, "Uniform variable SphereMapTexPezCuerpo not found!\n");


	// // Set the CubeMapTex uniform to texture unit 2
	// int locCM = glGetUniformLocation(this->programHandle, "CubeMapTex");
	// if(locCM >= 0) glUniform1i(locCM, 2);
	// else fprintf(stderr, "Uniform variable CubeMapTexPezCuerpo not found!\n");


	// Activamos textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);

	// Activamos normal map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalmap_id);

	// Activamos el cube map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemap_id);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, this->object_normal_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->object_texture_buffer);
	glColorPointer(3, GL_FLOAT, 0, this->object_tangent_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
