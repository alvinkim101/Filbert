#include "CameraController.h"
#include "Filbert/Input/Input.h"
#include "Filbert/Input/KeyCodes.h"
#include "Filbert/Input/MouseButtonCodes.h"

namespace Filbert
{
	void CameraController::OnUpdate(float deltaTime)
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

		// Rotation
		/*if (Input::IsMouseButtonPressed(FB_MOUSE_BUTTON_RIGHT))
		{
			float degrees = m_rotationSpeed * deltaTime;
			m_camera->Rotate(degrees, { 0.0, 0.0, 1.0 });
		}*/
	}

	bool CameraController::OnMouseScroll(MouseScrollEvent& event)
	{
		float offset = event.GetYOffset();
		m_camera->Translate(glm::vec3(0, 0, offset * m_zoomMultiplier));
		return true;
	}

	void PerspectiveCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(FB_BIND_EVENT_FN(CameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(FB_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		auto [width, height] = event.GetResolution();
		PerspectiveCamera* m_perspectiveCamera = static_cast<PerspectiveCamera*>(m_camera.get());

		m_perspectiveCamera->Config(m_perspectiveCamera->GetFOV(), static_cast<float>(width) / height);
		return false;
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(FB_BIND_EVENT_FN(CameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(FB_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		return false;
	}
}
