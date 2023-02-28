#include "vlmpch.h"

#include "OrthographicCameraController.h"
#include "Input.h"
#include "KeyCodes.h"

namespace Volum
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		// Move inputs
		if (Input::isKeyPressed(VLM_KEY_A))
			m_cameraPosition.x -= m_cameraTranslationSpeed * ts;
		else if (Input::isKeyPressed(VLM_KEY_D))
			m_cameraPosition.x += m_cameraTranslationSpeed * ts;
		else if (Input::isKeyPressed(VLM_KEY_W))
			m_cameraPosition.y += m_cameraTranslationSpeed * ts;
		else if (Input::isKeyPressed(VLM_KEY_S))
			m_cameraPosition.y -= m_cameraTranslationSpeed * ts;

		// Rotation inputs
		if (m_rotation)
		{
			if (Input::isKeyPressed(VLM_KEY_Q))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			else if (Input::isKeyPressed(VLM_KEY_E))
				m_cameraRotation -= m_cameraRotationSpeed * ts;

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