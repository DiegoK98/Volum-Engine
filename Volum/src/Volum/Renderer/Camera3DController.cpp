#include "vlmpch.h"

#include "Camera3DController.h"
#include "Volum/Core/Input.h"
#include "Volum/Core/KeyCodes.h"

namespace Volum
{
	static bool s_noPreviousPos = true;
	static float s_previousMousePosX = 0.0f;
	static float s_previousMousePosY = 0.0f;

	Camera3DController::Camera3DController(float fovY, float aspectRatio, float zNear, float zFar)
		: m_aspectRatio(aspectRatio), m_fovY(fovY), m_zNear(zNear), m_zFar(zFar), m_camera(fovY, aspectRatio, zNear, zFar)
	{

	}

	void Camera3DController::OnUpdate(TimeStep ts)
	{
		VLM_PROFILE_FUNCTION();

		// Move inputs
		if (Input::IsKeyPressed(VLM_KEY_A))
		{
			m_cameraPosition.x -= cos(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.z -= -sin(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VLM_KEY_D))
		{
			m_cameraPosition.x += cos(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.z += -sin(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(VLM_KEY_W))
		{
			m_cameraPosition.x += -sin(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.z += -cos(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VLM_KEY_S))
		{
			m_cameraPosition.x -= -sin(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.z -= -cos(glm::radians(m_cameraRotation.y)) * m_cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(VLM_KEY_E))
		{
			m_cameraPosition.y += m_cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VLM_KEY_Q))
		{
			m_cameraPosition.y -= m_cameraTranslationSpeed * ts;
		}

		m_camera.SetPosition(m_cameraPosition);

		m_cameraTranslationSpeed = 3.0f;
	}

	void Camera3DController::OnEvent(Event& e)
	{
		VLM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(VLM_BIND_EVENT_FN(Camera3DController::OnMouseScrolled));
		dispatcher.Dispatch<MouseButtonPressedEvent>(VLM_BIND_EVENT_FN(Camera3DController::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(VLM_BIND_EVENT_FN(Camera3DController::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(VLM_BIND_EVENT_FN(Camera3DController::OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(VLM_BIND_EVENT_FN(Camera3DController::OnWindowResize));
	}

	void Camera3DController::OnResize(float width, float height)
	{
		VLM_PROFILE_FUNCTION();

		m_aspectRatio = width / height;
		m_camera.SetProjection(m_fovY, m_aspectRatio, m_zNear, m_zFar);
	}

	bool Camera3DController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		m_fovY -= e.GetYOffset();
		m_fovY = std::clamp(m_fovY, 20.0f, 100.0f);

		m_camera.SetProjection(m_fovY, m_aspectRatio, m_zNear, m_zFar);

		return false;
	}

	bool Camera3DController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		if (e.GetMouseButton() == MouseCode::Button0)
		{
			m_cursorMoveCameraEnabled = true;

			s_noPreviousPos = true;
		}

		return false;
	}

	bool Camera3DController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		if (e.GetMouseButton() == MouseCode::Button0)
			m_cursorMoveCameraEnabled = false;

		return false;
	}

	bool Camera3DController::OnMouseMoved(MouseMovedEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		if (m_cursorMoveCameraEnabled)
		{
			if (s_noPreviousPos)
			{
				s_previousMousePosX = e.GetX();
				s_previousMousePosY = e.GetY();

				s_noPreviousPos = false;
			}

			m_cameraRotation.y -= (e.GetX() - s_previousMousePosX) * m_cameraRotationSpeed;
			m_cameraRotation.x -= (e.GetY() - s_previousMousePosY) * m_cameraRotationSpeed;

			// TODO: Fix cursor pos or disable it, so it does not go out of bounds

			s_previousMousePosX = e.GetX();
			s_previousMousePosY = e.GetY();

			if (m_cameraRotation.y > 180.0f)
				m_cameraRotation.y -= 360.0f;
			else if (m_cameraRotation.y <= -180.0f)
				m_cameraRotation.y += 360.0f;

			m_cameraRotation.x = glm::clamp(m_cameraRotation.x, -90.0f, 90.0f);

			m_camera.SetRotation(m_cameraRotation);
		}

		return false;
	}

	bool Camera3DController::OnWindowResize(WindowResizeEvent& e)
	{
		VLM_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());

		return false;
	}
}