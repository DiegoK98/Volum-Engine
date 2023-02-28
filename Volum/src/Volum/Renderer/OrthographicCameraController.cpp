#include "vlmpch.h"

#include "OrthographicCameraController.h"
#include "Volum/Core/Input.h"
#include "Volum/Core/KeyCodes.h"

namespace Volum
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		// Move inputs
		if (Input::IsKeyPressed(VLM_KEY_A))
		{
			m_cameraPosition.x -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VLM_KEY_D))
		{
			m_cameraPosition.x += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(VLM_KEY_W))
		{
			m_cameraPosition.x += -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VLM_KEY_S))
		{
			m_cameraPosition.x -= -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		// Rotation inputs
		if (m_rotation)
		{
			if (Input::IsKeyPressed(VLM_KEY_Q))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(VLM_KEY_E))
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

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(VLM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(VLM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.GetYOffset() * 0.25f;
		m_zoomLevel = std::clamp(m_zoomLevel, 0.2f, 100.0f);

		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

		return false;
	}
}