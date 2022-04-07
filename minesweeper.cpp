// minesweeper game
// table counted from 0
// different levels(simple --> hard)
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#define EASY_MAX 9
#define MEDIUM_MAX 16
#define TOUGH_MAX 24

#define EASY_BOMB 10
#define MEDIUM_BOMB 40
#define TOUGH_BOMB 99

/* ============Current Status============= */
/*  | 1 2 3 4 5 6 7 8 9 |1
----------------------2
1| X 2               |3
2| X 2               |4
3| X 2               |5
4| X 2               |6
5| X 2               |7
6| X 2               |8
7| X 2               |9
8| X 2               |1
9| X 2               |2
----------------------3
1234567891234567891234 */

using namespace std;

class grid{
public:
	bool is_opened=false;
	char data='-';
	int row=-1;
	int col=-1;
};

// FOREGROUND_RED|BACKGROUND_BLUE| ......
void change_font_color(WORD c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return;
}

// show table
void color_grid(string stats, char c){
    if(stats=="number"){  // green output
        change_font_color(FOREGROUND_GREEN);
        cout<<c;
        change_font_color(7);
    }
	else if(stats=="bomb"){
		change_font_color(FOREGROUND_RED);
        cout<<c;
        change_font_color(7);
	}else if(stats=="safe"){
		change_font_color(FOREGROUND_RED|FOREGROUND_GREEN);
        cout<<c;
        change_font_color(7);
	}
	else if(stats=="notopen"){
		change_font_color(7);
        cout<<c;
	}
    else{                     
        change_font_color(FOREGROUND_RED);
        cout<<"No matched stats instruction"<<endl;
        change_font_color(7);
    }
    return;
}

// show message
void show_message(string stats, string line, bool new_line){
    if(stats=="input"||stats=="info"){  // yellow output
        change_font_color(FOREGROUND_RED|FOREGROUND_GREEN);
        cout<<line;
        change_font_color(7);
    }                   
    else if(stats=="normal"){// normal white color
		cout<<line;
	}
    else{                     
        change_font_color(FOREGROUND_RED);
        cout<<"No matched stats instruction";
        change_font_color(7);
    }
	if(new_line)cout<<endl;
	return;
}

// game info 
void game_info(){
	show_message("info", "================MineSweeper================",true);
	show_message("normal", "> Easy mode to Tough mode", true);
	show_message("normal", "> Use bomb counts to analyze grid", true);
	show_message("normal", "> Sometimes, luck is important !!", true);
	show_message("info", "\n> creator: zardforever", true);
    show_message("info", "===========================================", true);
	system("pause");
	system("cls");
	show_message("info", "\n========Choose Mode========", true);
	show_message("normal", "> 1.Easy   (9*9)   10 bombs", true);
	show_message("normal", "> 2.Medium (16*16) 40 bombs", true);
	show_message("normal", "> 3.Tough  (24*24) 99 bombs", true);
	show_message("info", "===========================", true);
	return;
}

// yes or not
bool yes_or_not(const string ques){
    string input;
    while(true){
        show_message("info", ques, false);
        getline(cin, input);
        if(input=="Y"||input=="y")return true;
        else if(input=="n"||input=="N")return false;
        else show_message("normal", "failed: Only 'y' or 'n'", true);
    }
}

// get user input
string get_user_input(const string line, bool int_only, int min, int max){
	string input;
	bool okay=false;
	while(!okay){
		ENTER:
		show_message("input", line, false);
		getline(cin, input);
		if(input.size()==0){ //empty input
			show_message("normal", "failed: empty input", true);
			goto ENTER;
		}
		if(int_only){
			for(int i=0;i<input.size();i++){
				if(!isdigit(input[i])){
					show_message("normal", "failed: integer only", true);
					goto ENTER;
				}
				else if(i==input.size()-1)okay=true;
			}
			if(stoi(input)>max||stoi(input)<min){
				show_message("normal", "failed: invalid input", true);
				okay=false;
			}
		}
		else okay=true;
	}
	return input;
}

//generate bomb with given table
void generate_bomb(string game_mode, int max_size, vector<vector<grid>>& table){
	srand(time(NULL));
	int bomb_count=0, current=0;
	if(game_mode=="1")bomb_count=EASY_BOMB;
	else if(game_mode=="2")bomb_count=MEDIUM_BOMB;
	else bomb_count=TOUGH_BOMB;
	while(current!=bomb_count){
		int row=rand()%max_size;
		int col=rand()%max_size;
		if(table[row][col].data=='-'){
			table[row][col].data='X';
			current++;
		}
		else;
	}
	return;
}

// build game & initialize table
vector<vector<grid>> build_game(string game_mode){	
	if(game_mode=="1"){
		vector<vector<grid>> table(EASY_MAX, (vector<grid>(EASY_MAX)));
		generate_bomb(game_mode, EASY_MAX, table);
		return table;
	}
	else if(game_mode=="2"){
		vector<vector<grid>> table(MEDIUM_MAX, (vector<grid>(MEDIUM_MAX)));
		generate_bomb(game_mode, MEDIUM_MAX, table);
		return table;
	}
	else if(game_mode=="3"){
		vector<vector<grid>> table(TOUGH_MAX, (vector<grid>(TOUGH_MAX)));
		generate_bomb(game_mode, TOUGH_MAX,table);
		return table;
	}
	else{
		vector<vector<grid>> table;
		show_message("info", "failed: build_game error",true);
		return table;
	}
}

// print out table
void print_table(vector<vector<grid>> table){
	
	show_message("info", "============Current Status=============\n", true);
	for(int i=0;i<table.size();i++){
		for(int j=0;j<table.size();j++){
			color_grid("safe", table[i][j].data);
		}
		cout<<endl;
	}
	show_message("info", "=======================================", true);
}



void minesweeper(){
	game_info(); 
	string game_mode=get_user_input("\nChoose mode[1/2/3]: ", true, 1, 3);
	system("cls");
	vector<vector<grid>> table=build_game(game_mode);
	print_table(table);
	return;
}


int main(){
	bool again=true;
	while(again){
		minesweeper();
		again=yes_or_not("Do you want to continue?? [y/n] ");
		system("cls");
	}
	return 0;
}