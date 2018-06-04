#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Vehicle.h"

class VehicleSystem: public sf::Drawable, public sf::Transformable
{
private:
	static const int COL = 10;
	static const int ROW = 10;
	int windowWidth = 1280;
	int windowHeight = 720;
	int gridWidth;
	int gridHeight;
	int num;
	float behaviorWeights[3];
	std::vector<Vehicle*> vehicles;
	std::vector<Vehicle*> grids[ROW][COL];
	
public:
	VehicleSystem();
	~VehicleSystem();
	void update();
	void addVehicle(Vector2f location);
	void removeVehicle();
	virtual void draw(RenderTarget& target, RenderStates states) const;
	void UpdateWeights(float sep, float ali, float coh);
	Vector2i getBucket(sf::Vector2f position);
	void bucketRemove(sf::Vector2i bucket, Vehicle* v);
	void bucketAdd(sf::Vector2i bucket, Vehicle* v);
};

