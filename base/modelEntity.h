#pragma once
#include <memory>
#include <string>

#include "application.h"
#include "model.h"
#include "light.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

// enum class RenderMode {
// 	Simple, Blend, Checker
// };

class ModelEntity {
public:
	
	ModelEntity();
	~ModelEntity();

	ModelEntity(const std::string& filepath,const std::string& blendTexturePaths1, const std::string& blendTexturePaths2);

	void setPosition(glm::vec3 position);
	void setScale(glm::vec3 scale); 
	void setRotation(glm::quat rotation);

	void setDirectionalLight(glm::vec3 direction,glm::vec3 color,float intensity);
	void setSpotLight(glm::vec3 position,glm::vec3 direction,glm::vec3 color,float intensity, float angle, float kc, float kl,float kq);
	void setMaterial(glm::vec3 albedo,float ka,glm::vec3 kd,glm::vec3 ks, float ns,float blend);

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();

	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);

private:
    std::unique_ptr<Model> _model;
	
	// std::unique_ptr<Shader> _simpleShader;

	std::unique_ptr<Shader> _blendShader;
	glm::vec3 _albedo = { 1.0f, 1.0f, 1.0f };
	float _ka = 0.03f;
	glm::vec3 _kd = { 1.0f, 1.0f, 1.0f };
	glm::vec3 _ks = { 1.0f, 1.0f, 1.0f };
	float _ns = 0.5f;
	float _blend = 0.5f;

	std::unique_ptr<Texture> _blendTextures[2];

	std::unique_ptr<Shader> _blurShader;

	std::unique_ptr<DirectionalLight> _light;
	std::unique_ptr<SpotLight> _spotLight;

	void initSimpleShader();

	void initBlendShader();

	void initCheckerShader();

	void initBlurShader();
};
