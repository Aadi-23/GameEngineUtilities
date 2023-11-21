#pragma once
#include "raylib.h"
#include "Entity.h"
#include <iostream>


struct Player
{
	Vector2 Player_center = { 0,0 };
	
	
	Vector2 position{};
	Vector2 size{};
	Vector2 velocity{};
	Color color = WHITE;
	
	int health = 3;

	bool isMoving = false;

	bool dead = false;

	double hurtStartTime = 0.0f;

	bool isHurt = false;

	bool canMove{};
};

class PlayerController
{
public:
	static Player player;

	Animation player_run_animation;
	Animation player_jump_animation;
	AnimationPlayer player_animation_player;

	bool onGround = false;
	bool canJump = true;

	void PlayerSpawner(Player & player);
	void playerMovement();

	void SetPlayerName(const std::string& name);
	const std::string& GetPlayerName() const;

	void playerRender();
	void playerUpdate();

private:
	std::string playerName;
};