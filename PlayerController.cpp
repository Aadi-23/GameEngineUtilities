#pragma once
#include "raylib.h"
#include "PlayerController.h"
#include "ResourceManager.h"
#include "myMath.h"
#include <cmath>

Player PlayerController:: player;

void PlayerController::PlayerSpawner(Player & player)
{
	player.size = {PLAYERSIZE};
	player.position = { PLAYERXPOS,  PLAYERYPOS};
	player.canMove = true;
	player.velocity = { 0,0 };
	player.color = RED;


}


void PlayerController::playerMovement()
{
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		player.velocity.x = -PLAYERSPEED * FRICTION;
		player.isMoving = true;

		if (player_animation_player.animation_rec.width > 0)
		{
			player_animation_player.animation_rec.width *= -1;
		}
	}
	else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		player.velocity.x = PLAYERSPEED * FRICTION;
		player.isMoving = true;

		if (player_animation_player.animation_rec.width < 0)
		{
			player_animation_player.animation_rec.width *= -1;
		}
	}
	else
	{
		player.velocity.x = 0;
		player.isMoving = false;

	}

	//JUMP STUFF
	if (IsKeyPressed(KEY_SPACE) && canJump)
	{
		player.velocity.y = -PLAYERSPEED;
		onGround = false;

	}
	if (IsKeyDown(KEY_SPACE) && player.velocity.y <= PLAYERSPEED)
	{
		player.velocity.y -= PLAYERSPEED * 0.01f;
	}

	if (IsKeyReleased(KEY_SPACE))
	{
		canJump = false;
	}
	
    player.velocity += GRAVITY * GetFrameTime();
	
}



void PlayerController::playerUpdate()
{
	playerMovement();

	if (player.health <= 0)
	{
		player.dead = true;
	}
}

void PlayerController::SetPlayerName(const std::string& name)
{
	playerName = name;
}

const std::string& PlayerController::GetPlayerName() const 
{
	return playerName;
}


void PlayerController::playerRender()
{
	

	switch (player_animation_player.animation_state)
	{
	case(IDLE):
	{
		DrawTextureV(ResourceManager::textures.player_texture, player.position, WHITE);

		if (player.isMoving && onGround)
		{
			player_animation_player.animation_state = WALK;
			player_animation_player.StartAmination(&player_run_animation);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			player_animation_player.animation_state = JUMP;
			player_animation_player.StartAmination(&player_jump_animation);
		}
	}
	break;

	case(WALK):
	{
		player_animation_player.animation_update();
		player_animation_player.animation_render(player.position);

		if (IsKeyPressed(KEY_SPACE))
		{
			player_animation_player.animation_state = JUMP;
			player_animation_player.StartAmination(&player_jump_animation);
		}

		if (!player.isMoving)
		{
			player_animation_player.animation_state = IDLE;
		}
	}
	break;

	case(JUMP):
	{
		player_animation_player.animation_update();
		player_animation_player.animation_render(player.position);

		if (onGround)
		{
			player_animation_player.animation_state = IDLE;
		}
	}
	break;
	}
}