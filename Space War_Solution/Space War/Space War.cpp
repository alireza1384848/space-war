#pragma warning(disable:4996)
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
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
void menu_inform();
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
			break;
		case 2:
			break;
		case 3:
			exit(0);
			break;
		default:
			break;
		}




}











int main() {
	start_page();
	//menu_inform();


	return 0;
}