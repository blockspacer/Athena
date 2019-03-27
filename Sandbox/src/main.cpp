#include <Athena.h>
#include <spdlog/spdlog.h>

class ExampleLayer : public ath::Layer {
public:
	ExampleLayer()
		: Layer("Example") {
	}

	void OnUpdate() override {
		INFO("ExampleLayer::Update");
	}

	void OnEvent(ath::Event& event) override {
		TRACE("{0}", event);
	}

};

class Sandbox : public ath::Application {
public:
	Sandbox() {

		PushLayer(new ExampleLayer());
	}
	
	~Sandbox(){

	}
};

ath::Application * ath::CreateApplication() {
	return new Sandbox();
}