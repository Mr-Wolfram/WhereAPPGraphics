#pragma once

#include <memory>
#include <string>

#include "../base/application.h"
#include "../base/model.h"
#include "../base/light.h"
#include "../base/shader.h"
#include "../base/texture.h"
#include "../base/camera.h"
#include "../base/skybox.h"

enum class RenderMode {
	Simple, Blend, Checker
};

class TextureMapping : public Application {
public:
	TextureMapping();
	
	~TextureMapping();

private:
	std::unique_ptr<Model> _sphere;

	enum RenderMode _renderMode = RenderMode::Simple;

	std::unique_ptr<Shader> _simpleShader;

	std::unique_ptr<Shader> _blendShader;
	glm::vec3 _albedo = { 1.0f, 1.0f, 1.0f };
	float _ka = 0.03f;
	glm::vec3 _kd = { 1.0f, 1.0f, 1.0f };
	float _blend = 1.0f;
	std::unique_ptr<Texture> _blendTextures[2];
	
	std::unique_ptr<Shader> _checkerShader;
	int _repeat = 10;
	glm::vec3 _checkerColors[2] = {
		{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
	};

	std::unique_ptr<SkyBox> _skybox;

	std::unique_ptr<PerspectiveCamera> _camera;

	std::unique_ptr<DirectionalLight> _light;

	void initSimpleShader();

	void initBlendShader();

	void initCheckerShader();

	void handleInput() override;

	void renderFrame() override;
};