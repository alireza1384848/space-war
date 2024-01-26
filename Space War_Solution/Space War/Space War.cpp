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
void shape_Map();
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
		shape_Map();
	}
	else {
		signin_player2(loc_player_1);
	}


}

void shape_Map() {

	SetConsoleOutputCP(65001);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wchar_t map[24][112];
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
			if (i == 4 && j == 55) {
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







int main() {
	start_page();
	//menu_inform();


	return 0;
}