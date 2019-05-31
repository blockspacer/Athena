#pragma once
#include "Core.h"
#include "Input.h"

#include "Layer/Layer.h"
#include "Layer/LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Platform/Windows/Window.h"


#include <functional>

namespace ath {
	class ATHENA_API Application {
	public:
		Application(); 
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	
		inline static Application& Get() { return *s_Instance; }
		
		inline Window& GetWindow() { return *m_Window; }
		void virtual Exit();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	protected:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// to be defined in a client
	Application * CreateApplication();
}

