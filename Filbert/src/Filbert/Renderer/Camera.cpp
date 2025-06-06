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
		m_projection = glm::perspective(glm::radians(m_config.verticalFOV), m_config.aspectRatio, m_nearPlane, m_farPlane);

		CalculateViewProjection();
	}

	void OrthographicCamera::CalculateProjection()
	{
		m_projection = glm::ortho(m_config.left * m_zoom, m_config.right * m_zoom, m_config.bottom * m_zoom, m_config.top * m_zoom, m_nearPlane, m_farPlane);

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

	void PerspectiveCamera::Zoom(float offset)
	{
		// Zoom "flips" when going past these values
		constexpr float minVerticalFOV = 0.0f;
		constexpr float maxVerticalFOV = 180.0f;

		m_config.verticalFOV = std::clamp(m_config.verticalFOV += offset, minVerticalFOV, maxVerticalFOV);

		CalculateProjection();
	}

	void PerspectiveCamera::SetFOV(float verticalFOV)
	{
		m_config.verticalFOV = verticalFOV;

		CalculateProjection();
	}

	void PerspectiveCamera::SetAspectRatio(float aspectRatio)
	{
		m_config.aspectRatio = aspectRatio;

		CalculateProjection();
	}

	void OrthographicCamera::Zoom(float offset)
	{
		constexpr float minZoom = 0.01f;
		constexpr float maxZoom = 10.0f;

		offset *= 0.01f; // To roughly match PerspectiveCamera's zoom speed
		m_zoom = std::clamp(m_zoom + offset, minZoom, maxZoom);

		CalculateProjection();
	}

	void OrthographicCamera::SetBounds(float left, float right, float bottom, float top)
	{
		m_config = { left, right, bottom, top };

		CalculateProjection();
	}
}
