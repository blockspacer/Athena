#pragma once
#include <vector>
#include "Object.h"
#include "Input.h"

#include<glad/glad.h>
#include <GLFW/glfw3.h>

namespace ath {
	class ObjectManipulator {
	private:
		
		int selectedItemIndex = 0;
		
		ObjectManipulator() {

		}

		//
		const float rotatingSpeed = 1.0f;
		const float stepSpeed = 0.1f;
		const float scaleSpeed = 0.01f;
		const float colorSpeed = 0.01f;

	public:

		std::vector < Object * > objects;

	public:

		static ObjectManipulator & getInstance() {
			static ObjectManipulator instance;

			return instance;
		}

		bool isIncrease(int key) { // Shift is equal to 340
			return key == GLFW_KEY_KP_ADD || (key == GLFW_KEY_EQUAL && Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)); 
		}

		void reactToUserKeyBoardInput(int key) {
			
			/// change selected item
			if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
				this->selectedItemIndex = key - GLFW_KEY_0 >= objects.size()
				             ? objects.size() - 1
				             : key - GLFW_KEY_0;

			/// if anyone is not selected we will not spend time
			if (this->selectedItemIndex == -1)
				return;

			if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {

				/// rotating
				if (key == GLFW_KEY_RIGHT)
					this->objects[this->selectedItemIndex]->rotate(+this->rotatingSpeed, { 0.0f, 0.0f, 1.0f });
				if (key == GLFW_KEY_LEFT)
					this->objects[this->selectedItemIndex]->rotate(-this->rotatingSpeed, { 0.0f, 0.0f, 1.0f });
				if (key == GLFW_KEY_UP)
					this->objects[this->selectedItemIndex]->rotate(+this->rotatingSpeed, { 1.0f, 0.0f, 0.0f });
				if (key == GLFW_KEY_DOWN)
					this->objects[this->selectedItemIndex]->rotate(-this->rotatingSpeed, { 1.0f, 0.0f, 0.0f });

						}
			else {
				/// Scale control
				float scaleVar = 1.0f + (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) ? -1 : 1) * scaleSpeed;

				if (key == GLFW_KEY_LEFT)
					this->objects[this->selectedItemIndex]->scale({ scaleVar, 1.0f, 1.0f });
				if (key == GLFW_KEY_RIGHT)
					this->objects[this->selectedItemIndex]->scale({ 1.0f, scaleVar, 1.0f });
				if (key == GLFW_KEY_UP)
					this->objects[this->selectedItemIndex]->scale({ 1.0f, 1.0f, scaleVar });
			
				if(Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && this->objects[this->selectedItemIndex]) {
					// switch textures
					if (this->objects[this->selectedItemIndex]->IsTextureON) {
						if (this->isIncrease(key) || GLFW_KEY_MINUS == key)
							this->objects[this->selectedItemIndex]->setTexture(++(this->objects[this->selectedItemIndex]->textureIndex));
						if (Input::IsKeyPressed(GLFW_KEY_MINUS))
							this->objects[this->selectedItemIndex]->setTexture(--(this->objects[this->selectedItemIndex]->textureIndex));
					}

					if (Input::IsKeyPressed(GLFW_KEY_ENTER))
							this->objects[this->selectedItemIndex]->turnTexture(!this->objects[this->selectedItemIndex]->IsTextureON);
				}

				/// set custom color
				if (!this->objects[this->selectedItemIndex]->IsTextureON) {
					int sign = 1;
					if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
						sign = -1;

					if (Input::IsKeyPressed(GLFW_KEY_R))
						this->objects[this->selectedItemIndex]->addColorR(sign * this->colorSpeed);
					if (Input::IsKeyPressed(GLFW_KEY_G))
						this->objects[this->selectedItemIndex]->addColorG(sign * this->colorSpeed);
					if (Input::IsKeyPressed(GLFW_KEY_B))
						this->objects[this->selectedItemIndex]->addColorB(sign * this->colorSpeed);
					if (Input::IsKeyPressed(GLFW_KEY_O))
						this->objects[this->selectedItemIndex]->addColorA(sign * this->colorSpeed);
				}

				/// Move our object
				if (key == GLFW_KEY_KP_8)
					this->objects[this->selectedItemIndex]->move({ +0.0f, 0.0f, +stepSpeed });

				if (key == GLFW_KEY_KP_2)
					this->objects[this->selectedItemIndex]->move({ 0.0f, 0.0f, -stepSpeed });

				if (key == GLFW_KEY_KP_4)
					this->objects[this->selectedItemIndex]->move({ +stepSpeed, 0.0f, 0.0f });

				if (key == GLFW_KEY_KP_6)
					this->objects[this->selectedItemIndex]->move({ -stepSpeed, 0.0f, 0.0f });

				if (key == GLFW_KEY_KP_5)
					this->objects[this->selectedItemIndex]->move({ 0.0f, stepSpeed, 0.0f });

				if (key == GLFW_KEY_KP_0)
					this->objects[this->selectedItemIndex]->move({ 0.0f, -stepSpeed, 0.0f });

			}
		}

		~ObjectManipulator() {}
	};
}

