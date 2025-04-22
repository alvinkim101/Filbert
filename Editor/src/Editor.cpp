#include "EditorLayer.h"

#include <Filbert/Core/EntryPoint.h>

namespace Filbert
{
	class Editor : public Application
	{
	public:
		Editor() : Application("Editor")
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication()
	{
		return new Editor();
	}
}
