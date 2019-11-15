#pragma once

#include<Gl/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "iostream"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) OpenGL::GLClearError();\
	x;\
	ASSERT(OpenGL::GLLogCall(#x, __FILE__, __LINE__))

namespace OpenGL {
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);

	class Renderer
	{
	public:
		void Clear() const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}
