#define _CRT_NONSTDC_NO_DEPRECATE
#include <fstream>
#pragma warning(disable:4996) 
#include "iGraphics.h"
#include<iostream>
#include<string>
using namespace std;
#define screenWidth 1200
#define screenHeight 800
#define NUMBEROFPLANEENEMY 15
void scorePlate();
int opx=0, opy=0;
bool pause = true;
void enemyShoot();
void restart();
void collisionCheck();
void Plane1AndEnemyCollision();
void gameOver();
bool gameOver1 = false;
int scoreC = 0;
string str;
void saveScore();
void showHighScore();
void scorePlate();
int bgindex = 0;
bool bgSet = false;
int enemyIndex = 0;
//////////////////////////////////////////////////////////////////////////////Menu Page\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void showHighScore(){

	FILE* ptr;
	char str[50];
	ptr = fopen("scores.txt", "a+"); // reading the file in append mode
	string scores;
	int all_scores[100];
	int i = 0;

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}


	while (fgets(str, 50, ptr) != NULL) {
		
		if (str != "\n"){
			all_scores[i++] = stoi(str); //converting the string into integer and storing it in an array

		}
	}
	fclose(ptr);
	int len = i, a;

	//sorting in descending order to determine high scores...

	for (i = 0; i < len; ++i){
		for (int j = i + 1; j < len; ++j)
		{
			if (all_scores[i] < all_scores[j])
			{
				a = all_scores[i];
				all_scores[i] = all_scores[j];
				all_scores[j] = a;
			}
		}

	}




	int space = 300, max_scores = 10;
	char score_text[1000], c;

	for (int i = 0; i < len; i++){
		strcpy_s(score_text, to_string(all_scores[i]).c_str()); // converting the ints to string first and then char array
		iText(500, screenHeight - (space), score_text, GLUT_BITMAP_TIMES_ROMAN_24); // rendering it on display
		space += 35; // space for the next score
		max_scores--; // if it reaches 0, it means total 10 scores have been painted
		if (max_scores <= 0){
			break;
		}

	}


}



/*function to save score in a file in the same directory*/
void saveScore(){
	FILE *fp; //file pointer

	fp = fopen("scores.txt", "a"); //open the existing file in append mode
	char final_score[33];

	itoa(scoreC, final_score, 10); //converting numbers to string

	fprintf(fp, "%s", final_score); // printing final score to text file
	fprintf(fp, "%s", "\n");

	fclose(fp); //close file
}
struct buttonCordinate{
	int x;
	int y;
}bCordinate[4];
int mposX, mposY;
char button[10][15] = { "bg\\Play.bmp","bg\\Music.bmp","bg\\Score.bmp","bg\\AboutUs.bmp","bg\\exit.bmp"};
char homemenu[15] = {"bg\\Home3.bmp"};
char play[2][15] = { "bg\\100.bmp", "bg\\1000.bmp" };
char option[15] = { "bg\\1000.bmp"};
char sound[3][15] = { "bg\\sound.bmp", "bg\\on.bmp", "bg\\off.bmp" };
char score[25] = {"bg\\20.bmp"};
char about[25] = { "bg\\credit.bmp" };
char Exit[25] = { "bg\\22.bmp" };

//BACKGROUND Properties
char bgMain[1][20] = {"bg\\100.bmp" };
struct backGround{
	int x;
	int y;
};

//                                                                  PLANE1 PROPERTIES
char plane1[2][20] = { "char\\P1.bmp", "char\\P2.bmp" };
int plane1CordinateX = 0;
int plane1CordinateY = 400;
int plane1Index = 0;
char plane1Stand[15] = { "char\\P1.bmp" };
bool plane1StandPosition = true;
int plane1StandCounter = 0;


void plane1Movement(){
	
	if (!plane1StandPosition){

		iShowBMP2(plane1CordinateX, plane1CordinateY, plane1[plane1Index], 0);
		plane1StandCounter++;
		if (plane1StandCounter >= 20)
		{
			plane1StandCounter = 0;
			plane1Index = 0;
			plane1StandPosition = true;
		
		}
	}
	else{
		iShowBMP2(plane1CordinateX, plane1CordinateY, "char\\P1.bmp", 0);
	}
}
//                                                       ENEMY PLANE PROPERTIES
char planeE[4][20] = { "char\\111.bmp", "char\\121.bmp" ,};
struct Enemy{
	int planeEnemy1PositionX;
	int planeEnemy1PositionY;
	int planeEnemyIndex;
	bool planeEnemyShow;
};

