#pragma once
#include "Core.h"
#include "Input.h"

#include "Athena/Layer/Layer.h"
#include "Athena/Layer/LayerStack.h"

#include "Events/Event.h"
#include "Athena/Events/ApplicationEvent.h"
#include "Athena/Events/KeyEvent.h"
#include "Athena/Events/MouseEvent.h"

#include "Platform/Windows/Window.h"

#include "Athena/ImGui/ImGuiLayer.h" 



namespace ath {
	class ATHENA_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	
		inline static Application& Get() { return *s_Instance; }
		
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer * m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// to be defined in a client
	Application * CreateApplication();
}

