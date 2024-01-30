# scrabble-project

The project is a variation of the game Scrabble.

When the programme is started, a menu is printed on the console with the following options:
-start a new game;
-settings;
-add a new word to the dictionary;
-exit.

When the player chooses to start a game, they have a certain number of rounds they will play, and a certain number of letters from which they can choose in order to write a word (both are 10 by default). When given letters, the player can choose to change their current ones if they cannot write a word with them (choosing that option, the number of rounds will still decrease by 1). When the player enters a word, the programme checks if each of the letters of the input is encountered in the array of given letters, then if the word is encoutered in the file that the programme uses as a dictionary. If both of those requirements are fulfilled the player gets their points from the entered word (1 for each letter). This process is repeated until the rounds do not end. After which, the menu is printed again.

The game has two variables that can be modified by the player from the settings opion in the menu. They can choose how many letters they want to be given(the maximum is 100) or how many rounds they want to play. After modifying one of those variables, a game is started.

Choosing the option "add to dictionary" the player has the opportunity to enter a new word to the dicionary file, which will be available for the next games. The proggrame checks if the word is only made of small letters, in which case it is written in the file and the programme is ended.

The option "exit" ends the programme.

