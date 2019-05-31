//#include <Athena.h>
//
//class ExampleLayer : public ath::Layer {
//public:
//	ExampleLayer()
//		: Layer("Example") {
//	}
//
//	void OnUpdate() override {
//		if (ath::Input::IsKeyPressed(ATH_KEY_ENTER))
//			TRACE("Tab key is pressed (poll)!");
//	}
//
//	void OnEvent(ath::Event& event) override {
//		if (event.GetEventType() == ath::EventType::KeyPressed) {
//			ath::KeyPressedEvent& e = (ath::KeyPressedEvent&)event;
//			if (e.GetKeyCode() == 10)
//				TRACE("Tab key is pressed (event)!");
//			TRACE("{0}", (char)e.GetKeyCode());
//		} //else TRACE("ANOTHER EVENT {0}", event);
//	}
//
//};
//
//class Sandbox : public ath::Application {
//public:
//	Sandbox() {
//
//		PushLayer(new ExampleLayer());
//	}
//	
//	~Sandbox(){
//
//	}
//};
//
//ath::Application * ath::CreateApplication() {
//	return new Sandbox();
//}