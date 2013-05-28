/*******************************************************************************
* Environment.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* Environment function
*
* Placeholder.
***************************************************************************************************/
Environment::Environment( Renderer* renderer ) {
	this->renderer = renderer;
	this->model = glm::mat4();
	this->light = new Light( this->renderer );
	this->focusObject = new FocusObject( this->renderer );
	this->focusObject->setColor( glm::vec3( 1.0f, 1.0f, 1.0f ) );

	for ( int i = 0; i < 8; i++ ) {
		this->cubes.push_back( new Cube( this->renderer ) );
	}

	this->cubes[ 0 ]->setPosition( glm::vec3( 10.0f, 10.0f, 10.0f ) );
	this->cubes[ 1 ]->setPosition( glm::vec3( 10.0f, 10.0f, -10.0f ) );
	this->cubes[ 2 ]->setPosition( glm::vec3( 10.0f, -10.0f, 10.0f ) );
	this->cubes[ 3 ]->setPosition( glm::vec3( 10.0f, -10.0f, -10.0f ) );
	this->cubes[ 4 ]->setPosition( glm::vec3( -10.0f, 10.0f, 10.0f ) );
	this->cubes[ 5 ]->setPosition( glm::vec3( -10.0f, 10.0f, -10.0f ) );
	this->cubes[ 6 ]->setPosition( glm::vec3( -10.0f, -10.0f, 10.0f ) );
	this->cubes[ 7 ]->setPosition( glm::vec3( -10.0f, -10.0f, -10.0f ) );

	this->cubes[ 0 ]->setColor( glm::vec3( 0.3f, 0.3f, 1.0f ) );
	this->cubes[ 1 ]->setColor( glm::vec3( 1.0f, 0.3f, 0.3f ) );
	this->cubes[ 2 ]->setColor( glm::vec3( 0.3f, 1.0f, 0.3f ) );
	this->cubes[ 3 ]->setColor( glm::vec3( 1.0f, 1.0f, 0.3f ) );
	this->cubes[ 4 ]->setColor( glm::vec3( 1.0f, 1.0f, 0.3f ) );
	this->cubes[ 5 ]->setColor( glm::vec3( 0.3f, 1.0f, 0.3f ) );
	this->cubes[ 6 ]->setColor( glm::vec3( 1.0f, 0.3f, 0.3f ) );
	this->cubes[ 7 ]->setColor( glm::vec3( 0.3f, 0.3f, 1.0f ) );
}

/***************************************************************************************************
* ~Puzzle function
*
* Placeholder.
***************************************************************************************************/
Environment::~Environment( void ) {
	for ( int i = 0; i < 8; i++ ) {
		delete this->cubes[ i ];
	}
	delete this->light;
}

/***************************************************************************************************
* addDataPoint function
*
* Placeholder.
***************************************************************************************************/
void Environment::addDataPoint( glm::vec3 position ) {
	DataPoint* dataPoint = new DataPoint( this->renderer );
	dataPoint->setPosition( position );
	dataPoint->setColor( glm::vec3( 1.0f, 1.0f, 1.0f ) );
	this->dataPoints.push_back( dataPoint );
}

/***************************************************************************************************
* setModel function
*
* Placeholder.
***************************************************************************************************/
void Environment::setModel( glm::mat4 model ) {
	this->model = model;
}

/***************************************************************************************************
* getModel function
*
* Placeholder.
***************************************************************************************************/
glm::mat4 Environment::getModel( void ) {
	return this->model;
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void Environment::update( void ) {
	this->light->update();
	for ( int i = 0; i < 8; i ++ ) {
		this->cubes[ i ]->update();
	}
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Environment::draw( void ) {
	if ( !this->renderer->hideCube ) {
		for ( int i = 0; i < 8; i ++ ) {
			this->cubes[ i ]->draw();
		}
	}
	this->focusObject->draw();
	for ( int i = 0; i < this->dataPoints.size(); i++ ) {
		this->dataPoints[ i ]->draw();
	}
}