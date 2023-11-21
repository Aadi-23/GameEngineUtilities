#pragma once
#include"ScoreManager.h"



void ScoreManager::Reset_NameBox()                // This is reset box function that i use to reset the box
{
	while (nameInput[0] != '\0')
	{
		letter_count--;
		if (letter_count < 0)
		{
			letter_count = 0;
		}
		nameInput[letter_count] = '\0';

	}

	
}

void ScoreManager::NamingBoxHandler()
{
	naming_box.width = 150;
	naming_box.height = 60;
	naming_box.x = (GetRenderWidth() - naming_box.width) / 2;
	naming_box.y = (GetRenderHeight() - naming_box.height) / 2;

	
	int key = GetCharPressed();

	while (key > 0)
	{
		// Key code that limits all alphabets and numbers
		int key_startpoint = 32;
		int key_endpoint = 125;

		if (key >= key_startpoint && key <= key_endpoint && letter_count < MAX_INPUT_CHAR)
		{
			nameInput[letter_count] = (char)key;
			nameInput[letter_count + 1] = '\0';
			letter_count++;
		}

		key = GetCharPressed();      // gets the key code of key pressed
	}

	if (IsKeyPressed(KEY_BACKSPACE))         // when backspace press clear the name box and array
	{
		letter_count--;
		if (letter_count < 0)
		{
			letter_count = 0;
		}
		nameInput[letter_count] = '\0';
	}


}

void ScoreManager::Nameboxrender(const Level& level)
{
	Vector2 title_text_pos = { 260, 80 };

	// Title text
	DrawText("Enter Name", (int)title_text_pos.x, (int)title_text_pos.y, 50, WHITE);


	// Score text
	Vector2 score_offset = { 40,70 };
	DrawText(TextFormat("Your Score: %i", level.score), (int)(title_text_pos.x + score_offset.x), (int)(title_text_pos.y + score_offset.y), 30, WHITE);

	// Other text
	DrawText("Press ENTER to Save", (int)(naming_box.x + score_offset.x)/2, (int)(naming_box.y + score_offset.y), 35, RAYWHITE);


	// The naming box
	DrawRectangleRec(naming_box, GRAY);

	Vector2 Text_offset = { 10,8 };

	// Naming in the box
	DrawText(nameInput, (int)(naming_box.x + Text_offset.x), (int)(naming_box.y + Text_offset.y), 40, MAROON);

	// This is title text accroding to the player won bool
	if (level.player_won)
	{
		DrawText("YOU WON!", (int)title_text_pos.x ,(int)(title_text_pos.y - score_offset.y), 50, WHITE);
	}
	else
	{
		DrawText("YOU LOSE!", (int)title_text_pos.x, (int)(title_text_pos.y - score_offset.y), 50, WHITE);
	}
}


void ScoreManager::Add_highscore(const Level& level)
{
	HighscoreEntry temp_score;
	std::strcpy(temp_score.name, nameInput);
	temp_score.score = level.score;

	if(temp_highscore.size()< 5)
	{

		temp_highscore.push_back(temp_score);
	}

	

	/* Addition to the vector when the list size is or greater.Here As I am sorting the vector before this function.
	 The smallest score will be at the bottom where i can compare the new score and add if it is greater than the bottom score.*/

	if (temp_highscore.size() >= 5)
	{
		if (temp_highscore[temp_highscore.size()-1].score < temp_score.score)
		{
			temp_highscore[temp_highscore.size()-1] = temp_score;
	

		}
	}

	// sorting the vector before writing in the file
	ScoreSorting(temp_highscore);

}



void ScoreManager::FileEditor(const Level& level)
{
	std::ofstream temp_file;
	temp_file.open("./Assets/highscore.txt", std::ios::out);

	Add_highscore(level);
	
	if (temp_file)
	{
		for (int i = 0; i < temp_highscore.size(); i++)
		{
			temp_file.write(reinterpret_cast<char*>(&temp_highscore[i].name), sizeof(char)* 4);
			temp_file.write(reinterpret_cast<char*>(&temp_highscore[i].score), sizeof(int));
		}
	}

	temp_file.close();
	
}

void ScoreManager::FileReader(std::vector<HighscoreEntry>&v)
{
	std::ifstream temp_file;
	temp_file.open("./Assets/highscore.txt", std::ios::in | std::ios::binary);
	
	highscores.clear();       // clearing the vector before reading into the vector

	while(!temp_file.eof())
	{
		HighscoreEntry temp_highscoreentry;
		temp_file.read(reinterpret_cast<char*>(temp_highscoreentry.name), sizeof(char)*4);
		temp_file.read(reinterpret_cast<char*>(&temp_highscoreentry.score), sizeof(int));

		if (temp_file.eof())
		{
			break;
		}

		v.push_back(temp_highscoreentry);

	}

	temp_file.close();
}



void ScoreManager::ScoreSorting(std::vector<HighscoreEntry>&scorevector)
{
	// Sorting algorithm
	for (int i = 0; i < scorevector.size(); i++)
	{
		for (int j = i + 1; j < scorevector.size(); j++)
		{
			if (scorevector[j].score > scorevector[i].score)
			{
				HighscoreEntry temp = scorevector[i];
				scorevector[i] = scorevector[j];
				scorevector[j] = temp;
			}
		}
	}
}

void ScoreManager::Highscore_table_render()
{
	// Rendering the table background
	const Vector2 offset = { 130,50 };
	Table_background.width = 280;
	Table_background.height = 300;
	Table_background.x = (GetRenderWidth() - Table_background.width) / 2;
	Table_background.y = (GetRenderHeight() - Table_background.height - offset.y);

	DrawRectangleRec(Table_background, LIGHTGRAY);

	// Tile in score screen
	DrawText("HIGHSCORES", (int)(GetRenderWidth()/2 - offset.x), (int)(GetRenderHeight() / 5 - offset.y), 40, WHITE);


	// This is the margin and offset of the text
	const Vector2 Text_margin = { 120, 55 };
	const float Text_offset_x = 60;


	// I made a for loop So I go through the vector and render all data with their offset and margin
	for(unsigned int i = 0; i < highscores.size(); i++)
	{
		Vector2 name_text_pos = { Table_background.x + Text_offset_x, Table_background.y + (Text_margin.y* (i) + GAMEFONT_SIZE )};
		
		DrawText(TextFormat(TextFormat("%i.", i+ 1)), (int)(name_text_pos.x - Text_offset_x/2), (int)name_text_pos.y, GAMEFONT_SIZE, WHITE);
		DrawText(highscores[i].name, (int)name_text_pos.x, (int)name_text_pos.y, GAMEFONT_SIZE, WHITE);
		

		DrawText(TextFormat("%i", highscores[i].score), (int)(name_text_pos.x + Text_margin.x), (int)name_text_pos.y, GAMEFONT_SIZE, WHITE);
	}
}


void ScoreManager::ResetBoard()
{
	temp_highscore.clear();
	highscores.clear();
	
	std::fstream temp_file;
	temp_file.open("./Assets/highscore.txt", std::ios::out);


	temp_file.clear();
	temp_file.close();

}