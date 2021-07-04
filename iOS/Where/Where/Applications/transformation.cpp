#include <unordered_map>
#include <iostream>

#include "transformation.h"
#include "tiny_obj_loader.h"

Transformation::Transformation() {
    
}
void Transformation::setup(const char* cfilepath) {
    
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
    std::string filepath = std::string(cfilepath);
    
	std::string::size_type index = filepath.find_last_of("/");
	std::string mtlBaseDir = filepath.substr(0, index + 1);
    
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath.c_str(), mtlBaseDir.c_str())) {
		throw std::runtime_error("load " + filepath + " failure: " + err);
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::unordered_map<Vertex, GLuint> uniqueVertices;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};

			vertex.position.x = attrib.vertices[3 * index.vertex_index + 0];
			vertex.position.y = attrib.vertices[3 * index.vertex_index + 1];
			vertex.position.z = attrib.vertices[3 * index.vertex_index + 2];

			if (index.normal_index >= 0) {
				vertex.normal.x = attrib.normals[3 * index.normal_index + 0];
				vertex.normal.y = attrib.normals[3 * index.normal_index + 1];
				vertex.normal.z = attrib.normals[3 * index.normal_index + 2];
			}

			// not used for this experiment
			if (index.texcoord_index >= 0) {
				vertex.texCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
				vertex.texCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];
			}

			// check if the vertex appeared before to reduce redundant data
			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<GLushort>(vertices.size());
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}

	// in this experiment we will not process with any material...
	// no more code for material preprocess

	// pass the data to the tables
	for (int i = 0; i < 1; ++i) {
		_bunnies.push_back(Bunny(vertices, indices));
        _bunnies[i].loadShader();
        _blocks.push_back(Block());
        _blocks[i].loadShader();
        
	}
    
}


void Transformation::renderFrame() {
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// projection matrix transform the homogenous coordinates 
	// from view space to projection space, depending on following parameters:
	// @field of view
	const float fovy = glm::radians(60.0f);
	// @aspect of the window
    const float aspect = windowWidth / windowHeight;
	// @near plane for clipping
	const float znear = 0.1f;
	// @far plane for clipping
	const float zfar = 100.0f;

	const glm::mat4 projection = glm::perspective(fovy, aspect, znear, zfar);

	// view matrix transform the homogenous coordinates 
	// from world space to view space (view of camera), depending on following parameters:
	// @camera position
	const glm::vec3 eye = { 0.0f, 0.0f, 15.0f };
	// @target, positon and target defines the direction the camera looking at
	const glm::vec3 target = { 0.0f, 0.0f, 0.0f };
	// @up, up vector of the camera
	const glm::vec3 up = { 0.0f, 1.0f, 0.0f };

	const glm::mat4 view = glm::lookAt(eye, target, up);

	for (std::size_t i = 0; i < _blocks.size(); ++i) {
		_bunnies[i].setPosition(_positions[i]);
		_bunnies[i].setRotation(_rotateAxis[i], _rotateAngles[i]);
		_bunnies[i].setScale(_scales[i]);
		_bunnies[i].draw(projection, view);
//        _blocks[i].setPosition(_positions[i]);
//        _blocks[i].setRotation(_rotateAxis[i], _rotateAngles[i]);
//        _blocks[i].setScale(_scales[i]);
//        _blocks[i].draw(projection, view);
	}
    
}
