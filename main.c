#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void showIntro();
void showMenu();
void showGameMenu();
void playGame();

int diceRoll();

int ASDecides();

int main() {

	char prompt[3];

	srand(time(NULL));

	showIntro();

	/* Main menu loop */

	while (strcmp(prompt, "q\0")) {

		/* show main prompt and respond */
		printf(">");
		scanf("%s", prompt);

		if (strcmp(prompt, "m\0")==0) {

			showMenu();

		} else if (strcmp(prompt, "n\0")==0) {

			playGame();

		} else if (strcmp(prompt, "q\0")!=0){

			printf("That's not a thing.\n");
		}
	}

	return 0;
}

void playGame() {

	printf("The game begins!\t(m ... Show Menu)\n");

	char gamePrompt[3];
	int thisRoll=0;
	int thisTurn=0;
	int player1score=0;
	int player2score=0;

	/* game loop to 100 */

	while (strcmp(gamePrompt, "q\0")!=0 &&
		  (player1score <100 && player2score <100)) {

		/* player 1 turn */

		printf("-Your turn-\n");
		thisTurn = 0;

		thisRoll = diceRoll();
		printf("You roll a %d.\n", thisRoll);

		while (thisRoll !=1 && strcmp(gamePrompt, "h\0")!=0) {

			thisTurn += thisRoll;

			/* show game prompt and respond */
			printf("[%d+%d] >", player1score, thisTurn);
			scanf("%s", gamePrompt);

			if (strcmp(gamePrompt, "m\0")==0) {

				showGameMenu();
				thisRoll =0;

			} else if (strcmp(gamePrompt, "r\0")==0) {

				/* roll again */
				//printf("roll again activated...\n");

				thisRoll = diceRoll();

				printf("You rolled a %d.\n", thisRoll);

			} else if (strcmp(gamePrompt, "h\0")==0) {

				/* hold score */
				//printf("hold activated...\n");
				player1score += thisTurn;
				thisTurn=0;
				thisRoll=0;
				sleep(1);

			} else if (strcmp(gamePrompt, "q\0")!=0){

				printf("That's not a thing.\n");
				thisRoll =0;

			} else {
				break;
			}
		} /* End Player 1 turn */

		/* player 2 turn */

		if (strcmp(gamePrompt, "q\0")!=0 && player1score < 100) {

			printf("-My turn.-\n");
			sleep(1);

			thisTurn = 0;
			thisRoll = diceRoll();
			printf("I roll a %d.\n", thisRoll);

			while (thisRoll !=1) {

				thisTurn += thisRoll;

				printf("[%d+%d] ? ", player2score, thisTurn);

				if (ASDecides()==1) {

					sleep(1);

					printf("I roll again.\n");
					thisRoll = diceRoll();
					sleep(1);
					printf("I roll a %d.\n", thisRoll);

					if (thisRoll != 1){

						thisTurn += thisRoll;
					}

				} else {

					sleep(1);

					printf("I choose to hold.\n");
					player2score += thisTurn;
					thisTurn=0;
					thisRoll=0;
					sleep(1);
					break;

				}
				sleep(1);

			} /* End Player 2 turn */

			gamePrompt[0] = 'f';
		}

		printf("\tYou: %d\t\tMe: %d\n", player1score, player2score);
		sleep(1);

	} /* end game loop to 100 */

	/* Winning! */

	if (player1score >= 100 ) {
		printf("You Win!\n");
	} else if (player2score >= 100) {
		printf("I win!\n");
	} else {
		printf("You forfeit!\n");
	}

	printf("Game over.\t(m ... Show Menu)\n");
}

int diceRoll() {

	/* biased modulo dice roll */

	return (rand()%6)+1;
}

int ASDecides() {

	/* Artificial Stupid - simple binary coin flip */

	return rand()%2;
}

void showMenu() {

	printf("\tm ...\tShow Menu\n");
	printf("\tn ...\tNew Game\n");
	printf("\tq ...\tQuit Pig\n");
}

void showGameMenu() {

	printf("\tm ...\tShow Menu\n");
	printf("\tr ...\tRoll Again\n");
	printf("\th ...\tHold Score\n");
	printf("\tq ...\tQuit Game\n");
}

void showIntro() {
	printf("                   ____  _\n");
	printf("                  |  _ \\(_) __ _\n");
	printf(" _____ _____ _____| |_) | |/ _` |_____ _____ _____\n");
	printf("|_____|_____|_____|  __/| | (_| |_____|_____|_____|\n");
	printf("                  |_|   |_|\\__, |\n");
	printf("                           |___/\n");

	printf("Welcome to Pig! \t(m ... Show Menu)\n");
}
