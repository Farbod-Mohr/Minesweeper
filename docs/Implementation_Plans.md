# Implementation Plan

## [x] ~~Feature 0: Input Handling System~~ COMPLETED

**Trigger**: User presses a key on the keyboard.

**Input Needed**: Key press from the user.

**Implementation Flow**:

1. In the `InputHandler` class, implement the static function `getkey()`. This function will use `_getch()` from the `<conio.h>` library to capture a key press on windows. For other operating systems it will use a custom function that captures key presses in a similar way (without printing to the console).
2. Implement the static function `getAction()` in the `InputHandler` class. This function will call `getkey()` to get the key press and then map it to the corresponding `Action` enum value based on the key pressed. For example, 'w' or Up Arrow will map to `Action::UP`, 'a' or Left Arrow to `Action::LEFT`, and so on. It will use the keyMap hashmap to do this.
3. Other classes, mainly the `Game` and `Board` classes, will call `InputHandler::getAction()` to get the user's input and act accordingly.

**Data Modified**: None.

**Completion**:

- The program can capture user key presses and map them to game actions.

**Functions Used**:

- `InputHandler::getkey()`
- `InputHandler::getAction()`

## [x] ~~Feature 1: Main Menu Navigation~~ COMPLETED

**Trigger**: User starts the program.

**Input Needed**: User key input (W, S, Up Arrow, Down Arrow, Enter).

**Implementation Flow**:

1. On program start, display main menu options: Start Game, High Scores, and Exit.
2. Get user movement inputs for menu navigation. They can move with W, S, Up Arrow, and Down Arrow keys.
3. In the Game class, use InputHandler to capture user input and set the appropiate elements in the `UIButtons` struct to true.
4. Every time the user gives an input, a game tick passes. Every game tick, first the console is cleared via `Game::clear()`. After that, in the `renderMainMenu()` function, check which button with the `MM_` identifier in the `UIButtons` struct is true and highlight the corresponding menu option.
5. When the user presses Enter, check which menu option is currently set to true in the `UIButtons` struct and navigate to the corresponding screen. (for now it should just print a message to the console).
6. Reset all `UIButtons` struct values with the `MM_` identifier to false after handling the input. (except for MM_newGame which is true by default)
7. These same principals and program flow apply for all the other UI screens in the game, so they will no longer be mentioned in the following features list. Just know that all UI screens will use the `UIButtons` struct to track the user's current selection and render accordingly.

**Data Modified**:

- `UIButtons` struct in the Game class to track which menu option is selected.

**Completion**:

- Brings the user to the appropriate screen based on their selection.

**Functions Used**:

- `Game::renderMainMenu()`
- `Game::renderGameOver()` (in the future)
- `Game::renderWin()` (in the future)
- `Game::renderHighScores()` (in the future)
- `Game::renderExit()` (in the future)
- `Game::clear()`
- `Game::init()`
- `InputHandler::getAction()`

## [x] ~~Feature 2: New Game Start~~ COMPLETED

**Trigger**: User selects "Start New Game" from the main menu.

**Input Needed**: User key input for difficulty selection.

**Implementation Flow**:

1. When the user selects "Start New Game" from the main menu and presses Enter, bring them to the difficulty selection screen.
2. Call the `Game::renderDiffSelection()` function. This displays difficulty options: Easy, Medium, and Hard.
3. Use the principals mentioned in Feature 1 to navigate the UI.
4. When the user selects one of these options, get the respective preset `DiffInfo` object from the `Difficulty` hash map in the game class. Use this info to initialize a `Board` object with the appropriate rows, columns, and mine count via `Game::startNewGame(DiffInfo selected_diff)`. The `currentDiff` variable in the Game class should also be set to the selected difficulty's `DiffInfo` object for later use in score calculation.
5. After the board is initialized, the `startTime` variable in the Game class should be set to the current OS time to start tracking how long the game takes.
6. Lastly, the `Board::run()` will be called to begin the game loop.

