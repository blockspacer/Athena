#include <Athena.h>

class Sandbox : public ath::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

ath::Application * ath::CreateApplication() {
	return new Sandbox();
}