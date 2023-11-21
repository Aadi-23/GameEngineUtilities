#pragma once
#include"raylib.h"
#include <iostream>
#include "CONSTANT.h"
#include "Level.h"
#include <fstream>
#include <vector>


struct HighscoreEntry
{
	char name[4];
	int score;
};


struct ScoreManager
{
	//Naming variable and methods
	bool mouse_on_rec = false;
	char nameInput[MAX_INPUT_CHAR + 1] = "\0";

	int letter_count = 0;

	Rectangle naming_box;

	void NamingBoxHandler();
	void Reset_NameBox();
	void Nameboxrender(const Level&level);


	// File writing and reading methods
	std::vector<HighscoreEntry>highscores;

	std::vector<HighscoreEntry>temp_highscore;
	

	void FileEditor(const Level& level);
	void FileReader(std::vector<HighscoreEntry>& v);


	// HighScore Table Render
	Rectangle Table_background;

	void ScoreSorting(std::vector<HighscoreEntry>&scorevector);
	void Add_highscore(const Level& level);
	void Highscore_table_render();

	void ResetBoard();

};
