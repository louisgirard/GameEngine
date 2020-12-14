#include <iostream>
#include <cstdlib>

#include <Games/Header/GameSelection.hpp>
#include <Games/Header/GameBase.hpp>
#include <Games/Game1/Header/ShooterGame.hpp>
#include <Games/Game2/Header/BlobGame.hpp>
#include <Games/Game3/Header/TestMath.hpp>
#include <Games/Demo/Header/Demo.hpp>
#include <Games/Game3/Header/RigidBodyDemo.hpp>
#include <Games/Game3/Header/CarDemo.hpp>
#include <Games/Game4/Header/CollisionDemo.hpp>

namespace std
{
#include <cstdlib>
};

int main(int p_argc, char** p_argv)
{
	//Games::GameSelection::registerFactory<Games::SimpleTestGraphic>("Test graphic");
	Games::GameSelection::registerFactory<Games::Demo>("Demo", "Graphic engine demo.");
	Games::GameSelection::registerFactory<Games::Game1::ShooterGame>("Game 1", "Jeu qui presente le premier tp.");
	Games::GameSelection::registerFactory<Games::Game2::Blob>("Game 2", "Jeu qui presente le deuxieme tp.");
	Games::GameSelection::registerFactory<Games::Game3::RigidBodyDemo>("Demo 1 TP3");
	Games::GameSelection::registerFactory<Games::Game3::CarDemo>("Demo 2 TP3");
	Games::GameSelection::registerFactory<Games::Game4::CollisionDemo>("Game 4", "Jeu qui presente le quatrieme tp.");
	//Games::GameSelection::registerFactory<Games::Game3::TestMath>("Test Math", "Test math component");

	bool engineRunning = true;

	//Select a games and run it 
	while (engineRunning) {
		//Initialize here cause we need main arguments
		Games::GameBase::initializeGLUT(p_argc, p_argv);
		engineRunning = Games::GameSelection::selectAndRun();
		std::cout << "End Game " << std::endl << std::endl;
	}
}