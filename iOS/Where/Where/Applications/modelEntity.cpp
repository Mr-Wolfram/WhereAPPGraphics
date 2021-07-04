#include "modelEntity.h"

ModelEntity::ModelEntity(const std::string& filepath,GLuint _blendTextureID1, GLuint _blendTextureID2) {
	_model.reset(new Model(filepath));
	const GLuint blendTextureHandles[2] = {
        _blendTextureID1,
        _blendTextureID2
	};

	_light.reset(new DirectionalLight);
	_light->position = glm::vec3(10.0f, 10.0f, 10.0f);
	_light->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

	_spotLight.reset(new SpotLight);
	_spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
	_spotLight->rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 2; ++i) {
		_blendTextures[i].reset(new Texture2D(blendTextureHandles[i]));
	}
	// initSimpleShader();

	initBlendShader();

	// initCheckerShader();
}

ModelEntity::~ModelEntity(){
	
}

void ModelEntity::setPosition(glm::vec3 position) {
	_model.get()->position = position;
}

void ModelEntity::setScale(glm::vec3 scale) {
	_model.get()->scale = scale;
}

void ModelEntity::setRotation(glm::quat rotation) {
	_model.get()->rotation = rotation;
}

glm::vec3 ModelEntity::getPosition() {
	return _model.get()->position;
}
glm::vec3 ModelEntity::getScale() {
	return _model.get()->scale;
}
glm::quat ModelEntity::getRotation() {
	return _model.get()->rotation;
}

void ModelEntity::setDirectionalLight(glm::vec3 direction,glm::vec3 color,float intensity){
	_light->getFront()=direction;
	_light->color=color;
	_light->intensity=intensity;
}

void ModelEntity::setSpotLight(glm::vec3 position,glm::vec3 direction,glm::vec3 color,float intensity, float angle, float kc, float kl,float kq){
	_spotLight->position=position;
	_spotLight->getFront()=direction;
	_spotLight->intensity=intensity;
	_spotLight->color=color;
	_spotLight->angle=angle;
	_spotLight->kc=kc;
	_spotLight->kl=kl;
	_spotLight->kq=kq;
}

void ModelEntity::setMaterial(glm::vec3 albedo,float ka,glm::vec3 kd,glm::vec3 ks, float ns, float blend){
	_albedo=albedo;
	_ka=ka;
	_kd=kd;
	_ks=ks;
	_ns=ns;
	_blend=blend;
}

void ModelEntity::initBlendShader() {
	const char* vertCode =
        "#version 300 es\n"
        "precision highp float;"
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
        "#version 300 es\n"
        "precision highp float;"
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
	//----------------------------------------------------------------


	_blendShader.reset(new Shader(vertCode, fragCode));
}

void ModelEntity::draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {

	
	// 1. use the shader
	_blendShader->use();
	// 2. transfer mvp matrices to gpu 
	_blendShader->setMat4("projection", projection);
	_blendShader->setMat4("view", view);
	_blendShader->setMat4("model", _model->getModelMatrix());
	_blendShader->setVec3("viewPos", viewPos);
	_blendShader->setFloat("depth", viewPos.z);

	// 3. transfer light attributes to gpu
	_blendShader->setVec3("spotLight.position", _spotLight->position);
	_blendShader->setVec3("spotLight.direction", _spotLight->getFront());
	_blendShader->setFloat("spotLight.intensity", _spotLight->intensity);
	_blendShader->setVec3("spotLight.color", _spotLight->color);
	_blendShader->setFloat("spotLight.angle", _spotLight->angle);
	_blendShader->setFloat("spotLight.kc", _spotLight->kc);
	_blendShader->setFloat("spotLight.kl", _spotLight->kl);
	_blendShader->setFloat("spotLight.kq", _spotLight->kq);
	_blendShader->setVec3("directionalLight.direction", _light->getFront());
	_blendShader->setVec3("directionalLight.color", _light->color);
	_blendShader->setFloat("directionalLight.intensity", _light->intensity);
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
	//----------------------------------------------------------------

	_model->draw();
}

