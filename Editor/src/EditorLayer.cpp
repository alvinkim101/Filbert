#include "EditorLayer.h"

#include <imgui.h>

namespace Filbert
{
	EditorLayer::EditorLayer() : m_window(Filbert::Application::GetApplication().GetWindow())
	{
		// Framebuffer
		Filbert::FramebufferSpec frameBufferSpec;
		frameBufferSpec.width = m_window.GetWidth();
		frameBufferSpec.height = m_window.GetHeight();
		m_frameBuffer = Filbert::Framebuffer::Create(frameBufferSpec);

		// Textures
		std::shared_ptr<Filbert::Texture2D> cityTexture = Filbert::Texture2D::Create("assets/textures/kenney_roguelike-modern-city/Tilemap/tilemap_packed.png");
		m_textureAtlases["City"] = std::make_shared<Filbert::TextureAtlas>(cityTexture, glm::vec2(16, 16));
		m_subTextures["Grass"] = std::make_shared<Filbert::SubTexture2D>(m_textureAtlases["City"], glm::uvec2(1, 1));
		m_subTextures["Dirt"] = std::make_shared<Filbert::SubTexture2D>(m_textureAtlases["City"], glm::uvec2(11, 1));
	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{
		
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(float deltaTime)
	{
		FB_PROFILE_FN();

		m_cameraController.OnUpdate(deltaTime);

		Filbert::Renderer2D::ResetStats();
	}

	void EditorLayer::OnRender()
	{
		FB_PROFILE_FN();

		m_frameBuffer->Bind();
		Filbert::RenderCommand::Clear();
		Filbert::Renderer2D::BeginScene(m_cameraController.GetCamera());

		Filbert::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f }, m_subTextures["Dirt"]);

		Filbert::Renderer2D::EndScene();
		m_frameBuffer->Unbind();

		ImVec2 upperLeft(0.0f, 1.0f);
		ImVec2 bottomRight(1.0f, 0.0f);
		ImGui::Image(m_frameBuffer->GetColorAttachment(), ImVec2(m_window.GetWidth(), m_window.GetHeight()), upperLeft, bottomRight); // UL and BR because image is flipped vertically

		auto stats = Filbert::Renderer2D::GetStats();
		ImGui::Begin("Stats");
		ImGui::Text("Draw calls %u", stats.drawCalls);
		ImGui::Text("Quad count %u", stats.quadCount);
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		FB_PROFILE_FN();

		m_cameraController.OnEvent(event);
	}
}
