#include "CameraController.h"
#include "Filbert/Input/Input.h"
#include "Filbert/Input/KeyCodes.h"
#include "Filbert/Input/MouseButtonCodes.h"

namespace Filbert
{
	void PerspectiveCameraController::OnUpdate(float deltaTime)
	{
		// Translation
		float distance = m_translationSpeed * deltaTime;
		if (Input::IsKeyPressed(FB_KEY_W))
		{
			m_camera->Translate(glm::vec3(0, 0, distance));
		}
		if (Input::IsKeyPressed(FB_KEY_S))
		{
			m_camera->Translate(glm::vec3(0, 0, -distance));
		}
		if (Input::IsKeyPressed(FB_KEY_A))
		{
			m_camera->Translate(glm::vec3(-distance, 0, 0));
		}
		if (Input::IsKeyPressed(FB_KEY_D))
		{
			m_camera->Translate(glm::vec3(distance, 0, 0));
		}
	}

	void PerspectiveCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(FB_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(FB_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
	}

	bool PerspectiveCameraController::OnMouseScroll(MouseScrollEvent& event)
	{
		float offset = -event.GetYOffset();
		m_camera->Zoom(offset * m_zoomMultiplier);
		return true;
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		auto [width, height] = event.GetResolution();

		m_camera->SetAspectRatio(static_cast<float>(width) / height);
		return false;
	}

	void OrthographicCameraController::OnUpdate(float deltaTime)
	{
		// Translation
		float distance = m_translationSpeed * deltaTime;
		if (Input::IsKeyPressed(FB_KEY_W))
		{
			m_camera->Translate(glm::vec3(0, distance, 0));
		}
		if (Input::IsKeyPressed(FB_KEY_S))
		{
			m_camera->Translate(glm::vec3(0, -distance, 0));
		}
		if (Input::IsKeyPressed(FB_KEY_A))
		{
			m_camera->Translate(glm::vec3(-distance, 0, 0));
		}
		if (Input::IsKeyPressed(FB_KEY_D))
		{
			m_camera->Translate(glm::vec3(distance, 0, 0));
		}
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(FB_BIND_EVENT_FN(OrthographicCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(FB_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& event)
	{
		float offset = -event.GetYOffset();
		m_camera->Zoom(offset * m_zoomMultiplier);
		return true;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		auto [width, height] = event.GetResolution();

		// TODO: Implement
		return false;
	}
}
