#pragma once

#include <memory>
#include <vector>

#include "base/camera.h"
#include "base/skybox.h"
#include "base/modelEntity.h"
#include "base/ElementEntity.h"
#include "base/light.h"
#include "base/application.h"

class Entity : public Application {
public:
	Entity();
	
	~Entity();

	void setModel(const std::string& filepath,
	const std::string& blendTexturePaths5, const std::string& blendTexturePaths6,
	glm::vec3 position,glm::quat rotation,glm::vec3 scale,float speed,
	int amount1);

	void setElement();

	void handleInput() override;

	void renderFrame() override;

	
private:
	const float _cameraMoveSpeed = 0.5f;
	const float _cameraRotateSpeed = 0.02f;

	float _speed;

	int _amount1;

	glm::vec3 _position;

	glm::vec3 _planetPosition={0.0f, 0.0f, 0.0f};

	std::vector<glm::vec3> _elementPositions;

	glm::quat _rotation;

	glm::quat _planetRotation={1.0f, 0.0f, 0.0f, 0.0f};

	std::vector<glm::quat> _elementRotations;

	glm::vec3 _scale;

	std::vector<glm::vec3> _elementScales;

	glm::vec3 _direction1 = { 0.0f, 0.0f, -1.0f };
	
	glm::vec3 _color1 = { 0.38f, 0.0f, 0.0f };
	
	float _intensity1 = 1.0f;

	glm::vec3 _lightPosition = { 0.0f, 0.0f, 5.0f };
	
	glm::vec3 _direction = { 0.0f, 0.0f, -1.0f };
	
	glm::vec3 _color = { 1.0f, 0.0f, 0.0f };
	
	float _intensity = 1.4f;
	
	float _angle = glm::radians(60.0f);
	
	float _kc = 1.0f;
	
	float _kl = 0.0f;
	
	float _kq = 0.2f;

	glm::vec3 _albedo = { 1.0f, 0.92f, 0.92f };
	
	float _ka = 1.0f;
	
	glm::vec3 _kd = { 1.0f, 0.97f, 0.0f };
	
	glm::vec3 _ks = { 1.0f, 0.44f, 0.0f };
	
	float _ns = 25.0f;
	
	float _blend = 0.3f;

	// glm::quat _q1 = glm::angleAxis(0.0f, glm::vec3(0.0,1.0,0.0));
	// glm::quat _q2 = glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0));

    std::unique_ptr<DirectionalLight> _light;

    std::vector<std::shared_ptr<Camera>> _cameras;
	int activeCameraIndex = 0;

	std::vector<std::shared_ptr<ModelEntity>> _models;
	// std::vector<std::shared_ptr<ModelEntity>> _models2;
	// std::vector<std::shared_ptr<ModelEntity>> _models3;
	// std::unique_ptr<ModelEntity> _model;

	std::shared_ptr<ModelEntity> _body;

	std::vector<std::shared_ptr<Ball>> _balls;
	std::vector<std::shared_ptr<Ellipsoid>> _ellipsoids;
	std::vector<std::shared_ptr<Cubic>> _cubics;
	std::vector<std::shared_ptr<Cylinder>> _cylinders;
	std::vector<std::shared_ptr<Cone>> _cones;
	std::vector<std::shared_ptr<Prism>> _prisms;

	// std::unique_ptr<ModelEntity> _element;

	std::unique_ptr<SkyBox> _skybox;

	std::vector<std::unique_ptr<ModelEntity>> _planets;

};