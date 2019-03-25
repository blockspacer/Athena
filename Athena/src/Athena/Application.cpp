#include "ath_pch.h"

#include "Application.h"

#include "Athena/Log.h"
#include "Athena/Events/ApplicationEvent.h"
#include "Athena/Events/KeyEvent.h"
#include "Athena/Events/MouseEvent.h"

namespace ath {

	Application::Application() {
	}


	Application::~Application() {
	}

	void Application::Run() {
		// place for testing everything out

		ERROR(ath::KeyPressedEvent(90, 2));

		//e = &ath::MouseButtonPressedEvent(24);
		INFO(ath::MouseButtonPressedEvent(24));

		//e = &ath::AppTickEvent();
		WARN(AppTickEvent());

		//e = &ath::WindowCloseEvent();
		TRACE(WindowCloseEvent());
		while (true);
	}

}
