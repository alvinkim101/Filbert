#pragma once

#include <Filbert.h>

class Sandbox2D : public Filbert::Layer
{
public:
	Sandbox2D() : Layer("Sandbox2D") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnEvent(Filbert::Event& event) override;

private:
	Filbert::OrthographicCameraController m_cameraController{ std::make_shared<Filbert::OrthographicCamera>() };

	std::unordered_map<std::string, std::shared_ptr<Filbert::Texture2D>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<Filbert::TextureAtlas> > m_textureAtlases;
	std::unordered_map<std::string, std::shared_ptr<Filbert::SubTexture2D>> m_subTextures;

	glm::vec4 m_color[2]{
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	};

	float m_rotation = 0.0f;
	float m_rotationSpeed = 50.0f;
};
