#include "Game.h"


namespace ApplesGame
{

	void InitPlayer(Player& player, const Game& game)
	{
		// Init player state
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		// Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(OurVectorToSf(player.position));

		const sf::Vector2f spriteScale = (GetSpriteScale(player.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

		// We need to rotate and flip sprite to match player direction
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}
}
