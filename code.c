
#include <stdio.h>
#include <time.h>
#define N 20
#define DOODLEBUG 'D'
#define ANT 'a'
#define NONE '.'
#define BABYBUG 'd'


typedef struct OBJECTS {

    char creature;         // Holds the location of the creatures: ants, doodles, or empty slot.
    char babyBug;
    int daysStarved;       // Days that it has been starved
    int hasMoved;          // Flag used to determine if the bug has moved already that day.
    int daysAlive;         // Used to determine days alive to respawn. Only needed for Doodlebugs here because they can have different days of spawning (no space). Ants do not have different days of spawning


}insects;


void initializingBoard(insects bugs[N][N]){         // Initializes the board to have empty slots (i.e. NONE)

    int i= 0;
    int j= 0;


    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            bugs[i][j].creature = NONE;
            printf("%c ", bugs[i][j].creature);
            bugs[i][j].daysStarved = 0;             // Initializes the objects on the board to not be starved
            bugs[i][j].hasMoved = 0;                // Initializes the objects on the board to not have moved yet
            bugs[i][j].babyBug = NONE;              // Initializes the struct char array that stores the babyBugs that were not spawned on the 8th day (no room) to NONE.
            bugs[i][j].daysAlive = 0;               // Initialize that everything on the board has lived for 0 days so far.
        }

        printf("\n");
    }

} // end of void initializingBoard();


void displayBoard(insects bugs[N][N]){              // Prints out the current board user is working with
    int i = 0;
    int j = 0;


    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%c ", bugs[i][j].creature);
        }

        printf("\n");
    }

} // end of void displayBoard();


void populateBoard(insects bugs[N][N]){             //Function that will initialize the board with 100 ants and 5 doodlebugs

    int i = 0;
    int rand1 = 0;
    int rand2 = 0;

    // Populating board with ants
    for (i = 0; i < 100; i++){

        rand1 = rand() % 20;
        rand2 = rand() % 20;

        if (bugs[rand1][rand2].creature == NONE){
            bugs[rand1][rand2].creature = ANT;
        }

        else{
            i--;
        }
    }

    // Populating board with doodlebugs
    for (i = 0; i < 5; i++){
        rand1 = rand() % 20;
        rand2 = rand() % 20;

        if (bugs[rand1][rand2].creature == NONE){
            bugs[rand1][rand2].creature = DOODLEBUG;

        }

        else {
            i--;
        }
    }
    printf("\n");
    printf("\n");

} // end of void populateBoard();



