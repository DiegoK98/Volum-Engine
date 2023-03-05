#pragma once

#include "Volum/Renderer/OrthographicCamera.h"
#include "Volum/Core/TimeStep.h"
#include "Volum/Events/ApplicationEvent.h"
#include "Volum/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Volum
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		const OrthographicCamera& GetCamera() const { return m_camera; }
		OrthographicCamera& GetCamera() { return m_camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		float m_aspectRatio;
		float m_zoomLevel = 1.0f;

		OrthographicCamera m_camera;

		bool m_rotation;

		glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_cameraRotation = 0.0f;

		float m_cameraTranslationSpeed = 3.0f, m_cameraRotationSpeed = 90.0f;
	};
}