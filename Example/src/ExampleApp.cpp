#include <Volum.h>

class ExampleLayer : public Volum::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		VLM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Volum::Event& event) override
	{
		VLM_TRACE("{0}", event);
	}
};

class Example : public Volum::Application
{
public:
	Example()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Volum::ImGuiLayer());
	}

	~Example()
	{

	}
};

Volum::Application* Volum::CreateApplication()
{
	VLM_WARN("This is an example");

	return new Example();
}