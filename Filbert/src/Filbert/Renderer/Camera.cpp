#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Filbert
{
	Camera::Camera()
	{
		CalculateView();
	}

	PerspectiveCamera::PerspectiveCamera()
	{
		CalculateProjection();
		CalculateViewProjection();
	}

	OrthographicCamera::OrthographicCamera()
	{
		CalculateProjection();
		CalculateViewProjection();
	}

	void Camera::CalculateView()
	{
		/*
		eye     Position of the camera
		center  Position where the camera is looking at
		up      Normalized up vector, how the camera is oriented
		*/
		m_view = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void PerspectiveCamera::CalculateProjection()
	{
		/*
			fovy    Specifies the field of view angle in the y direction.Expressed in radians.
			aspect  Specifies the aspect ratio that determines the field of view in the x direction.The aspect ratio is the ratio of x(width) to y(height).
			near    Specifies the distance from the viewer to the near clipping plane(always positive).
			far     Specifies the distance from the viewer to the far clipping plane(always positive).
			*/
		m_projection = glm::perspective(m_config.verticalFOV, m_config.aspectRatio, m_nearPlane, m_farPlane);
	}

	void OrthographicCamera::CalculateProjection()
	{
		m_viewProjection = glm::ortho(m_config.left, m_config.right, m_config.bottom, m_config.top, m_nearPlane, m_farPlane);
	}

	void Camera::Translate(const glm::vec3& translation)
	{
		m_position += translation;
		CalculateView();
		CalculateViewProjection();
	}

	void Camera::Rotate(const glm::vec3& rotation)
	{
		//glm::rotate();
		CalculateView();
		CalculateViewProjection();
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_position = position;
		CalculateView();
		CalculateViewProjection();
	}

	void Camera::SetForward(const glm::vec3& forward)
	{
		m_forward = forward;
		CalculateView();
		CalculateViewProjection();
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		FB_CORE_ASSERT(nearPlane >= 0.0f, "Near plane should be positive");

		m_nearPlane = nearPlane;
		CalculateProjection();
		CalculateViewProjection();
	}

	void Camera::SetFarPlane(float farPlane)
	{
		FB_CORE_ASSERT(farPlane >= 0.0f, "Far plane should be positive");

		m_farPlane = farPlane;
		CalculateProjection();
		CalculateViewProjection();
	}

	void PerspectiveCamera::Config(float verticalFOV, float aspectRatio)
	{
		m_config = { verticalFOV, aspectRatio };
		CalculateProjection();
		CalculateViewProjection();
	}

	void OrthographicCamera::Config(float left, float right, float bottom, float top)
	{
		m_config = { left, right, bottom, top };
		CalculateProjection();
		CalculateViewProjection();
	}
}
