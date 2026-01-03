#include "Game.h"
#include <cassert>
#include "constants.h"
#include <random>

namespace ApplesGame
{

	void RestartGame(Game& game)
	{
		InitPlayer(game.player, game);

		// Init apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			InitApple(game.apples[i],game);
		}

		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rocks[i], game);
		}

		game.numEatenApples = 0;
	}

	void InitGame(Game& game)
	{
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Pacman.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		assert(game.startMenuTexture.loadFromFile(RESOURCES_PATH + "\\main.png"));
		game.startMenuSprite.setTexture(game.startMenuTexture);
		game.startMenuSprite.setScale(
			float(SCREEN_WIDTH) / game.startMenuTexture.getSize().x,
			float(SCREEN_HEIGHT) / game.startMenuTexture.getSize().y);

		assert(game.gameOverTexture.loadFromFile(RESOURCES_PATH + "\\loose.png"));
		game.gameOverSprite.setTexture(game.gameOverTexture);
		game.gameOverSprite.setScale(
			float(SCREEN_WIDTH) / game.gameOverTexture.getSize().x,
			float(SCREEN_HEIGHT) / game.gameOverTexture.getSize().y);

		assert(game.winTexture.loadFromFile(RESOURCES_PATH + "\\win.png"));
		game.winSprite.setTexture(game.winTexture);
		game.winSprite.setScale(
			float(SCREEN_WIDTH) / game.winTexture.getSize().x,
			float(SCREEN_HEIGHT) / game.winTexture.getSize().y);

		assert(game.eatBuffer.loadFromFile(RESOURCES_PATH +"\\Sounds/AppleEat.wav"));
		game.eatSound.setBuffer(game.eatBuffer);
		assert(game.hitBuffer.loadFromFile(RESOURCES_PATH +"\\Sounds/Crash.wav"));
		game.hitSound.setBuffer(game.hitBuffer);


		assert(game.menuMusic.openFromFile(RESOURCES_PATH + "\\Sounds/menu.wav"));
		game.menuMusic.setLoop(true);
		game.menuMusic.setVolume(30);

		assert(game.backgroundMusic.openFromFile(RESOURCES_PATH + "\\Sounds/Background.wav"));
		game.backgroundMusic.setLoop(true);
		game.backgroundMusic.setVolume(20);

		assert(game.gameOverMusic.openFromFile(RESOURCES_PATH + "\\Sounds/loose.wav"));
		game.gameOverMusic.setLoop(false);
		game.gameOverMusic.setVolume(20);

		assert(game.winMusic.openFromFile(RESOURCES_PATH + "\\Sounds/win.wav"));
		game.winMusic.setLoop(false);     
		game.winMusic.setVolume(20);


		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		InitUI(game.uiState, game.font);
		InitMainMenu(game);
		InitModeSelect(game);
		InitLeaderboard(game);

		RestartGame(game);
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (game.currentScreen != game.previousScreen)
		{
			switch (game.currentScreen)
			{
			case GameScreen::MAIN_MENU:
				game.backgroundMusic.stop();
				game.gameOverMusic.stop();
				game.winMusic.stop();
				game.menuMusic.play();
				break;

			case GameScreen::MODE_SELECT:
				UpdateModeSelect(game, deltaTime);
				break;

			case GameScreen::GAMEPLAY:
				game.menuMusic.stop();
				game.gameOverMusic.stop();
				game.winMusic.stop();
				game.backgroundMusic.play();
				break;

			case GameScreen::VICTORY:
				game.menuMusic.stop();
				game.backgroundMusic.stop();
				game.gameOverMusic.stop();
				game.winMusic.play();
				break;

			case GameScreen::GAME_OVER:
				game.menuMusic.stop();
				game.backgroundMusic.stop();
				game.winMusic.stop();
				game.gameOverMusic.play();
				break;
			}

			if (game.currentScreen == GameScreen::VICTORY || game.currentScreen == GameScreen::GAME_OVER)
			{
				UpdatePlayerScore(game, game.numEatenApples);
			}

			game.previousScreen = game.currentScreen;
		}


		switch (game.currentScreen)
		{
		case GameScreen::MAIN_MENU:
			UpdateMainMenu(game);
			break;

		case GameScreen::GAMEPLAY:
			UpdateGameplay(game, deltaTime);;
			break;

		case GameScreen::VICTORY:
			UpdateVictoryScreen(game);
			break;

		case GameScreen::GAME_OVER:
			UpdateGameOverScreen(game);
			break;
		}
	}

	void UpdateGameplay(Game & game, float deltaTime)
	{ 
		if (HasFlag(game.mode, GameModeFlags::FiniteTarget) &&
			game.numEatenApples >= game.targetApplesToWin)
		{
			game.currentScreen = GameScreen::VICTORY;
		}

		// Update game state
		if (game.currentScreen == GameScreen::GAMEPLAY)
		{
			game.background.setFillColor(sf::Color::Black);

			// Handle input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				game.player.direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				game.player.direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				game.player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				game.player.direction = PlayerDirection::Down;
			}

			// Update player state
			switch (game.player.direction)
			{
			case PlayerDirection::Right:
			{
				game.player.position.x += game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Up:
			{
				game.player.position.y -= game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Left:
			{
				game.player.position.x -= game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Down:
			{
				game.player.position.y += game.player.speed * deltaTime;
				break;
			}
			}

			// Find player collisions with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
					game.apples[i].position, APPLE_SIZE / 2.f))
				{
					game.eatSound.play();
					game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					++game.numEatenApples;

					if (HasFlag(game.mode, GameModeFlags::FiniteTarget) &&
						game.numEatenApples >= game.targetApplesToWin)
					{
						game.currentScreen = GameScreen::VICTORY;
					}

					if (!HasFlag(game.mode, GameModeFlags::NoAcceleration))
					{
						game.player.speed += ACCELERATION;
					}

				}
			}

			// Find player collisions with rocks
			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
					game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
				{
					game.hitSound.play();
					game.currentScreen = GameScreen::GAME_OVER;
				}
			}

			// Check screen borders collision
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				game.hitSound.play();
				game.currentScreen = GameScreen::GAME_OVER;
			}
		}
		
		UpdateUI(game.uiState, game, deltaTime);
	}

	void HandleEvent(Game& game, const sf::Event& event)
	{
		if (game.currentScreen != GameScreen::MODE_SELECT)
			return;


		if (game.isEnteringTarget)
		{
			if (event.type == sf::Event::TextEntered)
			{
				const uint32_t ch = event.text.unicode;

				if (ch >= '0' && ch <= '9')
				{
					if (game.targetInput.size() < 2)
						game.targetInput.push_back((char)ch);
				}
				else if (ch == 8) // Backspace
				{
					if (!game.targetInput.empty())
						game.targetInput.pop_back();
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			{
				if (game.targetInput.empty())
					return;

				int value = std::stoi(game.targetInput);

				if (value < 5 || value > 30)
					return;

				game.targetApplesToWin = value;
				game.mode = GameModeFlags::FiniteTarget;

				game.isEnteringTarget = false;
				RestartGame(game);
				game.currentScreen = GameScreen::GAMEPLAY;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				game.isEnteringTarget = false;
			}

			return;
		}

		
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
				game.modeMenuIndex = (game.modeMenuIndex + 2) % 3;

			if (event.key.code == sf::Keyboard::Down)
				game.modeMenuIndex = (game.modeMenuIndex + 1) % 3;

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (game.modeMenuIndex == 0) // Finite
				{
					game.isEnteringTarget = true;
					game.targetInput.clear();
					return;
				}

				if (game.modeMenuIndex == 1) // Endless score
				{
					game.mode = GameModeFlags::EndlessScore;
					RestartGame(game);
					game.currentScreen = GameScreen::GAMEPLAY;
					return;
				}

				if (game.modeMenuIndex == 2) // Easy (no acceleration)
				{
					game.mode = GameModeFlags::EndlessScore | GameModeFlags::NoAcceleration;
					RestartGame(game);
					game.currentScreen = GameScreen::GAMEPLAY;
					return;
				}
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{

		switch (game.currentScreen)
		{
		case GameScreen::MAIN_MENU:
			DrawMainMenu(game, window);
			break;
		case GameScreen::MODE_SELECT:
			DrawModeSelect(game, window);
			break;
		case GameScreen::GAMEPLAY:
			DrawGameplay(game, window);
			break;
		case GameScreen::VICTORY:
			DrawVictoryScreen(game, window);
			break;
		case GameScreen::GAME_OVER:
			DrawGameOverScreen(game, window);
			break;
		}
	}

	void DrawGameplay(Game & game, sf::RenderWindow & window)
	{ 
		window.draw(game.background);
		DrawPlayer(game.player, window);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			DrawApple(game.apples[i], window);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			DrawRock(game.rocks[i], window);
		}
		DrawUI(game.uiState, window);

	}

	void UpdateModeSelect(Game& game, float deltaTime)
	{
		static bool wasUp = false;
		static bool wasDown = false;
		static bool wasEnter = false;
		static bool wasEsc = false;

		const bool upNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		const bool downNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		const bool enterNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		const bool escNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

		if (game.ignoreInput)
		{
			
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game.ignoreInput = false;
			}
			return;
		}

	
		if (game.isEnteringTarget)
		{
			if (escNow && !wasEsc)
			{
				game.isEnteringTarget = false;
				game.targetInput.clear();
			}

			wasUp = upNow;
			wasDown = downNow;
			wasEnter = enterNow;
			wasEsc = escNow;
			return;
		}

		
		if (upNow && !wasUp)
		{
			game.modeMenuIndex = (game.modeMenuIndex + 2) % 3;
		}
		if (downNow && !wasDown)
		{
			game.modeMenuIndex = (game.modeMenuIndex + 1) % 3;
		}

		
		if (enterNow && !wasEnter)
		{
			if (game.modeMenuIndex == 0)
			{
				// Finite target-Open popup
				game.isEnteringTarget = true;
				game.targetInput.clear();
			}
			else if (game.modeMenuIndex == 1)
			{
				// Endless score
				game.mode = GameModeFlags::EndlessScore;
				game.isEnteringTarget = false;
				game.targetInput.clear();

				RestartGame(game);
				game.currentScreen = GameScreen::GAMEPLAY;
			}
			else if (game.modeMenuIndex == 2)
			{
				// Easy: no acceleration + endless score
				game.mode = GameModeFlags::EndlessScore | GameModeFlags::NoAcceleration;
				game.isEnteringTarget = false;
				game.targetInput.clear();

				RestartGame(game);
				game.currentScreen = GameScreen::GAMEPLAY;
			}
		}

		if (escNow && !wasEsc)
		{
			game.currentScreen = GameScreen::MAIN_MENU;
		}

		wasUp = upNow;
		wasDown = downNow;
		wasEnter = enterNow;
		wasEsc = escNow;
	}

	void DrawModeSelect(const Game& game, sf::RenderWindow& window)
	{
		auto SetButtonState = [](sf::RectangleShape& btn, bool selected)
			{
				btn.setFillColor(selected ? sf::Color(90, 90, 90) : sf::Color(50, 50, 50));
			};

		SetButtonState(const_cast<sf::RectangleShape&>(game.modeButtonFinite), game.modeMenuIndex == 0);
		SetButtonState(const_cast<sf::RectangleShape&>(game.modeButtonEndless), game.modeMenuIndex == 1);
		SetButtonState(const_cast<sf::RectangleShape&>(game.modeButtonEasy), game.modeMenuIndex == 2);

		window.draw(game.startMenuSprite);
		window.draw(game.modeButtonFinite);
		window.draw(game.modeButtonEndless);
		window.draw(game.modeButtonEasy);

		window.draw(game.modeTextFinite);
		window.draw(game.modeTextEndless);
		window.draw(game.modeTextEasy);

		// Apple target input popup
		if (game.isEnteringTarget)
		{
			window.draw(game.targetPopup);
			window.draw(game.targetPopupTitle);

			sf::Text valueText = game.targetPopupValue;
			valueText.setString(game.targetInput.empty() ? "_" : game.targetInput);
			window.draw(valueText);

			window.draw(game.targetPopupHint);
		}
	}

	void InitLeaderboard(Game& game)
	{
		game.leaderboard.clear();

		static std::mt19937 rng{ std::random_device{}() };

		auto RandInt = [&](int a, int b)
			{
				std::uniform_int_distribution<int> dist(a, b);
				return dist(rng);
			};

		
		int total = RandInt(5, 10);
		int fakeCount = total - 1;

		
		static const std::string names[] = {
			"Alice","Bob","Carol","Dave","Eve","Frank","Grace","Heidi","Ivan","Judy"
		};

		
		for (int i = 0; i < fakeCount; i++)
		{
			std::string name = names[RandInt(0, 9)];
			int score = RandInt(10, 150);

			
			if (name == "Player") { i--; continue; }

			
			game.leaderboard.insert({ name, score });
		}

		
		game.leaderboard["Player"] = 0;
	}

	void UpdatePlayerScore(Game& game, int playerScore)
	{
		game.leaderboard["Player"] = playerScore;
	}
}