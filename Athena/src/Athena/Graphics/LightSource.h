#pragma once
#include "Graphics/Object.h"
#include "Graphics/Square.h"

#include <glad/glad.h>

namespace ath {
	class LightSource : public Square {
	public:
		/// Same draw but textures disabled
		virtual void draw() override {
			this->turnTexture(false);
			Square::draw();
		}
	};
}