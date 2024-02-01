#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <io.h>
#include <fcntl.h>
#pragma execution_character_set("utf-8")

struct profile {
	char UserName[40];
	char Password[40];
	char email[40];
};
void game_play_map_3();
void game_play_map_2();
void game_play_map_1();
void shape_Map(wchar_t map[24][112],bool ghalb);
void signin_player2(int loc_player_1);
void change_email(int loc, char * username);
void Change_Username(int loc);
void changepass_1(int loc,char*username);
void game_menu(char* username);
void Change_profile(char* username);
void changepass(char* email, int loc);
void forgetpass();
void menu_inform();
int Username_checker(const char const* username);
void signup();
void start_page();
void signin();
////////////////////////////
#define PLAYER1_UP 'W'
#define PLAYER1_DOWN 'S'
#define PLAYER1_LEFT 'A'
#define PLAYER1_RIGHT 'D'
#define PLAYER1_SHOOT 'C'

#define PLAYER2_UP 'I'
#define PLAYER2_DOWN 'K'
#define PLAYER2_LEFT 'J'
#define PLAYER2_RIGHT 'L'
#define PLAYER2_SHOOT 'N'

//COORD structure represents the coordinates of a character cell in the console screen buffer
COORD moveDirection(COORD position, int dx, int dy) {
	position.X += dx;
	position.Y += dy;
	return position;
}

BOOL keyPressed(int key) {
	//This function returns a short integer that indicates whether a particular key is pressed or not.
	return GetAsyncKeyState(key);
	//returns a non-zero value if the key is currently pressed. If not, it will return 0.
}



void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

///////////////////////////make color
void magneta() {
	printf("\033[1;35m");
}
void yellow() {
	printf("\033[1;33m");
}
void blue() {
	printf("\033[1;34m");
}
void black() {
	printf("\033[1;30m");
}
void green() {
	printf("\033[1;32m");
}
void white() {
	printf("\033[1;37m");
}
void cyan() {
	printf("\033[1;36m");
}
void red() {
	printf("\033[1;31m");
}
void reset() {
	printf("\033[0m");
}
///////////////////////////////////////////////
void start_page() {
	system("color 40");
	yellow();
	printf("Space war");
    reset();
	Sleep(1000);
	system("cls");

	menu_inform();
}

void menu_inform() {
	int selected=1;
	int keypress;
	int p = 45;
	int p1 = 62;
	
		while (1) {
		printf("Hello\n");
			cyan();
		if (selected == 1)
		printf("%c%c",p,p1);
		printf("1.sign in\n");
		reset();
		green();
		if (selected == 2)
			printf("%c%c", p, p1);
		printf("2.sign up\n");
		reset;
		red();
		if (selected == 3)
			printf("%c%c", p, p1);
		printf("3.Exit\n");
		reset();
		keypress = _getch();
		if (keypress == 72 && selected > 1) {
			selected--;}
		else if (keypress == 80 && selected <3) {
			selected++;
		}
		else if (keypress == 13) {
			break;
		}
		system("cls");

	}
		switch (selected)
		{
		case 1:
			signin();
			break;
		case 2:
			signup();
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}




}

void signup() {
	system("cls");
	profile prof;
	char pass[40];
	FILE * Prof_Data;
	char username[40];
	Prof_Data = fopen("profile.bin", "a");
	system("color 70");
	printf("\t\tsign up page\n\n");
	///////////////////////////////////////////////////
	printf("Enter Your UserName=");
	magneta();
	scanf("%s", username);
	reset();
	system("color 70");
	while (1) {
		if (Username_checker(username) >= 1) {
			system("cls");
			printf("Your Username is already taken\n");
			magneta();
			printf("Please another Enter UserName=");
			reset();
			system("color 70");
			scanf("%s", username);
		}
		else {
			strcpy(prof.UserName, username);
			break;
		}
	}
	system("cls");
	/////////////////////////////////////////// /
	system("color 7d");
	printf("\t\tsign up page\n\n");
	printf("Enter Your Password=");
	blue();
	scanf("%s", pass);
	reset();
	system("color 7d");
	while (1)
	{
		if (strlen(pass) < 8) {
			system("cls");
			printf("\t\tsign up page\n\n");
			printf("Your Password is Too Short \nEnter Other Password=");
			blue();
			scanf("%s", pass);
			reset();
		}
		else {
			strcpy(prof.Password, pass);
			break;
		}
	}
	printf("Enter Your Password Again=");
	blue();
	scanf("%s",pass);
	reset();
	
	while (1)
	{
		if (strcmp(pass,prof.Password)!=0) {

			printf("Your Passwords isn,t same\nEnter Password Again=");
			blue();
			scanf("%s", pass);
			reset();
			system("color 7d");
		}
		else {
			break;
		}
	}
	/////////////////////////////////////
	char email[40];
	system("cls");
	printf("\t\tsign up page\n\n");
	printf("\nEnter Your Email=");
	magneta();
	scanf("%s", email);
	reset();
	system("color 70");
	while (1)
	{
		char a[3] = { "@" };
		if (strstr(email,a) == NULL) {
			system("cls");
			magneta();
			printf("Your Email is Wrong \nEnter Other Email=");
			reset();
			system("color 70");
			scanf("%s", pass);
		}
		else {
			strcpy(prof.email, email);
			break;
		}
	}
//////////////////////////////////////////////////////
	while (1) {
		if (Prof_Data == NULL) {
			Prof_Data = fopen("profile.bin", "a");
		}
		else {
			fwrite(&prof, sizeof(profile), 1, Prof_Data);
			break;
		}

	}
	fclose(Prof_Data);
	system("cls");
	printf("Your sign up is successful\n Now you can sign in");
	Sleep(1200);
	system("cls");
	signin();
}

int Username_checker(const char const * username){
	int i = 1;
	int returnere = 0;
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	for (int j = 1; j < i; j++) {
		if (strcmp(User_data[j].UserName, username) == 0)
			return j;
		else
			returnere = 0;
	}
	fclose(Data);
	return returnere;
}

int passfinder(const int loc,char * pass) {
	int i = 1;
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	if (strncmp(User_data[loc].Password, pass, strlen(User_data[loc].Password))==0) {
		return 0;
	}
	else {
		return 1;
	}
	fclose(Data);
	

}

void signin() {
	char pass1;
	int i = 0;
	char username[40];
	char pass[40];
	system("cls");
	system("color 81");
	printf("\t\tSign in page\n");
	system("color 85");
	printf("Enter Your UserName=");
	yellow();
	scanf("%s", username);
	reset();
	system("cls");
	system("color 71");
	blue();
	printf("\t\tSign in page\n");
	reset();
	system("color 71");
	magneta();
	printf("Enter Your Password=");
	reset();
	while ((pass1 = _getch()) != '\r') {
		pass[i] = pass1;
		i++;
	yellow();
		printf("*");
	reset();
	}
	system("cls");
		system("color 00");
	if (Username_checker(username) >= 1&&passfinder(Username_checker(username),pass)==0)
	{
		game_menu(username);
	}
	else {
		system("color 01");
		printf("\t\tSign in page\n");
		system("color 00");
		printf("!!!!!!!!!!!!!Your Username or password is Wrong please try again!!!!!!!!!!!!!!!");
		Sleep(1000);
		system("cls");
		int selected = 1;
		int keypress;
		int p = 45;
		int p1 = 62;
		while (1) {
			yellow();
			printf("\t\tMenu\n");
			reset();
			red();
			if (selected == 1)
				printf("%c%c", p, p1);
			printf("1.Forgot password\n\n");
			reset();
			green();
			if (selected == 2)
			printf("%c%c", p, p1);
			printf("2.Using Password&Username\n\n");
			reset;
			blue();
			if (selected == 3)
				printf("%c%c", p, p1);
			printf("3.Sign Up\n");
			reset;

			keypress = _getch();
			if (keypress == 72 && selected > 1) {
				selected--;
			}
			else if (keypress == 80 && selected < 3) {
				selected++;
			}
			else if (keypress == 13) {
				break;
			}
			system("cls");

		}
		switch (selected)
		{
		case 1:
			forgetpass();
			break;
		case 2:
			signin();
			break;
		case 3:
			signup();
		default:
			break;
		}
	}


}

void forgetpass() {
	system("cls");
	char Username[40];
	char Email[40];
	cyan();
	printf("\t\tForget Password Page\n");
	reset();
	magneta();
	printf("Enter your UserName=");
	reset;
	green();
	scanf("%s", Username);
	reset;
	system("cls");
	if (Username_checker(Username) != 0) {
		cyan();
		printf("\t\tForget Password Page\n");
		reset();
		printf("Enter Your Email=");
			red();
			scanf("%s", Email);
			reset();
			system("cls");
	changepass(Email,Username_checker(Username));
	}
	else {
		printf("!!!!!!!!Username isn,t correct!!!!!!!!!!\n");
		forgetpass();
	}
}

void changepass(char * email,int loc) {
	int i = 1;
	char newpass[40];
	char newpass1[40];
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	fclose(Data);
	if (strncmp(User_data[loc].email, email, strlen(User_data[loc].email)) == 0) {
		cyan();
		printf("\t\tChange password page\n\n");
		reset();
		yellow();
		printf("Enter your New password=");
		scanf("%s", newpass);
		reset();
		while (1)
		{
			if (strlen(newpass) < 8) {
				system("cls");
				printf("\t\tChange password page\n\n");
				printf("Your Password is Too Short \nEnter Other Password=");
				blue();
				scanf("%s", newpass);
				reset();
			}
			else {
				break;
			}
		}
		red();
		printf("Enter password Again=");
		scanf("%s", newpass1);
		if (strcmp(newpass, newpass1) == 0) {
			strcpy(User_data[loc].Password, newpass);
			Data = fopen("profile.bin", "wb");
			while (Data==NULL) {
				Data = fopen("profile.bin", "wb");
			}
			for (int j = 1; j <= i ; j++) {
				fwrite(&User_data[j], sizeof(profile), 1, Data);
			}
				fclose(Data);
					signin();
		}
		else {
			system("cls");
			cyan();
			printf("\t\tChange password page\n\n");
			reset();
			printf("!!!!!!!Passwords Are NOT Same!!!!!!!!!");
			Sleep(1200);
			system("cls");
			changepass(email, loc);
		}
		//fseek(Data, sizeof(profile) * (loc - 1), SEEK_SET);
	}
	else {
		red();
		printf("\t\tYour Email isn,t correct!!!!!!!\n");
		Sleep(1200);
		reset();
		forgetpass();
	}
	






}

