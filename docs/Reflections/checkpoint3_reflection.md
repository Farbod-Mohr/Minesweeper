# Checkpoint 3 Reflection

## What I Implemented

I implemented:

- Pattern Checkers: 3 helper functions design to detect unsolvable mine patterns during mine placement
  - `formsTwoByTwo`: Checks if placing a mine would create a 2x2 block with 3 or more mines.
  - `formsLongLine`: Checks if placing a mine would create a line of 4 or more consecutive mines horizontally or vertically.
  - `trapsSafeCell`: Checks if placing a mine would isolate a safe cell by surrounding it with mines.
- Mine Placement Algorithm: A mine placement algorithm that uses the above pattern checkers to ensure that any mine placed would not create unsolvable configurations. If so, it blacklists that cell and tries again. It also keeps a 3x3 safe zone around the first clicked cell and does not place mines there.

## Integration

- Dig Function: The mine placement algorithm is directly linked to the dig function implemented in checkpoint 2, because it respects the 3x3 area around the first dug cell when placing mines.
- Input Handling: It also follows that the dig function is dependent on the input handling system implemented in checkpoint 1.
- Color: The message printed when mine placement fails uses `Color::Magenta` from the Color namespace implemented in checkpoint 1.

## Challenges I Faced

This was by far the most challenging checkpoint of the entire project. It took a **LOT** of brainstorming and debugging to figure out how I would go about it.

The largest hurdle was what patterns to check for, as I'm definitely not a veteran Minesweeper player and didn't know all the ins and outs of what makes a board solvable or otherwise. After watching a couple youtube tutorials on the matter (notably [this one](https://www.youtube.com/watch?v=sh7SkYTP9SQ)), I was able to identify 3 main patterns that would make a board unsolvable, and eventually worked through how to turn them into functions.

The mine placement function itself was no easy feat either. Since I was dealing with a 2D array in the board, a vector in the candidates for mine placement, and an unordered map in the blacklisted cells, it took a lot of careful planning and consideration on how i would connect these different data structures together to make the algorithm work.

Additionally, as documented in the code, I also took some code from StackOverFlow to help me with shuffling the candidates vector, since I had no idea how to do so myself. The code for creating a seeded random number generator was very new to me and I still don't fully understand its workings, but it did the job well.

All in all, this checkpoint was a massive reality check when compared to the pervious two, and really showed me how much more complex and difficult game development can be when you get into the nitty gritty of making sure everything works as intended. Even still, I am proud of the end result and through my many rounds of testing, I'm confident that it reduced the amount of unsolvable boards by a large, noticeable margin.

## What I Learned

- Minesweeper: This checkpoint somewhat forced me to really understand minesweeper on a deeper level, since I had to research and learn about what makes a board solvable or unsolavable. Somewhat predictably, this project as a whole has made me a mildly better Minesweeper player in general.
- Algorithm Design: I learned a lot about how to design algorithms that interact with multiple data structure types, and how to make them compatiable with functions such as the `makeKey` function, which made the blacklist unordered map be compatiable with loops.

## Testing Results

See [testing code](../../tests/checkpoint3_testing.cpp) for the testing code and [test results](../Test_Results/checkpoint3_tests.md) for detailed review and results.

The only failed test was test 8, the "Stress Test". This was because the `maxRerolls` variable was not being decremented when the loop `continue`d, causing the loop to infinitely try to (and fail to) place new mines due to excessive blacklisting. I fixed this by adding a `maxRerolls--` line before each `continue` statement to make sure that, eventually, the program would run out of rerolls and give up, printing the warning message of how many mines failed to be placed.

Aside from that, all other tests passed successfully on the first try.

## Overall Project Completion Progress (This is new!)

- What percentage of your original planned features are now complete?
  - About 80-85%

- Which features from your original plan remain?
  - All of them except for:
    1. Mouse support: It required an entire external library which I would not be able to integrate in time, so it was scrapped rather early.
    2. Custom board sizes: This was scrapped due to both time constraints and concerns that the mine placement algorithm would not function properly with the custom numbers that users could input. If I had more time, I would create an extra placement function specifically for custom difficulty settings which would be a lot less restrictive.

- Are you still committed to your original scope, or do you see a need to adjust?
  - I am mostly committed to my original scope, as practically all features placed in the [README.md](../../README.md) when the project began are either completed or planned to be completed in the next checkpoint.

- What are the biggest remaining challenges?
  - Implementing the HighScoreSaver class is my main concern as of now, since file I/O is something I have very little experience with and it may take a while to get it working properly.
  - Another concern is making sure that the project is Linux and Unix compatible. I have tested it on WSL, but I have no way of testing it on an actual Linux or Mac machine, so there may be unforeseen compatibility issues that exist. I will still try my best to make sure it uses nothing that's windows-specific.

- Do you feel on track to complete your project by the final submission?
  - Yes, I believe I am on track to complete the project by the final submission date.

## Questions for Next Checkpoint

N/A

## Time Spent

Approximately 6-8 hours
