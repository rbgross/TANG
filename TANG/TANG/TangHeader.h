/***************************************************************************************************
* TangHeader.h
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#define GLEW_STATIC 
#include <glew.h>
#include <glfw.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

/* DEFINES */
#define NO_SHADER 0
#define PICKING_SHADER 1
#define COLOR_SHADER 2
#define ATTRIB_POSITION 0
#define ATTRIB_NORMAL 1
#define ATTRIB_TEXTURE 2

/* CLASS DEFINITIONS */
class Renderer;
class Mesh;
class Environment;
class Light;
class Cube;
class FocusObject;
class DataPoint;

// DataPoint class definition
class DataPoint {
	private:
		Renderer* renderer;
		Mesh* mesh;
		glm::vec3 position;
		glm::vec3 color;
	public:
		DataPoint( Renderer* );
		~DataPoint( void );
		void setPosition( glm::vec3 );
		void setColor( glm::vec3 );
		void update( void );
		void draw( void );
};

// FocusObject class definition
class FocusObject {
	private:
		Renderer* renderer;
		Mesh* mesh;
		glm::vec3 position;
		glm::vec3 color;
	public:
		FocusObject( Renderer* );
		~FocusObject( void );
		void setPosition( glm::vec3 );
		void setColor( glm::vec3 );
		void update( void );
		void draw( void );
};

// Cube class definition
class Cube {
	private:
		Renderer* renderer;
		Mesh* mesh;
		glm::vec3 position;
		glm::vec3 color;
	public:
		Cube( Renderer* );
		~Cube( void );
		void setPosition( glm::vec3 );
		void setColor( glm::vec3 );
		void update( void );
		void draw( void );
};

// Light class definition
class Light {
	private:
		Renderer* renderer;
		glm::vec4 lightPos;
	public:
		Light( Renderer* );
		~Light( void );
		void update( void );
		void draw( void );
};

// Environment class definition
class Environment {
	private:
		Renderer* renderer;
		glm::mat4 model;
		Light* light;
		FocusObject* focusObject;
		std::vector< DataPoint* > dataPoints;
		std::vector< Cube* > cubes;
	public:
		Environment( Renderer* );
		~Environment( void );
		void addDataPoint( glm::vec3 );
		void setModel( glm::mat4 );
		glm::mat4 getModel( void );
		void update( void );
		void draw( void );
};

// Mesh class definition
class Mesh {
	private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		std::vector< float > meshData;
		std::vector< GLuint > elements;
		void loadModel( std::string );
	public:
		Mesh( std::string );
		~Mesh( void );
		void update( void );
		void draw( void );
};

// ColorShader class definition
class ColorShader {
	private:
		GLuint shaderProgram;
		void printShaderInfoLog( GLuint );
		void printProgramInfoLog( GLuint );
	public:
		ColorShader( void );
		~ColorShader( void );
		GLuint getShaderProgram( void );
		void setModel( glm::mat4 );
		void setView( glm::mat4 );
		void setProj( glm::mat4 );
		void setLightPos( glm::vec4 );
		void setDiffCol( glm::vec3 );
};

// Renderer class definition
class Renderer {
	private:
		ColorShader* colorShader;
		int windowWidth;
		int windowHeight;
		glm::mat4 view;
		glm::mat4 proj;
		int wheelPosition;
		int oldMouseX;
		int curMouseX;
		int oldMouseY;
		int curMouseY;
		bool leftPressed;
		bool rightPressed;
		bool initialize( void );
		void pollInput( void );
		glm::vec3 calcArcBallVector( int, int );
		void readData( std::string );
	public:
		Environment* environment;
		bool hideCube;
		Renderer( void );
		~Renderer( void );
		void setModel( glm::mat4 );
		void setView( glm::mat4 );
		void setProj( glm::mat4 );
		void setLightPos( glm::vec4 );
		void setDiffCol( glm::vec3 );
		bool windowOpen( void );
		void draw( void );
};