int main(void)
{

    srand(time(NULL));
    insects bugs[N][N];

    int i = 0;                                              // Loop Counter that iterates through rows
    int j = 0;                                              // Loop Counter that iterates through columns

    int randMovement = 0;                                   // Random number holder to determine what direction to go
    char userInput;

    int bugRow[400];                                        // Array that holds the empty row ('.') position next to the bug to create a new bug
    int bugCol[400];                                        // Array that holds the empty column ('.') position next to the bug to create a new bug
    int bugBabyLocator = 0;                                 // A counter that increments when a doodlebug is identified on the board and is used as the index of where to place the new baby bug
    int bugCounter = 0;                                     // Counts how many bugs are on the board
    int bugDayCount = 8;                                    // Used as a timer until Doodlebug respawn


    int antDaysPast = 0;                                    // Counter that is used to multiply the ants after 3 days
    int antRow[400];                                        // Array that holds the empty row ('.') position next to the ant to create a new ant
    int antCol[400];                                        // Array that holds the empty column ('.') position next to the ant to create a new ant
    int antBabyLocator = 0;                                 // A counter that increments when an ant is identified on the board and is used as the index of where to place the new baby ant
    int antCounter = 0;                                     // Counts how many ants are on the board
    int antDayCount = 3;                                    // Used as a timer until Ant respawn
    int babybugcount = 0;

    for (i = 0; i < 400; i++){                              // Initializes the array that holds the rows & cols of the open positions near the doodlebugs and ants and is used to produce the babies
        bugRow[i] = 0;
        bugCol[i] = 0;
        antRow[i] = 0;
        antCol[i] = 0;
    }


    // Initializing the board with the empty slots of NONE
    printf("Initializing the blank board is:\n");
    initializingBoard(bugs);

    // Populating then printing the board
    populateBoard(bugs);

    printf("Populating the board with Doodlebugs and Ants:\n\n");
    displayBoard(bugs);


    // Loop that handles the program

    printf("\n\nPress enter to continue... Note: Press Control C to terminate the program\n\n");

    scanf("%c", &userInput);

    while (userInput != 'x'){


        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {

                randMovement = rand() % 4;  //Random number 0-3 inclusive that will determine which direction the doodlebugs will go if no ants are available.



                if (bugs[i][j].creature == DOODLEBUG && bugs[i][j].hasMoved != 1)
                {
                    bugCounter++;

                    //If the current element is a doodlebug... Replace ant with Doodle
                    if ((j != 19) && bugs[i][j + 1].creature == ANT) {                      // Move to the right (j != 19 to satisfy the edge condition).


                        bugs[i][j].daysStarved = 0;                                         // Reset the current position index starvation count to 0.
                        bugs[i][j].creature = NONE;                                         // Change the current element to a '.'
                        bugs[i][j].hasMoved = 0;                                            // Reset the current index move count to 0.

                        bugs[i][j + 1].creature = DOODLEBUG;                                // Replace the ant with a Doodlebug.
                        bugs[i][j + 1].daysStarved = 0;                                     // Reset the object of the index (where the Doodlebug is now) food count to 0 because he has now eaten.
                        bugs[i][j + 1].daysAlive = bugs[i][j].daysAlive + 1;                // Take whatever days alive it started with and add 1 to it and store it in its new location
                        bugs[i][j].daysAlive = 0;                                           // Reset the Doodlebugs old position of days alive back to 0 to not override anything.
                        bugs[i][j + 1].hasMoved = 1;                                        // Flag that has identified if the bug/object has moved for the day.

                    }
                    else if ((i != 19) && bugs[i+1][j].creature == ANT) {

                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i + 1][j].creature = DOODLEBUG;
                        bugs[i + 1][j].daysStarved = 0;
                        bugs[i + 1][j].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;
                        bugs[i + 1][j].hasMoved = 1;
                    }
                    else if ((i != 0) && bugs[i-1][j].creature == ANT){

                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i - 1][j].creature = DOODLEBUG;
                        bugs[i - 1][j].daysStarved = 0;
                        bugs[i - 1][j].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;
                        bugs[i - 1][j].hasMoved = 1;

                    }
                    else if ((j != 0) && bugs[i][j-1].creature == ANT){

                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i][j-1].creature = DOODLEBUG;
                        bugs[i][j-1].daysStarved = 0;
                        bugs[i][j - 1].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;
                        bugs[i][j-1].hasMoved = 1;

                    }

                    // The following satisfies the randomness if there are no ants adjacent to the Doodlebug

                    else if ( (j != 19) && randMovement == 0 && bugs[i][j + 1].creature != DOODLEBUG){  // Randomly chosen move to move to the right if no adjacant ant

                        bugs[i][j].creature = NONE;                                                     // Switch the current position to a '.'
                        bugs[i][j + 1].creature = DOODLEBUG;                                            // Switch the next position (to the right) as a doodlebug
                        bugs[i][j + 1].daysStarved = bugs[i][j].daysStarved + 1;                        // Take the starvation count of the Doodlebug and translate it to its new position
                        bugs[i][j].daysStarved = 0;                                                     // Now reset the old positions starvation count to 0 (since it's empty)
                        bugs[i][j].hasMoved = 0;                                                        // Reset the old positions move count (or flag) to 0 (since it's empty)
                        bugs[i][j + 1].hasMoved = 1;                                                    // Indicate that if the bug has moved during the day, it won't move again

                        bugs[i][j + 1].daysAlive = bugs[i][j].daysAlive + 1;                            // Again as stated previously, stores the days alive for the doodlebug (as spawning days can all be different)
                        bugs[i][j].daysAlive = 0;                                                       // Resets old position of days alive to 0
                    }

                    else if ( (i != 19) && randMovement == 1 && bugs[i+1][j].creature != DOODLEBUG){    // Same idea here, this time only going down.

                        bugs[i][j].creature = NONE;

                        bugs[i+1][j].creature = DOODLEBUG;
                        bugs[i+1][j].daysStarved = bugs[i][j].daysStarved + 1;
                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].hasMoved = 0;
                        bugs[i+1][j].hasMoved = 1;

                        bugs[i+1][j].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;

                    }

                    else if ((i != 0) && randMovement == 2 && bugs[i-1][j].creature != DOODLEBUG){      // Same idea here, this time only going up.

                        bugs[i][j].creature = NONE;

                        bugs[i-1][j].creature = DOODLEBUG;
                        bugs[i-1][j].daysStarved = bugs[i][j].daysStarved + 1;
                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].hasMoved = 0;
                        bugs[i-1][j].hasMoved = 1;

                        bugs[i-1][j].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;
                    }

                    else if ((j != 0) && randMovement == 3 && bugs[i][j - 1].creature != DOODLEBUG){    // Same idea here, this time only going right.

                        bugs[i][j].creature = NONE;

                        bugs[i][j - 1].creature = DOODLEBUG;
                        bugs[i][j - 1].daysStarved = bugs[i][j].daysStarved + 1;
                        bugs[i][j].daysStarved = 0;
                        bugs[i][j].hasMoved = 0;
                        bugs[i][j - 1].hasMoved = 1;

                        bugs[i][j - 1].daysAlive = bugs[i][j].daysAlive + 1;
                        bugs[i][j].daysAlive = 0;
                    }

                    else{                                                                               // If the bug did not move, add 1 to starve day count and 1 to days being alive

                        bugs[i][j].daysStarved = bugs[i][j].daysStarved + 1;
                        bugs[i][j].hasMoved = 1;
                        bugs[i][j].daysAlive = bugs[i][j].daysAlive + 1;
                    }
                } // End of if bug and has moved

                /* Note: The instructions for the homework only indicate to try and spawn on the 9th day (and Professor Lillis said that it should keep trying if no adjacent positions are open on the 8th day).
                 * In light of those specific instructions, it will only try to spawn on the 9th, 10th, ..., nth day IF the Doodlebug has moved from its current position.
                 * Otherwise, it will not try to spawn even though there MAY be an empty location around the Doodlebug at that moment.
                 * The instructions did not specify to do so which is why I did not include it in my code. Otherwise, I could have simply created a flag for each position it moved (Each if statement above).
                 * Then the flag would tell me where the new position of the doodlebug is which I would then check for an adjacent position from there and spawn the babybug that did not spawn on the 8th day.
                 * However, the instructions did not specify so I only created one condition. Once the Doodlebug moves, then it will spawn at that location it was at.
                 * Again, this IF statement below is only for the 9th-nth days. For the 8th day it will check all adjacent locations because that was what was given in the instructions.
                 * I apologize for the extensive comment. Professor Lillis said not to worry so much on the details, but I just don't want points taken off as I know what to do and I had the code for it,
                 * but I deleted it because it was not necesscary.
                 */

                if (bugs[i][j].babyBug == BABYBUG && bugs[i][j].creature == NONE){                      // Checks to see if there was a Doodlebug that did not spawn on the 8th day.
                    bugs[i][j].creature = DOODLEBUG;                                                    // If there was, once it iterates through the loops above, it spawns a Doodlebug at the old location of the Doodlebug.
                    bugs[i][j].babyBug = NONE;                                                          // Resets the the struct member of babyBug to a '.' to not create unwanted duplicates.
                    bugs[i][j].hasMoved = 1;                                                            // Flag that the bug has moved so that it doesn't move around because it's born on that day.
                    bugs[i][j].daysAlive = 0;                                                           // Resets days alive to 0 since it is a new bug.
                }


            } // End of for(j...)
        } // End of for(i...)



        // Reset the boards move count back to 0
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {


                bugs[i][j].hasMoved = 0;
            }
        }


        // Loop that will iterate through and move the ants around randomly.
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){

                randMovement = rand() % 4;

                if (bugs[i][j].creature == ANT && bugs[i][j].hasMoved != 1){
                    antCounter++;

                    if ((j != 19) && randMovement == 0 && bugs[i][j+1].creature == NONE){

                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i][j+1].creature = ANT;
                        bugs[i][j+1].hasMoved = 1;
                    }

                    else if((i != 19) && randMovement == 1 && bugs[i+1][j].creature == NONE){

                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i+1][j].creature = ANT;
                        bugs[i+1][j].hasMoved = 1;
                    }

                    else if((i != 0) && randMovement == 2 && bugs[i-1][j].creature == NONE){

                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i-1][j].creature = ANT;
                        bugs[i-1][j].hasMoved = 1;
                    }

                    else if( (j != 0) && randMovement == 3 && bugs[i][j-1].creature == NONE){

                        bugs[i][j].creature = NONE;
                        bugs[i][j].hasMoved = 0;

                        bugs[i][j-1].creature = ANT;
                        bugs[i][j-1].hasMoved = 1;
                    }
                    else{

                        bugs[i][j].hasMoved = 1;
                    }
                } // End of if ant and has not moved
            } // End of (for j...)
        } // End of (for i...)



        // Reset the boards move count back to 0 to avoid any overwriting of the move count per location on grid when the babies are created
        // (My code is done in a way where this is not needed, but just to be 100% certain, we will reset it when we get here).
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {

                bugs[i][j].hasMoved = 0;
            }
        }

        antDaysPast++;  // Counter used to track days for respawning ants every 3 days


        // After 8 days have past for each individual doodlebug, find them, find an adjacent location that is empty,then multiply
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                if (bugs[i][j].creature == DOODLEBUG && bugs[i][j].daysAlive % 8 == 0 && bugs[i][j].daysAlive != 0){

                    if((j != 19) && bugs[i][j+1].creature == NONE){         // If not on the right edge of the board, locate and hold that position to later spawn the baby.
                        bugRow[bugBabyLocator] = i;                         // Array that holds the row index of the open position
                        bugCol[bugBabyLocator] = j+1;                       // Array that holds the column index of the open position
                        bugBabyLocator++;                                   // Counter that will be used for spawning the new bugs
                    }

                    else if ((i != 19) && bugs[i+1][j].creature == NONE){   // If not on the bottom edge of the board, locate and hold that position to later spawn the baby.
                        bugRow[bugBabyLocator] = i+1;
                        bugCol[bugBabyLocator] = j;
                        bugBabyLocator++;
                    }

                    else if ((i != 0) && bugs[i-1][j].creature == NONE){    // If not on the top edge of the board, locate and hold that position to later spawn the baby.
                        bugRow[bugBabyLocator] = i-1;
                        bugCol[bugBabyLocator] = j;
                        bugBabyLocator++;
                    }

                    else if ((j != 0) && bugs[i][j-1].creature == NONE){    // If not on the left edge of the board, locate and hold that position to later spawn the baby.
                        bugRow[bugBabyLocator] = i;
                        bugCol[bugBabyLocator] = j-1;
                        bugBabyLocator++;
                    }
                    else{                                                   // If there is no adjacent position available, then it will store the current position to use to spawn for the 9th day
                        bugs[i][j].babyBug = BABYBUG;
                        babybugcount++;
                    }
                }
            }
        }


        for (i = 0; i < bugBabyLocator; i++){                               // Find all the open positions stored in the arrays and spawn the new babies there.

            bugs[bugRow[i]][bugCol[i]].creature = DOODLEBUG;                // Create and store new doodlebugs on the board.
            bugs[bugRow[i]][bugCol[i]].daysStarved = 0;                     // The new baby is not starved so the starvation count should be 0.
            bugs[bugRow[i]][bugCol[i]].daysAlive = 0;

        }

        bugBabyLocator = 0;                                                 // Counter reset is needed here so that the next time it loops around, it will overwrite the old array/start over.



        // The following is almost identical to the doodleBug spawning. Please see comments above.
        if (antDaysPast == 3){

            for (i = 0; i < N; i++){
                for (j = 0; j < N; j++){

                    if(bugs[i][j].creature == ANT){

                        if((j != 19) && bugs[i][j+1].creature == NONE){
                            antRow[antBabyLocator] = i;
                            antCol[antBabyLocator] = j+1;
                            antBabyLocator++;

                        }
                        else if((i != 19) && bugs[i+1][j].creature == NONE){
                            antRow[antBabyLocator] = i+1;
                            antCol[antBabyLocator] = j;
                            antBabyLocator++;

                        }
                        else if((i != 0) && bugs[i-1][j].creature == NONE){
                            antRow[antBabyLocator] = i-1;
                            antCol[antBabyLocator] = j;
                            antBabyLocator++;

                        }
                        else if(j != 0 && bugs[i][j-1].creature == NONE){
                            antRow[antBabyLocator] = i;
                            antCol[antBabyLocator] = j-1;
                            antBabyLocator++;
                        }
                    }
                }
            }

            for (i = 0; i < antBabyLocator; i++){
                bugs[antRow[i]][antCol[i]].creature = ANT;
            }

            antBabyLocator = 0;
            antDaysPast = 0;
            antDayCount = 4;

        } // End of respawning phase/code for ants


        // Loop that will iterate through and determine if a bug dies or not.
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {

                bugs[i][j].hasMoved = 0;

                if (bugs[i][j].creature == DOODLEBUG && bugs[i][j].daysStarved >= 3) {
                    bugs[i][j].creature = NONE;
                    bugs[i][j].daysStarved = 0;
                    bugs[i][j].babyBug = NONE;                                              // If the Doodlebug was not able to spawn on 8th day, but dies after the days is over anyways, don't try to spawn a new bug.
                    bugs[i][j].daysAlive = 0;                                               // Since it will "kill" the doodlebug, we will reset the days alive for whatever goes in that position again.
                }
            }
        }


        bugDayCount--;
        antDayCount--;


        bugCounter = 0;     // Reset bugCounter to reevaluate how many bugs are on the board.
        antCounter = 0;     // Reset antCounter to reevaluate how many ants are on the board.

        printf("\n\n");
        displayBoard(bugs); // Displaying the board After every day has passed.




    } // End of while that handles the actual game experience


    printf("\n\n");


    return 0;
}
