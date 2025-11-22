#include "UI.h"
#include "Game.h"
#include <string>

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font)
	{
		uiState.scoreText.setFont(font);
		uiState.scoreText.setCharacterSize(24);
		uiState.scoreText.setFillColor(sf::Color::Yellow);

		uiState.inputHintText.setFont(font);
		uiState.inputHintText.setCharacterSize(24);
		uiState.inputHintText.setFillColor(sf::Color::White);
		uiState.inputHintText.setString("Use arrow keys to move! Eat 10 Apples");
		uiState.inputHintText.setOrigin(GetTextOrigin(uiState.inputHintText, { 1.f, 0.f }));

		uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(48);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setFillColor(sf::Color::Red);
		uiState.gameOverText.setString("GAME OVER");
		uiState.gameOverText.setOrigin(GetTextOrigin(uiState.gameOverText, { 0.5f, 0.5f }));
	}

	void UpdateUI(UIState& uiState, const struct Game& game, float timeDelta)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));

		uiState.isGameOverTextVisible = game.isGameFinished;
		sf::Color gameOverTextColor = (int)game.timeSinceGameFinish % 2 ? sf::Color::Red : sf::Color::Yellow;
		uiState.gameOverText.setFillColor(gameOverTextColor);
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		uiState.scoreText.setPosition(10.f, 10.f);
		window.draw(uiState.scoreText);

		uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(uiState.inputHintText);

		if (uiState.isGameOverTextVisible)
		{
			uiState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(uiState.gameOverText);
		}
	}

	void InitMainMenu(Game& game)
	{
		// START button
		game.menuButtonStart.setSize(sf::Vector2f(300.f, 60.f));
		game.menuButtonStart.setFillColor(sf::Color(50, 50, 50));
		game.menuButtonStart.setPosition(250.f, 400.f);

		game.menuTextStart.setFont(game.font);
		game.menuTextStart.setString("START");
		game.menuTextStart.setCharacterSize(32);
		game.menuTextStart.setFillColor(sf::Color::White);
		game.menuTextStart.setPosition(350.f, 410.f);

		// EXIT button
		game.menuButtonExit.setSize(sf::Vector2f(300.f, 60.f));
		game.menuButtonExit.setFillColor(sf::Color(50, 50, 50));
		game.menuButtonExit.setPosition(250.f, 500.f);

		game.menuTextExit.setFont(game.font);
		game.menuTextExit.setString("EXIT");
		game.menuTextExit.setCharacterSize(32);
		game.menuTextExit.setFillColor(sf::Color::White);
		game.menuTextExit.setPosition(365.f, 510.f);

		// RESTART button 
		game.menuButtonRestart.setSize(sf::Vector2f(300.f, 60.f));
		game.menuButtonRestart.setFillColor(sf::Color(50, 50, 50));
		game.menuButtonRestart.setPosition(250.f, 400.f);

		game.menuTextRestart.setFont(game.font);
		game.menuTextRestart.setString("RESTART");
		game.menuTextRestart.setCharacterSize(32);
		game.menuTextRestart.setFillColor(sf::Color::White);
		game.menuTextRestart.setPosition(330.f, 410.f);
	}

	void UpdateMainMenu(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			game.mainMenuSelected = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			game.mainMenuSelected = 1;

		// Enter selection
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (game.mainMenuSelected == 0)
			{
				game.currentScreen = GameScreen::GAMEPLAY;
				RestartGame(game);
			}
			else if (game.mainMenuSelected == 1)
			{
				exit(0);
			}
		}
	}
	void DrawMainMenu(Game& game, sf::RenderWindow& window)
	{
		if (game.mainMenuSelected == 0)
		{

			game.menuButtonStart.setFillColor(sf::Color(100, 100, 100));
			game.menuButtonExit.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			game.menuButtonStart.setFillColor(sf::Color(50, 50, 50));
			game.menuButtonExit.setFillColor(sf::Color(100, 100, 100));
		}

		window.draw(game.startMenuSprite);
		window.draw(game.menuButtonStart);
		window.draw(game.menuButtonExit);
		window.draw(game.menuTextStart);
		window.draw(game.menuTextExit);
	}

	void UpdateVictoryScreen(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			game.mainMenuSelected = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			game.mainMenuSelected = 1;

		// Enter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (game.mainMenuSelected == 0)
			{
				game.currentScreen = GameScreen::GAMEPLAY;
				RestartGame(game);
			}
			else if (game.mainMenuSelected == 1)
			{
				exit(0);
			}
		}

	}
	void DrawVictoryScreen(Game& game, sf::RenderWindow& window)
	{
		if (game.mainMenuSelected == 0)
		{
			game.menuButtonRestart.setFillColor(sf::Color(100, 100, 100));
			game.menuButtonExit.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			game.menuButtonRestart.setFillColor(sf::Color(50, 50, 50));
			game.menuButtonExit.setFillColor(sf::Color(100, 100, 100));
		}


		window.draw(game.winSprite);
		window.draw(game.menuButtonRestart);
		window.draw(game.menuButtonExit);

		window.draw(game.menuTextRestart);
		window.draw(game.menuTextExit);
	}

	void UpdateGameOverScreen(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			game.mainMenuSelected = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			game.mainMenuSelected = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (game.mainMenuSelected == 0)
			{
				game.currentScreen = GameScreen::GAMEPLAY;
				RestartGame(game);
			}
			else if (game.mainMenuSelected == 1)
			{
				exit(0);
			}
		}
	}
	void DrawGameOverScreen(Game& game, sf::RenderWindow& window)
	{
		if (game.mainMenuSelected == 0)
		{
			game.menuButtonRestart.setFillColor(sf::Color(100, 100, 100));
			game.menuButtonExit.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			game.menuButtonRestart.setFillColor(sf::Color(50, 50, 50));
			game.menuButtonExit.setFillColor(sf::Color(100, 100, 100));
		}

		window.draw(game.gameOverSprite);
		window.draw(game.menuButtonRestart);
		window.draw(game.menuButtonExit);

		window.draw(game.menuTextRestart);
		window.draw(game.menuTextExit);
	}

}

