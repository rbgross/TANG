/***************************************************************************************************
* ColorShader.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* ColorShader function
*
* Placeholder.
***************************************************************************************************/
ColorShader::ColorShader( void ) {
	//Vertex Shader
	const char* vertexSource =
		"#version 150\n"
		"in vec3 position;"
		"in vec3 normal;"
		"out vec3 eyeNormal;"
		"out vec3 eyePosition;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 proj;"
		"void main() {"
		"	eyeNormal = mat3( view * model ) * normal;"
		"	eyePosition = vec3( view * model * vec4( position, 1.0f ) );"
		"	gl_Position = proj * view * model * vec4( position, 1.0f );"
		"}";

	//Fragment Shader
	const char* fragmentSource =
		"#version 150\n"
		"in vec3 eyePosition;"
		"in vec3 eyeNormal;"
		"out vec4 outColor;"
		"uniform mat4 view;"
		"uniform vec4 lightPosition;"
		"uniform vec3 diffuseColor;"
		"void main() {"
		"	vec4 eyeLightPosition = view * lightPosition;"
		"	vec3 normal = normalize( eyeNormal );"
		"	vec3 toLightDir = normalize( eyeLightPosition.xyz - eyeLightPosition.w * eyePosition );"
		"	vec3 lightIntensity = vec3( 1.0f, 1.0f, 1.0f );"
		"	vec3 ambientColor = 0.2f * diffuseColor;"
		"	vec3 ambient = ambientColor;"
		"	vec3 diffuse = diffuseColor * max ( dot( normal, toLightDir ), 0.0f );"
		"	outColor = vec4( lightIntensity * ( ambient + diffuse ), 1.0f );"
		"}";

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexSource, NULL );
	glCompileShader( vertexShader );

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
	glCompileShader( fragmentShader );

	// Attach the vertex and fragment shader to a shader program
	this->shaderProgram = glCreateProgram();
	glAttachShader( this->shaderProgram, vertexShader );
	glAttachShader( this->shaderProgram, fragmentShader );

	// Explicitly bind attribute and fragment data locations
	glBindAttribLocation( this->shaderProgram, ATTRIB_POSITION, "position" );
	glBindAttribLocation( this->shaderProgram, ATTRIB_NORMAL, "normal" ); 
	glBindFragDataLocation( this->shaderProgram, 0, "outColor" );

	// Link and use the shader program
	glLinkProgram( this->shaderProgram );
	glUseProgram( this->shaderProgram );

	// Print the shader logs (to check for potential errors)
	printShaderInfoLog( vertexShader );
	printShaderInfoLog( fragmentShader );
	printProgramInfoLog( this->shaderProgram );

	// Flag the vertex and fragment shaders for deletion when not in use
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
}

/***************************************************************************************************
* ~ColorShader function
*
* Placeholder.
***************************************************************************************************/
ColorShader::~ColorShader( void ) {
	// Clean up the program before exiting
	glDeleteProgram( this->shaderProgram );
}

/***************************************************************************************************
* getShaderProgram function
*
* Placeholder.
***************************************************************************************************/
GLuint ColorShader::getShaderProgram( void ) {
	return this->shaderProgram;
}

/***************************************************************************************************
* setModel function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::setModel( glm::mat4 model ) {
	glUniformMatrix4fv( glGetUniformLocation( this->shaderProgram, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
}

/***************************************************************************************************
* setView function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::setView( glm::mat4 view ) {
	glUniformMatrix4fv( glGetUniformLocation( this->shaderProgram, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
}

/***************************************************************************************************
* setProj function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::setProj( glm::mat4 proj ) {
	glUniformMatrix4fv( glGetUniformLocation( this->shaderProgram, "proj" ), 1, GL_FALSE, glm::value_ptr( proj ) );
}

/***************************************************************************************************
* setLightPos function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::setLightPos( glm::vec4 lightPos ) {
	glUniform4fv( glGetUniformLocation( this->shaderProgram, "lightPosition" ), 1, glm::value_ptr( lightPos ) );
}

/***************************************************************************************************
* setDiffCol function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::setDiffCol( glm::vec3 diffCol ) {
	glUniform3fv( glGetUniformLocation( this->shaderProgram, "diffuseColor" ), 1, glm::value_ptr( diffCol ) );
}

/***************************************************************************************************
* printShaderInfoLog function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::printShaderInfoLog( GLuint obj ) {
    int infoLogLength = 0; 
    glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &infoLogLength );
 
	if ( infoLogLength > 1 ) {
		int charsWritten = 0;
		char *infoLog = new char[ infoLogLength ];
        glGetShaderInfoLog( obj, infoLogLength, &charsWritten, infoLog );
		std::cerr << infoLog << std::endl;
		delete infoLog;
	}
}
 
/***************************************************************************************************
* printProgramInfoLog function
*
* Placeholder.
***************************************************************************************************/
void ColorShader::printProgramInfoLog( GLuint obj ) {
    int infoLogLength = 0; 
    glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &infoLogLength );
 
    if ( infoLogLength > 1 ) {
        int charsWritten = 0;
		char* infoLog = new char[ infoLogLength ];
        glGetProgramInfoLog( obj, infoLogLength, &charsWritten, infoLog );
		std::cerr << infoLog << std::endl;
		delete infoLog;
    }
}