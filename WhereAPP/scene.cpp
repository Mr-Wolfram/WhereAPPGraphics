#include <unordered_map>

#include <tiny_obj_loader.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "scene.h"

const std::string modelPath = "../data/sphere.obj";

const std::string blendTexturePaths[2] = {
	"../data/planet_Quom1200.png", 
	"../data/earthmap.jpg"
};

const std::vector<std::string> skyboxTexturePaths = {
	"../data/starfield/Right_Tex.jpg",
	"../data/starfield/Left_Tex.jpg",
	"../data/starfield/Up_Tex.jpg",
	"../data/starfield/Down_Tex.jpg",
	"../data/starfield/Front_Tex.jpg",
	"../data/starfield/Back_Tex.jpg"
};

Scene::Scene() {
	_windowTitle = "Texture Mapping";

	// init model
	_sphere.reset(new Model(modelPath));
	_sphere->scale = glm::vec3(3.0f, 3.0f, 3.0f);

	// init skybox
	_skybox.reset(new SkyBox(skyboxTexturePaths));

	// init camera
	_camera.reset(new PerspectiveCamera(glm::radians(50.0f), 1.0f * _windowWidth / _windowHeight, 0.1f, 10000.0f));
	_camera->position.z = 10.0f;

	// init light
	_light.reset(new DirectionalLight());
	_light->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

	// init textures
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}

	// init shaders
	initSimpleShader();

	initBlendShader();

	initCheckerShader();

	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();
}

Scene::~Scene() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Scene::initSimpleShader() {
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"

		"void main() {\n"
		"	TexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	const char* fragCode =
		"#version 330 core\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D mapKd;\n"
		"void main() {\n"
		"	color = texture(mapKd, TexCoord);\n"
		"}\n";

	_simpleShader.reset(new Shader(vertCode, fragCode));
}

void Scene::initBlendShader() {
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec3 FragPos;\n"
		"out vec3 Normal;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"

		"void main() {\n"
		"	FragPos = vec3(model * vec4(aPosition, 1.0f));\n"
		"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	TexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	//----------------------------------------------------------------
	// write your code here
	// change the following code to achieve the following goals
	// + blend of the two textures
	// + lambert shading, i.e the color is affected by the light
	const char* fragCode =
		"#version 330 core\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"

		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	vec3 color;\n"
		"	float intensity;\n"
		"};\n"

		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"	vec3 kd;\n"
		"	float blend;\n"
		"};\n"



		"uniform Material material;\n"
		"uniform DirectionalLight light;\n"
		"uniform sampler2D mapKd1;\n"
		"uniform sampler2D mapKd2;\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-light.direction);\n"
		"	// diffuse color\n"
		"	vec3 diffuse = light.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"	return light.intensity * diffuse ;\n"
		"}\n"

		"void main() {\n"
		"	vec3 ambient = material.ka * material.albedo;\n"
		"	vec3 normal = normalize(Normal);\n"
		"	// diffuse color\n"
		"	vec3 diffuse = calcDirectionalLight(normal);\n"
		"	vec4 tex = mix(texture(mapKd1, TexCoord), texture(mapKd2, TexCoord), material.blend);\n"
		"	color = vec4(ambient + diffuse, 1.0f) * tex;\n"
		"}\n";
	//----------------------------------------------------------------


	_blendShader.reset(new Shader(vertCode, fragCode));
}

void Scene::initCheckerShader() {
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	TexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	//----------------------------------------------------------------
	// write your code here
	// change the following code to achieve procedural checker texture
	// hint: use the TexCoord to determine the color
	const char* fragCode =
		"#version 330 core\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"

		"struct Material {\n"
		"	vec3 color1;\n"
		"	vec3 color2;\n"
		"	int repeat;\n"
		"};\n"

		"uniform Material material;\n"

		"vec3 colorSelector(float x, float y)\n"
		"{\n"
		"	float chk = mod(floor(material.repeat * x) + floor(material.repeat * y), 2.0);\n"
		"	if(chk >= 1.0f)\n"
		"		return material.color1;\n"
		"	else \n"
		"		return material.color2;\n"
		"}\n"

		"void main() {\n"
		"	color = vec4(colorSelector(TexCoord.x, TexCoord.y), 1.0f);\n"
		"}\n";
	//----------------------------------------------------------------



	_checkerShader.reset(new Shader(vertCode, fragCode));
}

