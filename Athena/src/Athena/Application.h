#pragma once
#include "Core.h"
#include "Athena/Layer.h"
#include "Athena/LayerStack.h"
#include "Events/Event.h"
#include "Athena/Events/ApplicationEvent.h"
#include "Athena/Events/KeyEvent.h"
#include "Athena/Events/MouseEvent.h"

#include "Window.h"



namespace ath {
	class ATHENA_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// to be defined in a client
	Application * CreateApplication();
}

