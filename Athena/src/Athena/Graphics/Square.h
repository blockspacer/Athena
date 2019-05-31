#pragma once
#include "Object.h"

namespace ath {
	class ATHENA_API Square : public Object {
	public:
		Square();

		Square(const char * customShaderPath);

		virtual void draw() override;

		virtual void showInfo() override;

		~Square();

	private:
		///   6 faces x 2 triangles x 3 vertices x 3 points
		///   6 faces x (4 points + 2 duplicate) x 1 normal x 3 points
		/// + 6 faces x 2 triangles x 2 texture Coordinates  x 3 points
		static const int points_count = 6 * 2 * 3 * 3 
			                          + 6 * (4 + 2) * 1 * 3
			                          + 6 * 2 * 2* 3;

		static const float square_vertices[];

		float * vertices;

		unsigned int VAO;

		unsigned int VBO;

		unsigned int texture;

	};
}