#pragma once

#include "Renderer/Camera.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Filbert
{
	class CameraController
	{
	public:
		CameraController(const std::shared_ptr<class Camera>& camera) : m_camera(camera) {}

		void OnUpdate(float deltaTime);
		bool OnMouseScroll(MouseScrollEvent& event);

		const Camera& GetCamera() const { return *m_camera.get(); }

		float GetTranslationSpeed() const { return m_translationSpeed; }
		float GetRotationSpeed() const { return m_rotationSpeed; }
		float GetZoomMultiplier() const { return m_zoomMultiplier; }

		void SetTranslationSpeed(float translationSpeed) { m_translationSpeed = translationSpeed; }
		void SetRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; }
		void SetZoomMultiplier(float zoomMultiplier) { m_zoomMultiplier = zoomMultiplier; }

	protected:
		std::shared_ptr<class Camera> m_camera;

		float m_translationSpeed = 1.0f;
		float m_rotationSpeed = 1.0f;
		float m_zoomMultiplier = 1.0f;
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		PerspectiveCameraController(const std::shared_ptr<class PerspectiveCamera>& camera) : CameraController(camera) {}

		void OnEvent(Event& event);

	private:
		bool OnWindowResize(WindowResizeEvent& event);
	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(const std::shared_ptr<class OrthographicCamera>& camera) : CameraController(camera) {}

		void OnEvent(Event& event);

	private:
		bool OnWindowResize(WindowResizeEvent& event);
	};
}
