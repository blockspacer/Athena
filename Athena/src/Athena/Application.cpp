#include "ath_pch.h"

#include "Application.h"

#include "Athena/Log.h"

#include "GLFW/glfw3.h"

namespace ath {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	//void Application::OnEvent(Event& e) {
	//	EventDispatcher dispatcher(e);
	//	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	//	
	//	CORE_TRACE(e);
	//}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
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


		glClearColor(0, 1, 0, 1);

		while (m_Running) {


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}
