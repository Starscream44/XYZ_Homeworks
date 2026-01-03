#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include <string>
#include <unordered_map>
#include "UI.h"

namespace ApplesGame
{

	enum class GameScreen
	{
		MAIN_MENU,
		MODE_SELECT,
		GAMEPLAY,
		VICTORY,
		GAME_OVER
	};

	enum class GameModeFlags : uint32_t
	{
		None = 0,
		FiniteTarget = 1 << 0, //target
		EndlessScore = 1 << 1, // endless
		NoAcceleration = 1 << 2  // easymode
	};

	inline GameModeFlags operator|(GameModeFlags a, GameModeFlags b)
	{
		return (GameModeFlags)((uint32_t)a | (uint32_t)b);
	}
	inline GameModeFlags operator&(GameModeFlags a, GameModeFlags b)
	{
		return (GameModeFlags)((uint32_t)a & (uint32_t)b);
	}
	inline GameModeFlags& operator|=(GameModeFlags& a, GameModeFlags b)
	{
		a = a | b; return a;
	}

	inline bool HasFlag(GameModeFlags value, GameModeFlags flag)
	{
		return ((uint32_t)value & (uint32_t)flag) != 0;
	}

	struct Game
	{
		Player player;
		Apple apples[NUM_APPLES];
		Rock rocks[NUM_ROCKS];
		bool ignoreInput = false;
		bool isPopupOpen = false;

		std::unordered_map<std::string, int> leaderboard;

		// Mode select UI
		int modeMenuIndex = 0;          // 0..2 (Finite / Endless / Easy)
		bool isEnteringTarget = false; 
		std::string targetInput; 

		GameModeFlags mode = GameModeFlags::None;
		int targetApplesToWin = 10;

		// Global game data
		int numEatenApples = 0;
		UIState uiState;
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

		sf::RectangleShape modeButtonFinite;
		sf::RectangleShape modeButtonEndless;
		sf::RectangleShape modeButtonEasy;

		sf::Text modeTextFinite;
		sf::Text modeTextEndless;
		sf::Text modeTextEasy;

		sf::RectangleShape targetPopup;
		sf::Text targetPopupTitle;
		sf::Text targetPopupValue;
		sf::Text targetPopupHint;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void HandleEvent(Game& game, const sf::Event& event);
	void UpdateModeSelect(Game& game, float dt);
	void DrawModeSelect(const Game& game, sf::RenderWindow& window);
	void InitLeaderboard(Game& game);
	void UpdatePlayerScore(Game& game, int playerScore);
}