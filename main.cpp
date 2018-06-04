#include "VehicleSystem.h"
#include "VMath.h"

using namespace sf;

int main()
{
	int windowWidth = 1280;
	int windowHeight = 720;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Flocking");

	VehicleSystem vs;

	float sep = 0;
	float ali = 0;
	float coh = 0;	

	while (window.isOpen()) {
		sep = 0;
		ali = 0;
		coh = 0;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					vs.addVehicle(Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
			}
			else if (event.type == Event::TextEntered) {
				if (Keyboard::isKeyPressed(Keyboard::Z)) {
					vs.removeVehicle();
				}

				else if (Keyboard::isKeyPressed(Keyboard::Q)) {
					sep+= 0.1f;  // add separation
				}

				else if (Keyboard::isKeyPressed(Keyboard::A)) {
					sep-= 0.1f;  // reduce separation
				}

				else if (Keyboard::isKeyPressed(Keyboard::W)) {
					ali+= 0.1f; // add cohesion
				}

				else if (Keyboard::isKeyPressed(Keyboard::S)) {
					ali-=0.1f;  // reduce cohesion
				}
				else if (Keyboard::isKeyPressed(Keyboard::E)) {
					coh+=0.1f;  // add align
				}
				else if (Keyboard::isKeyPressed(Keyboard::D)) {
					coh-=0.1f;  // reduce align
				}
			}
		}

		vs.UpdateWeights(sep, ali, coh);

		vs.update();

		window.clear();

		window.draw(vs);

		window.display();
		
	}


	return 0;
}