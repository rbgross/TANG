/***************************************************************************************************
* Renderer.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* Renderer function
*
* Placeholder.
***************************************************************************************************/
Renderer::Renderer( void ) {	
	this->windowWidth = 640	;
	this->windowHeight = 480;

	// Initalize the OpenGL context and Renderer
	if ( !this->initialize() ) {
		std::cerr << "Failed to create an OpenGL 3.2 context and window.\n";
		exit( EXIT_FAILURE );
	}

	// Load the shaders
	this->colorShader = new ColorShader();

	// Assign the value for the view matrix
	this->view = glm::lookAt( glm::vec3( 0.0f, 0.0f, 55.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
	this->setView( this->view );

	// Assign the value for the projection matrix
	this->proj = glm::perspective( 45.0f, ( float ) this->windowWidth / ( float ) this->windowHeight, 0.1f, 1000.0f );
	this->setProj( this->proj );

	this->environment = new Environment( this );

	this->wheelPosition = glfwGetMouseWheel();
	glfwGetMousePos( &this->oldMouseX, &this->oldMouseY );
	this->curMouseX = this->oldMouseX;
	this->curMouseY = this->oldMouseY;
	this->hideCube = false;
	this->leftPressed = false;
	this->rightPressed = false;

	this->readData( "C:\\Users\\Ryan\\Game Tests\\Data.txt" );
}

/***************************************************************************************************
* ~Renderer function
*
* Placeholder.
***************************************************************************************************/
Renderer::~Renderer( void ) {	
	// Close GLFW
	delete this->environment;
	delete this->colorShader;
    glfwTerminate();
}

/***************************************************************************************************
* setModel function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setModel( glm::mat4 model ) {
	this->colorShader->setModel( model );
}

/***************************************************************************************************
* setView function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setView( glm::mat4 view ) {
	this->colorShader->setView( view );
}

/***************************************************************************************************
* setProj function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setProj( glm::mat4 proj ) {
	this->colorShader->setProj( proj );
}

/***************************************************************************************************
* setLightPos function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setLightPos( glm::vec4 lightPos ) {
	this->colorShader->setLightPos( lightPos );
}

/***************************************************************************************************
* setDiffCol function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setDiffCol( glm::vec3 diffCol ) {
	this->colorShader->setDiffCol( diffCol );
}

/***************************************************************************************************
* windowOpen function
*
* Placeholder.
***************************************************************************************************/
bool Renderer::windowOpen( void ) {	
	return glfwGetWindowParam( GLFW_OPENED );
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Renderer::draw( void ) {
	// Poll inputs
	this->pollInput();

	// Update the augmented reality objects
	this->environment->update();

	// Bind the default screen buffer and clear the previous data
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw the scene
	this->environment->draw();
		
	// Swap the buffers
	glfwSwapBuffers();
}

/***************************************************************************************************
* initialize function
*
* Placeholder.
***************************************************************************************************/
bool Renderer::initialize( void ) {
	// Initalize GLFW
	if ( !glfwInit() ) {
		std::cerr << "Failed to initialize GLFW.\n";
		return false;
	}

	// Provide Renderer hints to GLFW
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 16 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );

	// Open a GLFW Renderer
	if ( !glfwOpenWindow( this->windowWidth, this->windowHeight, 0, 0, 0, 0, 24, 8, GLFW_WINDOW ) ) {
		std::cerr << "Failed to open GLFW window.\n";
		return false;
	}
	glfwSetWindowTitle( "Game Test" );

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if ( glewInit() != GLEW_OK ) {
		std::cerr << "Failed to initialize GLEW.\n";
		return false;
	}

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );

	return true;
}

/***************************************************************************************************
* pollInput function
*
* Placeholder.
***************************************************************************************************/
void Renderer::pollInput( void ) {	
	// Check mouse wheel
	int tempWheelPosition = glfwGetMouseWheel();
	if ( tempWheelPosition != this->wheelPosition ) {
		this->wheelPosition = tempWheelPosition;
		this->setView( glm::lookAt( glm::vec3( 0.0f, 0.0f, 55.0f - this->wheelPosition ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) ) );	
	}

	// Perform action on first left mouse click
	if ( !this->leftPressed && glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS ) {
		this->leftPressed = true;
		this->hideCube = !this->hideCube;
	}

	// Set left to not pressed when released
	if ( glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) == GLFW_RELEASE ) {
		this->leftPressed = false;
	}

	// Update current mouse cursor position when right mouse is pressed
	if ( !this->rightPressed && glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS ) {
		this->rightPressed = true;
		glfwGetMousePos( &this->oldMouseX, &this->oldMouseY );
		this->curMouseX = this->oldMouseX;
		this->curMouseY = this->oldMouseY;
	}

	// Set right to not pressed when released
	if ( glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_RELEASE ) {
		this->rightPressed = false;
	}

	// When right mouse is held down, rotate the environment
	if ( this->rightPressed ) {
		glfwGetMousePos( &this->curMouseX, &this->curMouseY );
		if ( this->curMouseX != this->oldMouseX || this->curMouseY != this->oldMouseY ) {
			glm::vec3 oldVec = calcArcBallVector( this->oldMouseX, this->oldMouseY );
			glm::vec3 curVec = calcArcBallVector( this->curMouseX, this->curMouseY );
			float angle = acos( std::min( 1.0f, glm::dot( oldVec, curVec ) ) );
			glm::vec3 cameraAxis = glm::cross( oldVec, curVec );
			glm::mat3 cameraToObjectCoords = glm::inverse( glm::mat3( this->view ) * glm::mat3( this->environment->getModel() ) );
			glm::vec3 cameraAxisObjectCoords = cameraToObjectCoords * cameraAxis;
			this->environment->setModel( glm::rotate( this->environment->getModel(), glm::degrees( angle ), cameraAxisObjectCoords ) );
			this->oldMouseX = this->curMouseX;
			this->oldMouseY = this->curMouseY;
		}
	}
}

/***************************************************************************************************
* calcArcBallVector function
*
* Placeholder.
***************************************************************************************************/
glm::vec3 Renderer::calcArcBallVector( int mouseX, int mouseY ) {
	// Calculate mouse coordinates in screen space
	glm::vec3 vec = glm::vec3( 1.0 * mouseX / this->windowWidth * 2 - 1.0, 1.0 * mouseY / this->windowHeight * 2 - 1.0, 0 );
	
	// Flip the y direction
	vec.y = -vec.y;
	
	// Calculate potential z value on the surface of the arc ball
	float distSquared = vec.x * vec.x + vec.y * vec.y;
	if ( distSquared <= 1.0 ) {
		vec.z = sqrt( 1.0f - distSquared );
	} else {
		vec = glm::normalize( vec );
	}

	return vec;
}

/***************************************************************************************************
* readData function
*
* Placeholder.
***************************************************************************************************/
void Renderer::readData( std::string fileName ) {
	std::ifstream in( fileName.c_str() );
	if ( !in ) {
		std::cerr << "Unable to open " << fileName << ".";
		return;
	}

	std::string line;
	while ( getline( in, line ) ) {
		std::istringstream s( line );
		glm::vec3 position;
		s >> position.x >> position.y >> position.z;
		this->environment->addDataPoint( position );
	}
}
