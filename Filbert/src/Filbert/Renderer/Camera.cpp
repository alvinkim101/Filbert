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
	}

	OrthographicCamera::OrthographicCamera()
	{
		CalculateProjection();
	}

	void Camera::Translate(const glm::vec3& localOffset)
	{
		m_position.x += GetRight().x * localOffset.x;
		m_position.y += m_up.y * localOffset.y;
		m_position.z += m_forward.z * localOffset.z;

		CalculateView();
	}

	void Camera::Rotate(float degrees, const glm::vec3& rotationAxis)
	{
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::normalize(rotationAxis));
		m_forward = glm::normalize(rotationMatrix * glm::vec4(m_forward, 0.0f));
		m_up = glm::normalize(rotationMatrix * glm::vec4(m_up, 0.0f));

		CalculateView();
	}

	void Camera::CalculateView()
	{
		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);

		CalculateViewProjection();
	}

	void PerspectiveCamera::CalculateProjection()
	{
		m_projection = glm::perspective(m_config.verticalFOV, m_config.aspectRatio, m_nearPlane, m_farPlane);

		CalculateViewProjection();
	}

	void OrthographicCamera::CalculateProjection()
	{
		m_viewProjection = glm::ortho(m_config.left, m_config.right, m_config.bottom, m_config.top, m_nearPlane, m_farPlane);

		CalculateViewProjection();
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_position = position;

		CalculateView();
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		FB_CORE_ASSERT(nearPlane >= 0.0f, "Near plane should be positive");
		m_nearPlane = nearPlane;

		CalculateProjection();
	}

	void Camera::SetFarPlane(float farPlane)
	{
		FB_CORE_ASSERT(farPlane >= 0.0f, "Far plane should be positive");
		m_farPlane = farPlane;

		CalculateProjection();
	}

	void PerspectiveCamera::Config(float verticalFOV, float aspectRatio)
	{
		m_config = { verticalFOV, aspectRatio };

		CalculateProjection();
	}

	void OrthographicCamera::Config(float left, float right, float bottom, float top)
	{
		m_config = { left, right, bottom, top };

		CalculateProjection();
	}
}
