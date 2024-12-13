#pragma once

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

namespace Filbert
{
	// TODO: Batch rendering
	class Renderer
	{
	public:
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::string& viewProjectionName, const glm::mat4& model, const std::string& modelName);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static glm::mat4 s_viewProjection;
	};
}
