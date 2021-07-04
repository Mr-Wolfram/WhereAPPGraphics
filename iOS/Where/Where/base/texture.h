#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <OpenGLES/ES3/gl.h>
#include <stb_image.h>

class Texture {
public:
	Texture(GLuint handle);

	virtual ~Texture();

	virtual void bind() const = 0;

	virtual void unbind() const = 0;

protected:
	GLuint _handle = {};

	virtual void cleanup();
};

class Texture2D : public Texture {
public:
    Texture2D(GLuint handle);
    
	~Texture2D() = default;

	void bind() const override;

	virtual void unbind() const;

private:
};

class TextureCubemap : public Texture {
public:
    TextureCubemap(GLuint handle);
    
	~TextureCubemap() = default;

	void bind() const override;

	void unbind() const override;

private:
};
