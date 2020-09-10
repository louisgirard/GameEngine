#include <iostream>
#include "Particle.h"

int main(int argc, const char* argv[])
{
	Particle p1;
	p1.setMass(10);
	p1.setPosition(100, 10, 50);
	p1.setVelocity(0, 0, 0);
	p1.setDamping(0.999);
	p1.setAcceleration(0, -10, 0);
	while (true) {
		p1.integrate(60);
		std::cout << "x = " << p1.getPosition().x << ", y = " << p1.getPosition().y << ", z = " << p1.getPosition().z << std::endl;
	}
}