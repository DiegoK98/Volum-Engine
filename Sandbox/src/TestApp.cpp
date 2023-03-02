#include <Volum.h>
#include <Volum/Core/EntryPoint.h>

#include "Test2D.h"
#include "TestLayer.h"

class Test : public Volum::Application
{
public:
	Test()
	{
		//PushLayer(new TestLayer());
		PushLayer(new Test2D());
	}

	~Test()
	{

	}
};

Volum::Application* Volum::CreateApplication()
{
	VLM_WARN("Created Test application");

	return new Test();
}