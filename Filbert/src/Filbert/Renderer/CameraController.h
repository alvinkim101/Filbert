#pragma once

#include "Camera.h"
#include "Filbert/Events/ApplicationEvent.h"
#include "Filbert/Events/MouseEvent.h"

namespace Filbert
{
	class CameraController
	{
	public:
		float GetTranslationSpeed() const { return m_translationSpeed; }
		float GetRotationSpeed() const { return m_rotationSpeed; }
		float GetZoomMultiplier() const { return m_zoomMultiplier; }

		void SetTranslationSpeed(float translationSpeed) { m_translationSpeed = translationSpeed; }
		void SetRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; }
		void SetZoomMultiplier(float zoomMultiplier) { m_zoomMultiplier = zoomMultiplier; }

	protected:
		float m_translationSpeed = 1.0f;
		float m_rotationSpeed = 1.0f;
		float m_zoomMultiplier = 1.0f;
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		PerspectiveCameraController(const std::shared_ptr<class PerspectiveCamera>& perspectiveCamera = std::make_shared<Filbert::PerspectiveCamera>()) : m_camera(perspectiveCamera) {}

		const PerspectiveCamera& GetCamera() const { return *m_camera.get(); }

		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);

	private:
		bool OnMouseScroll(MouseScrollEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		std::shared_ptr<class PerspectiveCamera> m_camera;
	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(const std::shared_ptr<class OrthographicCamera>& orthographicCamera = std::make_shared<Filbert::OrthographicCamera>()) : m_camera(orthographicCamera) {}

		OrthographicCamera& GetCamera() const { return *m_camera.get(); }

		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);

	private:
		bool OnMouseScroll(MouseScrollEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		std::shared_ptr<class OrthographicCamera> m_camera;
	};
}
