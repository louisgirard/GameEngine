#include <iostream>
#include <cstdlib>

#include <Games/Header/GameSelection.hpp>
#include <Games/Header/GameBase.hpp>
#include <Games/Game1/Header/ShooterGame.hpp>
#include <Games/Game2/Header/BlobGame.hpp>
#include <Games/Demo/Header/Demo.hpp>

namespace std
{
#include <cstdlib>
};

int main(int p_argc, char** p_argv)
{
	Games::GameSelection::registerFactory<Games::Demo>("Demo", "Graphic engine demo.");
	Games::GameSelection::registerFactory<Games::Game1::ShooterGame>("Game 1", "Jeu qui presente le premier tp.");
	Games::GameSelection::registerFactory<Games::Game2::Blob>();

	bool engineRunning = true; 
	
	
	//Select a games and run it 
	while (engineRunning) {
		//Initialize here cause we need main arguments
		Games::GameBase::initializeGLUT(p_argc, p_argv);
		engineRunning = Games::GameSelection::selectAndRun();
		std::cout << "End Game " << std::endl << std::endl;
	}
}