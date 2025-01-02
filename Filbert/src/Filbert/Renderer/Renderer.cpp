#include "Renderer.h"
#include "Renderer2D.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Filbert
{
	glm::mat4 Renderer::s_viewProjection = glm::mat4(1.0f);

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();
		Renderer2D::Initialize();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_viewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::string& viewProjectionName, const glm::mat4& model, const std::string& modelName)
	{
		shader->Bind();
		vertexArray->Bind();
		shader->SetMat4(viewProjectionName, s_viewProjection);
		shader->SetMat4(modelName, model);

		RenderCommand::DrawElements(vertexArray);
	}
}
