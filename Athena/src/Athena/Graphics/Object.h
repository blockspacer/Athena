#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "TexturePrototype.h"

namespace ath {
	class ATHENA_API Object {
	
	private:

		glm::mat4 model;


	public:

		bool IsTextureON = false;

		glm::vec4 color;

		glm::vec3 position;

		Object * lightSource;

		Shader shader;

		unsigned int textureIndex = 0;

	protected:

		Object(const char * shaderPath, glm::mat4 model) 
			: model(model), position(1.0f), 
			lightSource(nullptr), shader(shaderPath){
			this->color = glm::vec4(0.0f);
		}

	public:

		virtual void draw() = 0;

		virtual void showInfo() = 0;

		void move(glm::vec3 direction) {
			this->position += direction;
			this->model = glm::translate(this->model, direction);
		}

		glm::vec3 getPosition() {
			return this->position;
		}

		void rotate(float angle, glm::vec3 axis) {
			this->model = glm::rotate(this->model, glm::radians(angle), axis);
		}

		void rotate_radians(float angle, glm::vec3 axis) {
			this->model = glm::rotate(this->model, angle, axis);
		}

		void scale(glm::vec3 k) {
			this->model *= glm::vec4(k, 1.0f);
		}

		void setColor(glm::vec4 color) {
			this->shader.Bind();
			this->color = color;
			this->shader.SetUniform4f("objectColor", color.x, color.y, color.z, color.w);
		}

		glm::vec4 getColor() {
			glm::vec4 temp = this->color;
			return temp;
		}

		void addLightSource(Object * light) {
			this->lightSource = light;
		}

		void addColorR(float delta) {
			this->setColor({ this->color.x + (delta - (int)delta), this->color.y, this->color.z, this->color.z });
		}

		void addColorG(float delta) {
			this->setColor({ this->color.x, this->color.y + (delta - (int)delta), this->color.z, this->color.z });
		}

		void addColorB(float delta) {
			this->setColor({ this->color.x, this->color.y,  this->color.z + (delta - (int)delta), this->color.z });
		}

		void addColorA(float delta) {
			this->setColor({ this->color.x, this->color.y, this->color.z,  this->color.w + (delta - (int)delta) });
		}

		void setTexture(unsigned int index) {

			this->shader.unBind();
			this->draw();
			this->shader.Bind();

			this->shader.SetUniform1i("IsTextureActive", 1);
			this->shader.SetUniform1i("activeTexture", 0);

			this->textureIndex = index;
			this->IsTextureON = true;
		}

		void turnTexture(bool isActive) {
			this->shader.unBind();
			this->shader.Bind();
			this->draw();

			this->shader.SetUniform1i("IsTextureActive", isActive ? 1 : 0);

			this->IsTextureON = isActive;
		}

		void setShader(const char * path) {
			throw new std::exception("Not implemented");
		}

		const glm::mat4 & getModel() {
			return this->model;
		}


		virtual ~Object() {}
	};
};

