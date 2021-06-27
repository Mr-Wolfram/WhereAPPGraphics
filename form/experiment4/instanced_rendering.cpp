#include <unordered_map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <tiny_obj_loader.h>

#include "instanced_rendering.h"

const std::string planetPath = "../data/sphere.obj";
const std::string asternoidPath = "../data/rock.obj";

InstancedRendering::InstancedRendering() {
	_windowTitle = "Instanced Rendering";

	_camera.position = glm::vec3(0.0f, 25.0f, 100.0f);
	_camera.rotation = glm::angleAxis(-glm::radians(20.0f), _camera.getRight());

	/* init imgui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	/* import models */
	_planet.reset(new Model(planetPath));
	_planet->scale = glm::vec3(10.0f, 10.0f, 10.0f);

	_asternoid.reset(new Model(asternoidPath));

	/* shader issues */
	const char* planetVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		"}\n";

	const char* planetFsCode =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
		"}\n";


	_planetShader.reset(new Shader(planetVsCode, planetFsCode));

	const char* asternoidVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		"}\n";

	const char* asternoidInstancedVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 3) in mat4 aInstanceMatrix;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"void main() {\n"
		"	gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f);\n"
		"}\n";

	const char* asternoidFsCode =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);\n"
		"}\n";

	_asternoidShader.reset(new Shader(asternoidVsCode, asternoidFsCode));
	_asternoidInstancedShader.reset(new Shader(asternoidInstancedVsCode, asternoidFsCode));

	const float radius = 50.0f;
	const float offset = 10.0f;
	for (int i = 0; i < _amount; ++i) {
		glm::mat4 model(1.0f);
		// translate
		float angle = (float)i / (float)_amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.2f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// scale
		float scale = (rand() % 20) / 100.0f + 0.05f;
		model = glm::scale(model, glm::vec3(scale));

		// rotate
		float rotAngle = 1.0f * (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		_modelMatrices.push_back(model);
	}

	// configure instanced buffer and transform data
	unsigned int _instanceBuffer;
	glGenBuffers(1, &_instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, _amount * sizeof(glm::mat4), &_modelMatrices[0], GL_STATIC_DRAW);

	unsigned int VAO = _asternoid->getVertexArrayObject();
	glBindVertexArray(VAO);
	// ¶¥µãÊôÐÔ
	GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}

InstancedRendering::~InstancedRendering() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void InstancedRendering::handleInput() {
	if (_keyboardInput.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		_camera.position += _camera.getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		_camera.position -= _camera.getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		_camera.position -= _camera.getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		_camera.position += _camera.getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}
}

void InstancedRendering::renderFrame() {
	// some options related to imGUI
	static bool wireframe = false;

	// trivial settings
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// get camera properties
	glm::mat4 projection = _camera.getProjectionMatrix();
	glm::mat4 view = _camera.getViewMatrix();

	// draw planet
	_planetShader->use();
	_planetShader->setMat4("model", _planet->getModelMatrix());
	_planetShader->setMat4("view", view);
	_planetShader->setMat4("projection", projection);
	_planet->draw();

	// draw asternoids
	switch (_renderMode) {
	case RenderMode::Ordinary:
		_asternoidShader->use();
		_asternoidShader->setMat4("view", view);
		_asternoidShader->setMat4("projection", projection);
		for (int i = 0; i < _amount; ++i) {
			_asternoidShader->setMat4("model", _modelMatrices[i]);
			_asternoid->draw();
		}
		break;
	case RenderMode::Instanced:
		_asternoidInstancedShader->use();
		_asternoidInstancedShader->setMat4("view", view);
		_asternoidInstancedShader->setMat4("projection", projection);
		// instanced rendering code...

		glBindVertexArray(_asternoid->getVertexArrayObject());

		glDrawElementsInstanced(
			GL_TRIANGLES, _asternoid->getFaceCount() * 3, GL_UNSIGNED_INT, 0, _amount);

		glBindVertexArray(0);
		break;
	}

	// draw ui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (!ImGui::Begin("Control Panel")) {
		ImGui::End();
	} else {
		ImGui::Text("render method");
		ImGui::Separator();
		ImGui::RadioButton("ordinary rendering", (int*)&_renderMode, (int)(RenderMode::Ordinary));
		ImGui::RadioButton("instanced rendering", (int*)&_renderMode, (int)(RenderMode::Instanced));
		ImGui::Checkbox("wireframe", &wireframe);
		ImGui::NewLine();


		ImGui::ColorEdit3("background", (float*)&_clearColor);

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}