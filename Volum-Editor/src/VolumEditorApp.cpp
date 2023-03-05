#include <Volum.h>
#include <Volum/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Volum
{
	class VolumEditor : public Application
	{
	public:
		VolumEditor()
			: Application("Volum Editor")
		{
			PushLayer(new EditorLayer());
		}

		~VolumEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		VLM_WARN("Created Test application");

		return new VolumEditor();
	}
}