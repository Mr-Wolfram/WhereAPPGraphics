#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "modelEntity.h"
#include "light.h"
#include "application.hpp"
#include "skybox.h"

class Entity : public Application {
public:
	Entity();
	
	~Entity();
    
    void setup();

	void setModel(const char* filepath, GLuint _blendTextureID1, GLuint _blendTextureID2,
                  GLuint _blendTextureID3, GLuint _blendTextureID4,
                  GLuint _blendTextureID5, GLuint _blendTextureID6);

	void renderFrame() override;

    void move(glm::vec3 deltaPositon);
    void doScale(float s);
    
    GLint _skyboxTextureBoxID1;
    GLint _skyboxTextureBoxID2;
    GLint _skyboxTextureBoxID3;
    GLint _skyboxTextureBoxID4;
    GLint _skyboxTextureBoxID5;
    GLint _skyboxTextureBoxID6;
    
private:
	const float _cameraMoveSpeed = 10.0f;
	const float _cameraRotateSpeed = 0.02f;

	float _speed = 1.0;

	int _amount1 = 30;

	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 _planetPosition={0.0f, 0.0f, 0.0f};

	glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::quat _planetRotation={1.0f, 0.0f, 0.0f, 0.0f};

	glm::vec3 _scale = glm::vec3(1.5f, 1.5f, 1.5f);

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
	
	float _blend = 0.4f;

	// glm::quat _q1 = glm::angleAxis(0.0f, glm::vec3(0.0,1.0,0.0));
	// glm::quat _q2 = glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0));

    std::unique_ptr<DirectionalLight> _light;

    std::vector<std::shared_ptr<Camera>> _cameras;
	int activeCameraIndex = 0;
    
//    std::unique_ptr<SkyBox> _skybox;
	std::vector<std::shared_ptr<ModelEntity>> _models;
	std::unique_ptr<ModelEntity> _model;

	std::vector<std::shared_ptr<ModelEntity>> _elements;
	std::unique_ptr<ModelEntity> _element;

	std::unique_ptr<ModelEntity> _planet;

};
