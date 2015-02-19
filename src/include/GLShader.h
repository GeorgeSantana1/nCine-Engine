#ifndef CLASS_NCINE_GLSHADER
#define CLASS_NCINE_GLSHADER

#define NCINE_INCLUDE_OPENGL
#include "common.h"

namespace ncine
{

class GLShader
{
public:
	void loadFromFile(const char *filename);
	bool compile();

private:  
    GLuint glHandle_;

	explicit GLShader(GLenum type);
	GLShader(GLenum type, const char *filename);
	~GLShader();

	/// Private copy constructor
	GLShader(const GLShader&);
	/// Private assignment operator
	GLShader& operator=(const GLShader&);

	friend class GLShaderProgram;
};

}

#endif
