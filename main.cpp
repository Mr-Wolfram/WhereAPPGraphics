#include "entity.h"

int main() {
	try {
		Entity app;
		app.setModel("data/sphere.obj",
		"data/planetMap.png", "data/planetMap.png",
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