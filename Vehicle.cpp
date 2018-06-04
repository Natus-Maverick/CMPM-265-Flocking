#include "Vehicle.h"
#include "VMath.h"


Vehicle::Vehicle(Vector2f location)
{
	this->acceleration = Vector2f(0, 0);
	this->velocity = Vector2f((std::rand() % 200 - 100) * 0.01f, (std::rand() % 200 - 100) * 0.01f);
	this->location = location;
	this->radius = 10;
	this->maxSpeed = 0.05f;
	this->maxForce = 0.1f;
	behaviorWeights[0] = 0.0f;
	behaviorWeights[1] = 0.0f;
	behaviorWeights[2] = 0.0f;
	
	triangle.setPointCount(3);
	triangle.setPoint(0, Vector2f(radius, 0));
	triangle.setPoint(1, Vector2f(radius * 0.5f, radius * 1.866f));
	triangle.setPoint(2, Vector2f(radius * 1.5f, radius * 1.866f));
	triangle.setFillColor(Color::Color(102, 204, 255, 100));
	triangle.setOrigin(radius, radius);
	triangle.setPosition(location);
}


void Vehicle::update()
{
	boarders();
	velocity += acceleration;
	VMath::Limit(velocity, maxSpeed);
	location += velocity;
	acceleration = acceleration * 0.0f;
	triangle.setPosition(location);
	triangle.setRotation(VMath::Rot(velocity));
}

void Vehicle::boarders() {
	sf::Vector2f desired = sf::Vector2f(0, 0);

	if (location.x < 25.f) {
		desired = Vector2f(maxSpeed, velocity.y);
	}
	else if (location.x > windowWidth - 25.f) {
		desired = Vector2f(-maxSpeed, velocity.y);
	}
	if (location.y < 25.f) {
		desired = Vector2f(velocity.x, maxSpeed);
	}
	else if (location.y > windowHeight - 25.f) {
		desired = Vector2f(velocity.x, -maxSpeed);
	}

	if (desired != Vector2f(0, 0)) {
		Vector2f steer = desired - velocity;		
		VMath::Limit(steer, maxForce);
		applyForce(steer);
	}
}

void Vehicle::applyForce(Vector2f force)
{
	acceleration += force;
}

void Vehicle::setSpeed(float speed) {
	maxSpeed = speed;
}

Vector2f Vehicle::getPosition()
{
	return location;
}
Vector2f Vehicle::getVelocity()
{
	return velocity;
}

float Vehicle::getMaxForce()
{
	return maxForce;
}

void Vehicle::UpdateBehaviors(std::vector<Vehicle*>* const vehicles)
{
	Vector2f s = Separate(vehicles);
	Vector2f a = Alignment(vehicles);
	Vector2f c = Cohesion(vehicles);
	s *= behaviorWeights[0];
	a *= behaviorWeights[1];
	c *= behaviorWeights[2];
	applyForce(s);
	applyForce(a);
	applyForce(c);
}

Vector2f Vehicle::Seek(Vector2f target)
{
	Vector2f desired = target - location;
	//float distanceX = VMath::Mag(desired);
	desired = VMath::Nor(desired);
	desired *= maxSpeed;
	/*if (distanceX < 100.0f)
	{
		desired *= VMath::Map(distanceX, Vector2f(0, 0), Vector2f(100.0f, maxSpeed));
	}
	else {
		desired *= maxSpeed;
	}*/

	Vector2f steer = desired - velocity;
	VMath::Limit(steer, maxForce);
	return steer;
}
Vector2f Vehicle::Separate(std::vector<Vehicle*>* const vehicles)
{
	float desiredseparation = radius * 3;
	Vector2f sum = Vector2f(0, 0);
	int num = 0;
	for (auto *other : *vehicles)
	{
		float d = VMath::Mag(this->location - other->location);
		if ((d > 0) && (d < desiredseparation))
		{
			Vector2f diff = VMath::Nor(this->location - other->location);
			diff /= d;
			sum += diff;
			num++;
		}
	}
	if (num > 0) {
		sum /= num * 1.0f;
	}
	if (VMath::Mag(sum) > 0)
	{
		sum = VMath::Nor(sum);
		sum *= maxSpeed;
		sum -= velocity;
		VMath::Limit(sum, maxForce);
	}
	return sum;
}
Vector2f Vehicle::Alignment(std::vector<Vehicle*>* const vehicles)
{
	float neighbordist = 50.0f;
	Vector2f sum = Vector2f(0, 0);
	int num = 0;
	for (auto other : *vehicles) {
		float d = VMath::Mag(this->location - other->location);
		if ((d > 0) && (d < neighbordist)) {
			sum += other->velocity;
			num++;
		}
	}
	if (num > 0) {
		sum /= num * 1.0f;
		sum = VMath::Nor(sum);
		sum *= maxSpeed;
		Vector2f steer = sum - velocity;
		VMath::Limit(steer, maxForce);
		return steer;
	}
	else {
		return Vector2f(0, 0);
	}
}
Vector2f Vehicle::Cohesion(std::vector<Vehicle*>* const vehicles)
{
	float neighbordist = 10.0f;
	Vector2f sum = Vector2f(0, 0);
	int num = 0;
	for (auto *other : *vehicles) {
		float d = VMath::Mag(this->location - other->location);
		if ((d > 0) && (d < neighbordist)) {
			sum += other->location;
			num++;
		}
	}
	if (num > 0) {
		sum /= num  * 1.0f;
		return Seek(sum);
	}
	else {
		return Vector2f(0, 0);
	}
}

void Vehicle::UpdateWeights(float sep, float ali, float coh)
{
	behaviorWeights[0] = sep;
	behaviorWeights[1] = ali;
	behaviorWeights[2] = coh;
}

void Vehicle::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(triangle, states);
}