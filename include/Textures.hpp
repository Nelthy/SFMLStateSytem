#pragma once
#include "Keys.hpp"
namespace MTB {

	class Textures
	{
	public:

		sf::Texture * NoTexture = nullptr;
		//sf::Texture* TestCircle = nullptr;
		//sf::Texture* MakeAnimGold = nullptr;
		//sf::Texture* TestBackGround = nullptr;
		//sf::Texture* Camera = nullptr;

		//

		//void loadTextures(int textgroup) {
		//
		//	switch (textgroup)
		//	{
		//	case 1:
		//	
		//		TestCircle = new sf::Texture;
		//		if (!this->TestCircle->loadFromFile("Assets/TestCircle.png")) {
		//			TestCircle = NoTexture;
		//		}
		//		MakeAnimGold = new sf::Texture;
		//		if (!this->MakeAnimGold->loadFromFile("Assets/MakeAnimGold.png")) {
		//			MakeAnimGold = NoTexture;
		//		}
		//		TestBackGround = new sf::Texture;
		//		if (!this->TestBackGround->loadFromFile("Assets/TestBackground.png")) {
		//			TestBackGround = NoTexture;
		//		}
		//						Camera = new sf::Texture;
		//		if (!this->Camera->loadFromFile("Assets/Camera.png")) {
		//			Camera = NoTexture;
		//		}
		//		std::cout << "Textures: loaded group " << textgroup << std::endl;
		//		break;
		//	case 2:

		//		

		//	default:
		//		
		//		break;
		//	}

		//};
		Textures() {
			NoTexture = new sf::Texture();
			};

		~Textures() {
			std::map<std::string, sf::Texture*>::iterator it;
			for (it = m_Textures.begin(); it != m_Textures.end(); it++)
			{
				std::cout<<"Deleting: "<<it->first << "\n";
				delete it->second;	
				it->second = nullptr;
			}
			delete NoTexture;
			
			
		};

		void addTexture(std::string filePath, std::string key) {
			sf::Texture *tex = new sf::Texture;
			if (tex->loadFromFile(filePath))
			{
				m_Textures[key] = tex;
			}
		};

		sf::Texture* getTexture(std::string key) {
			if (m_Textures.contains(key))
			{
				return m_Textures[key];
			}
			else 
			{
				std::cout<<"State does not contain: ("<<key <<")" << "\n";
				return NoTexture;
			}
		}

	private:
		std::map<std::string, sf::Texture*> m_Textures;
	};
}
/*
How to add new textures
Make the art and put it in the asset file.
Create the pointer to store it
To set the texture in the object's pushbackstate funciton write this bit of code

this->texture = state->textures.(you texture here);
*/
