#include <iostream>
#include <cstdlib>
#include <PhysicEngine/Header/Particle.h>
#include <Games/Header/GameSelection.h>
#include <Games/Game1/Header/ShooterGame.h>

namespace std
{
#include <cstdlib>
};

int main(int argc, const char* argv[])
{
	Games::GameSelection::registerFactory<Games::Game1::ShooterGame>();

	bool engineRunning = true;

	//Select a games and run it 
	while (engineRunning) {
		engineRunning = Games::GameSelection::selectAndRun();
		std::cout << "End Game " << std::endl << std::endl;
	}
}