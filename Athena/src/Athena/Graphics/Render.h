#pragma once
#include "ath_pch.h"
#include "Graphics/Render.h"
#include "Graphics/Camera.h"
#include "Graphics/Object.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace ath {
	class Render {
	public:

		glm::vec4 color;
		std::vector < Object * > objects;

		Render::Render() : color(0.4f, 0.3f, 1.0f, 1.0f){
			glEnable(GL_DEPTH_TEST);
		}

		void Render::run() {
			/// Architecture issue
		}


		void Render::drawFrame() {

			glClearColor(color.x, color.y, color.z, color.w );
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			for (Object * obj : this->objects)
				obj->draw();

			Camera::getInstance().Update();
		}

		Render::~Render() {
		}
	};
}

