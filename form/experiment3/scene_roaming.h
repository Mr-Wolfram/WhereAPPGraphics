#pragma once

#include <memory>
#include <vector>

#include "../base/application.h"
#include "../base/camera.h"
#include "../base/model.h"

class SceneRoaming : public Application {
public:
	SceneRoaming();
	
	~SceneRoaming();

	void handleInput() override;

	void renderFrame() override;

private:


	std::vector<std::shared_ptr<Camera>> _cameras;
	int activeCameraIndex = 0;

	std::unique_ptr<Model> _bunny;

	std::unique_ptr<Shader> _shader;

	void initShader();
};