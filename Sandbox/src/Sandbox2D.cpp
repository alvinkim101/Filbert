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

	// Object transform
	m_translation = { 5.0f, 0.0f, 0.0f };
	m_rotation = 45.0f;
	m_scale = { 2.0f, 2.0f };
}

void Sandbox2D::OnRender()
{
	// Object color
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
	ImGui::End();

	Filbert::Renderer2D::BeginScene(m_cameraController.GetCamera());

	Filbert::Renderer2D::DrawQuad(m_translation, m_rotation, m_scale, m_color);

	Filbert::Renderer2D::EndScene();

	/*m_texture->Bind();
	auto shader = m_shaderLibrary.Get("Texture");*/
}

void Sandbox2D::OnEvent(Filbert::Event& event)
{
	m_cameraController.OnEvent(event);
}
