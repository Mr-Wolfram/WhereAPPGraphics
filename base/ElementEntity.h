#pragma once
#include <memory>
#include <string>


#include "element.h"
#include "light.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"


// enum class RenderMode {
// 	Simple, Blend, Checker
// };

class ElementEntity {
public:

	ElementEntity() {};
	~ElementEntity() {};
	ElementEntity(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	
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

// 	void setPosition(glm::vec3 position);
// 	void setScale(glm::vec3 scale);
// 	void setRotation(glm::quat rotation);
// 	glm::vec3 getPosition();
// 	glm::vec3 getScale();
// 	glm::quat getRotation();
// 	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);

protected:
//     std::unique_ptr<Model> _model;
	
	// std::unique_ptr<Shader> _simpleShader;
	std::unique_ptr<Element> _element;

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
// protected:
//     std::unique_ptr<Element> _element;
	
// 	std::unique_ptr<Shader> _simpleShader;

// 	std::unique_ptr<Shader> _blendShader;
// 	glm::vec3 _albedo = { 1.0f, 1.0f, 1.0f };
// 	float _ka = 0.03f;
// 	glm::vec3 _kd = { 1.0f, 1.0f, 1.0f };
// 	float _blend = 0.5f;
// 	std::unique_ptr<Texture> _blendTextures[2];

// 	std::unique_ptr<Shader> _checkerShader;
// 	int _repeat = 10;
// 	glm::vec3 _checkerColors[2] = {
// 		{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}
// 	};

// 	std::unique_ptr<Shader> _blurShader;

// 	std::unique_ptr<DirectionalLight> _light;
// 	std::unique_ptr<SpotLight> _spotLight;

// 	void initSimpleShader();

// 	void initBlendShader();

// 	void initCheckerShader();

// 	void initBlurShader();
};

class Ball : public ElementEntity {
public:
	Ball(float radius);
	~Ball() {};
private:
	float _radius = 1.0f;
};

class Ellipsoid : public ElementEntity {
public:
	Ellipsoid(float xaxis, float yaxis, float zaxis);
	~Ellipsoid() {};
private:
	float _xaxis = 1.0f;
	float _yaxis = 1.0f;
	float _zaxis = 1.0f;
};

class Cubic : public ElementEntity {
public:
	Cubic(float size);
	~Cubic() {};
private:
	float _size = 1.0f;
};

class Cylinder : public ElementEntity {
public:
	Cylinder(float radius, float height);
	~Cylinder() {};
private:
	float _radius = 1.0f;
	float _height = 1.0f;
};

class Cone : public ElementEntity {
public:
	Cone(float radius, float height);
	~Cone() {};
private:
	float _radius = 1.0f;
	float _height = 1.0f;
};

class Prism : public ElementEntity {
public:
	Prism(float radius, float height, int facenum);
	~Prism() {};
private:
	float _radius = 1.0f;
	float _height = 1.0f;
	int _facenum = 3;
};
