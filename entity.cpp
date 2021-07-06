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

const float radius = 15.0f;
const float offset = 10.0f;

float angle1 = 0.0f;
float angle2 = 0.0f;

int count = 0;

int elementSet = 1 ;

const std::vector<std::string> skyboxTexturePaths = {
	"/Users/lion/CG/CG_Project4/data/skybox/right.jpg",
	"/Users/lion/CG/CG_Project4/data/skybox/left.jpg",
	"/Users/lion/CG/CG_Project4/data/skybox/top.jpg",
	"/Users/lion/CG/CG_Project4/data/skybox/bottom.jpg",
	"/Users/lion/CG/CG_Project4/data/skybox/front.jpg",
	"/Users/lion/CG/CG_Project4/data/skybox/back.jpg"
};

Entity::Entity() {
    _light.reset(new DirectionalLight);

	_cameras.resize(2);

	_skybox.reset(new SkyBox(skyboxTexturePaths));

	_models.resize(51);

	_body.reset(new ModelEntity("/Users/lion/CG/CG_Project4/data/sphere.obj","/Users/lion/CG/CG_Project4/data/eye.png","/Users/lion/CG/CG_Project4/data/bodyMap.png"));

	for (int i =0;i<51;i++){
		std::string OBJpath;
		if(i<10){
			OBJpath = "/Users/lion/CG/CG_Project4/data/OBJ/untitled_00000"+std::to_string(i)+".obj";
		}else{
			OBJpath = "/Users/lion/CG/CG_Project4/data/OBJ/untitled_0000"+std::to_string(i)+".obj";
		}
		_models[i].reset(new ModelEntity(OBJpath,"/Users/lion/CG/CG_Project4/data/eye.png","/Users/lion/CG/CG_Project4/data/bodyMap.png"));
	}

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

void Entity::setModel(const std::string& filepath,
	const std::string& blendTexturePaths5, const std::string& blendTexturePaths6,
	glm::vec3 position,glm::quat rotation,glm::vec3 scale,float speed,
	int amount1) {  

	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);	
	_amount1=amount1;
	_speed = speed;
	_position = position;
	_rotation = rotation;
	_scale = scale;

	_ellipsoids.resize(amount1);
	_cubics.resize(amount1);
	_cylinders.resize(amount1);
	_cones.resize(amount1);
	_prisms.resize(amount1);
	_balls.resize(amount1);

	_planets.resize(3);

	_elementPositions.resize(amount1);
	_elementRotations.resize(amount1);
	_elementScales.resize(amount1);

	for (int i = 0; i < 3; ++i) {
	_planets[i].reset(new ModelEntity(filepath,blendTexturePaths5,blendTexturePaths6));
	}

	for (int i = 0; i < _amount1; ++i) {

		_balls[i].reset(new Ball(0.05f));
		_cubics[i].reset(new Cubic(1.0f));
		_ellipsoids[i].reset(new Ellipsoid(0.3f, 1.0f, 2.0f));
		_cylinders[i].reset(new Cylinder(0.5f,0.6f));
		_cones[i].reset(new Cone(1.0f,1.6f));
		_prisms[i].reset(new Prism(1.5f,0.6f,6));

		float angle = (float)i / _amount1 * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		_elementPositions[i].x = _position.x+sin(angle) * radius+displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		
		_elementPositions[i].y = displacement * 0.2f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		_elementPositions[i].z = _position.z+sin(angle) * radius+displacement;
		
		// scale
		_elementScales[i] = glm::vec3(1.0f, 1.0f, 1.0f);
		// rotate
		float rotAngle = 1.0f * (rand() % 360);
		_elementRotations[i] = glm::angleAxis(rotAngle, axis)* rotation;
	}

	// glm::translate(glm::mat4(1.0f),_position)

}


