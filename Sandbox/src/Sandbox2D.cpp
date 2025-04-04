#include "Sandbox2D.h"

#include <Filbert/Core/EntryPoint.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D")
{
	m_textures["Reddit"] = Filbert::Texture2D::Create("assets/textures/reddit.png");
	m_textures["Snoop"] = Filbert::Texture2D::Create("assets/textures/Smoku Smoki.jpg");

	std::shared_ptr<Filbert::Texture2D> cityTexture = Filbert::Texture2D::Create("assets/textures/kenney_roguelike-modern-city/Tilemap/tilemap_packed.png");
	m_textureAtlases["City"] = std::make_shared<Filbert::TextureAtlas>(cityTexture, glm::vec2(16, 16));
	m_subTextures["Grass"] = std::make_shared<Filbert::SubTexture2D>(m_textureAtlases["City"], glm::uvec2(1, 1));
	m_subTextures["Dirt"] = std::make_shared<Filbert::SubTexture2D>(m_textureAtlases["City"], glm::uvec2(11, 1));

	const char* happyFace =
	{
		"XXXXXXXX"
		"XXOXXOXX"
		"XXXXXXXX"
		"XXXXXXXX"
		"XOXXXXOX"
		"XXOXXOXX"
		"XXXOOXXX"
		"XXXXXXXX"
	};
	uint16_t happyFaceWidth = 8;
	SetTileMap(happyFace, happyFaceWidth);

	m_charToSubTexture['X'] = m_subTextures["Dirt"];
	m_charToSubTexture['O'] = m_subTextures["Grass"];
}

void Sandbox2D::OnAttach()
{

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

	/*
	Filbert::Renderer2D::DrawQuad({ -0.5f, -0.5f }, m_rotation, { 1.0f, 1.0f }, m_color[0]);
	Filbert::Renderer2D::DrawQuad({ 2.0f, 2.0f }, 0.0f, { 1.0f, 1.0f }, m_textures["Reddit"]);
	Filbert::Renderer2D::DrawQuad({ -2.0f, 2.0f }, 0.0f, { 1.0f, 1.0f }, m_color[1], m_textures["Snoop"]);

	ImGui::Begin("Color");
	ImGui::ColorEdit4("A", glm::value_ptr(m_color[0]));
	ImGui::ColorEdit4("B", glm::value_ptr(m_color[1]));
	ImGui::End();
	*/

	DrawTileMap();

	Filbert::Renderer2D::EndScene();

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

void Sandbox2D::SetTileMap(const char* tileMap, uint16_t tileMapWidth)
{
	m_tileMap = tileMap;
	m_tileMapWidth = tileMapWidth;
	m_tileMapHeight = strlen(m_tileMap) / tileMapWidth;
}

void Sandbox2D::DrawTileMap() const
{
	FB_PROFILE_FN();

	// https://www.studyplan.dev/pro-cpp/mdspan
	std::mdspan tileMap(m_tileMap, m_tileMapHeight, m_tileMapWidth);

	for (int row = 0; row < tileMap.extent(0); row++)
	{
		for (int col = 0; col < tileMap.extent(1); col++)
		{
			// MSVC doesn't support the subscript operator [i, j]; workaround from https://stackoverflow.com/questions/78498320/mdspan-operator-doesnt-compile-in-visual-studio

			try
			{
				// -row, because [0, 0] is top-left of the tileMap, while in OpenGL it's bottom-left
				Filbert::Renderer2D::DrawQuad({ col, -row }, 0.0f, { 1.0f, 1.0f }, m_charToSubTexture.at(tileMap[std::array{ row, col }]));
			}
			catch (const std::out_of_range&)
			{
				FB_INFO("{} not found in charToSubTexture mapping", tileMap[std::array{ row, col }]);
			}
		}
	}
}
