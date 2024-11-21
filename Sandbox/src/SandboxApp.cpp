#include <Filbert.h>

class Sandbox : public Filbert::Application
{
public:
	Sandbox()
	{

	}

	virtual ~Sandbox()
	{

	}
};

Filbert::Application* Filbert::CreateApplication()
{
	return new Sandbox();
}
