#include "ElementEntity.h"
#include <assert.h>

#define PI 3.14159265358979323846

ElementEntity::ElementEntity(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
	_element.reset(new Element(vertices,indices));

	_light.reset(new DirectionalLight);
	_light->position = glm::vec3(10.0f, 10.0f, 10.0f);
	_light->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

	_spotLight.reset(new SpotLight);
	_spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
	_spotLight->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	_spotLight->color = glm::vec3(1.0f, 0.0f, 0.0f);
	_spotLight->angle = glm::radians(60.0f);
	_spotLight->kc = glm::radians(60.0f);
	_spotLight->kl = 0.0f;
	_spotLight->kq = 0.2f;
	// initBlendShader();
}

void ElementEntity::setPosition(glm::vec3 position) {
	_element.get()->position = position;
}

void ElementEntity::setScale(glm::vec3 scale) {
	_element.get()->scale = scale;
}

void ElementEntity::setRotation(glm::quat rotation) {
	_element.get()->rotation = rotation;
}

glm::vec3 ElementEntity::getPosition() {
	return _element.get()->position;
}
glm::vec3 ElementEntity::getScale() {
	return _element.get()->scale;
}
glm::quat ElementEntity::getRotation() {
	return _element.get()->rotation;
}

void ElementEntity::setDirectionalLight(glm::vec3 direction,glm::vec3 color,float intensity){
	_light->getFront()=direction;
	_light->color=color;
	_light->intensity=intensity;
}

void ElementEntity::setSpotLight(glm::vec3 position,glm::vec3 direction,glm::vec3 color,float intensity, float angle, float kc, float kl,float kq){
	_spotLight->position=position;
	_spotLight->getFront()=direction;
	_spotLight->intensity=intensity;
	_spotLight->color=color;
	_spotLight->angle=angle;
	_spotLight->kc=kc;
	_spotLight->kl=kl;
	_spotLight->kq=kq;
}

void ElementEntity::setMaterial(glm::vec3 albedo,float ka,glm::vec3 kd,glm::vec3 ks, float ns, float blend){
	_albedo=albedo;
	_ka=ka;
	_kd=kd;
	_ks=ks;
	_ns=ns;
	_blend=blend;
}
//ElementEntity::ElementEntity()

