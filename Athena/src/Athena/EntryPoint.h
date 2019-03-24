#pragma once

#ifdef ATH_PLATFORM_WINDOWS

extern ath::Application * ath::CreateApplication();

int main(int argc, char ** argv) {

	std::cout << "Gavno" << std::endl;
	auto app = ath::CreateApplication();
	app->Run();
	delete app;
}

#endif