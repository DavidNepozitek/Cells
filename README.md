# The Hungry Cell
---

The Hungry Cell is a simple 2D agar/osmos like game. 


## Gameplay
The main concept of the game is moving a cell and eating as much food and other cells as possible. The thing is that you can eat only cells smaller than you and every movement costs you a bit of your mass. The goal is to be the biggest cell in the game.

## Implementation
The game is build on [SFML](https://www.sfml-dev.org/). It uses some patterns recommended by SFML tutorials:

- __Scene Graph__ - The drawable part of the world forms a graph. That is useful because transformations on its nodes can be computed relative to all the parent transformations. Moreover it's simple to create cmoposite objects that are composed of more smaller ones.
- __State Stack__ - It's a stack of states such as GameState, MenuState, PauseState etc. All the changes and events are handled from the top of the stack and can be stopped at on some level. So the pausing the game is done trivially by introducing a state that stops the propagation of all changes. The stack handles the drawing as well; all the states are drawn from the top to the bottom of the stack.
- __Resource Holder__ - It's a pattern of loading a resource during the initialization of the game, retrieving it from the game's context, and releasing it with the destruction of the game object.

The game is based on interaction of various cells and moving in an area with low resistance. During every update a cell can react with every other cell and the interaction is based on the types of both of the cells (implemeted as double dispatch). That's why it's simple to add more types of cells to the game.

## Install
> If you're using windows, you can download the executable directly from [releases](https://github.com/DavidNepozitek/Cells/releases/)
1. Instal the latest version of [cmake](https://cmake.org/) for your system.
2. Download [SFML](https://www.sfml-dev.org/) for your system and compiler (or possibly build it with cmake by the instruction on their website). 
3. In the root directory of this repository run `cmake -S . -B <build_path> -DSFML_DIR:STRING="<path_to_sfml_cmake>"`
    - You might need to specify the target compiler with `-G` argument (for example `-G "Visual Studio 15 2017"`)
    - `<path_to_sfml_cmake>` must point to `SFML-2.5.1\lib\cmake\SFML` directory where `SFMLConfig.cmake` is located
4. In the build directory run `cmake --build .`
5. Make sure `Fonts` folder is in the same directory as the executable (especially on Windows)
6. Run the executable

## TODOS
- Create more types of cells
- Add levels with other goals
- Make the graphics better