void game_menu(char * username) {
	int selected = 1;
	int keypress;
	int p = 45;
	int p1 = 62;

	while (1) {
		printf("Game menu\n");
		cyan();
		if (selected == 1)
			printf("%c%c", p, p1);
		printf("1.Start\n");
		reset();
		green();
		if (selected == 2)
			printf("%c%c", p, p1);
		printf("2.Change Profile information\n");
		reset;
		red();
		if (selected == 3)
			printf("%c%c", p, p1);
		printf("3.History\n");
		reset();
		magneta();
		if (selected == 4)
			printf("%c%c", p, p1);
		printf("4.Return To Main Menu\n");
		keypress = _getch();
		if (keypress == 72 && selected > 1) {
			selected--;
		}
		else if (keypress == 80 && selected < 4) {
			selected++;
		}
		else if (keypress == 13) {
			break;
		}
		system("cls");

	}
	switch (selected)
	{
	case 1:
		signin_player2(Username_checker(username));                                                //start
		break;
	case 2:
		Change_profile(username);
		break;
	case 3:
		;                                                                      ///history
		break;
	case 4:
		system("cls");
		menu_inform();
		break;
	default:
		break;
	}



}

void Change_profile(char * username) {
	system("cls");
	int selected = 1;
	int keypress;
	int p = 45;
	int p1 = 62;
	int loc = Username_checker(username);
	while (1) {
		printf("Change profile\n");
		cyan();
		if (selected == 1)
			printf("%c%c", p, p1);
		printf("1.Change password\n");
		reset();
		green();
		if (selected == 2)
			printf("%c%c", p, p1);
		printf("2.Change Username\n");
		reset;
		red();
		if (selected == 3)
			printf("%c%c", p, p1);
		printf("3.Change Email\n");
		reset();
		keypress = _getch();
		if (keypress == 72 && selected > 1) {
			selected--;
		}
		else if (keypress == 80 && selected < 4) {
			selected++;
		}
		else if (keypress == 13) {
			break;
		}
		system("cls");

	}
	switch (selected)
	{
	case 1:
		changepass_1(loc,username);                                                        
		break;
	case 2:
		Change_Username(loc);
		break;
	case 3:
		change_email(loc,username);
		break;
	default:
		break;
	}
}

void changepass_1(int loc,char * username) {
	system("cls");
	int i = 1;
	char newpass[40];
	char newpass1[40];
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	fclose(Data);
		cyan();
		printf("\t\tChange password page\n\n");
		reset();
		yellow();
		printf("Enter your New password=");
		scanf("%s", newpass);
		reset();
		while (1)
		{
			if (strlen(newpass) < 8) {
				system("cls");
				printf("\t\tChange password page\n\n");
				printf("Your Password is Too Short \nEnter Other Password=");
				blue();
				scanf("%s", newpass);
				reset();
			}
			else {
				break;
			}
		}
		red();
		printf("Enter password Again=");
		scanf("%s", newpass1);
		if (strcmp(newpass, newpass1) == 0) {
			strcpy(User_data[loc].Password, newpass);
			Data = fopen("profile.bin", "wb");
			while (Data == NULL) {
				Data = fopen("profile.bin", "wb");
			}
			for (int j = 1; j <= i; j++) {
				fwrite(&User_data[j], sizeof(profile), 1, Data);
			}
			fclose(Data);
			game_menu(username);
		}
		else {
			system("cls");
			cyan();
			printf("\t\tChange password page\n\n");
			reset();
			printf("!!!!!!!Passwords Are NOT Same!!!!!!!!!");
			Sleep(1200);
			system("cls");
			changepass_1(loc, username);
		}
}

void Change_Username(int loc) {
	system("cls");
	int i = 1;
	char newUsername[40];
	//char newUsername1[40];
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	fclose(Data);
	cyan();
	printf("\t\tChange UserName page\n\n");
	reset();
	yellow();
	printf("Enter your New UserName=");
	scanf("%s", newUsername);
	reset();
	while (1)
	{
		if (Username_checker(newUsername) > 0) {
			system("cls");
			printf("\t\tChange UseName page\n\n");
			printf("Your Username Was already Token \nEnter Other Username=");
			blue();
			scanf("%s", newUsername);
			reset();
		}
		else {
			break;
		}
	}
		strcpy(User_data[loc].UserName, newUsername);
		Data = fopen("profile.bin", "wb");
		while (Data == NULL) {
			Data = fopen("profile.bin", "wb");
		}
		for (int j = 1; j <= i; j++) {
			fwrite(&User_data[j], sizeof(profile), 1, Data);
		}
		fclose(Data);
		system("cls");
		game_menu(newUsername);
}

void change_email(int loc, char * username){
	system("cls");
	int i = 1;
	char newEmail[40];
	//char newUsername1[40];
	FILE* Data;
	Data = fopen("profile.bin", "rb");
	profile User_data[50];
	while (!feof(Data)) {
		fread(&User_data[i], sizeof(profile), 1, Data);
		i++;
	}
	fclose(Data);
	cyan();
	printf("\t\tChange Email page\n\n");
	reset();
	yellow();
	printf("Enter your New Email=");
	scanf("%s", newEmail);
	reset();
	while (1)
	{
		if (Username_checker(newEmail) > 0) {
			system("cls");
			printf("\t\tChange UseName page\n\n");
			printf("Your Username Was already Token \nEnter Other Username=");
			blue();
			scanf("%s", newEmail);
			reset();
		}
		else {
			break;
		}
	}
	strcpy(User_data[loc].email, newEmail);
	Data = fopen("profile.bin", "wb");
	while (Data == NULL) {
		Data = fopen("profile.bin", "wb");
	}
	for (int j = 1; j <= i; j++) {
		fwrite(&User_data[j], sizeof(profile), 1, Data);
	}
	fclose(Data);
	system("cls");
	game_menu(newEmail);
}

void signin_player2(int loc_player_1) {
	char pass1;
	int i = 0;
	char username[40];
	char pass[40];
	system("cls");
	system("color 81");
	printf("\t\tSign in page  :  player 2\n");
	system("color 85");
	printf("Enter Your UserName=");
	yellow();
	scanf("%s", username);
	reset();
	system("cls");
	system("color 71");
	blue();
	printf("\t\tSign in page  :  player 2\n");
	reset();
	system("color 71");
	magneta();
	printf("Enter Your Password=");
	reset();
	while ((pass1 = _getch()) != '\r') {
		pass[i] = pass1;
		i++;
		yellow();
		printf("*");
		reset();
	}
	system("cls");
	system("color 00");

	int loc_player_2 = Username_checker(username);

	if (Username_checker(username) >= 1 && passfinder(Username_checker(username), pass) == 0)
	{
	
		game_play_map_1();
	}
	else {
		signin_player2(loc_player_1);
	}


}

