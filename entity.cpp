#include <unordered_map>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "base/vertex.h"
#include "tiny_obj_loader/tiny_obj_loader.h"
#include "entity.h"
#include <math.h>

const float PI = acos(-1.0);

float step = 0.0f;

const float radius = 5.0f;
const float offset = 2.0f;

float angle1 = 0.0f;
float angle2 = 0.0f;

Entity::Entity() {
    _light.reset(new DirectionalLight);

	_cameras.resize(2);

	const float aspect = 1.0f * _windowWidth / _windowHeight;
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

	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();
}

Entity::~Entity() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    
}

void Entity::setModel(const std::string& filepath,const std::string& blendTexturePaths1, const std::string& blendTexturePaths2,
	const std::string& blendTexturePaths3, const std::string& blendTexturePaths4,
	const std::string& blendTexturePaths5, const std::string& blendTexturePaths6,
	glm::vec3 position,glm::quat rotation,glm::vec3 scale,float speed,
	int amount1) {  

	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);	
	_amount1=amount1;
	_speed = speed;
	_position = position;
	_rotation = rotation;
	_scale = scale;
	 
	_models.resize(amount1);
	for(int i=0;i<amount1;i++){	
		_models[i].reset(new ModelEntity(filepath,blendTexturePaths1,blendTexturePaths2));
	}

	_elements.resize(amount1);
	for(int i=0;i<amount1;i++){	
		_elements[i].reset(new ModelEntity(filepath,blendTexturePaths3,blendTexturePaths4));
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

	_planet.reset(new ModelEntity(filepath,blendTexturePaths5,blendTexturePaths6));

	// glm::translate(glm::mat4(1.0f),_position)

}

void Entity::handleInput() {

	std::shared_ptr<Camera> camera = _cameras[0];

	if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		std::cout << "W" << std::endl;
		/* write your code here */
		// move front
		camera->position += camera->getFront()*_cameraMoveSpeed;
		
	}

	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		std::cout << "A" << std::endl;
		/* write your code here */
		// move left
		camera->position -= glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * _cameraRotateSpeed*3.0;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		std::cout << "S" << std::endl;
		/* write your code here */
		// move back
		camera->position -= camera->getFront()*_cameraMoveSpeed;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		std::cout << "D" << std::endl;
		
		/* write your code here */
		// move right
		camera->position += glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * _cameraRotateSpeed*3.0;
	}

	if (_mouseInput.move.xCurrent != _mouseInput.move.xOld) {
		std::cout << "mouse move in x direction" << std::endl;
		// rotate around world up: glm::vec3(0.0f, 1.0f, 0.0f)
		const float angle = -_cameraRotateSpeed * _deltaTime * (_mouseInput.move.xCurrent - _mouseInput.move.xOld);
		const glm::vec3 axis1 = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 axis2 = camera->getRight();
		/* write your code here */
		// you should know how quaternion works to represent rotation
		angle1 -= angle;
		camera->rotation = { glm::cos(angle * 0.5f),axis2[0] * glm::sin(angle2*0.5f) , axis1[1] * glm::sin(angle1*0.5f)+ axis2[1] * glm::sin(angle1* 0.5f), 0.0f };
		

		_mouseInput.move.xOld = _mouseInput.move.xCurrent;
	}

	if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
		std::cout << "mouse move in y direction" << std::endl;
		/* write your code here */
		// rotate around local right
		const float angle = -_cameraRotateSpeed * _deltaTime * (_mouseInput.move.yCurrent - _mouseInput.move.yOld);
		const glm::vec3 axis1 = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 axis2 = camera->getRight();
		// you should know how quaternion works to represent rotation
		// camera->rotation = ...
		angle2 -= angle;
		camera->rotation = { glm::cos(angle * 0.5f),axis2[0] * glm::sin(angle2*0.5f) , axis1[1] * glm::sin(angle1*0.5f) + axis2[1] * glm::sin(angle1* 0.5f), 0.0f };


		_mouseInput.move.yOld = _mouseInput.move.yCurrent;
	}
}

void Entity::renderFrame() {

	const float angluarVelocity = 0.3f;
	const float angle = angluarVelocity * static_cast<float>(_deltaTime);
	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);	

	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection = _cameras[0]->getProjectionMatrix();
	glm::mat4 view = _cameras[0]->getViewMatrix();
	glm::vec3 viewPos = _cameras[0]->position;

	step += _deltaTime * _speed;

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
	_planet->setScale(glm::vec3(2000.0,2000.0,2000.0));
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

	// draw ui elements
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (!ImGui::Begin("Control Panel", nullptr, flags)) {
		ImGui::End();
	} else {
		ImGui::Text("Render Mode");

		ImGui::Text("directional light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##1", &_intensity1, 0.0f, 2.0f);
		ImGui::ColorEdit3("color##1", (float*)&_color1);
		ImGui::NewLine();

		ImGui::Text("spot light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##2", &_intensity, 0.0f, 5.0f);
		ImGui::ColorEdit3("color##2", (float*)&_color);
		ImGui::SliderFloat("angle##2", (float*)&_angle, 0.0f, glm::radians(180.0f), "%f rad");
		ImGui::NewLine();

		ImGui::Text("Material");
		ImGui::Separator();
		ImGui::ColorEdit3("albedo", (float*)&_albedo);
		ImGui::SliderFloat("ka", &_ka, 0.0f, 1.0f);
		ImGui::ColorEdit3("kd", (float*)&_kd);
		ImGui::ColorEdit3("ks", (float*)&_ks);
		ImGui::SliderFloat("ns", &_ns, 0.0f, 50.0f);
		ImGui::SliderFloat("blend", &_blend, 0.0f, 1.0f);

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}