Enemy enemy[NUMBEROFPLANEENEMY];

void planeEnemyMovement(){
	for (int i = 0; i < NUMBEROFPLANEENEMY; i++)
	{
		if (enemy[i].planeEnemyShow){
			iShowBMP2(enemy[i].planeEnemy1PositionX, enemy[i].planeEnemy1PositionY, planeE[enemy[i].planeEnemyIndex], 0);
		}
	}
}
int gameState = -1;

//////////////////////////////////// PLAYER BULLET PROPERTIES side1\\\\\\\\\\\\\\\\

char BulletPicplayer[1][20] = { "char\\bollet1.bmp" };
bool firing = false;
bool shoot = false;
bool firing1 = false;
bool shoot1 = false;
struct PlayerBullet{
	int playerBulletPositionX;
	int playerBulletPositionY;
	int playerBulletIndex;
	bool playerBulletShow = false;
};
PlayerBullet playerBullet;
void setPlayerBollet(){
	if (pause){
	
			playerBullet.playerBulletPositionX = plane1CordinateX + 60;
			playerBullet.playerBulletPositionY = plane1CordinateY + 60;
			
			playerBullet.playerBulletShow = true;
		
     }
}
PlayerBullet playerBullet1;
void setPlayerBollet1(){
	if (pause){
		
			playerBullet1.playerBulletPositionX = plane1CordinateX + 60;
			playerBullet1.playerBulletPositionY = plane1CordinateY + 20;
			
			playerBullet1.playerBulletShow = true;
		

	}
}

void showPlayerBullet(){
	if (firing && shoot){

		if (playerBullet.playerBulletShow)
			iShowBMP2(playerBullet.playerBulletPositionX, playerBullet.playerBulletPositionY, BulletPicplayer[playerBullet.playerBulletIndex], 0);
		
	}
}
void playerShoot(){
	if (pause){
		if (shoot){
			
				playerBullet.playerBulletPositionX += 10;
				if (playerBullet.playerBulletPositionX >= screenWidth){
					firing = false;
					shoot = false;
					playerBullet.playerBulletShow = false;
					playerBullet.playerBulletPositionX = 11000000000000000;
					playerBullet.playerBulletPositionY = 10000000000000000;
					
				}
				playerBullet.playerBulletIndex++;
				if (playerBullet.playerBulletIndex >= 1){
					playerBullet.playerBulletIndex = 0;

				
				}
			}
		}
	}

//////////////////////////////////// PLAYER BULLET PROPERTIES side2\\\\\\\\\\\\\\\\

void playerShoot1(){
if (pause){
	if (shoot1){
		
			playerBullet1.playerBulletPositionX += 10;
			if (playerBullet1.playerBulletPositionX >= screenWidth){
				plane1Movement();
				firing1 = false;
				shoot1 = false;
				playerBullet1.playerBulletShow = false;
				playerBullet1.playerBulletPositionX = 11000000000000000;
				playerBullet1.playerBulletPositionY = 10000000000000000;
			}
			playerBullet1.playerBulletIndex++;
			if (playerBullet1.playerBulletIndex >= 1){
				playerBullet1.playerBulletIndex = 0;

			}
		}
	}
}
	
void showPlayerBullet1(){
	if (firing1&&shoot1){
		
			if (playerBullet1.playerBulletShow)
				iShowBMP2(playerBullet1.playerBulletPositionX, playerBullet1.playerBulletPositionY, BulletPicplayer[playerBullet1.playerBulletIndex], 0);
		
	}
}


///Back
int BackX = 0;
int BackY = 650;
char BACK[20] = { "bg\\back.bmp" };
void Back(){
	iShowBMP2(BackX, BackY, BACK, 0);
}
///Back
int Back2X = 0;
int Back2Y = 720;
char BACK2[20] = { "bg\\back2.bmp" };
void Back2(){
	iShowBMP2(Back2X, Back2Y, BACK2, 0);
}
///Pause
int pauseX = 80;
int pauseY = 720;
char Pause1[20] = { "bg\\pause.bmp" };
void Pause(){
	iShowBMP2(pauseX, pauseY, Pause1, 0);
}