void shape_Map(wchar_t map[24][112], bool ghalb) {

	SetConsoleOutputCP(65001);
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 112; j++) {
			map[i][j] = L' ';
		}

	}

	for (int i = 0; i < 24; i++) {
		map[i][0] = L'█';
	}
	for (int i = 0; i < 112; i++) {
		map[0][i] = L'█';
	}
	for (int i = 0; i < 112; i++) {
		map[23][i] = L'█';
	}
	for (int i = 0; i < 24; i++) {
		map[i][111] = L'█';
	}
	///////////////////////////
	for (int i = 12; i < 20; i++) {

		map[4][i] = L'█';

	}
	for (int i = 4; i < 16; i++) {
		map[i][19] = L'█';
	}



	for (int i = 19; i > 12; i--) {
		map[16][i] = L'█';
	}
	map[5][20] = L'║';
	map[6][20] = L'║';

	map[15][20] = L'║';
	map[14][20] = L'║';
	map[2][27] = L'█';
	map[3][27] = L'█';
	map[2][28] = L'║';
	map[3][28] = L'║';

	map[18][27] = L'█';
	map[19][27] = L'█';
	for (int i = 5; i < 16; i++) {
		if (i == 10)
			map[i][56] = L'║';
		else
			map[i][56] = L'█';
	}


	for (int i = 50; i > 40; i--) {
		map[14][i] = L'█';
	}
	for (int i = 62; i < 72; i++) {
		map[6][i] = L'█';
	}
	//////////////////
	for (int i = 99; i > 91; i--) {
		map[4][i] = L'█';
	}

	for (int i = 4; i < 16; i++) {
		map[i][92] = L'█';
	}
	for (int i = 92; i < 100; i++) {
		map[16][i] = L'█';
	}
	map[5][91] = L'║';
	map[6][91] = L'║';


	map[15][91] = L'║';
	map[14][91] = L'║';

	map[2][84] = L'█';
	map[3][84] = L'█';
	map[18][83] = L'║';
	map[19][83] = L'║';

	map[18][84] = L'█';
	map[19][84] = L'█';

	int m = 0;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 112; j++) {
			if (i == 4 && j == 55 && ghalb==1) {
				map[i][j] = L'❤';
				wprintf(L"%wc", map[i][j]);
			}
			else if (j == 11 && i == 19) {
				map[i][j] = L'֍';
				wprintf(L"\033[1;33m֍\033[0m");
			}
			else if (j == 101 && i == 19) {
				map[i][j] = L'֍';
				wprintf(L"\033[1;33m֍\033[0m");
			}
			else if (i == 17 && j == 29) {
				map[i][j] = L'෧';
				wprintf(L"\033[1;37m෧\033[0m");
			}
			else if (i == 3 && j == 88) {
				map[i][j] = L'෧';
				wprintf(L"\033[1;37m෧\033[0m");
			}
			else
				wprintf(L"%wc", map[i][j]);

		}
		wprintf(L"\n");

	}

	_setmode(_fileno(stdout), _O_TEXT);
}
void shape_Map_2() {
	SetConsoleOutputCP(65001);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wchar_t map_2[24][112];
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 112; j++) {
			map_2[i][j] = L' ';
		}
	}
	///////////////////dor kesh
	for (int i = 0; i < 24; i++) {
		map_2[i][0] = L'█';
	}
	for (int i = 0; i < 112; i++) {
		map_2[0][i] = L'█';
	}
	for (int i = 0; i < 112; i++) {
		map_2[23][i] = L'█';
	}
	for (int i = 0; i < 24; i++) {
		map_2[i][111] = L'█';
	}
	//////////////////////////////khat chi
	for (int i = 7; i < 14; i++)
		map_2[i][12] = L'║';

	for (int i = 7; i < 14; i++)
		map_2[i][99] = L'║';

	map_2[3][86] = L'█';
	map_2[4][86] = L'█';
	map_2[4][85] = L'║';

	map_2[3][25] = L'█';
	map_2[4][25] = L'█';
	map_2[3][26] = L'║';


	map_2[19][86] = L'█';
	map_2[18][86] = L'█';
	map_2[19][85] = L'║';



	map_2[19][25] = L'█';
	map_2[18][25] = L'█';
	map_2[18][26] = L'║';

	map_2[5][57] = L'█';
	map_2[5][56] = L'█';
	map_2[5][55] = L'█';

	map_2[7][56] = L'█';
	map_2[8][56] = L'█';
	map_2[8][55] = L'█';
	map_2[8][54] = L'█';
	map_2[8][53] = L'█';
	map_2[9][53] = L'█';
	map_2[10][53] = L'█';
	map_2[10][52] = L'█';
	map_2[10][51] = L'█';
	map_2[10][60] = L'█';
	map_2[10][61] = L'█';
	map_2[10][62] = L'█';
	map_2[11][60] = L'█';
	map_2[12][60] = L'█';
	map_2[12][59] = L'█';
	map_2[12][58] = L'█';
	map_2[12][57] = L'█';
	map_2[12][56] = L'█';
	map_2[13][56] = L'█';
	map_2[16][56] = L'█';
	map_2[16][57] = L'█';
	map_2[16][55] = L'█';
	map_2[10][54] = L'║';
	map_2[11][39] = L'║';
	map_2[9][74] = L'║';



	map_2[7][42] = L'█';
	map_2[7][41] = L'█';
	map_2[8][40] = L'█';
	map_2[8][39] = L'█';
	map_2[9][38] = L'█';
	map_2[9][37] = L'█';
	map_2[10][36] = L'█';
	map_2[10][35] = L'█';
	map_2[11][37] = L'█';
	map_2[11][38] = L'█';
	map_2[12][39] = L'█';
	map_2[12][40] = L'█';
	map_2[13][41] = L'█';
	map_2[13][42] = L'█';




	map_2[7][71] = L'█';
	map_2[7][72] = L'█';
	map_2[8][73] = L'█';
	map_2[8][74] = L'█';
	map_2[9][75] = L'█';
	map_2[9][76] = L'█';
	map_2[10][77] = L'█';
	map_2[10][78] = L'█';
	map_2[11][76] = L'█';
	map_2[11][75] = L'█';
	map_2[12][74] = L'█';
	map_2[12][73] = L'█';
	map_2[13][72] = L'█';
	map_2[13][71] = L'█';


	map_2[3][56] = L'ѽ';
	map_2[10][56] = L'❤';
	map_2[15][56] = L'Ơ';


	for (int i = 0; i < 24; i++) {

		for (int j = 0; j < 112; j++) {
			if (i == 9 && j == 60) {
				map_2[9][60] = L'෧';
				wprintf(L"\033[1;37m෧\033[0m");
			}
			else if (i == 14 && j == 56) {
				map_2[14][56] = L'෧';
				wprintf(L"\033[1;37m෧\033[0m");
			}
			else if (i == 11 && j == 53) {
				map_2[11][53] = L'෧';
				wprintf(L"\033[1;37m෧\033[0m");
			}
			else if (i == 19 && j == 9) {
				map_2[19][9] = L'֍';

				wprintf(L"\033[1;33m֍\033[0m");
			}
			else if (i == 19 && j == 104) {
				map_2[19][104] = L'֍';
				wprintf(L"\033[1;33m֍\033[0m");
			}
			else if (i == 9 && j == 25) {
				map_2[9][25] = L'✶';

				wprintf(L"\033[1;33m✶\033[0m");
			}
			else if (i == 9 && j == 96) {
				map_2[9][96] = L'✶';
				wprintf(L"\033[1;33m✶\033[0m");
			}
			else if (i == 15 && j == 56) {
				map_2[15][56] = L'Ơ';

				wprintf(L"\033[1;35mƠ\033[0m");
			}
			else
			{
				wprintf(L"%wc", map_2[i][j]);
			}
		}
		wprintf(L"\n");
	}



	_setmode(_fileno(stdout), _O_TEXT);
}
void game_play_map_1() {
	int up = 0, down = 0, right = 0, left = 0;
	int up_2 = 0, down_2 = 0, right_2 = 0, left_2 = 0;
	int health_player_1 = 5;
	int health_player_2 = 5;
	bool ghalb = 1;


	wchar_t map[24][112];
	COORD player1_pos = { 10, 10 };
	COORD player2_pos = { 100, 10 };
	COORD saved_player1_pos = { 0,0 };
	COORD player1_bullet = { -1, -1 };
	COORD player2_bullet = { -1, -1 };

	//DWORD stands for “Double Word” and is used to represent 32-bit unsigned integers
	DWORD bytes_written;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int U = 0, D = 0, L = 0, R = 0;
	int U2 = 0, D2 = 0, L2 = 0, R2 = 0;
	hidecursor();
	while (health_player_1>0 && health_player_2>0) {
		// Clear screen
		system("cls");

		// Input handling for Player 1
		if (keyPressed(PLAYER1_UP) && map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'█' && map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'║') {
			up = 1; down = 0; right = 0; left = 0;
			if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'෧') {
				health_player_1--;
				player1_pos = { 10 , 10 };
			}
			else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'֍') {
				if (moveDirection(player1_pos, 0, -1).X == 101)
					player1_pos = { 11,19 };
				else
					player1_pos = { 101,19 };
			}
			else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'❤') {
				health_player_1 += 5;
				ghalb = 0;
				map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] = L' ';
				player1_pos = moveDirection(player1_pos, 0, -1);

			}

			else
				player1_pos = moveDirection(player1_pos, 0, -1);
		}
		if (keyPressed(PLAYER1_DOWN) && map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'█' && map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'║') {
			down = 1; up = 0; right = 0; left = 0;


			if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'෧')
			{
				health_player_1--;
				player1_pos = { 10 , 10 };
			}

			else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'֍') {
				if (moveDirection(player1_pos, 0, 1).X == 101)
					player1_pos = { 11,19 };
				else
					player1_pos = { 101,19 };
			}
			else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'❤')
			{
				health_player_1 += 5;
				ghalb = 0;
				map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] = L' ';
				player1_pos = moveDirection(player1_pos, 0, 1);
			}


			else
				player1_pos = moveDirection(player1_pos, 0, 1);
		}
		if (keyPressed(PLAYER1_LEFT) && map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'█' && map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'║') {
			left = 1; up = 0; down = 0; right = 0;
			if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'෧') {
				health_player_1--;
				player1_pos = { 10 , 10 };
			}
			else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'֍') {
				if (moveDirection(player1_pos, -1, 0).X == 101)
					player1_pos = { 11,19 };
				else
					player1_pos = { 101,19 };
			}
			else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'❤')
			{
				health_player_1 += 5;
				ghalb = 0;
				map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] = L' ';
				player1_pos = moveDirection(player1_pos, -1, 0);
			}

			else
				player1_pos = moveDirection(player1_pos, -1, 0);
		}
		if (keyPressed(PLAYER1_RIGHT) && map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'█' && map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'║')
		{
			right = 1; up = 0; down = 0; left = 0;
			if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'෧') {
				health_player_1--;
				player1_pos = { 10 , 10 };
			}
			else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'֍') {
				if (moveDirection(player1_pos, 1, 0).X == 101)
					player1_pos = { 11,19 };
				else
					player1_pos = { 101,19 };
			}
			else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'❤')
			{
				health_player_1 += 5;
				ghalb = 0;
				map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] = L' ';
				player1_pos = moveDirection(player1_pos, 1, 0);
			}

			else
				player1_pos = moveDirection(player1_pos, 1, 0);

		}
		if (keyPressed(PLAYER1_SHOOT)) {
			if (up == 1) {
				player1_bullet = moveDirection(player1_pos, 0, -1);
				U = 1; D = 0; L = 0; R = 0;
			}
			else if (down == 1) {
				player1_bullet = moveDirection(player1_pos, 0, 1);
				D = 1; U = 0; L = 0; R = 0;
			}
			else if (left == 1) {
				player1_bullet = moveDirection(player1_pos, -1, 0);
				L = 1; U = 0; D = 0; R = 0;
			}
			else if (right == 1) {
				player1_bullet = moveDirection(player1_pos, 1, 0);
				R = 1; U = 0; D = 0; L = 0;
			}

		}

		// Input handling for Player 2
		if (keyPressed(PLAYER2_UP) && map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'█' && map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'║') {
			up_2 = 1; down_2 = 0; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'෧') {
				health_player_2--;
				player2_pos = { 100 , 10 };
			}
			else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'֍') {
				if (moveDirection(player2_pos, 0, -1).X == 101)
					player2_pos = { 11,19 };
				else
					player2_pos = { 101,19 };
			}
			else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤')
			{
				health_player_2 += 5;
				ghalb = 0;
				map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤';
				player2_pos = moveDirection(player2_pos, 0, -1);
			}



			else
				player2_pos = moveDirection(player2_pos, 0, -1);
		}
		if (keyPressed(PLAYER2_DOWN) && map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'█' && map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'║')
		{
			up_2 = 0; down_2 = 1; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'෧') {
				health_player_2--;
				player2_pos = { 100 , 10 };
			}
			else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'֍') {
				if (moveDirection(player2_pos, 0, 1).X == 101)
					player2_pos = { 11,19 };
				else
					player2_pos = { 101,19 };
			}
			else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤')
			{
				health_player_2 += 5;
				ghalb = 0;
				map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤';
				player2_pos = moveDirection(player2_pos, 0, 1);
			}


			else
				player2_pos = moveDirection(player2_pos, 0, 1);
		}
		if (keyPressed(PLAYER2_LEFT) && map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'█' && map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'║')
		{
			up_2 = 0; down_2 = 0; right_2 = 0; left_2 = 1;
			if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'෧') {
				health_player_2--;
				player2_pos = { 100 , 10 };
			}
			else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'֍') {
				if (moveDirection(player2_pos, -1, 0).X == 101)
					player2_pos = { 11,19 };
				else
					player2_pos = { 101,19 };
			}
			else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤')
			{
				health_player_2 += 5;
				ghalb = 0;
				map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤';
				player2_pos = moveDirection(player2_pos, -1, 0);
			}

			else
				player2_pos = moveDirection(player2_pos, -1, 0);

		}
		if (keyPressed(PLAYER2_RIGHT) && map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'█' && map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'║')
		{
			up_2 = 0; down_2 = 0; right_2 = 1; left_2 = 0;
			if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'෧') {
				health_player_2--;
				player2_pos = { 100 , 10 };
			}
			else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'֍') {
				if (moveDirection(player2_pos, 1, 0).X == 101)
					player2_pos = { 11,19 };
				else
					player2_pos = { 101,19 };
			}
			else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤')
			{
				health_player_2 += 5;
				ghalb = 0;
				map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤';
				player2_pos = moveDirection(player2_pos, 1, 0);
			}
			else
				player2_pos = moveDirection(player2_pos, 1, 0);
		}
		if (keyPressed(PLAYER2_SHOOT)) {
			if (up_2 == 1) {
				player2_bullet = moveDirection(player2_pos, 0, -1);
				U2 = 1; D2 = 0; L2 = 0; R2 = 0;
			}
			else if (down_2 == 1) {
				player2_bullet = moveDirection(player2_pos, 0, 1);
				D2 = 1; U2 = 0; L2 = 0; R2 = 0;
			}
			else if (left_2 == 1) {
				player2_bullet = moveDirection(player2_pos, -1, 0);
				L2 = 1; U2 = 0; D2 = 0; R2 = 0;
			}
			else if (right_2 == 1) {
				player2_bullet = moveDirection(player2_pos, -1, 0);
				R2 = 1; U2 = 0; D2 = 0; L2 = 0;
			}
		}

		int score_move = 0;
		score_move += (up + down + left + right);
		// Update bullet positions
		if (player1_bullet.X != -1) {
			if (U == 1 && map[moveDirection(player1_bullet, 0, -1).Y][moveDirection(player1_bullet, 0, -1).X] != L'█') {
				player1_bullet.Y--;
				if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X)
					health_player_2--;
				if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
					U = 0; D = 1;
					player1_bullet.Y += 2;
				}
			}
			else if (D == 1 && map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█')
			{
				player1_bullet.Y++;
				if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X)
					health_player_2--;
				if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
					U = 1; D = 0;
					player1_bullet.Y -= 2;
				}
			}
			else if (R == 1 && map[moveDirection(player1_bullet, 1, 0).Y][moveDirection(player1_bullet, 1, 0).X] != L'█')
			{
				player1_bullet.X++;
				if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X)
					health_player_2--;
				if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
					R = 0; L = 1;
					player1_bullet.X -= 2;
				}
			}
			else if (L == 1 && map[moveDirection(player1_bullet, -1, 0).Y][moveDirection(player1_bullet, -1, 0).X] != L'█')
			{
				player1_bullet.X--;
				if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X)
					health_player_2--;
				if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
					R = 1; L = 0;
					player1_bullet.X += 2;
				}
			}
			else {
				player1_bullet.X = -1;
			}

		}
		if (player2_bullet.X != -1) {
			if (U2 == 1 && map[moveDirection(player2_bullet, 0, -1).Y][moveDirection(player2_bullet, 0, -1).X] != L'█') {
				player2_bullet.Y--;
				if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X)
					health_player_1--;
				if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
					U2 = 0; D2 = 1;
					player2_bullet.Y += 2;
				}
			}
			else if (D2 == 1 && map[moveDirection(player2_bullet, 0, 1).Y][moveDirection(player2_bullet, 0, 1).X] != L'█')
			{
				player2_bullet.Y++;
				if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X)
					health_player_1--;
				if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
					U2 = 1; D2 = 0;
					player2_bullet.Y -= 2;
				}
			}

			else if (R2 == 1 && map[moveDirection(player2_bullet, 1, 0).Y][moveDirection(player2_bullet, 1, 0).X] != L'█')
			{
				player2_bullet.X++;
				if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X)
					health_player_1--;
				if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
					R2 = 0; L2 = 1;
					player2_bullet.X -= 2;
				}

			}
			else if (L2 == 1 && map[moveDirection(player2_bullet, -1, 0).Y][moveDirection(player2_bullet, -1, 0).X] != L'█')
			{
				player2_bullet.X--;
				if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X)
					health_player_1--;
				if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
					R2 = 1; L2 = 0;
					player2_bullet.X += 2;
				}
			}
			else {
				player2_bullet.X = -1;
			}
		}

		// Draw map
		SetConsoleOutputCP(65001);
		_setmode(_fileno(stdout), _O_U16TEXT);
		shape_Map(map,ghalb);
		// Draw players
		map[player1_pos.Y][player1_pos.X] = '1';
		map[player2_pos.Y][player2_pos.X] = '2';

		// Draw bullets
		if (player1_bullet.X < 112 && player1_bullet.X != -1) map[player1_bullet.Y][player1_bullet.X] = '.';
		if (player2_bullet.X < 112 && player2_bullet.X != -1) map[player2_bullet.Y][player2_bullet.X] = '.';

		// Output to console
		for (int y = 0; y < 24; y++) {
			COORD place;
			place.X = 0;
			place.Y = y;
			WriteConsoleOutputCharacterW(hStdout, map[y], 112, place, &bytes_written);
			//WriteConsoleOutputCharacterA is a function in the Windows Console API that writes a string of characters to a console screen buffer at a specified location.
			//The first parameter identifies where to write the characters
			//The second parameter is a C-style string or an array of characters that you want to write to the screen buffer.
			//The third parameter specifies how many characters from the string should be written to the screen buffer.
			//The fourth parameter specifies the coordinates (given as a COORD structure) of the first cell in the console screen buffer where writing will begin.
			//The fifth parameter is a pointer to a variable that receives the number of characters actually written to the console screen buffer.

		}

		_setmode(_fileno(stdout), _O_TEXT);
		printf("\n1:%d,2:%d", health_player_1, health_player_2);
		// Game tick delay
		Sleep(100);
	}
	game_play_map_2();

}
void game_play_map_2() {
	int up = 0, down = 0, right = 0, left = 0;
	int up_2 = 0, down_2 = 0, right_2 = 0, left_2 = 0;
	int health_player_1 = 5;
	int health_player_2 = 5;
	bool ghalb = 1;


	wchar_t map[24][112];

	COORD player1_pos = { 10, 10 };
	COORD player2_pos = { 100, 10 };
	COORD saved_player1_pos = { 0,0 };
	COORD player1_bullet = { -1, -1 };
	COORD player2_bullet = { -1, -1 };

	//DWORD stands for “Double Word” and is used to represent 32-bit unsigned integers
	DWORD bytes_written;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int U = 0, D = 0, L = 0, R = 0;
	int U2 = 0, D2 = 0, L2 = 0, R2 = 0;
	int score_bullet_player_1 = 0;
	int score_bullet_player_2 = 0;

	int saved_2 = 0;
	int saved_1 = 0;

	bool upgrade_bullets_1 = 0;
	bool upgrade_bullets_2 = 0;

	bool ghost_player_1 = 0;
	bool ghost_player_2 = 0;

	bool pos_ghost_player = 0;

	int move_ghost_player_1 = 0;
	int move_ghost_player_2 = 0;

	int score_move_1 = 0;
	int score_move_2 = 0;


	bool pos_upgrade_bullets_R = 0;
	bool pos_upgrade_bullets_L = 0;

	bool frag_player_1 = 0;
	bool frag_player_2 = 0;

	bool pos_frag_player = 0;

	int  wall_x = 0;
	int  wall_y = 0;
	int saved_frag_1 = 0;
	int saved_frag_2 = 0;
	hidecursor();
	while (1) {
		// Clear screen
		system("cls");

		//ghost being
		if (move_ghost_player_1 + 7 == score_move_1) ghost_player_1 = 0;
		if (move_ghost_player_2 + 7 == score_move_2) ghost_player_2 = 0;
		// Input handling for Player 1
		if (keyPressed(PLAYER1_UP) && map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'║') {
			score_move_1++;
			up = 1; down = 0; right = 0; left = 0;
			if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'█' || ghost_player_1 == 1)
			{

				if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'֍') {
					if (moveDirection(player1_pos, 0, -1).X == 104)
						player1_pos = { 9,19 };
					else
						player1_pos = { 104,19 };
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'❤') {
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] = L' ';
					player1_pos = moveDirection(player1_pos, 0, -1);

				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 0, -1).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player1_pos = moveDirection(player1_pos, 0, -1);
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'ѽ')
				{
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					move_ghost_player_1 = score_move_1;
					player1_pos = moveDirection(player1_pos, 0, -1);
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'Ơ') {
					frag_player_1 = 1;
					saved_frag_1 = score_bullet_player_1;
					pos_frag_player = 1;
					player1_pos = moveDirection(player1_pos, 0, -1);
				}

				else
					player1_pos = moveDirection(player1_pos, 0, -1);
			}
		}
		if (keyPressed(PLAYER1_DOWN) && map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'║') {
			down = 1; up = 0; right = 0; left = 0; score_move_1++;
			if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'෧')
				{
					health_player_1--;
					player1_pos = { 10 , 10 };
				}

				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'֍') {
					if (moveDirection(player1_pos, 0, 1).X == 104)
						player1_pos = { 9,19 };
					else
						player1_pos = { 104,19 };
				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] = L' ';
					player1_pos = moveDirection(player1_pos, 0, 1);
				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 0, 1).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;
					player1_pos = moveDirection(player1_pos, 0, 1);
				}

				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'ѽ')
				{

					ghost_player_1 = 1;
					move_ghost_player_1 = score_move_1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, 0, 1);

				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'Ơ') {
					frag_player_1 = 1;
					pos_frag_player = 1;
					saved_frag_1 = score_bullet_player_1;
					player1_pos = moveDirection(player1_pos, 0, 1);
				}
				else
					player1_pos = moveDirection(player1_pos, 0, 1);
			}
		}
		if (keyPressed(PLAYER1_LEFT) && map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'║') {
			left = 1; up = 0; down = 0; right = 0; score_move_1++;
			if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'֍') {
					if (moveDirection(player1_pos, -1, 0).X == 104)
						player1_pos = { 9,19 };
					else
						player1_pos = { 104,19 };
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] = L' ';
					player1_pos = moveDirection(player1_pos, -1, 0);
				}

				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, -1, 0).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}

				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'ѽ')
				{
					move_ghost_player_1 = score_move_1;
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'Ơ') {
					frag_player_1 = 1;
					saved_frag_1 = score_bullet_player_1;
					pos_frag_player = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}
				else
					player1_pos = moveDirection(player1_pos, -1, 0);

			}
		}
		if (keyPressed(PLAYER1_RIGHT) && map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'║')
		{
			score_move_1++;
			right = 1; up = 0; down = 0; left = 0;
			if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'֍') {
					if (moveDirection(player1_pos, 1, 0).X == 104)
						player1_pos = { 9,19 };
					else
						player1_pos = { 104,19 };
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] = L' ';
					player1_pos = moveDirection(player1_pos, 1, 0);
				}

				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 1, 0).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player1_pos = moveDirection(player1_pos, 1, 0);
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'ѽ')
				{
					move_ghost_player_1 = score_move_1;
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, 1, 0);
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'Ơ') {
					frag_player_1 = 1;
					pos_frag_player = 1;
					saved_frag_1 = score_bullet_player_1;
					player1_pos = moveDirection(player1_pos, 1, 0);
				}

				else
					player1_pos = moveDirection(player1_pos, 1, 0);
			}

		}
		if (keyPressed(PLAYER1_SHOOT)) {
			score_bullet_player_1++;
			score_move_1++;
			if (up == 1) {
				player1_bullet = player1_pos;
				U = 1; D = 0; L = 0; R = 0;
			}
			else if (down == 1) {
				player1_bullet = player1_pos;
				D = 1; U = 0; L = 0; R = 0;
			}
			else if (left == 1) {
				player1_bullet = player1_pos;
				L = 1; U = 0; D = 0; R = 0;
			}
			else if (right == 1) {
				player1_bullet = player1_pos;
				R = 1; U = 0; D = 0; L = 0;
			}

		}

		// Input handling for Player 2
		if (keyPressed(PLAYER2_UP) && map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'║') {
			score_move_2++;
			up_2 = 1; down_2 = 0; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'█' || ghost_player_1 == 2)
			{
				if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'֍') {
					if (moveDirection(player2_pos, 0, -1).X == 104)
						player2_pos = { 9,19 };
					else
						player2_pos = { 104,19 };
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 0, -1).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, 0, -1);
				}

				else
					player2_pos = moveDirection(player2_pos, 0, -1);
			}
		}
		if (keyPressed(PLAYER2_DOWN) && map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 1; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'֍') {
					if (moveDirection(player2_pos, 0, 1).X == 104)
						player2_pos = { 9,19 };
					else
						player2_pos = { 104,19 };
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 0, 1);
				}

				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 0, 1).X == 25)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 0, 1);
				}

				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 0, 1);
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, 0, 1);
				}
				else
					player2_pos = moveDirection(player2_pos, 0, 1);
			}
		}
		if (keyPressed(PLAYER2_LEFT) && map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 0; right_2 = 0; left_2 = 1;
			if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'֍') {
					if (moveDirection(player2_pos, -1, 0).X == 104)
						player2_pos = { 9,19 };
					else
						player2_pos = { 104,19 };
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤';
					player2_pos = moveDirection(player2_pos, -1, 0);
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, -1, 0).X == 25)
						pos_upgrade_bullets_L = 1;
					else
						pos_upgrade_bullets_R = 1;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}

				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}

				else
					player2_pos = moveDirection(player2_pos, -1, 0);
			}
		}
		if (keyPressed(PLAYER2_RIGHT) && map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 0; right_2 = 1; left_2 = 0;
			if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'֍') {
					if (moveDirection(player2_pos, 1, 0).X == 104)
						player2_pos = { 9,19 };
					else
						player2_pos = { 104,19 };
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 1, 0);
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 1, 0).X == 25)
						pos_upgrade_bullets_L = 1;
					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 1, 0);
				}

				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 1, 0);
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'Ơ') {
					frag_player_2 = 1;
					saved_frag_2 = score_bullet_player_2;
					pos_frag_player = 1;
					player2_pos = moveDirection(player2_pos, 1, 0);
				}


				else
					player2_pos = moveDirection(player2_pos, 1, 0);
			}
		}
		if (keyPressed(PLAYER2_SHOOT)) {
			score_move_2++;
			score_bullet_player_2++;
			if (up_2 == 1) {
				player2_bullet = player2_pos;
				U2 = 1; D2 = 0; L2 = 0; R2 = 0;
			}
			else if (down_2 == 1) {
				player2_bullet = player2_pos;
				D2 = 1; U2 = 0; L2 = 0; R2 = 0;
			}
			else if (left_2 == 1) {
				player2_bullet = player2_pos;
				L2 = 1; U2 = 0; D2 = 0; R2 = 0;
			}
			else if (right_2 == 1) {
				player2_bullet = player2_pos;
				R2 = 1; U2 = 0; D2 = 0; L2 = 0;
			}
		}
		// frag
			if (saved_frag_1 + 2 == score_bullet_player_1)frag_player_1 = 0;
			if (saved_frag_2 + 2 == score_bullet_player_2)frag_player_2 = 0;

			//upgrade bullet
		if (saved_1 + 6 == score_bullet_player_1) {
			upgrade_bullets_1 = 0;
		}
		if (saved_2 + 6 == score_bullet_player_2) {
			upgrade_bullets_2 = 0;
		}
		/////

		// Update bullet positions
		if (player1_bullet.X != -1) {
			if (frag_player_1 == 0)
			{

				if (U == 1) {
					if (map[moveDirection(player1_bullet, 0, -1).Y][moveDirection(player1_bullet, 0, -1).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.Y--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							U = 0; D = 1;
							player1_bullet.Y += 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}
				}
				else if (D == 1)
				{
					if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█' || ghost_player_1 == 1)
					{
						if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█' || ghost_player_1 == 1)
						{
							player1_bullet.Y++;
							if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
								health_player_2--;

							else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
								health_player_2 -= 2;

							if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
								U = 1; D = 0;
								player1_bullet.Y -= 2;
							}

						}
					}
					else {
						player1_bullet.X = -1;
					}

				}
				else if (R == 1)
				{
					if (map[moveDirection(player1_bullet, 1, 0).Y][moveDirection(player1_bullet, 1, 0).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.X++;

						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							R = 0; L = 1;
							player1_bullet.X -= 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}

				}
				else if (L == 1)
				{
					if (map[moveDirection(player1_bullet, -1, 0).Y][moveDirection(player1_bullet, -1, 0).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.X--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							R = 1; L = 0;
							player1_bullet.X += 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}
				}
				else {
					player1_bullet.X = -1;
				}

			}
			else {
				if (U == 1) {
					if (map[moveDirection(player1_bullet, 0, -1).Y][moveDirection(player1_bullet, 0, -1).X] != L'█')
					{
						player1_bullet.Y--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 5;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else if (D == 1)
				{
					if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█')
					{
						player1_bullet.Y++;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else if (R == 1)
				{
					if (map[moveDirection(player1_bullet, 1, 0).Y][moveDirection(player1_bullet, 1, 0).X] != L'█')
					{
						player1_bullet.X++;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}

				}
				else if (L == 1)
				{
					if (map[moveDirection(player1_bullet, -1, 0).Y][moveDirection(player1_bullet, -1, 0).X] != L'█')
					{
						player1_bullet.X--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else {
					if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
						health_player_2--;
					}
					player1_bullet.X = -1;
				}
			}
		}
		if (player2_bullet.X != -1) {
			if (frag_player_2 == 0)
			{
				if (U2 == 1) {
					if (map[moveDirection(player2_bullet, 0, -1).Y][moveDirection(player2_bullet, 0, -1).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.Y--;

						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							U2 = 0; D2 = 1;
							player2_bullet.Y += 2;
						}
					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (D2 == 1)
				{
					if (map[moveDirection(player2_bullet, 0, 1).Y][moveDirection(player2_bullet, 0, 1).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.Y++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							U2 = 0; D2 = 1;
							player2_bullet.Y += 2;
						}
					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (R2 == 1)
				{
					if (map[moveDirection(player2_bullet, 1, 0).Y][moveDirection(player2_bullet, 1, 0).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.X++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							R2 = 0; L2 = 1;
							player2_bullet.X -= 2;
						}

					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (L2 == 1)
				{
					if (map[moveDirection(player2_bullet, -1, 0).Y][moveDirection(player2_bullet, -1, 0).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.X--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							R2 = 1; L2 = 0;
							player2_bullet.X += 2;
						}

					}
					else {
						player2_bullet.X = -1;
					}
				}
				else {
					player2_bullet.X = -1;
				}

			}


			else {
				if (U2 == 1) {
					if (map[moveDirection(player2_bullet, 0, -1).Y][moveDirection(player2_bullet, 0, -1).X] != L'█')
					{
						player2_bullet.Y--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else if (D2 == 1)
				{
					if (map[moveDirection(player2_bullet, 0, 1).Y][moveDirection(player2_bullet, 0, 1).X] != L'█')
					{
						player2_bullet.Y++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else if (R2 == 1)
				{
					if (map[moveDirection(player2_bullet, 1, 0).Y][moveDirection(player2_bullet, 1, 0).X] != L'█')
					{
						player2_bullet.X++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}

				}
				else if (L2 == 1)
				{
					if (map[moveDirection(player2_bullet, -1, 0).Y][moveDirection(player2_bullet, -1, 0).X] != L'█')
					{
						player2_bullet.X--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else {
					if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
						health_player_1--;
					}
					player2_bullet.X = -1;
				}
			}

		}

		// Draw map
		SetConsoleOutputCP(65001);
		_setmode(_fileno(stdout), _O_U16TEXT);
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 112; j++) {
				map[i][j] = L' ';
			}
		}
		///////////////////dor kesh
		for (int i = 0; i < 24; i++) {
			map[i][0] = L'█';
		}
		for (int i = 0; i < 112; i++) {
			map[0][i] = L'█';
		}
		for (int i = 0; i < 112; i++) {
			map[23][i] = L'█';
		}
		for (int i = 0; i < 24; i++) {
			map[i][111] = L'█';
		}
		//////////////////////////////khat chi
		for (int i = 7; i < 14; i++) {
			if (wall_y != i)
				map[i][12] = L'║';
		}
		for (int j = 7; j < 14; j++) {
			if (wall_y != j)
				map[j][99] = L'║';
		}
		map[3][86] = L'█';
		map[4][86] = L'█';
		if (wall_x != 85 && wall_y != 4)
			map[4][85] = L'║';

		map[3][25] = L'█';
		map[4][25] = L'█';
		if (wall_x != 26 && wall_y != 3)
			map[3][26] = L'║';


		map[19][86] = L'█';
		map[18][86] = L'█';
		if (wall_x != 85 && wall_y != 19)
			map[19][85] = L'║';



		map[19][25] = L'█';
		map[18][25] = L'█';
		if (wall_x != 26 && wall_y != 18)
			map[18][26] = L'║';

		map[5][57] = L'█';
		map[5][56] = L'█';
		map[5][55] = L'█';

		map[7][56] = L'█';
		map[8][56] = L'█';
		map[8][55] = L'█';
		map[8][54] = L'█';
		map[8][53] = L'█';
		map[9][53] = L'█';
		map[10][53] = L'█';
		map[10][52] = L'█';
		map[10][51] = L'█';
		map[10][60] = L'█';
		map[10][61] = L'█';
		map[10][62] = L'█';
		map[11][60] = L'█';
		map[12][60] = L'█';
		map[12][59] = L'█';
		map[12][58] = L'█';
		map[12][57] = L'█';
		map[12][56] = L'█';
		map[13][56] = L'█';
		map[16][56] = L'█';
		map[16][57] = L'█';
		map[16][55] = L'█';
		if (wall_x != 54 && wall_y != 10)
			map[10][54] = L'║';
		if (wall_x != 39 && wall_y != 11)
			map[11][39] = L'║';
		if (wall_x != 74 && wall_y != 9)
			map[9][74] = L'║';



		map[7][42] = L'█';
		map[7][41] = L'█';
		map[8][40] = L'█';
		map[8][39] = L'█';
		map[9][38] = L'█';
		map[9][37] = L'█';
		map[10][36] = L'█';
		map[10][35] = L'█';
		map[11][37] = L'█';
		map[11][38] = L'█';
		map[12][39] = L'█';
		map[12][40] = L'█';
		map[13][41] = L'█';
		map[13][42] = L'█';




		map[7][71] = L'█';
		map[7][72] = L'█';
		map[8][73] = L'█';
		map[8][74] = L'█';
		map[9][75] = L'█';
		map[9][76] = L'█';
		map[10][77] = L'█';
		map[10][78] = L'█';
		map[11][76] = L'█';
		map[11][75] = L'█';
		map[12][74] = L'█';
		map[12][73] = L'█';
		map[13][72] = L'█';
		map[13][71] = L'█';

		if (pos_ghost_player == 0)
			map[3][56] = L'ѽ';
		if (ghalb == 1)
			map[10][56] = L'❤';



		for (int i = 0; i < 24; i++) {

			for (int j = 0; j < 112; j++) {
				if (i == 9 && j == 60) {
					map[9][60] = L'෧';
					wprintf(L"\033[1;37m෧\033[0m");
				}
				else if (i == 14 && j == 56) {
					map[14][56] = L'෧';
					wprintf(L"\033[1;37m෧\033[0m");
				}
				else if (i == 11 && j == 53) {
					map[11][53] = L'෧';
					wprintf(L"\033[1;37m෧\033[0m");
				}
				else if (i == 19 && j == 9) {
					map[19][9] = L'֍';

					wprintf(L"\033[1;33m֍\033[0m");
				}
				else if (i == 19 && j == 104) {
					map[19][104] = L'֍';
					wprintf(L"\033[1;33m֍\033[0m");
				}
				else if (i == 9 && j == 25 && pos_upgrade_bullets_L == 0) {
					map[9][25] = L'✶';

					wprintf(L"\033[1;33m✶\033[0m");
				}
				else if (i == 9 && j == 96 && pos_upgrade_bullets_R == 0) {
					map[9][96] = L'✶';
					wprintf(L"\033[1;33m✶\033[0m");
				}
				else if (i == 15 && j == 56 && pos_frag_player == 0) {
					map[15][56] = L'Ơ';

					wprintf(L"\033[1;35mƠ\033[0m");
				}
				else
				{
					wprintf(L"%wc", map[i][j]);
				}
			}
			wprintf(L"\n");
		}

		// Draw players
		map[player1_pos.Y][player1_pos.X] = '1';
		map[player2_pos.Y][player2_pos.X] = '2';

		// Draw bullets
		if (player1_bullet.X < 112 && player1_bullet.X != -1) {
			if (frag_player_1 == 0)
				map[player1_bullet.Y][player1_bullet.X] = '.';
			else
				map[player1_bullet.Y][player1_bullet.X] = L'Ơ';
		}

		if (player2_bullet.X < 112 && player2_bullet.X != -1) {
			if (frag_player_2 == 0)
				map[player2_bullet.Y][player2_bullet.X] = '.';
			else
				map[player2_bullet.Y][player2_bullet.X] = L'Ơ';
		}
		// Output to console
		for (int y = 0; y < 24; y++) {
			COORD place;
			place.X = 0;
			place.Y = y;
			WriteConsoleOutputCharacterW(hStdout, map[y], 112, place, &bytes_written);
			//WriteConsoleOutputCharacterA is a function in the Windows Console API that writes a string of characters to a console screen buffer at a specified location.
			//The first parameter identifies where to write the characters
			//The second parameter is a C-style string or an array of characters that you want to write to the screen buffer.
			//The third parameter specifies how many characters from the string should be written to the screen buffer.
			//The fourth parameter specifies the coordinates (given as a COORD structure) of the first cell in the console screen buffer where writing will begin.
			//The fifth parameter is a pointer to a variable that receives the number of characters actually written to the console screen buffer.

		}

		_setmode(_fileno(stdout), _O_TEXT);
		printf("\n1:%d,2:%d,%d,%d", health_player_1, health_player_2, score_move_2, move_ghost_player_1);
		// Game tick delay
		Sleep(100);
	}





}
void game_play_map_3() {
	int up = 0, down = 0, right = 0, left = 0;
	int up_2 = 0, down_2 = 0, right_2 = 0, left_2 = 0;
	int health_player_1 = 5;
	int health_player_2 = 5;
	bool ghalb = 1;


	wchar_t map[24][112];

	COORD player1_pos = { 10, 10 };
	COORD player2_pos = { 100, 10 };
	COORD saved_player1_pos = { 0,0 };
	COORD player1_bullet = { -1, -1 };
	COORD player2_bullet = { -1, -1 };

	//DWORD stands for “Double Word” and is used to represent 32-bit unsigned integers
	DWORD bytes_written;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int U = 0, D = 0, L = 0, R = 0;
	int U2 = 0, D2 = 0, L2 = 0, R2 = 0;
	int score_bullet_player_1 = 0;
	int score_bullet_player_2 = 0;

	int saved_2 = 0;
	int saved_1 = 0;

	bool upgrade_bullets_1 = 0;
	bool upgrade_bullets_2 = 0;

	bool ghost_player_1 = 0;
	bool ghost_player_2 = 0;

	bool pos_ghost_player = 0;

	int move_ghost_player_1 = 0;
	int move_ghost_player_2 = 0;

	int score_move_1 = 0;
	int score_move_2 = 0;


	bool pos_upgrade_bullets_R = 0;
	bool pos_upgrade_bullets_L = 0;

	bool frag_player_1 = 0;
	bool frag_player_2 = 0;

	bool pos_frag_player = 0;

	int  wall_x = 0;
	int  wall_y = 0;
	int saved_frag_1 = 0;
	int saved_frag_2 = 0;
	hidecursor();
	while (1) {
		// Clear screen
		system("cls");

		//ghost being
		if (move_ghost_player_1 + 7 == score_move_1) ghost_player_1 = 0;
		if (move_ghost_player_2 + 7 == score_move_2) ghost_player_2 = 0;
		// Input handling for Player 1
		if (keyPressed(PLAYER1_UP) && map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'║') {
			score_move_1++;
			up = 1; down = 0; right = 0; left = 0;
			if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] != L'█' || ghost_player_1 == 1)
			{

				if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'֍') {
					if (moveDirection(player1_pos, 0, -1).X == 40 && moveDirection(player1_pos, 0, -1).Y == 12)
						player1_pos = { 72,10 };
					else if (moveDirection(player1_pos, 0, -1).X == 72 && moveDirection(player1_pos, 0, -1).Y == 10) {
						player1_pos = { 40,12 };
					}
					else if (moveDirection(player1_pos, 0, -1).X == 56 && moveDirection(player1_pos, 0, -1).Y == 4) {
						player1_pos = { 56,21 };

					}
					else if (moveDirection(player1_pos, 0, -1).X == 56 && moveDirection(player1_pos, 0, -1).Y == 21) {
						player1_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'❤') {
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] = L' ';
					player1_pos = moveDirection(player1_pos, 0, -1);

				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 0, -1).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player1_pos = moveDirection(player1_pos, 0, -1);
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'ѽ')
				{
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					move_ghost_player_1 = score_move_1;
					player1_pos = moveDirection(player1_pos, 0, -1);
				}
				else if (map[moveDirection(player1_pos, 0, -1).Y][moveDirection(player1_pos, 0, -1).X] == L'Ơ') {
					frag_player_1 = 1;
					saved_frag_1 = score_bullet_player_1;
					pos_frag_player = 1;
					player1_pos = moveDirection(player1_pos, 0, -1);
				}

				else
					player1_pos = moveDirection(player1_pos, 0, -1);
			}
		}
		if (keyPressed(PLAYER1_DOWN) && map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'║') {
			down = 1; up = 0; right = 0; left = 0; score_move_1++;
			if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'෧')
				{
					health_player_1--;
					player1_pos = { 10 , 10 };
				}

				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'֍') {
					if (moveDirection(player1_pos, 0, 1).X == 40 && moveDirection(player1_pos, 0, 1).Y == 12)
						player1_pos = { 72,10 };
					else if (moveDirection(player1_pos, 0, 1).X == 72 && moveDirection(player1_pos, 0, 1).Y == 10) {
						player1_pos = { 40,12 };
					}
					else if (moveDirection(player1_pos, 0, 1).X == 56 && moveDirection(player1_pos, 0, 1).Y == 4) {
						player1_pos = { 56,21 };

					}
					else if (moveDirection(player1_pos, 0, 1).X == 56 && moveDirection(player1_pos, 0, 1).Y == 21) {
						player1_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] = L' ';
					player1_pos = moveDirection(player1_pos, 0, 1);
				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 0, 1).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;
					player1_pos = moveDirection(player1_pos, 0, 1);
				}

				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'ѽ')
				{

					ghost_player_1 = 1;
					move_ghost_player_1 = score_move_1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, 0, 1);

				}
				else if (map[moveDirection(player1_pos, 0, 1).Y][moveDirection(player1_pos, 0, 1).X] == L'Ơ') {
					frag_player_1 = 1;
					pos_frag_player = 1;
					saved_frag_1 = score_bullet_player_1;
					player1_pos = moveDirection(player1_pos, 0, 1);
				}
				else
					player1_pos = moveDirection(player1_pos, 0, 1);
			}
		}
		if (keyPressed(PLAYER1_LEFT) && map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'║') {
			left = 1; up = 0; down = 0; right = 0; score_move_1++;
			if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'֍') {
					if (moveDirection(player1_pos, -1, 0).X == 40 && moveDirection(player1_pos, -1, 0).Y == 12)
						player1_pos = { 72,10 };
					else if (moveDirection(player1_pos, -1, 0).X == 72 && moveDirection(player1_pos, -1, 0).Y == 10) {
						player1_pos = { 40,12 };
					}
					else if (moveDirection(player1_pos, -1, 0).X == 56 && moveDirection(player1_pos, -1, 0).Y == 4) {
						player1_pos = { 56,21 };

					}
					else if (moveDirection(player1_pos, -1, 0).X == 56 && moveDirection(player1_pos, -1, 0).Y == 21) {
						player1_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] = L' ';
					player1_pos = moveDirection(player1_pos, -1, 0);
				}

				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, -1, 0).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}

				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'ѽ')
				{
					move_ghost_player_1 = score_move_1;
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}
				else if (map[moveDirection(player1_pos, -1, 0).Y][moveDirection(player1_pos, -1, 0).X] == L'Ơ') {
					frag_player_1 = 1;
					saved_frag_1 = score_bullet_player_1;
					pos_frag_player = 1;
					player1_pos = moveDirection(player1_pos, -1, 0);
				}
				else
					player1_pos = moveDirection(player1_pos, -1, 0);

			}
		}
		if (keyPressed(PLAYER1_RIGHT) && map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'║')
		{
			score_move_1++;
			right = 1; up = 0; down = 0; left = 0;
			if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] != L'█' || ghost_player_1 == 1)
			{
				if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'෧') {
					health_player_1--;
					player1_pos = { 10 , 10 };
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'֍') {
					if (moveDirection(player1_pos, 1, 0).X == 40 && moveDirection(player1_pos, 1, 0).Y == 12)
						player1_pos = { 72,10 };
					else if (moveDirection(player1_pos, 1, 0).X == 72 && moveDirection(player1_pos, 1, 0).Y == 10) {
						player1_pos = { 40,12 };
					}
					else if (moveDirection(player1_pos, 1, 0).X == 56 && moveDirection(player1_pos, 1, 0).Y == 4) {
						player1_pos = { 56,21 };

					}
					else if (moveDirection(player1_pos, 1, 0).X == 56 && moveDirection(player1_pos, 1, 0).Y == 21) {
						player1_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'❤')
				{
					health_player_1 += 5;
					ghalb = 0;
					map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] = L' ';
					player1_pos = moveDirection(player1_pos, 1, 0);
				}

				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'✶') {
					upgrade_bullets_1 = 1;
					saved_1 = score_bullet_player_1;
					if (moveDirection(player1_pos, 1, 0).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player1_pos = moveDirection(player1_pos, 1, 0);
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'ѽ')
				{
					move_ghost_player_1 = score_move_1;
					ghost_player_1 = 1;
					pos_ghost_player = 1;
					player1_pos = moveDirection(player1_pos, 1, 0);
				}
				else if (map[moveDirection(player1_pos, 1, 0).Y][moveDirection(player1_pos, 1, 0).X] == L'Ơ') {
					frag_player_1 = 1;
					pos_frag_player = 1;
					saved_frag_1 = score_bullet_player_1;
					player1_pos = moveDirection(player1_pos, 1, 0);
				}

				else
					player1_pos = moveDirection(player1_pos, 1, 0);
			}

		}
		if (keyPressed(PLAYER1_SHOOT)) {
			score_bullet_player_1++;
			score_move_1++;
			if (up == 1) {
				player1_bullet = player1_pos;
				U = 1; D = 0; L = 0; R = 0;
			}
			else if (down == 1) {
				player1_bullet = player1_pos;
				D = 1; U = 0; L = 0; R = 0;
			}
			else if (left == 1) {
				player1_bullet = player1_pos;
				L = 1; U = 0; D = 0; R = 0;
			}
			else if (right == 1) {
				player1_bullet = player1_pos;
				R = 1; U = 0; D = 0; L = 0;
			}

		}

		// Input handling for Player 2
		if (keyPressed(PLAYER2_UP) && map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'║') {
			score_move_2++;
			up_2 = 1; down_2 = 0; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'֍') {
					if (moveDirection(player2_pos, 0, -1).X == 40 && moveDirection(player2_pos, 0, -1).Y == 12)
						player2_pos = { 72,10 };
					else if (moveDirection(player2_pos, 0, -1).X == 72 && moveDirection(player2_pos, 0, -1).Y == 10) {
						player2_pos = { 40,12 };
					}
					else if (moveDirection(player2_pos, 0, -1).X == 56 && moveDirection(player2_pos, 0, -1).Y == 4) {
						player2_pos = { 56,21 };

					}
					else if (moveDirection(player2_pos, 0, -1).X == 56 && moveDirection(player2_pos, 0, -1).Y == 21) {
						player2_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 0, -1).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 0, -1);
				}
				else if (map[moveDirection(player2_pos, 0, -1).Y][moveDirection(player2_pos, 0, -1).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, 0, -1);
				}

				else
					player2_pos = moveDirection(player2_pos, 0, -1);
			}
		}
		if (keyPressed(PLAYER2_DOWN) && map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 1; right_2 = 0; left_2 = 0;
			if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'֍') {
					if (moveDirection(player2_pos, 0, 1).X == 40 && moveDirection(player2_pos, 0, 1).Y == 12)
						player2_pos = { 72,10 };
					else if (moveDirection(player2_pos, 0, 1).X == 72 && moveDirection(player2_pos, 0, 1).Y == 10) {
						player2_pos = { 40,12 };
					}
					else if (moveDirection(player2_pos, 0, 1).X == 56 && moveDirection(player2_pos, 0, 1).Y == 4) {
						player2_pos = { 56,21 };

					}
					else if (moveDirection(player2_pos, 0, 1).X == 56 && moveDirection(player2_pos, 0, 1).Y == 21) {
						player2_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 0, 1);
				}

				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 0, 1).X == 15)
						pos_upgrade_bullets_L = 1;

					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 0, 1);
				}

				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 0, 1);
				}
				else if (map[moveDirection(player2_pos, 0, 1).Y][moveDirection(player2_pos, 0, 1).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, 0, 1);
				}
				else
					player2_pos = moveDirection(player2_pos, 0, 1);
			}
		}
		if (keyPressed(PLAYER2_LEFT) && map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 0; right_2 = 0; left_2 = 1;
			if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'֍') {
					if (moveDirection(player2_pos, -1, 0).X == 40 && moveDirection(player2_pos, -1, 0).Y == 12)
						player2_pos = { 72,10 };
					else if (moveDirection(player2_pos, -1, 0).X == 72 && moveDirection(player2_pos, -1, 0).Y == 10) {
						player2_pos = { 40,12 };
					}
					else if (moveDirection(player2_pos, -1, 0).X == 56 && moveDirection(player2_pos, -1, 0).Y == 4) {
						player2_pos = { 56,21 };

					}
					else if (moveDirection(player2_pos, -1, 0).X == 56 && moveDirection(player2_pos, -1, 0).Y == 21) {
						player2_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'❤';
					player2_pos = moveDirection(player2_pos, -1, 0);
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, -1, 0).X == 15)
						pos_upgrade_bullets_L = 1;
					else
						pos_upgrade_bullets_R = 1;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}

				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}
				else if (map[moveDirection(player2_pos, -1, 0).Y][moveDirection(player2_pos, -1, 0).X] == L'Ơ') {
					frag_player_2 = 1;
					pos_frag_player = 1;
					saved_frag_2 = score_bullet_player_2;
					player2_pos = moveDirection(player2_pos, -1, 0);
				}

				else
					player2_pos = moveDirection(player2_pos, -1, 0);
			}
		}
		if (keyPressed(PLAYER2_RIGHT) && map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'║')
		{
			score_move_2++;
			up_2 = 0; down_2 = 0; right_2 = 1; left_2 = 0;
			if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] != L'█' || ghost_player_2 == 1)
			{
				if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'෧') {
					health_player_2--;
					player2_pos = { 100 , 10 };
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'֍') {
					if (moveDirection(player2_pos, 1, 0).X == 40 && moveDirection(player2_pos, 1, 0).Y == 12)
						player2_pos = { 72,10 };
					else if (moveDirection(player2_pos, 1, 0).X == 72 && moveDirection(player2_pos, 1, 0).Y == 10) {
						player2_pos = { 40,12 };
					}
					else if (moveDirection(player2_pos, 1, 0).X == 56 && moveDirection(player2_pos, 1, 0).Y == 4) {
						player2_pos = { 56,21 };

					}
					else if (moveDirection(player2_pos, 1, 0).X == 56 && moveDirection(player2_pos, 1, 0).Y == 21) {
						player2_pos = { 56,4 };

					}
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤')
				{
					health_player_2 += 5;
					ghalb = 0;
					map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'❤';
					player2_pos = moveDirection(player2_pos, 1, 0);
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'✶') {
					upgrade_bullets_2 = 1;
					saved_2 = score_bullet_player_2;
					if (moveDirection(player2_pos, 1, 0).X == 15)
						pos_upgrade_bullets_L = 1;
					else
						pos_upgrade_bullets_R = 1;

					player2_pos = moveDirection(player2_pos, 1, 0);
				}

				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'ѽ')
				{
					move_ghost_player_2 = score_move_2;
					ghost_player_2 = 1;
					pos_ghost_player = 1;
					player2_pos = moveDirection(player2_pos, 1, 0);
				}
				else if (map[moveDirection(player2_pos, 1, 0).Y][moveDirection(player2_pos, 1, 0).X] == L'Ơ') {
					frag_player_2 = 1;
					saved_frag_2 = score_bullet_player_2;
					pos_frag_player = 1;
					player2_pos = moveDirection(player2_pos, 1, 0);
				}


				else
					player2_pos = moveDirection(player2_pos, 1, 0);
			}
		}
		if (keyPressed(PLAYER2_SHOOT)) {
			score_move_2++;
			score_bullet_player_2++;
			if (up_2 == 1) {
				player2_bullet = player2_pos;
				U2 = 1; D2 = 0; L2 = 0; R2 = 0;
			}
			else if (down_2 == 1) {
				player2_bullet = player2_pos;
				D2 = 1; U2 = 0; L2 = 0; R2 = 0;
			}
			else if (left_2 == 1) {
				player2_bullet = player2_pos;
				L2 = 1; U2 = 0; D2 = 0; R2 = 0;
			}
			else if (right_2 == 1) {
				player2_bullet = player2_pos;
				R2 = 1; U2 = 0; D2 = 0; L2 = 0;
			}
		}
		// frag
		if (saved_frag_1 + 2 == score_bullet_player_1)frag_player_1 = 0;
		if (saved_frag_2 + 2 == score_bullet_player_2)frag_player_2 = 0;

		//upgrade bullet
		if (saved_1 + 6 == score_bullet_player_1) {
			upgrade_bullets_1 = 0;
		}
		if (saved_2 + 6 == score_bullet_player_2) {
			upgrade_bullets_2 = 0;
		}
		/////

		// Update bullet positions
		if (player1_bullet.X != -1) {
			if (frag_player_1 == 0)
			{

				if (U == 1) {
					if (map[moveDirection(player1_bullet, 0, -1).Y][moveDirection(player1_bullet, 0, -1).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.Y--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							U = 0; D = 1;
							player1_bullet.Y += 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}
				}
				else if (D == 1)
				{
					if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█' || ghost_player_1 == 1)
					{
						if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█' || ghost_player_1 == 1)
						{
							player1_bullet.Y++;
							if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
								health_player_2--;

							else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
								health_player_2 -= 2;

							if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
								U = 1; D = 0;
								player1_bullet.Y -= 2;
							}

						}
					}
					else {
						player1_bullet.X = -1;
					}

				}
				else if (R == 1)
				{
					if (map[moveDirection(player1_bullet, 1, 0).Y][moveDirection(player1_bullet, 1, 0).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.X++;

						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							R = 0; L = 1;
							player1_bullet.X -= 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}

				}
				else if (L == 1)
				{
					if (map[moveDirection(player1_bullet, -1, 0).Y][moveDirection(player1_bullet, -1, 0).X] != L'█' || ghost_player_1 == 1)
					{
						player1_bullet.X--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2--;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 2;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							R = 1; L = 0;
							player1_bullet.X += 2;
						}
					}
					else {
						player1_bullet.X = -1;
					}
				}
				else {
					player1_bullet.X = -1;
				}

			}
			else {
				if (U == 1) {
					if (map[moveDirection(player1_bullet, 0, -1).Y][moveDirection(player1_bullet, 0, -1).X] != L'█')
					{
						player1_bullet.Y--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 5;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else if (D == 1)
				{
					if (map[moveDirection(player1_bullet, 0, 1).Y][moveDirection(player1_bullet, 0, 1).X] != L'█')
					{
						player1_bullet.Y++;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else if (R == 1)
				{
					if (map[moveDirection(player1_bullet, 1, 0).Y][moveDirection(player1_bullet, 1, 0).X] != L'█')
					{
						player1_bullet.X++;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}

				}
				else if (L == 1)
				{
					if (map[moveDirection(player1_bullet, -1, 0).Y][moveDirection(player1_bullet, -1, 0).X] != L'█')
					{
						player1_bullet.X--;
						if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 0)
							health_player_2 -= 1;

						else if (player1_bullet.Y == player2_pos.Y && player1_bullet.X == player2_pos.X && upgrade_bullets_1 == 1)
							health_player_2 -= 5;

						if (map[player1_bullet.Y][player1_bullet.X] == L'║') {
							wall_x = player1_bullet.X;
							wall_y = player1_bullet.Y;
							if (player1_pos.X <= player1_bullet.X + 1 && player1_pos.X >= player1_bullet.X - 1 && player1_pos.Y <= player1_bullet.Y + 1 && player1_pos.Y >= player1_bullet.Y - 1) {
								health_player_1--;
							}
							if (player2_pos.X <= player1_bullet.X + 1 && player2_pos.X >= player1_bullet.X - 1 && player2_pos.Y <= player1_bullet.Y + 1 && player2_pos.Y >= player1_bullet.Y - 1) {
								health_player_2--;
							}
							player1_bullet.X = -1;
						}
					}
					else {
						if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
							health_player_2--;
						}
						player1_bullet.X = -1;
					}
				}
				else {
					if (player2_pos.X <= player1_bullet.X + 2 && player2_pos.X >= player1_bullet.X - 2 && player2_pos.Y <= player1_bullet.Y + 2 && player2_pos.Y >= player1_bullet.Y - 2) {
						health_player_2--;
					}
					player1_bullet.X = -1;
				}
			}
		}
		if (player2_bullet.X != -1) {
			if (frag_player_2 == 0)
			{
				if (U2 == 1) {
					if (map[moveDirection(player2_bullet, 0, -1).Y][moveDirection(player2_bullet, 0, -1).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.Y--;

						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							U2 = 0; D2 = 1;
							player2_bullet.Y += 2;
						}
					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (D2 == 1)
				{
					if (map[moveDirection(player2_bullet, 0, 1).Y][moveDirection(player2_bullet, 0, 1).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.Y++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							U2 = 0; D2 = 1;
							player2_bullet.Y += 2;
						}
					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (R2 == 1)
				{
					if (map[moveDirection(player2_bullet, 1, 0).Y][moveDirection(player2_bullet, 1, 0).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.X++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							R2 = 0; L2 = 1;
							player2_bullet.X -= 2;
						}

					}
					else {
						player2_bullet.X = -1;
					}
				}
				else if (L2 == 1)
				{
					if (map[moveDirection(player2_bullet, -1, 0).Y][moveDirection(player2_bullet, -1, 0).X] != L'█' || ghost_player_2 == 1)
					{
						player2_bullet.X--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1--;
						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 2;
						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							R2 = 1; L2 = 0;
							player2_bullet.X += 2;
						}

					}
					else {
						player2_bullet.X = -1;
					}
				}
				else {
					player2_bullet.X = -1;
				}

			}


			else {
				if (U2 == 1) {
					if (map[moveDirection(player2_bullet, 0, -1).Y][moveDirection(player2_bullet, 0, -1).X] != L'█')
					{
						player2_bullet.Y--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else if (D2 == 1)
				{
					if (map[moveDirection(player2_bullet, 0, 1).Y][moveDirection(player2_bullet, 0, 1).X] != L'█')
					{
						player2_bullet.Y++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else if (R2 == 1)
				{
					if (map[moveDirection(player2_bullet, 1, 0).Y][moveDirection(player2_bullet, 1, 0).X] != L'█')
					{
						player2_bullet.X++;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}

				}
				else if (L2 == 1)
				{
					if (map[moveDirection(player2_bullet, -1, 0).Y][moveDirection(player2_bullet, -1, 0).X] != L'█')
					{
						player2_bullet.X--;
						if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 0)
							health_player_1 -= 1;

						else if (player2_bullet.Y == player1_pos.Y && player2_bullet.X == player1_pos.X && upgrade_bullets_2 == 1)
							health_player_1 -= 5;

						if (map[player2_bullet.Y][player2_bullet.X] == L'║') {
							wall_x = player2_bullet.X;
							wall_y = player2_bullet.Y;
							if (player2_pos.X <= player2_bullet.X + 1 && player2_pos.X >= player2_bullet.X - 1 && player2_pos.Y <= player2_bullet.Y + 1 && player2_pos.Y >= player2_bullet.Y - 1) {
								health_player_2--;
							}
							if (player1_pos.X <= player2_bullet.X + 1 && player1_pos.X >= player2_bullet.X - 1 && player1_pos.Y <= player2_bullet.Y + 1 && player1_pos.Y >= player2_bullet.Y - 1) {
								health_player_1--;
							}
							player2_bullet.X = -1;
						}
					}
					else {
						if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
							health_player_1--;
						}
						player2_bullet.X = -1;
					}
				}
				else {
					if (player1_pos.X <= player2_bullet.X + 2 && player1_pos.X >= player2_bullet.X - 2 && player1_pos.Y <= player2_bullet.Y + 2 && player1_pos.Y >= player2_bullet.Y - 2) {
						health_player_1--;
					}
					player2_bullet.X = -1;
				}
			}

		}

		// Draw map
		SetConsoleOutputCP(65001);
		_setmode(_fileno(stdout), _O_U16TEXT);

		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 112; j++) {
				map[i][j] = L' ';
			}
		}
		///////////////////dor kesh
		for (int i = 0; i < 24; i++) {
			map[i][0] = L'█';
		}
		for (int i = 0; i < 112; i++) {
			map[0][i] = L'█';
		}
		for (int i = 0; i < 112; i++) {
			map[23][i] = L'█';
		}
		for (int i = 0; i < 24; i++) {
			map[i][111] = L'█';
		}
		//////////////////////////////khat chi
		for (int i = 4; i < 20; i++) {
			if (wall_x != 55 && wall_y != i)
				map[i][55] = L'║';
		}

		for (int i = 4; i < 20; i++)
		{
			if (wall_x != 58 && wall_y != i)
				map[i][58] = L'║';
		}
		for (int i = 67; i < 105; i++)
			map[11][i] = L'█';

		for (int i = 6; i < 46; i++)
			map[11][i] = L'█';


		map[12][43] = L'█';
		map[12][42] = L'█';
		map[13][41] = L'█';
		map[13][40] = L'█';
		map[14][39] = L'█';
		map[14][38] = L'█';
		map[15][37] = L'█';
		map[15][36] = L'█';

		map[12][69] = L'█';
		map[12][70] = L'█';
		map[13][71] = L'█';
		map[13][72] = L'█';
		map[14][73] = L'█';
		map[14][74] = L'█';
		map[15][75] = L'█';
		map[15][76] = L'█';


		map[10][43] = L'█';
		map[10][42] = L'█';
		map[9][41] = L'█';
		map[9][40] = L'█';
		map[8][39] = L'█';
		map[8][38] = L'█';
		map[7][37] = L'█';
		map[7][36] = L'█';



		map[10][69] = L'█';
		map[10][70] = L'█';
		map[9][71] = L'█';
		map[9][72] = L'█';
		map[8][73] = L'█';
		map[8][74] = L'█';
		map[7][75] = L'█';
		map[7][76] = L'█';

		map[3][14] = L'█';
		map[3][15] = L'█';
		map[4][13] = L'█';
		map[4][12] = L'█';
		map[5][14] = L'█';
		map[5][15] = L'█';

		map[3][97] = L'█';
		map[3][96] = L'█';
		map[4][99] = L'█';
		map[4][98] = L'█';
		map[5][97] = L'█';
		map[5][96] = L'█';




		map[20][14] = L'█';
		map[20][15] = L'█';
		map[19][13] = L'█';
		map[19][12] = L'█';
		map[18][14] = L'█';
		map[18][15] = L'█';

		map[18][97] = L'█';
		map[18][96] = L'█';
		map[19][99] = L'█';
		map[19][98] = L'█';
		map[20][97] = L'█';
		map[20][96] = L'█';


		map[3][56] = L'█';
		map[3][55] = L'█';
		map[3][57] = L'█';
		map[3][58] = L'█';

		map[20][56] = L'█';
		map[20][55] = L'█';
		map[20][57] = L'█';
		map[20][58] = L'█';
		for (int i = 0; i < 24; i++) {

			for (int j = 0; j < 112; j++) {
				if (i == 4 && j == 96) {
					map[i][j] = L'෧';
					wprintf(L"\033[1;35m%wc\033[0m", map[i][j]);

				}
				else if (i == 19 && j == 15) {
					map[i][j] = L'෧';
					wprintf(L"\033[1;35m%wc\033[0m", map[i][j]);
				}
				else if (i == 10 && j == 72) {
					map[i][j] = L'֍';
					wprintf(L"\033[1;33m%wc\033[0m", map[i][j]);
				}
				else if (i == 12 && j == 40) {
					map[i][j] = L'֍';
					wprintf(L"\033[1;33m%wc\033[0m", map[i][j]);
				}
				else if (i == 4 && j == 15 && pos_upgrade_bullets_L == 0)
				{
					map[i][j] = L'✶';
					wprintf(L"\033[1;33m%wc\033[0m", map[i][j]);
				}
				else if (i == 19 && j == 96 && pos_upgrade_bullets_R == 0)
				{
					map[i][j] = L'✶';
					wprintf(L"\033[1;33m%wc\033[0m", map[i][j]);
				}
				else if (i == 11 && j == 56 && ghalb == 0)
				{
					map[i][j] = L'❤';
					wprintf(L"%wc", map[i][j]);
				}
				else if (i == 15 && j == 56)
				{
					map[i][j] = L'෧';
					wprintf(L"\033[1;35m%wc\033[0m", map[i][j]);
				}
				else if (i == 18 && j == 56 && pos_ghost_player == 0)
				{
					map[i][j] = L'ѽ';
					wprintf(L"%wc", map[i][j]);
				}
				else if (i == 8 && j == 56 && pos_frag_player == 0)
				{
					map[i][j] = L'Ơ';
					wprintf(L"\033[1;31m%wc\033[0m", map[i][j]);
				}
				else if (i == 4 && j == 56)
				{
					map[i][j] = L'֍';
					wprintf(L"\033[1;34m%wc\033[0m", map[i][j]);
				}
				else if (i == 21 && j == 56)
				{
					map[i][j] = L'֍';
					wprintf(L"\033[1;34m%wc\033[0m", map[i][j]);
				}


				else
					wprintf(L"%wc", map[i][j]);
			}
			wprintf(L"\n");
		}

		// Draw players
		map[player1_pos.Y][player1_pos.X] = '1';
		map[player2_pos.Y][player2_pos.X] = '2';

		// Draw bullets
		if (player1_bullet.X < 112 && player1_bullet.X != -1) {
			if (frag_player_1 == 0)
				map[player1_bullet.Y][player1_bullet.X] = '.';
			else
				map[player1_bullet.Y][player1_bullet.X] = L'Ơ';
		}

		if (player2_bullet.X < 112 && player2_bullet.X != -1) {
			if (frag_player_2 == 0)
				map[player2_bullet.Y][player2_bullet.X] = '.';
			else
				map[player2_bullet.Y][player2_bullet.X] = L'Ơ';
		}
		// Output to console
		for (int y = 0; y < 24; y++) {
			COORD place;
			place.X = 0;
			place.Y = y;
			WriteConsoleOutputCharacterW(hStdout, map[y], 112, place, &bytes_written);
			//WriteConsoleOutputCharacterA is a function in the Windows Console API that writes a string of characters to a console screen buffer at a specified location.
			//The first parameter identifies where to write the characters
			//The second parameter is a C-style string or an array of characters that you want to write to the screen buffer.
			//The third parameter specifies how many characters from the string should be written to the screen buffer.
			//The fourth parameter specifies the coordinates (given as a COORD structure) of the first cell in the console screen buffer where writing will begin.
			//The fifth parameter is a pointer to a variable that receives the number of characters actually written to the console screen buffer.

		}

		_setmode(_fileno(stdout), _O_TEXT);
		printf("\n1:%d,2:%d,%d,%d", health_player_1, health_player_2, score_move_2, move_ghost_player_1);
		// Game tick delay
		Sleep(100);
	}
}

















int main() {
	start_page();
	//menu_inform();


	return 0;
}