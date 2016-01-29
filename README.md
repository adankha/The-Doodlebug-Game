# The-Doodlebug-Game
An introduction to Object Orientated Programming (in C)

The program in this repository is a simple doodlebug animation game. 
Here is a short description and facts about the game
100 ants and 5 doodlebugs are initially populated on the board
Each doodlebug moves in a direction (up down left or right) depending on if there is an ant to eat. If there is no adjacent ant, the doodlebug will choose a random direction and move.
Each ant on the board will move at a random location adjacent to them that is available to move to.

If a Doodlebug does not "eat" an ant within 3 days, it will die.
If a Doodlebug survives 8 days, it will multiply.
If an ant survives 3 days, it will multiply.
If a doodlebug cannot reproduce due to no adjacent space available, it will attempt to do so again the following day.
Each doodlebug has its own days alive count and if they've eaten. Likewise for the ants.

The program is done in a way where each time it prints a board, it represents a new day. When you execute the program, you will notice a nice pattern as the days progress.
