#include "ath_pch.h"

#include "Application.h"

#include "Athena/Log.h"

#include <glad/glad.h>

#include <ImGui/ImGuiLayer.h>

namespace ath {

	Application * Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

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



		while (m_Running) {

			glClearColor(0, 1, 0, 1);

			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

}
