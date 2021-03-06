#pragma once

#include "Graphics/Object.h"

namespace ath {

	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class  Mesh : public Object {
	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		unsigned int VAO;


		/*  Functions  */
		// constructor
		Mesh(const char * customShaderPath, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

		virtual void showInfo() override;

		// render the mesh
		virtual void draw() override;

	private:
		/*  Render data  */
		unsigned int VBO, EBO;

		/*  Functions    */
		// initializes all the buffer objects/arrays
		void setupMesh();
	};
}