void Entity::handleInput() {

	std::shared_ptr<Camera> camera = _cameras[0];

	if (_keyboardInput.keyStates[GLFW_KEY_1] != GLFW_RELEASE){
		elementSet = 1;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_2] != GLFW_RELEASE){
		elementSet = 2;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_3] != GLFW_RELEASE){
		elementSet = 3;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_4] != GLFW_RELEASE){
		elementSet = 4;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_5] != GLFW_RELEASE){
		elementSet = 5;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_6] != GLFW_RELEASE){
		elementSet = 6;
	}

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
		if (_mouseInput.click.left == true){
		std::cout << "mouse move in x direction" << std::endl;
		// rotate around world up: glm::vec3(0.0f, 1.0f, 0.0f)
		const float angle = -_cameraRotateSpeed * _deltaTime * (_mouseInput.move.xCurrent - _mouseInput.move.xOld);
		const glm::vec3 axis1 = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 axis2 = camera->getRight();
		/* write your code here */
		// you should know how quaternion works to represent rotation
		angle1 -= angle;
		camera->rotation = { glm::cos(angle * 0.5f),axis2[0] * glm::sin(angle2*0.5f) , axis1[1] * glm::sin(angle1*0.5f)+ axis2[1] * glm::sin(angle1* 0.5f), 0.0f };
		}

		_mouseInput.move.xOld = _mouseInput.move.xCurrent;
	}

	if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
		if (_mouseInput.click.left == true){
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
		}
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

	glm::vec3 boxPosition = glm::vec3(_cameras[0]->position.x,_cameras[0]->position.y,_cameras[0]->position.z-10);
	glm::mat4 boxModel = glm::translate(glm::mat4(1.0f), boxPosition);

	_skybox->draw(projection, view, boxModel);

	step += _deltaTime * _speed;


	_position = glm::vec3(sin(step),cos(step),sin(step));
	_body->setDirectionalLight(_direction1,_color1,_intensity1);
	_body->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
	_body->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
	_body->setPosition(_position);
	_body->draw(projection, view, viewPos);

	_position = glm::vec3(sin(step)*5,cos(step)*5,sin(step)*5);

	_models[count]->setDirectionalLight(_direction1,_color1,_intensity1);
	_models[count]->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
	_models[count]->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);

	_models[count]->setPosition(_position);
	_models[count]->setRotation(_rotation);
	_models[count]->draw(projection, view, viewPos);

	if(count==50){
		count=0;
	}else{count++;}

	for (int i= 0;i<3;i++){
		const glm::vec3 axis1 = glm::vec3(1.0f, 0.0f, 0.0f);	
		_elementRotations[i] *= glm::angleAxis(angle, axis1);

		_planets[i]->setDirectionalLight(_direction1,_color1,_intensity1);
		_planets[i]->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
		_planets[i]->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);


		_planetPosition = glm::vec3(_cameras[0]->position.x+200,_cameras[0]->position.y+200,_cameras[0]->position.z-1000);
		_planets[i]->setRotation(_elementRotations[i]);
		_planets[i]->setScale(glm::vec3(400.0,400.0,400.0));
		_planets[i]->setPosition(_planetPosition);
		_planets[i]->draw(projection, view, viewPos);
	}

	for (int i= 0;i<_amount1;i++){

		const glm::vec3 axis2 = glm::vec3(1.0f, 0.0f, 0.0f);	
		_elementRotations[i] *= glm::angleAxis(angle, axis2);

		if(elementSet == 1){
		
		_balls[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_balls[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_balls[i].get()->setRotation(_elementRotations[i]); 
		_balls[i].get()->setScale(_elementScales[i]); 
		_balls[i].get()->draw(projection, view, viewPos);
		}

		if(elementSet == 2){
		
		_ellipsoids[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_ellipsoids[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_ellipsoids[i].get()->setRotation(_elementRotations[i]); 
		_ellipsoids[i].get()->setScale(_elementScales[i]); 
		_ellipsoids[i].get()->draw(projection, view, viewPos);
		
		}

		if(elementSet == 3){
		
		_cubics[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_cubics[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_cubics[i].get()->setRotation(_elementRotations[i]); 
		_cubics[i].get()->setScale(_elementScales[i]); 
		_cubics[i].get()->draw(projection, view, viewPos);
		}

		if(elementSet == 4){
		
		_cylinders[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_cylinders[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_cylinders[i].get()->setRotation(_elementRotations[i]); 
		_cylinders[i].get()->setScale(_elementScales[i]); 
		_cylinders[i].get()->draw(projection, view, viewPos);
		}

		if(elementSet == 5){
		_prisms[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_prisms[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_prisms[i].get()->setRotation(_elementRotations[i]); 
		_prisms[i].get()->setScale(_elementScales[i]); 
		_prisms[i].get()->draw(projection, view, viewPos);
		}	

		if(elementSet == 6){
		_cones[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		_cones[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_cones[i].get()->setRotation(_elementRotations[i]); 
		_cones[i].get()->setScale(_elementScales[i]); 
		_cones[i].get()->draw(projection, view, viewPos);
		}	
	}

	// _ball.get()->draw(projection, view, viewPos);

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