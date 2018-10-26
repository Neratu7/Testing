#include <iostream>
#include <assert.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


#include "SDL2-2.0.8\include\SDL.h"
#include "SDL2-2.0.8\include\SDL_image.h"


#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2.lib")
#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2main.lib")
#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2_image.lib")
#pragma comment(linker,"/subsystem:console")


using namespace std;


namespace Game
{
	SDL_Renderer *renderer = NULL;
	int screen_width = 960;
	int screen_height = 768;

	SDL_Window *window = SDL_CreateWindow(
		"Fortnite",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width, screen_height, SDL_WINDOW_SHOWN);
}




void PullMap(int x, int y);
void TilePlacement(vector<vector<int>> &vect);
//SDL_Texture* Texture(const char* texture);
SDL_Texture* TexLoad(string path);
void initialize();
int numRow();
int numCol();


int pause;
//SDL_Texture* dirt;
//SDL_Texture* grass;
//SDL_Texture* sky;
//SDL_Texture* water;
//SDL_Texture* cloud;


struct tile
{
	int x;
	int y;
	int w;
	int h;
	int col;
	string name;
};




int main(int argc, char **argv)
{


	int rows = 0;
	int cols = 0;
	unsigned char prev_key_state[256];
	unsigned char *keys = (unsigned char*)SDL_GetKeyboardState(NULL);


	rows = numRow();
	cout << "********** " << rows << " **********" << endl;
	cols = numCol();
	cout << "********** " << cols << " **********" << endl;


	PullMap(cols, rows);
	bool done = false;
	while (!done)
	{
		memcpy(prev_key_state, keys, 256);

		SDL_Event event;


		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = true;
			}
		}

	}

	return 0;
}


////////////////////////////////


int numRow()
{
	std::ifstream bork("Art\\test2.txt");


	string data;
	int rowCount = 0;
	while (getline(bork, data))
	{
		rowCount++;
	}
	return rowCount;
}

int numCol()
{
	std::ifstream bork("Art\\test2.txt");

	string data;
	char derp;
	int colCount = 1;
	getline(bork, data);

	for (int i = 0; data[i]; i++)
	{
		if (data[i] == ',')
		{
			colCount++;
		}

	}
	return colCount;
}




void PullMap(int x, int y)
{

	ifstream infile("Art\\test2.txt");

	string line = "";

	vector<vector<int>> map;
	map.resize(y, std::vector<int>(x, 0));




	{


		string s;
		int b;


		for (int j = 0; j < y; j++)
		{




			for (int k = 0; k < x; k++)
			{
				getline(infile, s, ',');
				map[j][k] = stoi(s);


			}
		}

		cout << endl << "OUTY " << map[5][5] << endl;
		cout << map[4][3] << endl;
		cout << map[4][3] << " " << map[2][3] << " " << map[30][3] << " " << map[6][3] << " " << map[5][3] << " " << map[7][3] << " " << map[31][123] << endl;


		//cin >> pause;
		TilePlacement(map);
	}
}




void TilePlacement(vector<vector<int>> &vect)
{
	//cin >> pause;
	cout << vect[3][3] << endl;

	//string carp = 0;
	cout << "in tileplacement1" << endl;

	//cin >> pause;

	//Game::renderer = SDL_CreateRenderer(Game::window,
	//	-1, SDL_RENDERER_ACCELERATED);

	cin >> pause;

	//SDL_Renderer * renderer = SDL_CreateRenderer(Game::window, -1, 0);
	//SDL_Surface * image = IMG_Load("Art\\generic.png");
	//SDL_Texture * texture = SDL_CreateTextureFromSurface(Game::renderer, image);


	SDL_Texture * texture = TexLoad("double.png");//thing for loading textures
	Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED);//renderer for game
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 15, 15);

	int imgFlags = IMG_INIT_PNG;




	cout << "in tileplacement2" << endl;


	SDL_Rect src;
	src.x = 124;
	src.y = 124;
	src.w = 256;
	src.h = 256;


	SDL_Rect dest;
	dest.x = Game::screen_width / 2;
	dest.y = Game::screen_height / 2;
	dest.w = 64;
	dest.h = 64;



	SDL_RenderClear(Game::renderer);
	cout << " Renderer Cleared" << endl;
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
	cout << " Texture Copied " << endl;
	SDL_RenderPresent(Game::renderer);
	cout << " Renderer Applied" << endl;


	//if (carp == "dirt");
	//{
	//	cout << "in if dirt " << endl;

	//	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	//	SDL_RenderClear(Game::renderer);




	//	SDL_SetTextureAlphaMod(texture, 255);
	//	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
	//	SDL_RenderPresent(Game::renderer);


	//}

}



//SDL_Texture* Texture(const char* texture)
//{
//	SDL_Surface* tempSurface = IMG_Load(texture);
//	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
//	SDL_FreeSurface(tempSurface);
//
//	return tex;
//}


void initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	srand(time(0));

}



SDL_Texture* TexLoad(string path) //loads texture from path given, then returns texture
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	newTexture = SDL_CreateTextureFromSurface(Game::renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);


	cout << endl << "Texture Path: " << path << " Loaded!" << endl;
	return newTexture;

};

void end()
{
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(Game::window);
	Game::renderer = NULL;
	Game::window = NULL;

	IMG_Quit();
	SDL_Quit();

}


