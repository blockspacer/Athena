#include "ath_pch.h"

#include "Application.h"

#include "Log.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Render.h"
#include "Graphics/Square.h"
#include "Graphics/ObjectManipulator.h"

#include <glad/glad.h>

namespace ath {

	Application * Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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

		// CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	Application::~Application() {
	}


	void Application::Exit() {
		this->m_Running = false;
	}

	void Application::Run() {
		///Overrided in client function

			for (ath::Layer* layer : m_LayerStack)
				layer->OnUpdate();

			for (ath::Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			//Geometry
			ath::Render render;
			ath::Square square;  

			// load models
			// -----------
			//Model ourModel("res/source/scene.fbx", "Nanosuit.glsl");
			// lights
			ath::Square light("light.glsl");
			square.addLightSource(&light);
			light.setColor(glm::vec4(1.0f));
			light.move({ -2.0, -1.0, +9.0f });
			//light.scale(glm::vec3(0.2));
			/*
			square.setTexture(0);
			square.setTexture(1);*/
			ath::ObjectManipulator::getInstance().objects.push_back(&square);
			ath::ObjectManipulator::getInstance().objects.push_back(&light);
			square.setColor({ 1.0f , 0.0f, .0f, 1.0f });
			square.setTexture(1);

			while (this->m_Running) {

				render.drawFrame();

				//ourModel.Draw();
				square.draw();
				light.draw();
				//square2.draw();

				m_Window->OnUpdate();

				if (ath::Input::IsKeyPressed(256))
					m_Running = false;
			}
	}
}
