#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>

namespace Filbert
{
	/*
		OpenGL camera convention
		+X -> Right
		+Y -> Up
		-Z -> Forward
	*/

	class Camera
	{
	public:
		Camera();

		glm::mat4 GetViewProjection() const { return m_viewProjection; }

		void Translate(const glm::vec3& translation);
		void Rotate(const glm::vec3& rotation);

		glm::vec3 GetPosition() const { return m_position; }
		glm::vec3 GetForward() const { return m_forward; }
		void SetPosition(const glm::vec3& position);
		void SetForward(const glm::vec3& forward);

		float GetNearPlane() const { return m_nearPlane; }
		float GetFarPlane() const { return m_farPlane; }
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

	protected:
		inline void CalculateView();
		inline virtual void CalculateProjection() = 0;
		void CalculateViewProjection() { m_viewProjection = m_projection * m_view; }

		glm::mat4 m_viewProjection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
		glm::mat4 m_projection = glm::mat4(1.0f);

		glm::vec3 m_position{0.0f, 0.0f, 0.0f};
		glm::vec3 m_forward{0.0f, 0.0f, -1.0f};

		float m_nearPlane = 0.1f; // Doesn't work if set to 0
		float m_farPlane = 10.0f;
	};

	class PerspectiveCamera : public Camera
	{
		struct PerspectiveConfig
		{
			float verticalFOV = glm::radians(60.0f);
			float aspectRatio = 1.77f;
		};

	public:
		PerspectiveCamera();

		void Config(float verticalFOV, float aspectRatio);

	private:
		inline void CalculateProjection() final;

		PerspectiveConfig m_config;
	};

	class OrthographicCamera : public Camera
	{
		struct OrthographicConfig
		{
			float left = -1.0f;
			float right = 1.0f;
			float bottom = -1.0f;
			float top = 1.0f;
		};

	public:
		OrthographicCamera();

		void Config(float left, float right, float bottom, float top);

	private:
		inline void CalculateProjection() final;

		OrthographicConfig m_config;
	};
}
