#include "Sandbox2D.h"

#include <Filbert/Core/EntryPoint.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(float deltaTime)
{
	// Camera controller update
	m_cameraController.OnUpdate(deltaTime);

	// Object rotation
	float degrees = m_objectRotationSpeed * deltaTime;
	m_objectRotation = glm::rotate(m_objectRotation, glm::radians(degrees), m_objectRotationAxis);
}

void Sandbox2D::OnRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
	ImGui::End();

	Filbert::Renderer2D::BeginScene(m_cameraController.GetCamera());

	Filbert::Renderer2D::DrawQuad({ 0, 0, 0 }, { 0, 0 }, m_color);

	Filbert::Renderer2D::EndScene();

	/*m_texture->Bind();
	auto shader = m_shaderLibrary.Get("Texture");*/
}

void Sandbox2D::OnEvent(Filbert::Event& event)
{
	m_cameraController.OnEvent(event);
}
