#include "entity.h"

int main() {
	try {
		Entity app;
		app.setModel("/Users/lion/CG/CG_Project4/data/sphere.obj",
		"/Users/lion/CG/CG_Project4/data/planetMap.png", "/Users/lion/CG/CG_Project4/data/planetMap.png",
		glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),glm::vec3(1.5f, 1.5f, 1.5f),1.0,
		30);
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