#pragma once

#include <Filbert.h>

namespace Filbert
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnEvent(Event& event) override;

	private:
		std::shared_ptr<Filbert::Framebuffer> m_frameBuffer;

		std::unordered_map<std::string, std::shared_ptr<Filbert::TextureAtlas> > m_textureAtlases;
		std::unordered_map<std::string, std::shared_ptr<Filbert::SubTexture2D>> m_subTextures;

		OrthographicCameraController m_cameraController;

		glm::vec2 m_viewportContentRegion{1920, 1080}; // Could use ImVec2 but want to learn about bit_cast
		bool m_windowFocusedAndHovered = false;

		std::shared_ptr<Scene> m_scene;
	};
}
