#include "RenderMain.h"

#if SHADER_PLAFORM==SHADER_PLAFORM_CV
#include "../opencv/OpenCVMain.h"
#endif // SHADER_OPEN_CV

#if SHADER_PLAFORM==SHADER_PLAFORM_GL
#include "../opengl/OpenGLMain.h"
#endif

namespace Render 
{
	long getCurrentRenderTime() {
		return clock();
	}

	unsigned int CreateVBO()
	{
	#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreateVBO();
	#endif
	#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateVBO();
	#endif
	}

	unsigned int CreateVAO()
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreateVAO();
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateVAO();
#endif
	}

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, dataLength, data);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, dataLength, data);
#endif
	}

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::BindArrayBufferData(vbo, dataSize, data);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::BindArrayBufferData(vbo, dataSize, data);
#endif
	}

	void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::VertexAttribPointer(passageway, dataSize, dataType, b, delaySize, startIndex);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::VertexAttribPointer(passageway, dataSize, dataType, b, delaySize, startIndex);
#endif
	}


	void RenderVBO(int vbo)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::RenderVBO(vbo);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::RenderVBO(vbo);
#endif
	}

	RenderProgram* CreateRenderProgram(std::string materialName)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreateRenderProgram(materialName);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateRenderProgram(materialName);
#endif
	}

	Material* CreateMaterial(std::string materialName)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreateMaterial(materialName);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateMaterial(materialName);
#endif
	}

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreateShader(shaderName, vsPath, fsPath);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateShader(shaderName, vsPath, fsPath);
#endif
	}

	// 添加到渲染队列
	void AddRenderQueue(RenderProgram* renderProgram)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::AddRenderQueue(renderProgram);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::AddRenderQueue(dynamic_cast<OpenGL::RenderGLProgram*>(renderProgram));
#endif
	}

	void InitEngine()
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return;
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::InitEngine();
#endif
	}

	int CreateWindow(int w, int h, std::string title)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::CreaterWindow(w, h, title);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::CreateWindow(w, h, title);
#endif
	}

	void ClearBuffer()
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::ClearBuffer();
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::ClearBuffer();
#endif
	}

	void SetBackgroundColor(Math::Vector3 color)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return ;
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::SetBackgroundColor(color);
#endif
	}

	void Render(float delay)
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::Render(delay);
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::Render(delay);
#endif
	}

	void RenderEnd()
	{
#if SHADER_PLAFORM==SHADER_PLAFORM_CV
		return OpenCV::RenderEnd();
#endif
#if SHADER_PLAFORM==SHADER_PLAFORM_GL
		return OpenGL::RenderEnd();
#endif
	}
}