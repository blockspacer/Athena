#include "ath_pch.h"

#include "Graphics/TexturePrototype.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define STB_IMAGE_IMPLEMENTATION
#include "Graphics/stb_image.h"
namespace ath {


	std::vector<std::string> TexturePrototype::images;
	std::map<std::string, unsigned int> TexturePrototype::Textures;

	void TexturePrototype::LoadTexture(const char * TexturePath, unsigned int * texture) {

		glGenTextures(1, texture);

		int width, height, nrComponents;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(TexturePath, &width, &height, &nrComponents, 0);
		if (data) {
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, *texture);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		} else 
			CORE_ERROR("Texture failed to load at path: {0}", TexturePath);

		stbi_image_free(data);
	}
}