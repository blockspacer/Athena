#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace ath {
	class TexturePrototype {
		static std::vector<std::string> images;
		static std::map<std::string, unsigned int> Textures;

		TexturePrototype() {
			std::string placement("./res/textures/jpg/");
			images.emplace_back(placement + "AthenaAvatar.jpg");
			images.emplace_back(placement + "BlackAthena.jpg");
			images.emplace_back(placement + "cherno.png");
			images.emplace_back(placement + "SkyAthena.jpg");

			unsigned int * numbers = new unsigned int[images.size()];

			for (int i = 0; i < images.size(); i++) {
				LoadTexture(images[i].c_str(), &numbers[i]);
				Textures.insert({ images[i], numbers[i] });
			}
		}

		~TexturePrototype() {
			
		}

	public:

		static TexturePrototype & getInstance() {
			static TexturePrototype instance;

			return instance;
		}

		inline unsigned int createTexture(unsigned int number) {
			return Textures.at(images[number % images.size()]);
		}

		static void LoadTexture(const char * TexturePath, unsigned int * texture);
	};
}