void ElementEntity::draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {

		// 1. use the shader
	_blendShader->use();
	// // 2. transfer mvp matrices to gpu 
	// _blendShader->setMat4("projection", projection);
	// _blendShader->setMat4("view", view);
	// _blendShader->setMat4("model", _element->getModelMatrix());
	// _blendShader->setVec3("viewPos", viewPos);
	// _blendShader->setFloat("depth", viewPos.z);

	// // 3. transfer light attributes to gpu
	// _blendShader->setVec3("spotLight.position", _spotLight->position);
	// _blendShader->setVec3("spotLight.direction", _spotLight->getFront());
	// _blendShader->setFloat("spotLight.intensity", _spotLight->intensity);
	// _blendShader->setVec3("spotLight.color", _spotLight->color);
	// _blendShader->setFloat("spotLight.angle", _spotLight->angle);
	// _blendShader->setFloat("spotLight.kc", _spotLight->kc);
	// _blendShader->setFloat("spotLight.kl", _spotLight->kl);
	// _blendShader->setFloat("spotLight.kq", _spotLight->kq);
	// _blendShader->setVec3("directionalLight.direction", _light->getFront());
	// _blendShader->setVec3("directionalLight.color", _light->color);
	// _blendShader->setFloat("directionalLight.intensity", _light->intensity);
	// // 4. transfer materials to gpu
	// // 4.1 transfer simple material attributes
	// _blendShader->setVec3("material.albedo", _albedo);
	// _blendShader->setFloat("material.ka", _ka);
	// _blendShader->setVec3("material.kd", _kd);
	// _blendShader->setVec3("material.ks", _ks);
	// _blendShader->setFloat("material.ns", _ns);
	// // 4.2 transfer blend cofficient to gpu
	// _blendShader->setFloat("material.blend", _blend);
		// 2. transfer mvp matrices to gpu 
	_blendShader->setMat4("projection", projection);
	_blendShader->setMat4("view", view);
	_blendShader->setMat4("model", _element->getModelMatrix());
	_blendShader->setVec3("viewPos", viewPos);
	_blendShader->setFloat("depth", viewPos.z);

	// 3. transfer light attributes to gpu
	_blendShader->setVec3("spotLight.position", glm::vec3(0.0f, 0.0f, 5.0f));
	_blendShader->setVec3("spotLight.direction", glm::vec3(0.0f, 0.0f, 5.0f));
	_blendShader->setFloat("spotLight.intensity", 0.2f);
	_blendShader->setVec3("spotLight.color", glm::vec3(0.0f, 0.0f, 5.0f));
	_blendShader->setFloat("spotLight.angle", glm::radians(60.0f));
	_blendShader->setFloat("spotLight.kc", glm::radians(60.0f));
	_blendShader->setFloat("spotLight.kl", 0.0f);
	_blendShader->setFloat("spotLight.kq", 0.2f);
	_blendShader->setVec3("directionalLight.direction", glm::vec3(0.0f, 0.0f, 5.0f));
	_blendShader->setVec3("directionalLight.color", glm::vec3(0.0f, 0.0f, 5.0f));
	_blendShader->setFloat("directionalLight.intensity", 0.2f);
	// 4. transfer materials to gpu
	// 4.1 transfer simple material attributes
	_blendShader->setVec3("material.albedo", _albedo);
	_blendShader->setFloat("material.ka", _ka);
	_blendShader->setVec3("material.kd", _kd);
	_blendShader->setVec3("material.ks", _ks);
	_blendShader->setFloat("material.ns", _ns);
	// 4.2 transfer blend cofficient to gpu
	_blendShader->setFloat("material.blend", _blend);
	// 4.3 enable textures and transform textures to gpu
	//----------------------------------------------------------------
	// write your code here
	glActiveTexture(GL_TEXTURE0);
	_blendTextures[0]->bind();
	glActiveTexture(GL_TEXTURE1);
	_blendTextures[1]->bind();
	_blendShader->setInt("mapKd1", 0);
	_blendShader->setInt("mapKd2", 1);
	_element->draw();
}



void ElementEntity::initBlendShader() {
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

		"struct SpotLight {\n"
		"	vec3 position;\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"	float angle;\n"
		"	float kc;\n"
		"	float kl;\n"
		"	float kq;\n"
		"};\n"

		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"	vec3 kd;\n"
		"	vec3 ks;\n"
		"	float ns;\n"
		"	float blend;\n"
		"};\n"

		"// uniform variables\n"
		"uniform Material material;\n"
		"uniform DirectionalLight directionalLight;\n"
		"uniform SpotLight spotLight;\n"
		"uniform vec3 viewPos;\n"
		"uniform float depth;\n"
		"uniform sampler2D mapKd1;\n"
		"uniform sampler2D mapKd2;\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-directionalLight.direction);\n"
		"// diffuse color\n" 
		"	vec3 diffuse = directionalLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"// specular color\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	vec3 specular = directionalLight.color * pow(max(dot(viewDir, reflectDir), 0.0f), material.ns) * material.ks;\n"
		"	return directionalLight.intensity * diffuse + directionalLight.intensity * specular ;\n"
		"}\n"

		"vec3 calcSpotLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(spotLight.position - FragPos);\n"
		"	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));\n"
		"	if (theta > spotLight.angle) {\n"
		"		return vec3(0.0f, 0.0f, 0.0f);\n"
		"	}\n"
		"	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"// specular color\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	vec3 specular = spotLight.color * pow(max(dot(viewDir, reflectDir), 0.0f), material.ns) * material.ks;\n"
		"	float distance = length(spotLight.position - FragPos);\n"

		"	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);\n"
		"	return spotLight.intensity * attenuation * diffuse + spotLight.intensity * attenuation * specular;\n"
		"}\n"

		"void main() {\n"
		"	vec3 ambient = material.ka * material.albedo;\n"
		"	vec3 normal = normalize(Normal);\n"
    	"	float blur = 0.0;\n"
 
    	"	float far_distance = 10.0;\n"
    	"	float far_plane = 0.0;\n"
 
        "	blur = clamp(depth, far_plane - far_distance, far_plane);\n"
        "	blur = (far_plane - blur) / far_distance;\n"

		"	// diffuse color\n"
		"	vec3 diffuse = calcDirectionalLight(normal);\n"
		"	vec4 tex = mix(texture(mapKd1, TexCoord), texture(mapKd2, TexCoord), material.blend);\n"
		"	color = vec4(ambient + diffuse, 1.0f) * tex;\n"
		"	color.a = blur;\n"
		"}\n";

	_blendShader.reset(new Shader(vertCode, fragCode));
}


