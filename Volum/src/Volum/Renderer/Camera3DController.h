#pragma once

#include "Volum/Renderer/PerspectiveCamera.h"
#include "Volum/Core/TimeStep.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Volum
{
	class Camera3DController
	{
	public:
		Camera3DController(float fovY, float aspectRatio, float zNear = 0.1f, float zFar = 1000.0f);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		const PerspectiveCamera& GetCamera() const { return m_camera; }
		PerspectiveCamera& GetCamera() { return m_camera; }

		void SetCursorMoveCamera(bool enabled = true) { m_cursorMoveCameraEnabled = enabled; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_cursorMoveCameraEnabled = false;

		float m_aspectRatio;
		float m_fovY;
		float m_zNear;
		float m_zFar;

		PerspectiveCamera m_camera;

		glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_cameraRotation = { 0.0f, 0.0f, 0.0f };

		float m_cameraTranslationSpeed = 3.0f, m_cameraRotationSpeed = 0.1f;
	};
}