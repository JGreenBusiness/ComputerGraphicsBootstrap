#include "ComputerGraphicsApp.h"
#include "SolarSystem.h"

int main() {
	
	// allocation
	//auto app = new ComputerGraphicsApp();
	auto app = new SolarSystem();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}