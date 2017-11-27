# Simple Newtonian 2-D Physics and AI Engine

A simple physics and AI engine written in C++, demonstrated by moving entities in a 2-D enviroment, with position updates determined by 
their velocities, which are in turn determined by the forces being applied upon them. The AI component of the system uses two slightly 
different versions of the A* pathfinding algorithm to navigate entites through the environment: classical A* using the first lowest cost
found path to reach the goal node; and a tactical A* where entities try to avoid Open terrain tiles when possible to reach the goal node.

## The environment
The environment in which the entities roam is a 2-D grid map where each grid square represent a terrain type, which effects the maximum
velocity an entity can traverse through it. To construct the world map details are read from a text file in order to determine the colors
and positions the grid squares (Tile objects) should be rendered in, and each Tile is added to the game's Map object, which is essentially
a wrapper for a two-dimensional array of Tile objects (represented as a Tile\*\*). By reading the map this way we are able to quickly
determine the tile the user is currently in, each physics update, as by knowing the the entity's position and the length of a Tile we can
determine the Tile in the Map object with the formula: 

*Map[(entity.x + entity.halfWidth) / tile_width][(entity.y + entity.halfHeight) / tile_height]*

## Physics
### Acceleration, Velocity, and Position
Upon pressing the WASD or arrow keys the user-controlled entity gets applied an acceleration force on the corresponding direction 
(acceleration upwards when W/up arrow key, acceleration leftwards when A/left arrow key, etc...). Note that acceleration can be in 
directions outside of up, down, left, right; as when a combination of any of the keys is pressed the entity will move in the resulting
combined acceleration vector direction. Once the acceleration vector's magnitude and directio is determined, we can move onto updating
the velocity of the entity, and thus its position.

Entity velocities and positions are calculated using Semi-Implicit (or Symplectic) Euler Integration, denoted by the following formulas:

![Semi-Implicit Euler formula](http://i64.tinypic.com/2cnw7x0_th.png "Semi-Implicit Euler")

where a is the newly calculated acceleration vector, Δt is the timestep between physics updates (set to 1/120)

### Collisions
Other than handling the movement of entities and updating them correctly, the engine is also able to handle collision detection via a 
bounding box check between entities, and collision response between entities and objects or wall-type terrains in the map. Collisions
with wall tiles are resolved using the impulse method, denoted by the following formula:

![Impulse Collision response formula](http://oi64.tinypic.com/fp6xkj.jpg "Impulse Collision response formula")

where J is the impulse force, calculated using:

![Impulse force formula](http://i66.tinypic.com/k39ob7_th.png "Impulse force formula")

## AI

### Flocking Behavior
While the player entity moves around the Map, the other AI entities must follow it to be able to reach the castle alongside the 
user-controlled entity. A very simple version of Reynolds' flocking algorithm is used here to ensure the other entities are following you.
Instead of following all three flocking properties (cohesion, alignment, and separation), only the cohesion property is used to make the 
AIs stay within range of the player.

*NOTE: The other flocking properties are present in the code, but were unsuccessful in running, thusly were commented out.*

### A* Pathfinding Implementation
The secondary focus of the code is generating two seperate implementations of the A\*, or A-Star, search pathfinding algorithm in order 
to make the AI entities traverse the environment. In order to run the A* algorithm the Map has to be first represented as a list of 
nodes, as A\* assumes that the environment is represeted as a node graph, therefore it is necessary to be able to represent the Tiles 
that make up the Map as PathNodes. With the list of PathNodes, all A\* operations are handled by the AStar class. As mentioned beforehand,
two implementations of A* have been written: classic/lowest cost, and tactical/least time spent in Open terrain Tiles.

The first implementation of A\* is the classic form of it which tries to get the 
best/cheapest/lowest cost path between point A and point B, while avoiding impassable objects such as walls or obstacles.

The second implementation of A\* still focuses on traveling from A to B, but attempts to arrive to B while minimizing the time spent in 
open terrain tiles, thus taking a more "tactical" approach.

## Simulation Execution
There are three simulations to execute, triggered by pressing the following keys:
- 'K' : User controls on of the entities, while others flock around him following his lead to reach the castle
- 'J' : Entities determine the classic A* path from a random base tiles to the closest castle tile
- 'L' : Entities determine the tactical A* path from a random base tiles to the closest castle tile

## Other
#### Video
Recording of the engine running can be found at: https://dzinzi.tinytake.com/sf/MTc5MTI0NV81ODQ4MDk3
