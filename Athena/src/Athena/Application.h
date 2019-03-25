#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace ath {
	class ATHENA_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// to be defined in a client
	Application * CreateApplication();
}

