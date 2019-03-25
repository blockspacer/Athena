#pragma once

#ifdef ATH_PLATFORM_WINDOWS

extern ath::Application * ath::CreateApplication();

int main(int argc, char ** argv) {

	ath::Log::Init();



	TRACE("Athena Bless you");
	CORE_WARN("Hi my child");

	auto app = ath::CreateApplication();
	app->Run();
	delete app;
}

#endif