void ElementEntity::initBlurShader() {
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

	_blurShader.reset(new Shader(vertCode, fragCode));
}


Ball::Ball(float radius){	
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	int segments = 50;

	//vertices
	for (int y = 0; y <= segments; y++)
	{
		for (int x = 0; x <= segments; x++)
		{
			Vertex vertex{};
			float xSegment = (float)x / (float)segments;
			float ySegment = (float)y / (float)segments;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			vertex.position.x = xPos;
			vertex.position.y = yPos;
			vertex.position.z = zPos;
			vertex.normal.x = xPos;
			vertex.normal.y = yPos;
			vertex.normal.z = zPos;
			vertex.texCoord.x = 1 - xSegment;
			vertex.texCoord.y = 1 - ySegment;
			vertices.push_back(vertex);
		}
	}

	//indices
	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j + 1);
		}
	}
	_element.reset(new Element(vertices, indices));
	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}

	initBlendShader();

	// initCheckerShader();
	this->setScale({ radius,radius,radius });
	_radius = radius;
}

Ellipsoid::Ellipsoid(float xaxis, float yaxis, float zaxis) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	int segments = 50;

	//vertices
	for (int y = 0; y <= segments; y++)
	{
		for (int x = 0; x <= segments; x++)
		{
			Vertex vertex{};
			float xSegment = (float)x / (float)segments;
			float ySegment = (float)y / (float)segments;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			vertex.position.x = xPos;
			vertex.position.y = yPos;
			vertex.position.z = zPos;
			vertex.normal.x = xPos;
			vertex.normal.y = yPos;
			vertex.normal.z = zPos;
			vertex.texCoord.x = 1 - xSegment;
			vertex.texCoord.y = 1 - ySegment;
			vertices.push_back(vertex);
		}
	}

	//indices
	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j + 1);
		}
	}
	_element.reset(new Element(vertices, indices));
	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}


	initBlendShader();


	this->setScale({ xaxis,yaxis,zaxis });
	_xaxis = xaxis;
	_yaxis = yaxis;
	_zaxis = zaxis;
}

Cubic::Cubic(float size) {
	static const float position[6][6][5] = {
		// left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// right
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

		// top
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		// bottom
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// front
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

		// back
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	};

	static const float normals[6][3] = {
		{ -1, 0, 0 },
		{ +1, 0, 0 },
		{ 0, +1, 0 },
		{ 0, -1, 0 },
		{ 0, 0, +1 },
		{ 0, 0, -1 }
	};

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	for (int i = 0; i < 6; i++) {
		for (int v = 0; v < 6; v++) {
			Vertex vertex{};
			vertex.position.x = position[i][v][0];
			vertex.position.y = position[i][v][1];
			vertex.position.z = position[i][v][2];
			vertex.normal.x = normals[i][0];
			vertex.normal.y = normals[i][1];
			vertex.normal.z = normals[i][2];
			vertex.texCoord.x = 1 - position[i][v][3];
			vertex.texCoord.y = 1 - position[i][v][4];
			vertices.push_back(vertex);
			indices.push_back(indice);
			indice++;
		}
	}
	
	_element.reset(new Element(vertices, indices));

	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}


	initBlendShader();

	this->setScale({ size,size,size });
	_size = size;
}

