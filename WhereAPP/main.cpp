#include "texture_mapping.h"

int main() {
	try {
		TextureMapping app;
		app.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown Error" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}