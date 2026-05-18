*This project has been created as part of the 42 curriculum by iumorave, mariserr*

**Description**

CUB3D is a 3D raycasting engine build using C and the Minilibx library. The project's primary goal is to simulate a first-person 3D perspective within a 2D grid-based environment.

The project uses the **DDA (Digital Differential Analyzer)** algorithm to calculate ray-wall intersections accurately, ensuring rays do not "leak" through corners. It includes a custom `.cub` file parser for map layouts, texture configurations, and environmental colors.

**Instructions**

Compilation and Execution
The program must take as a first argument a file with the .cub extension (./game map.cub)

Controls
W, A, S, D: Move the player (Forward, Left-Strafe, Backward, Right-Strafe).
Left/Right Arrows: Rotate the camera view.
ESC: Close the application properly.

## **Resources**
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html): The definitive guide for raycasting mathematics and DDA implementation.
- [42 MiniLibX Docs](https://harm-smits.github.io/42docs/libs/minilibx): Reference for window and image management.

## **AI Usage**
AI was utilized as a pair-programming assistant for the following tasks:

- **DDA Implementation**: Translating the mathematical theory of Digital Differential Analysis into functional C code.
- **Performance Optimization**: Refactoring rendering logic to implement a more efficient color-mapping approach for textures.
- **Logic Debugging**: Identifying and resolving edge-case issues in ray-boundary calculations and texture mapping.