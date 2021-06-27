#pragma once

#include "../base/application.h"
#include "../base/camera.h"
#include "../base/model.h"

enum class RenderMode {
	Ordinary, Instanced
};

class InstancedRendering : public Application {
public:
	InstancedRendering();

	~InstancedRendering();
	
	void handleInput() override;
	
	void renderFrame() override;

private:
	const float _cameraMoveSpeed = 10.0f;
	const float _cameraRotateSpeed = 0.05f;

	PerspectiveCamera _camera = {
		glm::radians(45.0f),
		1.0f * _windowWidth / _windowHeight,
		0.1f, 10000.0f
	};

	std::unique_ptr<Model> _planet;
	std::unique_ptr<Model> _asternoid;

	std::unique_ptr<Shader> _planetShader;
	std::unique_ptr<Shader> _asternoidShader;
	std::unique_ptr<Shader> _asternoidInstancedShader;

	GLuint _instanceBuffer = {};

	int _amount = 50000;
	std::vector<glm::mat4> _modelMatrices;

	enum RenderMode _renderMode = RenderMode::Ordinary;
};