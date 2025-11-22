#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UI.h"

namespace ApplesGame
{

	enum class GameScreen
	{
		MAIN_MENU,
		GAMEPLAY,
		VICTORY,
		GAME_OVER
	};

	struct Game
	{
		Player player;
		Apple apples[NUM_APPLES];
		Rock rocks[NUM_ROCKS];

		// Global game data
		int numEatenApples = 0;
		UIState uiState;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		sf::RectangleShape background;

		//Resources
		sf::Font font;


		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::Texture startMenuTexture;
		sf::Sprite startMenuSprite;

		sf::Texture gameOverTexture;
		sf::Sprite gameOverSprite;


		sf::Texture winTexture;
		sf::Sprite winSprite;

		sf::SoundBuffer eatBuffer;
		sf::SoundBuffer hitBuffer;
		sf::Sound eatSound;
		sf::Sound hitSound;
		sf::Music backgroundMusic;
		sf::Music menuMusic;
		sf::Music gameOverMusic;
		sf::Music winMusic;

		GameScreen currentScreen = GameScreen::MAIN_MENU;
		GameScreen previousScreen = (GameScreen)-1;

		int mainMenuSelected = 0; 

		sf::RectangleShape menuButtonStart;
		sf::RectangleShape menuButtonExit;
		sf::RectangleShape menuButtonRestart;

		sf::Text menuTextStart;
		sf::Text menuTextRestart;
		sf::Text menuTextExit;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
}