//////////////////////////////////////Health////////////

int plane1Health = 6;
void ShowHealth(){
	if (plane1Health == 5 || plane1Health == 6){
		iShowBMP2(900, 700, "bg\\health1.bmp",0);
	}
	else if (plane1Health == 4 ){
		iShowBMP2(900, 700, "bg\\health2.bmp", 0);
	}
	else if (plane1Health == 3 ){
		iShowBMP2(900, 700, "bg\\health3.bmp", 0);
	}
	else if (plane1Health == 2 ){
		iShowBMP2(900, 700, "bg\\health4.bmp", 0);
	}
	else if (plane1Health == 1){
		iShowBMP2(900, 700, "bg\\health5.bmp", 0);
	}

	

}
 //////////////////////////////////////////////IDraw//////////////////////////////////////////////////////////////////////////////////////////////

void iDraw()
{
	iClear(); 
	
	if (gameState == -1){
		//HomeMEnu
		iClear();
		iShowBMP(0, 0, homemenu);
		for (int i = 0; i < 5; i++){
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 0);
			
		}
	}
	 if (gameState == 0){
		iClear();
		if (!bgSet)
		iShowBMP(0, 0, "bg\\select.bmp");
		if (bgSet){
			iShowBMP(0, 0, play[bgindex]);
			ShowHealth();

			planeEnemyMovement();
			showPlayerBullet();
			showPlayerBullet1();


			plane1Movement();
			Pause();
			scorePlate();
			Back2();
			Plane1AndEnemyCollision();
			collisionCheck();
			if (plane1Health < 1)
				gameOver();
		}
		
	}

	 if (gameState == 1){
		 iShowBMP(0, 0, option);
		 for (int i = 0; i < 3; i++){
			
			 if (i == 0){
				 opx = 500;
				 opy = 500;
			 }
			 else if (i == 1){
				 opx = 350;
				 opy = 300;
			 }
			 else if (i == 2){
				 opx = 700;
				 opy = 300;
			 }
			 iShowBMP2(opx, opy, sound[i],0);
		 }
		 Back();
	 }
    if (gameState == 2){
	   iShowBMP(0, 0, score);
	   showHighScore();
	   Back();
	}
	 if (gameState == 3){
		iShowBMP(0, 0, about);
		Back();
	}
	 if (gameState ==4 ){
		 exit(0);
	}
		


}


void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse  (int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == -1){
			for (int i = 0; i < 5; i++){
				if (mx >= bCordinate[i].x&& mx <= bCordinate[i].x + 320 && my >= bCordinate[i].y && my <= bCordinate[i].y + 150){
					gameState = i;
					
				}
			}
			pause = false;
		}
		if (gameState != -1 && gameState != 0){
			if (mx >= BackX && mx <= BackX + 150 && my >= BackY&& my <= BackY + 200){
				gameState = -1;
				restart();
				
			}
		}
		if (gameState == 0){
			//pause = true;
			if (mx >= Back2X && mx <= Back2X + 80 && my >= Back2Y&& my <= Back2Y + 80){
				gameState = -1;
				restart();
				

			}
			if (mx >= pauseX && mx <= pauseX + 80 && my >= pauseY&& my <= pauseY + 80){

				if (pause == true){
					pause = false;
					PlaySound(0, 0, 0);

				}
				else{
					pause = true;
					PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);
				}
			}
		if (gameOver1){
			if (mx >= 365 && mx <= 365 + 490  && my >= 100 && my <= 200 + 100){
				gameState = -1;
				restart();
				}
			
			}
		}
		if (gameState == 1){

			if (mx >= 700 && mx <= 700 + 330 && my >= 300 && my <= 300 + 200){

				
					PlaySound(0, 0, 0);
				}
			
			else if (mx >= 350 && mx <= 350 + 330 && my >= 300 && my <= 300 + 200){
				
				PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		if (gameState == 0){
			if (!bgSet){
				if (mx >= 300 && mx <= 350 + 330 && my >= 200 && my <= 400){
					bgindex = 0;
					bgSet = true;
					enemyIndex = 1;
					pause = true;

				}
				else if (mx >= 700 && mx <= 1060 && my >= 200 && my <= 400){
					bgindex = 1;
					bgSet = true;
					enemyIndex = 0;
					pause = true;
				}
			}
		}
		
	}
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}


