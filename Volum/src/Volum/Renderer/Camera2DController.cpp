#include "vlmpch.h"

#include "Camera2DController.h"
#include "Volum/Core/Input.h"
#include "Volum/Core/KeyCodes.h"

namespace Volum
{
	Camera2DController::Camera2DController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio* m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{

	}

	void Camera2DController::OnUpdate(TimeStep ts)
	{
		VLM_PROFILE_FUNCTION();

		// Move inputs
		if (Input::IsKeyPressed(Key::A))
		{
			m_cameraPosition.x -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_cameraPosition.x += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_cameraPosition.x += -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_cameraPosition.x -= -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		// Rotation inputs
		if (m_rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(Key::E))
				m_cameraRotation -= m_cameraRotationSpeed * ts;

			if (m_cameraRotation > 180.0f)
				m_cameraRotation -= 360.0f;
			else if (m_cameraRotation <= -180.0f)
				m_cameraRotation += 360.0f;

			m_camera.SetRotation(m_cameraRotation);
		}

		m_camera.SetPosition(m_cameraPosition);

		m_cameraTranslationSpeed = 3.0f * m_zoomLevel;
	}

	void Camera2DController::OnEvent(Event& e)
	{
		VLM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(VLM_BIND_EVENT_FN(Camera2DController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(VLM_BIND_EVENT_FN(Camera2DController::OnWindowResize));
	}

	void Camera2DController::OnResize(float width, float height)
	{
		VLM_PROFILE_FUNCTION();

		m_aspectRatio = width / height;
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
	}

	bool Camera2DController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		m_zoomLevel -= e.GetYOffset() * 0.25f;
		m_zoomLevel = std::clamp(m_zoomLevel, 0.2f, 100.0f);

		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

		return false;
	}

	bool Camera2DController::OnWindowResize(WindowResizeEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());

		return false;
	}
}