void Scene::handleInput() {
	const float angluarVelocity = 0.1f;
	const float angle = angluarVelocity * static_cast<float>(_deltaTime);
	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
	_sphere->rotation = glm::angleAxis(angle, axis) * _sphere->rotation;
}

void Scene::renderFrame() {
	// some options related to imGUI
	static bool wireframe = false;
	
	// trivial things
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	const glm::mat4& projection = _camera->getProjectionMatrix();
	const glm::mat4& view = _camera->getViewMatrix();

	// draw planet
	switch (_renderMode) {
	case RenderMode::Simple:
		// 1. use the shader
		_simpleShader->use();
		// 2. transfer mvp matrices to gpu 
		_simpleShader->setMat4("projection", projection);
		_simpleShader->setMat4("view", view);
		_simpleShader->setMat4("model", _sphere->getModelMatrix());
		// 3. enable textures and transform textures to gpu
		glActiveTexture(GL_TEXTURE0);
		_blendTextures[0]->bind();
		break;
	case RenderMode::Blend:
		// 1. use the shader
		_blendShader->use();
		// 2. transfer mvp matrices to gpu 
		_blendShader->setMat4("projection", projection);
		_blendShader->setMat4("view", view);
		_blendShader->setMat4("model", _sphere->getModelMatrix());
		// 3. transfer light attributes to gpu
		_blendShader->setVec3("light.direction", _light->getFront());
		_blendShader->setVec3("light.color", _light->color);
		_blendShader->setFloat("light.intensity", _light->intensity);
		// 4. transfer materials to gpu
		// 4.1 transfer simple material attributes
		_blendShader->setVec3("material.albedo", _albedo);
		_blendShader->setFloat("material.ka", _ka);
		_blendShader->setVec3("material.kd", _kd);
		// 4.2 transfer blend cofficient to gpu
		_blendShader->setFloat("material.blend", _blend);
		// 4.3 enable textures and transform textures to gpu
		//----------------------------------------------------------------
		// write your code here
		glActiveTexture(GL_TEXTURE0);
		_blendTextures[0]->bind();
		glActiveTexture(GL_TEXTURE1);
		_blendTextures[1]->bind();
		_blendShader->setInt("mapKd2", 1);
		//----------------------------------------------------------------
		break;
	case RenderMode::Checker:
		// 1. use the shader
		_checkerShader->use();
		// 2. transfer mvp matrices to gpu 
		_checkerShader->setMat4("projection", projection);
		_checkerShader->setMat4("view", view);
		_checkerShader->setMat4("model", _sphere->getModelMatrix());
		// 3. transfer material attributes to gpu
		_checkerShader->setInt("material.repeat", _repeat);
		_checkerShader->setVec3("material.color1", _checkerColors[0]);
		_checkerShader->setVec3("material.color2", _checkerColors[1]);
		break;
	}

	_sphere->draw();

	//draw skybox
	_skybox->draw(projection, view);

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
		ImGui::Separator();
		ImGui::RadioButton("Simple Texture Shading", (int*)&_renderMode, (int)(RenderMode::Simple));
		ImGui::RadioButton("Blend Texture Shading", (int*)&_renderMode, (int)(RenderMode::Blend));
		ImGui::SliderFloat("blend", &_blend, 0.0f, 1.0f);
		ImGui::RadioButton("Checker Shading", (int*)&_renderMode, (int)(RenderMode::Checker));
		ImGui::SliderInt("repeat", &_repeat, 2, 20);
		ImGui::ColorEdit3("color1", (float*)&_checkerColors[0]);
		ImGui::ColorEdit3("color2", (float*)&_checkerColors[1]);
		ImGui::Checkbox("wireframe", &wireframe);
		ImGui::NewLine();

		ImGui::Text("Directional light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity", &_light->intensity, 0.0f, 2.0f);
		ImGui::ColorEdit3("color", (float*)&_light->color);
		ImGui::NewLine();

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}