***IMPORTANT NOTE***: MINE PLACEMENT LOGIC IS NOT PART OF THIS FEATURE, AS THEY WILL HAVE TO BE PLACED WHEN THE PLAYER DIGS THEIR FIRST CELL. THIS IS TO ENSURE THE PLAYER DOES NOT DIG A MINE ON THEIR FIRST MOVE.

**Data Modified**:

- `currentDiff` variable in the Game class to track the selected difficulty.
- `startTime` variable in the Game class to track when the game started.

**Completion**:

- A new game board based on the selected difficulty is initialized and ready to be rendered.

**Functions Used**:

- `Game::renderDiffSelection()`
- `Game::startNewGame(DiffInfo selected_diff)`
- `Board::Board(int rows, int cols, int mines)`
- `Board::run()`
- `InputHandler::getAction()`
- `Game::clear()`

## [] Feature 3: Cell/Board Rendering

**Trigger**: A new game is started or the user interacts with the board.

**Input Needed**: User key input for cell interaction, if applicable.

**Implementation Flow**:

1. In a `Cell` object, implement a `print()` function that returns a character representation of the cell. This is decided on many factors:
    - The cell's state: normal, dug, flagged, exploded, or wall. Wall cells are the borders around the board and cannot be interacted with.
    - If the cell is dug, what number of adjacent mines it has (0-8)
    - Whether or not the cell is currently selected by the user, which changes the color to cyan.
2. In the `Board` class, implement a `render()` function that loops through all the cells in the board's 2D vector and calls each cell's `print()` function to get its character representation. Print these characters to the console in a grid format to represent the board.
3. In the `Board::render()` function, some of the game's current stats should be displayed. These include:
    - Number of mines remaining (`minesRemaining` property in the Board class).
    - `dugCells` / `totalCells` to show the number of cells left until they win.
4. The `Board::render()` function is called every game tick inside `Board::run()` to update the board's display based on user interactions.

**Data Modified**: None.

**Completion**:

- The game board is visually represented in the console, showing the current state of each along with the game's stats.

**Functions Used**:

- `Cell::print()`
- `Board::render()`
- `Board::clear()`

## [] Feature 4: User Interaction with Cells

**Trigger**: User is in a game and wants to interact with the board.

**Input Needed**: User key input (W, A, S, D, or the Arrow Keys for movement; Q for flagging; E, Space or Enter for digging).

**Implementation Flow**:

1. In the `Board::run()` function, implement a game loop that continues until the game is won or lost.
2. Inside the loop, use `InputHandler::getAction()` to capture user input and determine the desired action.
3. Based on the action returned, update the board state accordingly:
    - Movement (W, A, S, D, or the Arrow Keys): Use the `Board::selectCell(int r, int c)`, `Board::unselectCell(int r, int c)`, and the `selctedCell` pointer in the Board class to move the selection around the board according to the input. Must make sure that the selection does not move into WALL cells. The cell that has been selected should have its color changed to cyan when rendered. When a new cell is selected, the previously selected cell should be unselected. Selecting a cell involves updating the `selectedCell` pointer inside the Board class to point to the new cell and the `isSelected` property of the Cell object itself to `true`. It must then and unselect the previous cell, setting its selected state to false.
    - Digging (E, Space): Call the `digCell(int x, int y)` funtion with the coordinates of the currently selected cell. If the dug cell is a mine, set its state to exploded and end the game. If it's safe, reveal it. If it has 0 adjacent mines, recursively dig all adjacent cells, calling the `digCell(int x, int y)` with the coordinates of a 3x3 grid around the cell we just dug. Update the `dugCells` property in the Board class accordingly. After each dig, the game should check if the player has won via the `Board::hasWon()` function, which checks if the number of dug cells equals the total number of safe cells.
    - Flagging (Q): Toggle the flagged state of the currently selected cell using a `toggleFlagCell(int x, int y)` function. Flagged cells cannot be dug. Update the `flagCount` and `minesRemaining` properties in the Board class accordingly
4. After handling the input, call the `Board::render()` function to update the board's display.

**Data Modified**:

- `selectedCell` pointer in the Board class to track the currently selected cell.
- `dugCells`, `flagCount`, and `minesRemaining` properties in the Board class to track game progress.

**Completion**:

- The user can navigate the board, dig cells, and flag cells.

**Functions Used**:

- `Board::run()`
- `InputHandler::getAction()`
- `Board::selectCell(int r, int c)`
- `Board::unselectCell(int r, int c)`
- `Board::digCell(int x, int y)`
- `Board::toggleFlagCell(int x, int y)`
- `Board::render()`
- `Board::hasWon()`

## [] Feature 5: Algorythmic Mine Placement

**Trigger**: User digs their first cell in a new game.

**Input Needed**: Coordinates of the first dug cell.

**Implementation Flow**:

1. In the `Board` class, implement the `placeMines(int safeX, int safeY)` function.
2. This function should randomly place mines on the board, ensuring that the cell at (safeX, safeY) is not a mine.
3. It then runs multiple checks to make sure that the board is solvable, attempting to minimize the chances of 50/50 guesses by the player by spotting common unsolvable patterns due the clustering of mines.
4. If a check doesn't pass, it will remove one of the mines from the cluster that made the board unsolvable, blacklist the space it was in from ever having a mine again, and attempts to place it somewhere else.
5. This process is repeated until all mines are placed and all the checks pass.
6. If the number of mines that must be placed exeeds the number of available spaces, possibly due to blacklisting, It will subtract the number of excess mines from the total mine count and proceed with placement, starting the game with less mines than requested. It should show a message to the viewer in this case, telling them that the mine was eaten by the hungry hungry caterpillar.

**Data Modified**:

- `isMine` property of `Cell` objects in the Board's grid to indicate mine placement.
- `mineCount` property in the Board class to reflect any changes in the total number of mines placed.

**Completion**:

- Mines are placed on the board in a way that ensures the game is as solvable and fair for the player as possible.

**Functions Used**:

- `Board::placeMines(int safeX, int safeY)`

## [] Feature 6: Game Timer

**Trigger**: User starts a new game.

**Input Needed**: None.

**Implementation Flow**:

1. In the `Game` class, implement a system to track the time taken for each game.
2. When a new game starts, record the current OS time in the `startTime` variable (mentioned in Feature 2).
3. When the game ends (either by winning or losing), record the current OS time in the `endTime` variable.
4. Calculate the total time taken for the game by subtracting `startTime` from `endTime` and returning it in the form of a formatted string (HH:MM:SS). This is done via the `calcTime()` function.
5. The time taken will be displayed on the WIN screen after the player successfully clears the board.
6. After the time is calculated and displayed, it along with the difficulty selected (`currentDiff`) will be sent to the HighScoreSaver class to be recorded as a high score if applicable.

## [] Feature 7: High Score Tracking

**Trigger**: User wins a game.

**Input Needed**: None.

**Implementation Flow**:

1. In the `Game` class, implement the `saveScore(string total_time)` function that is called when the user wins a game. This function will be called inside of the `calcTime()` function after the total time is calculated.
2. This function should pass the time taken to beat the game along with the current difficulty level (`currentDiff`) to the `HighScoreSaver::addScore(string time, DiffInfo difficulty)` function.
3. The ``HighScoreSaver::addScore(string time, DiffInfo difficulty)` function must:
    - Check if the new score is better than any of the existing scores in the list for that difficulty. This will be done by converting the time string (HH:MM:SS) into total seconds for easier comparison.
    - If it is, insert the new score in the correct position to maintain a sorted order (best times first).
    - If the list exceeds `MAX_SCORES`, remove the lowest score.
4. The high scores should be saved to a file specified by the `SAVEFILE` variable in the HighScoreSaver class.

**Data Modified**:

- `highScores` array in the HighScoreSaver class to store the top scores for each difficulty.
- The text file which saves the high scores.

**Completion**:

- The user's high score is recorded and saved if it is among the top scores for the selected difficulty.

**Functions Used**:

- `Game::calcTime()`
- `Game::saveScore(string total_time)`
- `HighScoreSaver::addScore(string time, DiffInfo difficulty)`
- `HighScoreSaver::saveToFile()`
- `HighScoreSaver::loadFromFile()` will also now be called on program start to load existing high scores into the `highScores` array.
