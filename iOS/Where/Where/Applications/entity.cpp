//#include <unordered_map>

#include "vertex.h"
#include "tiny_obj_loader/tiny_obj_loader.h"
#include "entity.h"
#include <math.h>
#include <iostream>

const float PI = acos(-1.0);

float step = 0.0f;

const float radius = 8.0f;
const float offset = 3.0f;

float angle1 = 0.0f;
float angle2 = 0.0f;

Entity::Entity() {
    std::cout << "hello\n";
}

Entity::~Entity() {
    std::cout << "bye\n";
    
}

void Entity::setup() {
    _light.reset(new DirectionalLight);

    _cameras.resize(2);
    
//    _skybox.reset(new SkyBox(_skyboxTextureBoxID1, _skyboxTextureBoxID2, _skyboxTextureBoxID3, _skyboxTextureBoxID4, _skyboxTextureBoxID5, _skyboxTextureBoxID6));

    const float aspect = 1.0f * windowWidth / windowHeight;
    constexpr float znear = 0.1f;
    constexpr float zfar = 10000.0f;

    // perspective camera
    _cameras[0] = std::make_shared<PerspectiveCamera>(
        glm::radians(60.0f), aspect, 0.1f, 10000.0f);
    _cameras[0]->position = glm::vec3(0.0f, 0.0f, 15.0f);

    // orthographic camera
    _cameras[1] = std::make_shared<OrthographicCamera>(
        -4.0f * aspect, 4.0f * aspect, -4.0f, 4.0f, znear, zfar);
    _cameras[1]->position = glm::vec3(0.0f, 0.0f, 15.0f);
}

void Entity::setModel(const char* _filepath, GLuint _blendTextureID1, GLuint _blendTextureID2, GLuint _blendTextureID3, GLuint _blendTextureID4,
                      GLuint _blendTextureID5, GLuint _blendTextureID6) {
    
    std::string filepath = std::string(_filepath);
    
	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
	int amount1 = _amount1;
	glm::vec3 position = _position;
	glm::quat rotation = _rotation;
	glm::vec3 scale = _scale;

	_models.resize(amount1);
	for(int i=0;i<amount1;i++){
		_models[i].reset(new ModelEntity(filepath, _blendTextureID1, _blendTextureID2));
	}

	_elements.resize(amount1);
	for(int i=0;i<amount1;i++){
		_elements[i].reset(new ModelEntity(filepath,_blendTextureID3,_blendTextureID4));
	}

	for (int i = 0; i < _amount1; ++i) {
		// translate
		float angle = (float)i / _amount1 * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		position.x = _position.x + sin(angle) * radius+displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;

		position.y = _position.y + cos(angle) * radius+displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		position.z = _position.z + sin(angle) * radius+displacement;

		// scale
		scale = glm::vec3(0.8,0.8,0.8);
		// rotate
		float rotAngle = 1.0f * (rand() % 360);
		rotation = glm::angleAxis(rotAngle, axis)* rotation;

		_elements[i]->setPosition(position);
		_elements[i]->setRotation(rotation);
		_elements[i]->setScale(scale);
	}

	_planet.reset(new ModelEntity(filepath,_blendTextureID5,_blendTextureID6));

	// glm::translate(glm::mat4(1.0f),_position)

}

void Entity::move(glm::vec3 deltaPositon) {
    std::shared_ptr<Camera> camera = _cameras[0];
    
    camera->position += deltaPositon * _cameraMoveSpeed;
}

void Entity::doScale(float s) {
    std::shared_ptr<Camera> camera = _cameras[0];
    
    camera->position += camera->getFront() * s * _cameraMoveSpeed;
}


void Entity::renderFrame() {

	const float angluarVelocity = 0.3f;
	const float angle = angluarVelocity * static_cast<float>(deltaTime);
	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection = _cameras[0]->getProjectionMatrix();
	glm::mat4 view = _cameras[0]->getViewMatrix();
	glm::vec3 viewPos = _cameras[0]->position;
    
    glm::vec3 boxPosition = glm::vec3(_cameras[0]->position.x,_cameras[0]->position.y,_cameras[0]->position.z-10);
    glm::mat4 boxModel = glm::translate(glm::mat4(1.0f), boxPosition);

//    _skybox->draw(projection, view, boxModel);

	step += deltaTime * _speed;

	_position = glm::vec3(sin(step),cos(step),sin(step));

	_models[0]->setPosition(_position);
	_models[0]->setScale(_scale);
	_models[0]->setRotation(_rotation);
	_models[0]->draw(projection, view, viewPos);

	_planet->setDirectionalLight(_direction1,_color1,_intensity1);
	_planet->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
	_planet->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);

	_planetPosition = glm::vec3(_cameras[0]->position.x+20,_cameras[0]->position.y+20,_cameras[0]->position.z-5000);

	_planetRotation = glm::angleAxis(angle, axis) * _planetRotation;
	_planet->setRotation(_planetRotation);
	_planet->setScale(glm::vec3(1000.0,1000.0,1000.0));
	_planet->setPosition(_planetPosition);
	_planet->draw(projection, view, viewPos);

	for (int i= 0;i<_amount1;i++){
		_models[i]->setDirectionalLight(_direction1,_color1,_intensity1);
		_models[i]->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
		_models[i]->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);

		_elements[i]->setDirectionalLight(_direction1,_color1,_intensity1);
		_elements[i]->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
		_elements[i]->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);

		// _position += glm::vec3(sin(step)*radius,cos(step)*radius,sin(step)*radius);
		// _elements[i]->setPosition(_position);
		_elements[i]->draw(projection, view, viewPos);
	}


}
