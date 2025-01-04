#include "Sandbox2D.h"

#include <Filbert/Core/EntryPoint.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

void Sandbox2D::OnAttach()
{
	m_textures["Reddit"] = Filbert::Texture2D::Create("assets/textures/reddit.png");
	m_textures["Snoop"] = Filbert::Texture2D::Create("assets/textures/Smoku Smoki.jpg");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(float deltaTime)
{
	// Camera controller update
	m_cameraController.OnUpdate(deltaTime);
}

void Sandbox2D::OnRender()
{
	// Object color
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
	ImGui::End();

	Filbert::Renderer2D::BeginScene(m_cameraController.GetCamera());

	Filbert::Renderer2D::DrawQuad({ 0.0f, 2.0f }, 0.0f, { 1.0f, 1.0f }, m_textures["Reddit"]);
	Filbert::Renderer2D::DrawQuad({ -2.0f, 0.0f }, 45.0f, { 2.0f, 1.0f }, m_textures["Snoop"]);
	Filbert::Renderer2D::DrawQuad({ 2.0f, 0.0f }, 135.0f, { 1.0f, 2.0f }, m_color);

	Filbert::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Filbert::Event& event)
{
	m_cameraController.OnEvent(event);
}