Cylinder::Cylinder(float radius, float height) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	int sidecount = 36;
	float y = height / 2.0;
	
	//up circle
	Vertex vertexup{};
	vertexup.position.x = 0;
	vertexup.position.y = y;
	vertexup.position.z = 0;
	vertexup.normal.x = 0;
	vertexup.normal.y = 1;
	vertexup.normal.z = 0;
	vertexup.texCoord.x = 0.5;
	vertexup.texCoord.y = 0.5;
	
	for (int i = sidecount; i >= 0; --i) {
		float angle = i / (float)sidecount * PI * 2;
		vertices.push_back(vertexup);
		indices.push_back(indice);
		indice++;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	//bottom circle
	Vertex vertexdown{};
	y = -height / 2.0;
	vertexdown.position.x = 0;
	vertexdown.position.y = y;
	vertexdown.position.z = 0;
	vertexdown.normal.x = 0;
	vertexdown.normal.y = -1;
	vertexdown.normal.z = 0;
	vertexdown.texCoord.x = 0.5;
	vertexdown.texCoord.y = 0.5;
	for (int i = 0; i <= sidecount; ++i) {
		vertices.push_back(vertexdown);
		indices.push_back(indice);
		indice++;

		float angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	//middle rectangles
	float yup = height / 2.0;
	float ydown = -height / 2.0;
	for (int i = 0; i <= sidecount; ++i) {
		GLfloat angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = i / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}

	_element.reset(new Element(vertices, indices));
	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}


	initBlendShader();


	this->setScale({ radius, height, radius });
	_radius = radius;
	_height = height;
}

Cone::Cone(float radius, float height) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	int sidecount = 36;

	//bottom circle
	Vertex vertexdown{};
	float yup = height / 2.0;
	float ydown = -height / 2.0;
	vertexdown.position.x = 0;
	vertexdown.position.y = ydown;
	vertexdown.position.z = 0;
	vertexdown.normal.x = 0;
	vertexdown.normal.y = -1;
	vertexdown.normal.z = 0;
	vertexdown.texCoord.x = 0.5;
	vertexdown.texCoord.y = 0.5;
	for (int i = 0; i <= sidecount; ++i) {
		vertices.push_back(vertexdown);
		indices.push_back(indice);
		indice++;

		float angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}

	//uppoint
	Vertex vertexup{};
	vertexup.position.x = 0;
	vertexup.position.y = yup;
	vertexup.position.z = 0;
	vertexup.normal.x = 0;
	vertexup.normal.y = 1;
	vertexup.normal.z = 0;
	vertexup.texCoord.x = 0.5;
	vertexup.texCoord.y = 0.5;
	for (int i = sidecount; i >= 0; --i) {
		float angle = i / (float)sidecount * PI * 2;
		vertices.push_back(vertexup);
		indices.push_back(indice);
		indice++;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	

	_element.reset(new Element(vertices, indices));
	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}


	initBlendShader();

	this->setScale({ radius, height, radius });
	_radius = radius;
	_height = height;
}

Prism::Prism(float radius, float height, int facenum) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	int sidecount = facenum;
	float y = height / 2.0;

	//up circle
	Vertex vertexup{};
	vertexup.position.x = 0;
	vertexup.position.y = y;
	vertexup.position.z = 0;
	vertexup.normal.x = 0;
	vertexup.normal.y = 1;
	vertexup.normal.z = 0;
	vertexup.texCoord.x = 0.5;
	vertexup.texCoord.y = 0.5;

	for (int i = sidecount; i >= 0; --i) {
		float angle = i / (float)sidecount * PI * 2;
		vertices.push_back(vertexup);
		indices.push_back(indice);
		indice++;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	//bottom circle
	Vertex vertexdown{};
	y = -height / 2.0;
	vertexdown.position.x = 0;
	vertexdown.position.y = y;
	vertexdown.position.z = 0;
	vertexdown.normal.x = 0;
	vertexdown.normal.y = -1;
	vertexdown.normal.z = 0;
	vertexdown.texCoord.x = 0.5;
	vertexdown.texCoord.y = 0.5;
	for (int i = 0; i <= sidecount; ++i) {
		vertices.push_back(vertexdown);
		indices.push_back(indice);
		indice++;

		float angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	//middle rectangles
	float yup = height / 2.0;
	float ydown = -height / 2.0;
	for (int i = 0; i <= sidecount; ++i) {
		GLfloat angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = i / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}

	_element.reset(new Element(vertices, indices));
	const std::string blendTexturePaths[2] = {
	"../data/bodyMap.png",
	"../data/bodyMap.png"
	};
	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTexturePaths[i]));
	}

	initBlendShader();

	this->setScale({ radius, height, radius });


	_radius = radius;
	_height = height;
	_facenum = facenum;
}