void iKeyboard(unsigned char key){

	if (key == 'p')
	{
		if (pause == true)
			pause = false;
		else
			pause = true;
	}
	if (key == 'g'){
		if (firing == false && shoot == false){
			
				playerBullet.playerBulletPositionX = plane1CordinateX + 60;
				playerBullet.playerBulletPositionY = plane1CordinateY + 60;
				playerBullet.playerBulletShow = true;
				

				firing = true;
				shoot = true;
			}
		if (firing1 == false && shoot1 == false){
				
					playerBullet1.playerBulletPositionX = plane1CordinateX + 60;
					playerBullet1.playerBulletPositionY = plane1CordinateY + 20;
					playerBullet1.playerBulletShow = true;
					

					firing1 = true;
					shoot1 = true;
				}
			}
		
	
}


void iSpecialKeyboard(unsigned char key)
{
	if (pause){

		if (key == GLUT_KEY_LEFT)
		{
			plane1CordinateX -= 10;
			plane1Index = 1;
			Plane1AndEnemyCollision();
			if (plane1Index >= 1){
				plane1Index = 1;
			}
			plane1StandPosition = false;
		}
		else if (key == GLUT_KEY_RIGHT)
		{
			plane1CordinateX += 10;
			plane1Index = 0;
			Plane1AndEnemyCollision();
			if (plane1Index <= 0){
				plane1Index = 0;
			}
			plane1StandPosition = false;
		}

		else if (key == GLUT_KEY_UP)
		{
			plane1CordinateY += 10;
			plane1Index = 0;
			Plane1AndEnemyCollision();
			if (plane1Index <= 0){
				plane1Index = 0;
			}
			plane1StandPosition = false;
		}

		else if (key == GLUT_KEY_DOWN){
			plane1CordinateY -= 10;
			plane1Index = 0;
			Plane1AndEnemyCollision();
			if (plane1Index <= 0){
				plane1Index = 0;
			}
			plane1StandPosition = false;
		}
	}
}



////////                                                                   ENEMY
void change(){
	if (pause ){
		for (int i = 0; i < NUMBEROFPLANEENEMY; i++){
			enemy[i].planeEnemy1PositionX -= 10;
			if (enemy[i].planeEnemy1PositionX <= 0){
				enemy[i].planeEnemy1PositionX = screenWidth + ((rand() % 50) * 10) + 1;
				enemy[i].planeEnemyShow = true;
			
			}
			else if (enemy[i].planeEnemy1PositionY <= 0){
				enemy[i].planeEnemy1PositionY = rand() % 700 + 1;
			}
			
			if (enemyIndex==0){
				enemy[i].planeEnemyIndex = 0;

			}
			else 
				enemy[i].planeEnemyIndex = 1;

		}
	}
}
		
		
void setPlaneEnemy(){
	
		for (int i = 0; i < NUMBEROFPLANEENEMY; i++)
		{
			enemy[i].planeEnemy1PositionX = screenWidth + (rand() % 50) *10;
			enemy[i].planeEnemy1PositionY = rand() % 700;
			enemy[i].planeEnemyIndex = rand() % 25;
			enemy[i].planeEnemyShow = true;
		}
}

