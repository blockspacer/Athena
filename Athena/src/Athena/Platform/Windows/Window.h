#pragma once

#include "ath_pch.h"

#include "Core.h"
#include "Events/Event.h"

namespace ath {

	#define ATH_INITIAL_WIDTH  1280
    #define ATH_INITIAL_HEIGHT 720

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Athena Engine",
			unsigned int width = ATH_INITIAL_WIDTH,
			unsigned int height = ATH_INITIAL_HEIGHT)
			: Title(title), Width(width), Height(height) {
		}
	};

	// Interface representing a desktop system based Window
	class ATHENA_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}