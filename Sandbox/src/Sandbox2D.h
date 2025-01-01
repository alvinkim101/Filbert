#pragma once

#include <Filbert.h>

class Sandbox2D : public Filbert::Layer
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 textureCoordinates;
	};

public:
	Sandbox2D() : Layer("Sandbox2D") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnEvent(Filbert::Event& event) override;

private:
	Filbert::OrthographicCameraController m_cameraController{ std::make_shared<Filbert::OrthographicCamera>() };

	glm::vec3 m_color = { 1.0f, 0.0f, 0.0f };
	//std::shared_ptr<Filbert::Texture2D> m_texture;

	glm::mat4 m_objectRotation = glm::mat4(1.0f);
	glm::vec3 m_objectRotationAxis = glm::vec3{ 0, 0, 1.0f };
	float m_objectRotationSpeed = 0.0f; // degrees per sec
};
