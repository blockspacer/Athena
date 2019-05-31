#include <Athena.h>

#include "Application.h"

#include "Log.h"
#include "Graphics/Render.h"
#include "Graphics/Object.h"
#include "Graphics/Square.h"
#include "Graphics/ObjectManipulator.h"

#include "Platform/Windows/Window.h"

#include <functional>

#define loh(x) ERROR((#x))
class ExampleLayer : public ath::Layer {
public:
	ExampleLayer()
		: Layer("Example") {
	}

	void OnUpdate() override {
		//if (ath::Input::IsKeyPressed(ATH_KEY_ENTER))
		//	TRACE("Tab key is pressed (poll)!");
	}



	void OnEvent(ath::Event& event) override {
		if (event.GetEventType() == ath::EventType::KeyPressed) {
			ath::KeyPressedEvent& e = (ath::KeyPressedEvent&)event;
			if (e.GetKeyCode() == 256) {// esc 
				TRACE("Exit!!!");			
			}
		} //else TRACE("ANOTHER EVENT {0}", event);
	}

};

class Sandbox : public  ath::Application {
public:
	Sandbox() : ath::Application() {

		PushLayer(new ExampleLayer());
	}

	/// called once per frame
	void Run() override {
		ath::Application::Run();
	}

	
	~Sandbox(){

	}
};

ath::Application * ath::CreateApplication() {
	return new Sandbox();
}