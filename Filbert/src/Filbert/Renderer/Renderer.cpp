#include "Renderer.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Filbert
{
	glm::mat4 Renderer::s_viewProjection = glm::mat4(1.0f);

	void Renderer::BeginScene(const Camera& camera)
	{
		s_viewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::string& viewProjectionName)
	{
		shader->Bind();
		vertexArray->Bind();
		shader->UploadUniform(viewProjectionName, s_viewProjection);

		RenderCommand::DrawElements(vertexArray);
	}
}
