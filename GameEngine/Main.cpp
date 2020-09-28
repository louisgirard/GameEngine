#include <iostream>
#include <cstdlib>
#include <Games/Header/GameSelection.hpp>
#include <Games/Header/GameBase.hpp>
#include <Games/Game1/Header/ShooterGame.hpp>

namespace std
{
#include <cstdlib>
};

int main(int argc, char** argv)
{
	Games::GameSelection::registerFactory<Games::Game1::ShooterGame>();

	bool engineRunning = true; 
	
	
	//Select a games and run it 
	while (engineRunning) {
		//Initialize here cause we need main arguments
		Games::GameBase::initializeGLUT(argc, argv);
		engineRunning = Games::GameSelection::selectAndRun();
		std::cout << "End Game " << std::endl << std::endl;
	}
}