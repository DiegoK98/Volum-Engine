#include <Volum.h>
#include <Volum/Core/EntryPoint.h>

#include "EditorLayer.h"
#include "Editor3DLayer.h"

namespace Volum
{
	class VolumEditor : public Application
	{
	public:
		VolumEditor()
			: Application("Volum Editor")
		{
			//PushLayer(new EditorLayer());
			PushLayer(new Editor3DLayer());
		}

		~VolumEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		VLM_INFO("Created Editor application");

		return new VolumEditor();
	}
}
