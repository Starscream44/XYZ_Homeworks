#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct UIState
	{
		bool isGameOverTextVisible = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateUI(UIState& uiState, const struct Game& game, float timeDelta);
	void DrawUI(UIState& uiState, sf::RenderWindow& window);

	void InitMainMenu(Game& game);

	void UpdateMainMenu(Game& game);
	void DrawMainMenu(Game& game, sf::RenderWindow& window);

	void UpdateGameplay(Game& game, float deltaTime);
	void DrawGameplay(Game& game, sf::RenderWindow& window);

	void UpdateVictoryScreen(Game& game);
	void DrawVictoryScreen(Game& game, sf::RenderWindow& window);

	void UpdateGameOverScreen(Game& game);
	void DrawGameOverScreen(Game& game, sf::RenderWindow& window);


}
