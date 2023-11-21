#pragma once
#include "raylib.h"
#include <string>

struct Vector2
{
	float x;
	float y;
};

struct Rectangle
{
	// Position
	float x;
	float y;

	// Size
	float width;
	float height;
};

enum AnimationState
{
	IDLE, WALK, JUMP,
};


struct Animation
{
	Texture2D* sprite_sheet = {};
	int Frames = 0;
	// I made this bool So I can pass to animation player if i want the animation to loop or not. This loop exist in animation as i load this data from file.
	bool animation_loop = false;
	
};

class AnimationPlayer
{
private:
	const Animation* current_animation = {};
	int frame_counter = 0;
	float framerate = 0;

	


public:
	AnimationState animation_state = IDLE;

	int current_frame = 0;
	Rectangle animation_rec{};       // This is source rectangle from sprite sheet helps rendering texture

	void StartAmination(const Animation* anim);
	void animation_update();
	void animation_render(const Vector2 & anim_pos);
};
