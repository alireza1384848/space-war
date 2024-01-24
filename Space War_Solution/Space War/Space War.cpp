#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
struct profile {
	char UserName[40];
	char Password[40];
	char email[40];
};
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
	//////////////////////////////////////////
	magneta();
	printf("\nEnter Your Password=");
	scanf("%s", pass);
	reset();
	system("color 70");
	while (1)
	{
		if (strlen(pass) < 8) {
			system("cls");
			printf("\nYour Password is Too Short \nEnter Other Password=");
			scanf("%s", pass);
		}
		else {
			strcpy(prof.Password, pass);
			break;
		}
	}
	printf("\nEnter Your Password Again=");
	magneta();
	scanf("%s",pass);
	reset();
	system("color 70");
	while (1)
	{
		if (strcmp(pass,prof.Password)!=0) {
			printf("\nYour Passwords isn,t same\nEnter Password=");
			magneta();
			scanf("%s", pass);
			reset();
			system("color 70");
		}
		else {
			break;
		}
	}
	/////////////////////////////////////
	char email[40];
	system("cls");
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
	menu_inform();
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
	system("color 85");
	system("cls");
	printf("Enter Your UserName=");
	yellow();
	scanf("%s", username);
	reset();
	system("cls");
	system("color 85");
	printf("Enter Your Password=");
	yellow();
	while ((pass1 = _getch()) != '\r') {
		pass[i] = pass1;
		i++;
		printf("*");
	}
	reset();
	system("cls");
	
		system("color 00");
	if (Username_checker(username) >= 1&&passfinder(Username_checker(username),pass)==0)
	{
//start menu
	}
	else {
		printf("!!!!!!!!!!!!!Your Username or password is Wrong please try again!!!!!!!!!!!!!!!");
		Sleep(1000);
		system("cls");
		int selected = 1;
		int keypress;
		int p = 45;
		int p1 = 62;
		while (1) {
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
	magneta();
	char Username[40];
	char Email[40];
	printf("Enter your UserName=");
	reset;
	green();
	scanf("%s", Username);
	reset;
	system("cls");
	if (Username_checker(Username) > 0) {
			printf("Enter Your Email=");
			red();
			scanf("%s", Email);
			reset();
	changepass(Email, Username_checker(Username));
	}
	else {
		printf("!!!!!!!!Username isn,t correct!!!!!!!!!!\n");
		forgetpass();
		//star menu game
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
		yellow();
		printf("Enter your New password=");
		scanf("%s", newpass);
		reset();
		red();
		printf("Enter password Again=");
		scanf("%s", newpass1);
		if (strcmp(newpass, newpass1) == 0) {
			strcpy(User_data[loc].Password, newpass);
			Data = fopen("profile.bin", "w");
			for (int j = 1; j <= i ; j++) {
				fwrite(&User_data[j], sizeof(profile), 1, Data);
			}
		}
		else {
			printf("!!!!!!!Passwords Are NOT Same!!!!!!!!!");
			Sleep(1200);
			system("cls");
			changepass(email, loc);
		}
		//fseek(Data, sizeof(profile) * (loc - 1), SEEK_SET);
	}
	else {
		
	}
	fclose(Data);






}


int main() {
	start_page();
	//menu_inform();


	return 0;
}