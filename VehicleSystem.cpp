#include "VehicleSystem.h"
#include "VMath.h"


VehicleSystem::VehicleSystem()
{
	this->num = 0;
	behaviorWeights[0] = 0.0f;
	behaviorWeights[1] = 0.0f;
	behaviorWeights[2] = 0.0f;
	gridWidth = windowWidth / COL;
	gridHeight = windowHeight / ROW;
}


VehicleSystem::~VehicleSystem()
{
	vehicles.clear();
	{
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++) {
				grids[i][j].clear();
			}
	}
}

void VehicleSystem::update()
{
	for (auto vehicle : vehicles)
	{
		Vector2i currentBucket = getBucket(vehicle->getPosition());
		vehicle->update();
		Vector2i newBucket = getBucket(vehicle->getPosition());
		if (currentBucket != newBucket) {
			bucketRemove(currentBucket, vehicle);
			bucketAdd(newBucket, vehicle);
		}
		vehicle->UpdateBehaviors(&grids[newBucket.x][newBucket.y]);
	}
}

void VehicleSystem::addVehicle(Vector2f location)
{
	Vehicle *v = new Vehicle(location);
	vehicles.push_back(v);
	num++;
}

void VehicleSystem::removeVehicle()
{
	if (num <= 0) {
		return;
	}
	else
	{
		vehicles.pop_back();
		num--;
	}
}

void VehicleSystem::UpdateWeights(float sep, float ali, float coh) {
	behaviorWeights[0] += sep;
	behaviorWeights[1] += ali;
	behaviorWeights[2] += coh;

	for (auto boid : vehicles) {
		boid->UpdateWeights(behaviorWeights[0], behaviorWeights[1], behaviorWeights[2]);
	}
}

Vector2i VehicleSystem::getBucket(Vector2f position) {
	return Vector2i(position.x / gridWidth, position.y / gridHeight);
}

void VehicleSystem::bucketRemove(Vector2i bucket, Vehicle* v) {
	auto i = std::find(grids[bucket.x][bucket.y].begin(), grids[bucket.x][bucket.y].end(), v);
	if (i != grids[bucket.x][bucket.y].end()) {
		grids[bucket.x][bucket.y].erase(i);
	}
}

void VehicleSystem::bucketAdd(Vector2i bucket, Vehicle* v) {
	grids[bucket.x][bucket.y].push_back(v);
}

void VehicleSystem::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	for (auto v : vehicles)
	{
		target.draw(*v, states);
	}
}

