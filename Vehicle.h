#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class Vehicle: public sf::Drawable, public sf::Transformable
{
private:
	ConvexShape triangle;
	Vector2f location;
	Vector2f velocity;
	Vector2f acceleration;
	float radius;
	float maxSpeed;
	float maxForce;
	float behaviorWeights[3];
	int windowWidth = 1280;
	int windowHeight = 720;

public:
	Vehicle(Vector2f loc);	
	void update();
	void applyForce(Vector2f force);
	Vector2f getPosition();
	Vector2f getVelocity();
	float getMaxForce();
	void setSpeed(float speed);
	void boarders();
	void UpdateBehaviors(std::vector<Vehicle*>* const vehicles);
	void UpdateWeights(float sep, float ali, float coh);
	Vector2f Seek(Vector2f vector);
	Vector2f Separate(std::vector<Vehicle*>* const vehicles);
	Vector2f Cohesion(std::vector<Vehicle*>* const vehicles);
	Vector2f Alignment(std::vector<Vehicle*>* const vehicles);

	virtual void draw(RenderTarget& target, RenderStates states) const;
};

