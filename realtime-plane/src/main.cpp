//! [starter]
#include "main_simulator.h"


int main(int argc, char **argv) {

	MainSimulator app;

	try {
		app.go();
	} catch (const std::exception& e) {
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
	}

	return 0;
}

//! [starter]
