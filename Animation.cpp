#include "Animation.h"

void AnimationPlayer::StartAmination(const Animation* anim)
{
	int game_FPS = 60
	current_animation = anim;
	framerate = (float)(game_FPS / (anim->Frames*2));       
	animation_rec = { 0,0, (float)(anim->sprite_sheet->width / anim->Frames), (float)anim->sprite_sheet->height };
	current_frame = 0;

}

void AnimationPlayer::animation_update()
{
	frame_counter++;
	
	if (frame_counter >= framerate)
	{
		
		// This part i use to handle my animation looping. It stops updating framecounter as it reaches to the last frame of the spritesheet
		if (current_frame < current_animation->Frames - 1 || current_animation->animation_loop)
		{
			current_frame++;
			frame_counter = 0;
		}

		
		// This part resets the cerrentframe to beginining So animation can loop
		if (current_frame > current_animation->Frames - 1 && current_animation-> animation_loop)
		{
 			current_frame = 0;
		}

		// Updating the position of source rectangle. for my animation
		animation_rec.x = (float)(current_frame * (current_animation->sprite_sheet->width / current_animation->Frames));
	}
	
	

	

}

void AnimationPlayer::animation_render(const Vector2& anim_pos)
{
	DrawTextureRec(*current_animation->sprite_sheet, animation_rec, anim_pos, WHITE);
}