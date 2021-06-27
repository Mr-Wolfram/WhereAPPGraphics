#pragma once

#include <memory>
#include <string>

#include <imgui.h>

#include "../base/application.h"
#include "../base/shader.h"
#include "../base/model.h"
#include "../base/light.h"
#include "../base/camera.h"

enum class RenderMode {
	Ambient, Lambert, Phong
};

class ShadingTutorial : public Application {
public:
	ShadingTutorial();

	~ShadingTutorial();

private:
	// model
	std::unique_ptr<Model> _bunny;

	// shaders
	std::unique_ptr<Shader> _ambientShader;
	std::unique_ptr<Shader> _lambertShader;
	std::unique_ptr<Shader> _phongShader;

	// lights
	std::unique_ptr<DirectionalLight> _directionalLight;
	std::unique_ptr<SpotLight> _spotLight;

	// camera
	std::unique_ptr<PerspectiveCamera> _camera;

	// material coefficients
	// for ambient color calculation
	glm::vec3 _albedo = { 1.0f, 1.0f, 1.0f };
	float _ka = 0.03f;

	// for diffuse color calculation
	glm::vec3 _kd = { 1.0f, 1.0f, 1.0f };

	// for specular color calculation
	glm::vec3 _ks = { 1.0f, 1.0f, 1.0f };
	float _ns = 10.0f;

	RenderMode _renderMode = RenderMode::Ambient;

	// I = ka * albedo
	void initFlatShader();

	// I = ka * albedo + kd * max(cos<I, n>, 0)
	void initLambertShader();

	// I = ka * albedo + kd * cos<I, n> + ks * (max(cos<R, V>, 0) ^ ns)
	void initPhongShader();

	void handleInput() override;

	void renderFrame() override;
};