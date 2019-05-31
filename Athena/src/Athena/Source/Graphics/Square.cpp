#include "ath_pch.h"
#include "Graphics/Square.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/TexturePrototype.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "glm/gtx/string_cast.hpp"

#include <random>

namespace ath {

	Square::Square() : Square("square.glsl") {
	}

	Square::Square(const char * customShader) 
		: Object((std::string("./res/shaders/") + customShader).c_str(), glm::mat4(1.0f)) {
		
		this->vertices = new float[points_count];
		
		for (int i = 0; i < points_count; i++)
			this->vertices[i] = square_vertices[i];

		// creating openGl
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, points_count * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);

		/// data setting up
		glBindVertexArray(this->VAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		glUniformMatrix4fv(shader.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(Camera::getInstance().GetViewMatrix()));
		glUniformMatrix4fv(shader.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(Camera::getInstance().GetProjectionMatrix()));
		glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(this->getModel()));
		
		
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_real_distribution<> dist(0.0f, 1.0f);

		this->setColor({ dist(rng), dist(rng), dist(rng), 1.0f });
	}

	void Square::draw() {

		shader.Bind();
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		shader.SetUniformMatrix4fv("view", glm::value_ptr(Camera::getInstance().GetViewMatrix()));
		shader.SetUniformMatrix4fv("projection", glm::value_ptr(Camera::getInstance().GetProjectionMatrix()));
		shader.SetUniformMatrix4fv("model", glm::value_ptr(this->getModel()));
		
		if (this->lightSource) {
			shader.SetUniform3f("lightPos", this->lightSource->getPosition());
			shader.SetUniform3f("viewPos", Camera::getInstance().Position);
			shader.SetUniform4f("lightColor", this->lightSource->getColor());
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexturePrototype::getInstance().createTexture(this->textureIndex));

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	void Square::showInfo() {
		CORE_WARN("Model matrix");
		CORE_ERROR(glm::to_string(this->getModel()));
	}

	Square::~Square() {
		CORE_INFO("Square Destroyed");
	}

	const float Square::square_vertices[] = {
		/// cube coordinates   // Normals          // Textures
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
							  
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, +1.0f,   0.0f, 0.0f,
							  
		-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
							  
		 0.5f,  0.5f,  0.5f,   +1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   +1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   +1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   +1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   +1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   +1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
							  
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,   0.0f, +1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, +1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, +1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, +1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, +1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, +1.0f, 0.0f,  0.0f, 1.0f
	};
}