void gameOver(){
	gameOver1 = true;
	pause = false;
	iShowBMP(0, 0,"char\\gameOver.bmp" );
	char score[20] = { 0 };
	iSetColor(165, 42, 42);
	_itoa(scoreC, score, 10);
	iText(400, 400, "FINAL SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(650, 400, score, GLUT_BITMAP_TIMES_ROMAN_24);
}
void restart(){
	bgSet = false;

	saveScore();
	scoreC = 0;
	plane1Health = 6;
	if (plane1Health == 10 || plane1Health == 9){
		iShowBMP2(900, 700, "bg\\health1.bmp", 0);
	}
	else if (plane1Health == 8 || plane1Health == 7){
		iShowBMP2(900, 700, "bg\\health2.bmp", 0);
	}
	else if (plane1Health == 6 || plane1Health == 5){
		iShowBMP2(900, 700, "bg\\health3.bmp", 0);
	}
	else if (plane1Health == 4 || plane1Health == 3){
		iShowBMP2(900, 700, "bg\\health4.bmp", 0);
	}
	else if (plane1Health == 2 || plane1Health == 1){
		iShowBMP2(900, 700, "bg\\health5.bmp", 0);
	}
	scorePlate();
	setPlaneEnemy();
	showPlayerBullet();
	showPlayerBullet1();
	ShowHealth();
	plane1CordinateX = 0;
	plane1CordinateY = 400;
	plane1Index = 0;
	plane1StandPosition = true;
	pause = true;
	Plane1AndEnemyCollision();
	collisionCheck();
}


///////////////////////////score
void scorePlate(){
	char score[20] = { 0 };
	iSetColor(256, 256, 256);
	_itoa(scoreC, score, 10);
	iText(200, 750, "SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(300, 750, score, GLUT_BITMAP_TIMES_ROMAN_24);
}




////////////////////////////Collision\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void collisionCheck()
{
	for (int i = 0; i < NUMBEROFPLANEENEMY; i++){

		if (enemy[i].planeEnemy1PositionX <= playerBullet.playerBulletPositionX && enemy[i].planeEnemy1PositionX+100 >= playerBullet.playerBulletPositionX && enemy[i].planeEnemy1PositionY <= playerBullet.playerBulletPositionY &&enemy[i].planeEnemy1PositionY + 100 >= playerBullet.playerBulletPositionY){

			enemy[i].planeEnemyShow = false;
			playerBullet.playerBulletPositionX = screenWidth + 10000000000;
			enemy[i].planeEnemy1PositionX = 0;
			if (!enemy[i].planeEnemyShow){
				scoreC += 20;
			}
	

		}
		if (enemy[i].planeEnemy1PositionX <= playerBullet1.playerBulletPositionX && enemy[i].planeEnemy1PositionX + 100 >= playerBullet1.playerBulletPositionX && enemy[i].planeEnemy1PositionY <= playerBullet1.playerBulletPositionY &&enemy[i].planeEnemy1PositionY + 100 >= playerBullet1.playerBulletPositionY){

			enemy[i].planeEnemyShow = false;
			playerBullet1.playerBulletPositionX = screenWidth + 10000000000000;
			enemy[i].planeEnemy1PositionX = 0;
			if (!enemy[i].planeEnemyShow){
				scoreC += 20;
			}
			}
			
		}
	
	
}
void Plane1AndEnemyCollision(){

	for (int i = 0; i < NUMBEROFPLANEENEMY; i++){
		if (enemy[i].planeEnemy1PositionX <= plane1CordinateX+150  && enemy[i].planeEnemy1PositionX+100 >= plane1CordinateX && enemy[i].planeEnemy1PositionY >= plane1CordinateY &&enemy[i].planeEnemy1PositionY + 100 <= plane1CordinateY+150 ){
			if (enemy[i].planeEnemyShow){
				plane1Health--;
				if (plane1Health <= 0){
					gameOver();
				}
			}
				enemy[i].planeEnemyShow = false; 
				enemy[i].planeEnemy1PositionX = 0;
			}

	}

}


int main()
{

	int sum = 0;
	for (int i = 4; i >= 0; i--){
		bCordinate[i].x = 100;
		bCordinate[i].y = sum;
		sum += 150;
	}
	PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);
	
	plane1Movement();
	setPlaneEnemy();
	iSetTimer(150, change);
	setPlayerBollet();
	iSetTimer(10, playerShoot); 
	setPlayerBollet1();
	iSetTimer(10, playerShoot1);
	iSetTimer(1,Plane1AndEnemyCollision);
	iSetTimer(1,collisionCheck);
	iSetTimer(150, ShowHealth);
	iInitialize(screenWidth, screenHeight, "EVER SPACE");
	iStart();
	return 0;
}