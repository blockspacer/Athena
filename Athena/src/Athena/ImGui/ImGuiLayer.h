#pragma once

#include "Athena/Layer/Layer.h"

#include "Athena/Events/ApplicationEvent.h"
#include "Athena/Events/KeyEvent.h"
#include "Athena/Events/MouseEvent.h"

namespace ath {

	class ATHENA_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}