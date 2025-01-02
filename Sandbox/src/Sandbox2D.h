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

	glm::vec3 m_translation;
	float m_rotation;
	glm::vec2 m_scale;

	glm::vec3 m_color = { 1.0f, 0.0f, 0.0f };
	//std::shared_ptr<Filbert::Texture2D> m_texture;
};
