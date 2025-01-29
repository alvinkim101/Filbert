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
	FB_PROFILE_FN();

	m_cameraController.OnUpdate(deltaTime);

	m_rotation += m_rotationSpeed * deltaTime;

	Filbert::Renderer2D::ResetStats();
}

void Sandbox2D::OnRender()
{
	FB_PROFILE_FN();

	Filbert::Renderer2D::BeginScene(m_cameraController.GetCamera());
	Filbert::Renderer2D::DrawQuad({ -0.5f, -0.5f }, m_rotation, { 1.0f, 1.0f }, m_color[0]);
	Filbert::Renderer2D::DrawQuad({ 2.0f, 2.0f }, 0.0f, { 1.0f, 1.0f }, m_textures["Reddit"]);
	Filbert::Renderer2D::DrawQuad({ -2.0f, 2.0f }, 0.0f, { 1.0f, 1.0f }, m_color[1], m_textures["Snoop"]);
	Filbert::Renderer2D::EndScene();

	ImGui::Begin("Color");
	ImGui::ColorEdit4("A", glm::value_ptr(m_color[0]));
	ImGui::ColorEdit4("B", glm::value_ptr(m_color[1]));
	ImGui::End();

	auto stats = Filbert::Renderer2D::GetStats();
	ImGui::Begin("Stats");
	ImGui::Text("Draw calls %u", stats.drawCalls);
	ImGui::Text("Quad count %u", stats.quadCount);
	ImGui::End();
}

void Sandbox2D::OnEvent(Filbert::Event& event)
{
	FB_PROFILE_FN();

	m_cameraController.OnEvent(event);
}
