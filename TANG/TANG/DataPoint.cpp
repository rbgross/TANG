/*******************************************************************************
* DataPoint.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* DataPoint function
*
* Placeholder.
***************************************************************************************************/
DataPoint::DataPoint( Renderer* renderer ) {
	this->renderer = renderer;
	this->mesh = new Mesh( "C:\\Users\\Ryan\\Game Tests\\SphereTest.obj" );
	this->position = glm::vec3();
	this->color = glm::vec3();
}

/***************************************************************************************************
* ~DataPoint function
*
* Placeholder.
***************************************************************************************************/
DataPoint::~DataPoint( void ) {
	delete this->mesh;
}

/***************************************************************************************************
* setPosition function
*
* Placeholder.
***************************************************************************************************/
void DataPoint::setPosition( glm::vec3 position ) {
	this->position = position;
}

/***************************************************************************************************
* setColor function
*
* Placeholder.
***************************************************************************************************/
void DataPoint::setColor( glm::vec3 color ) {
	this->color = color;
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void DataPoint::update( void ) {
	
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void DataPoint::draw( void ) {
	// Calculate and apply the cube model transformation
	glm::mat4 model = glm::translate( this->renderer->environment->getModel(), this->position );
	model = glm::scale( model, glm::vec3( 0.05f, 0.05f, 0.05f ) );
	this->renderer->setModel( model );
	this->renderer->setDiffCol( this->color );
	this->mesh->draw();
}