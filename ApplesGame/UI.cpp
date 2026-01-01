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
		uiState.inputHintText.setString("Use arrow keys to move!");
		uiState.inputHintText.setOrigin(GetTextOrigin(uiState.inputHintText, { 1.f, 0.f }));

	}

	void UpdateUI(UIState& uiState, const struct Game& game, float timeDelta)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		uiState.scoreText.setPosition(10.f, 10.f);
		window.draw(uiState.scoreText);

		uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(uiState.inputHintText);

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
				game.currentScreen = GameScreen::MODE_SELECT;
				game.ignoreInput = true;
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
				game.currentScreen = GameScreen::MODE_SELECT;
				game.mainMenuSelected = 0;
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
				game.currentScreen = GameScreen::MODE_SELECT;
				game.mainMenuSelected = 0;
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

	void InitModeSelect(Game& game)
	{
		const sf::Vector2f buttonSize(360.f, 60.f);
		const float startY = 260.f;
		const float spacing = 80.f;
		const float centerX = 400.f;

		// ---------- Finite apples ----------
		game.modeButtonFinite.setSize(buttonSize);
		game.modeButtonFinite.setOrigin(buttonSize.x / 2.f, buttonSize.y / 2.f);
		game.modeButtonFinite.setPosition(centerX, startY);
		game.modeButtonFinite.setFillColor(sf::Color(50, 50, 50));

		game.modeTextFinite.setFont(game.font);
		game.modeTextFinite.setString("Apples Target (5-30)");
		game.modeTextFinite.setCharacterSize(24);
		game.modeTextFinite.setFillColor(sf::Color::White);

		sf::FloatRect textRect = game.modeTextFinite.getLocalBounds();
		game.modeTextFinite.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
		game.modeTextFinite.setPosition(centerX, startY - 6.f);

		// ---------- Endless ----------
		game.modeButtonEndless.setSize(buttonSize);
		game.modeButtonEndless.setOrigin(buttonSize.x / 2.f, buttonSize.y / 2.f);
		game.modeButtonEndless.setPosition(centerX, startY + spacing);
		game.modeButtonEndless.setFillColor(sf::Color(50, 50, 50));

		game.modeTextEndless.setFont(game.font);
		game.modeTextEndless.setString("Endless Score");
		game.modeTextEndless.setCharacterSize(24);
		game.modeTextEndless.setFillColor(sf::Color::White);

		textRect = game.modeTextEndless.getLocalBounds();
		game.modeTextEndless.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
		game.modeTextEndless.setPosition(centerX, startY + spacing - 6.f);

		// ---------- Easy ----------
		game.modeButtonEasy.setSize(buttonSize);
		game.modeButtonEasy.setOrigin(buttonSize.x / 2.f, buttonSize.y / 2.f);
		game.modeButtonEasy.setPosition(centerX, startY + spacing * 2.f);
		game.modeButtonEasy.setFillColor(sf::Color(50, 50, 50));

		game.modeTextEasy.setFont(game.font);
		game.modeTextEasy.setString("Easy Mode (No Acceleration)");
		game.modeTextEasy.setCharacterSize(24);
		game.modeTextEasy.setFillColor(sf::Color::White);

		textRect = game.modeTextEasy.getLocalBounds();
		game.modeTextEasy.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
		game.modeTextEasy.setPosition(centerX, startY + spacing * 2.f - 6.f);

		// ---------- Popup ----------
		game.targetPopup.setSize(sf::Vector2f(420.f, 200.f));
		game.targetPopup.setOrigin(210.f, 100.f);
		game.targetPopup.setPosition(centerX, 300.f);
		game.targetPopup.setFillColor(sf::Color(20, 20, 20, 220));

		game.targetPopupTitle.setFont(game.font);
		game.targetPopupTitle.setString("Enter apples to win (5-30)");
		game.targetPopupTitle.setCharacterSize(22);
		game.targetPopupTitle.setFillColor(sf::Color::White);
		game.targetPopupTitle.setPosition(centerX - 170.f, 230.f);

		game.targetPopupValue.setFont(game.font);
		game.targetPopupValue.setCharacterSize(36);
		game.targetPopupValue.setFillColor(sf::Color::Yellow);
		game.targetPopupValue.setPosition(centerX - 20.f, 280.f);

		game.targetPopupHint.setFont(game.font);
		game.targetPopupHint.setString("Enter - confirm   Esc - cancel");
		game.targetPopupHint.setCharacterSize(18);
		game.targetPopupHint.setFillColor(sf::Color(150, 150, 150));
		game.targetPopupHint.setPosition(centerX - 150.f, 340.f);
	}

}

