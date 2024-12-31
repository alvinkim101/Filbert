#include "Sandbox2D.h"

class Sandbox : public Filbert::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	virtual ~Sandbox()
	{

	}
};

Filbert::Application* Filbert::CreateApplication()
{
	return new Sandbox();
}
