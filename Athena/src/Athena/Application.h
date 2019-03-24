#pragma once
#include "Core.h"

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

