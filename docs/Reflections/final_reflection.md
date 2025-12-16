# Checkpoint 4 (Final) Reflection

## Section 1: Project Summary

- **What is your project? (1-2 sentences)**

My project is a console-based recreation of the classic Minesweeper game, implemented in C++. It features multiple difficulty levels, a mine placement algorithm to help keep the board solvable, and a high score tracking system.

- **What features did you implement?**

I implemented:

1. Input Habdling: Functions to handle user input no matter their operating system (Windows, Linux, or Unix).
2. Core Gameplay: The core Minesweeper game mechanics including digging and flagging cells, revealing numbers, and handling win/loss conditions.
3. Difficulty Levels: Three preset difficulty levels (Easy, Medium, Hard) with varying board sizes and mine counts.
4. Mine Placement Algorithm: An algorithm that places mines while avoiding unsolvable layouts as much as possible.
5. High Score Tracking: A system to save and load high scores for each difficulty level, saving your best times to a file.
6. Console UI: A console-based UI that displays and allows interaction with several menus and the game board.

- **What does your project do well?**

My project does well in providing a functional and enjoyable Minesweeper experience within the console. My mine placement algorithm reduces the chances of unsolvable boards significantly with minimal performance costs. My high score tracking system works as a way for the user to keep a list of their best time that presists through program uses. My the input handling system also has compatibility across different operating systems, making the game accessible to anyone.

## Section 2: What Remains

Be honest about what you didn’t finish:

- **What features from your original plan are not implemented?**

1. As mentioned in checkpoint 3's reflection:
    - Supporting mouse inputs for cell selection and flagging.
    - Allowing for a custom board creation mode where the player can pick their own board size and mine count.

- **What bugs or issues remain?**

No known bugs or issues remain, at least to my knowledge.

- **What would you need to do to consider this project “complete”?**

I personally consider it complete as it is, since all the core features are implemented and functional. However, to enhance it even further, I would implement the mouse support and custom board creation features mentioned above.

## Section 3: Time Estimate

For each remaining item:

- **How much time would it take to implement?**

See table below.

- **What would be involved (new classes, modifications, etc.)?**

1. Mouse Input Support: This would involve modifying the InputHandler class to capture mouse events and translating those into game actions. It would also require updating the Game and Board classes to handle these new input types. I would have to learn to how to use a new library for mouse input handling in console applications, such as ncurses. This would take a good long while to both research and properly implement.

2. Custom Board Creation Mode: This would involve adding a new menu option in the difficulty selection UI to allow users to input their desired board size and mine count. The Game class would need to be modified to accept these custom parameters when initializing a new game, since right now the UI system can only handle simple button selection inputs. This would also require input validation to ensure the custom settings are reasonable. I would also have to implement a new mine placement algorithm that can handle arbitrary board sizes and mine counts, since they can be outside reasonable ranges. I would have to make it much less strict for higher mine counts so the user would actually get the board they want. This would be an absolutely herculean task to undertake and would take a very long time to brainstorm, research, and implement since so many systems would have to be changed to support it.

- **What’s the priority (must-have vs nice-to-have)?**

See table below.

- **Table: Remaining Work**

| Remaining Item | Time Estimate | Priority |
| -------------- | ------------- | -------- |
| Mouse Input Support | 4-6 hours | Nice-to-have |
| Custom Board Creation Mode | 6-8 hours | Nice-to-have |

## Section 4: What I Learned

This is the most important section. Reflect on your learning:

- **What C++ concepts did you learn or improve on?**

- file I/O operations for saving and loading high scores. I had never used them in any programming courses before this project.
- cross-platform compatibility techniques.
- General OOP design principles, especially in the context of game development. Before this project, I had mostly always used lua for game development, so using C++ and OOP principles in this context was a new experience for me.

- **What was the hardest part of this project?**

The hardest part of this project was designing and implementing the mine placement algorithm. It required a deep understand of Minesweeper's actual mechanics what makes a board solvable or unsolvable. I had to research various strategies and techniques used in the actual Minesweeper and then adapt them to be functions that check for them programmatically.

- **What would you do differently if starting over?**

- I would use a library like ncurses from the start so that i wouldn't have to change my whole project later on to support mouse input.
- I would use more classes to avoid having too much functionality and dependecies in a single class. For example, i would have the DiffInfo struct be its own class that handles all difficulty-related logic, instead of being a simple struct inside the Game class. This would also make implementing the custom difficulty easier later on.

- **What are you most proud of?**

- While I'm proud of my mine placement algorithm, I'm most proud of my rendering and UI systems. I've always been a UI/UX enthusiast at heart, so having to adapt that to a console-based enviroment was equal parts challenging and and fun. I'm happy with how it turned out and i believe that everything looks good and is simple to use.

- **How has your understanding of data structures changed?**

- I've gained a deeper understanding of how to use various data structures effectively in C++. Previously i had taken elementry Java and C# courses, which never really required anything past arrays and the occasional list. Here, I've had to use unordered_maps, vectors, arrays, and structs to effeciently store and manage game data. This was most prevelant in the mine plamcement algorithm, where I had to use multiple data structures such as vectors and unordered_maps and had to link and use them together.

## Section 5: Time Log

Estimate the total time you spent on this project across all checkpoints:

- **Planning and design:** 5-6 days
- **Implementation:** 4-5 days
- **Testing and debugging:** 393240011408329399109042902e+49432 eons (approximately 1-1.5 days)
- **Documentation:** 10-12 hours
- **Total:** Approximately 12-15 days
