#include "render_flag.h"

RenderFlag::RenderFlag() {
	_windowTitle = "Render Flag";

	_flag = new Flag;
	// create 5 stars
	// write your code here
	// _stars[i] = new Star(ndc_position, rotation_in_radians, size_of_star, aspect_of_the_window);
	// hint: aspect_of_the_window = _windowWidth / _windowHeight
}

RenderFlag::~RenderFlag() {
	if (_flag) {
		delete _flag;
		_flag = nullptr;
	}

	for (int i = 0; i < 5; ++i) {
		delete _stars[i];
		_stars[i] = nullptr;
	}
}

void RenderFlag::handleInput() {
	// do nothing
}

void RenderFlag::renderFrame() {
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	_flag->render();
	for (int i = 0; i < 1; ++i) {
		if (_stars[i] != nullptr) {
			_stars[i]->render();
		}
	}
}