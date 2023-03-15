#pragma once

#include "Volum/Core/Window.h"
#include "Volum/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Volum {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_data.Width; }
		unsigned int GetHeight() const override { return m_data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		void SetVSync(bool enabled, unsigned int swapInterval = 1) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* m_window;
		Scope<GraphicsContext> m_context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};

}