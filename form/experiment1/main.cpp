#include <iostream>
#include <cstdlib>
#include "render_flag.h"

int main() {
	try {
		RenderFlag app;
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}