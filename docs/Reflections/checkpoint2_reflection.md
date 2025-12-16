# Checkpoint 2 Reflection

## What I Implemented

I implemented:

- Board Creation: Constructors and initialization functions to set up the board with the appropriate amount of cells and mines.
- Board Rendering: Functions to display the board in the console. This included rendering walls, rendering cells, cursor highlighting, game info (such as mines remaining or cells dug), and rendering of cell states by making them have their own internal print function.
- Board Interaction: Functions to handle user input for navigating the board by moving the cursor, digging cells, and flagging cells. This was done via the input handler function from checkpoint 1.

## Integration

- Input Handling: The Input handling implemented in checkpoint 1 was used to manage user inputs and convert them to actions on the board, allowing for board interaction.
- Color: The Color namespace from checkpoint 1 was used to color and styalize pratically every element of the board, from the different cell types to the selection highlighting to the difficulty header.

## Challenges I Faced

Challenges during this checkpoint were minimal, however did include:

- The dig function: Recursively digging adjacent cells required quite a bit of planning and testing.
- Initialization of the Board itself: Making sure that all the properties of the board object were correctly set up needed a lot of trial and error. A lot of crashing arose due to the `selectedCell` pointer because it was not being initialized and set properly.
- Difficulty Settings: It took a lot of brainstorming to figure out how to best implement and use preset difficulty settings. I eventually went with a simple `DiffInfo` struct mapped to an unordered map, but making it an entire class altogether was also definitely an option to avoid having to deal with circular dependencies.

## What I Learned

- I learnt just how many small checks are required to not have your program explode into ash and dust. Making sure every property is initialized correctly, making sure pointers are properly being assigned to memory addresses, making sure that the board cursor doesn't move out of bounds, making sure that the loops loop through the playable area of the board and not the walls, etc. All of these small "nit picky" checks were vital to making sure the game is as unbreakable as possible.
- Additionally, due to the board-like nature of Minesweeper, I learnt a lot about 2D arrays and how to set them up correctly. This included how to properly index them, along with making sure what scope each variable and object was in to avoid accidental overwriting or incorrect refrencing.

## Testing Results

See [testing code](../../tests/checkpoint2_testing.cpp) for the testing code and [test results](../Test_Results/checkpoint2_tests.md) for detailed review and results.

All tests thankfully passed successfully, including edge cases. This makes me confident that all the checks I've added are working as intended and preventing bugs.

## Questions for Next Checkpoint

N/A

## Time Spent

Approximately 3-4 hours
