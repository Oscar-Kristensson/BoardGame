# Games
## Installation
TBD

## Structure
Each game is contained in a folder, which must contain a game.txt file. 

### Game Data File
The game data file defines the behavior of the game. The game is based on a similar syntax to classes, with each class creating an "object" in the game of one of the following types:

* **Game Info** - Defines the size of the game board etc
* **Entity** - Creates "entities" that have an image and is shown on the game board.
* **CommonPlayerInfo** - Controlls the default account balance
* **PlayerInfo** - Stores information about a player
* **DiceInfo** - Creates a dice
* **Label** - Displays text

This is an example of how the game.txt file could look:

``` txt
GameInfo,
    boardWidth=8000,
    boardHeight=8000,
    backgroundColor=7dcfe7;

DiceInfo, x=32, y=20, min=1, max=6;


Entity, id=Background, img=assets/WorldGame/map.png, x=0, y=0, draggable=false;

CommonPlayerInfo, hasAccounts=true, accountBalance=100;

PlayerInfo, x=4850, y=3555, color=ff2a2a;
PlayerInfo, x=3950, y=3420, color=009b00;
PlayerInfo, x=5841, y=3285, color=2a2aff;


```

#### Game Info
The game info object has the following parameters:

| Parameter       | Values    | Comments |
|-----------------|-----------|----------|
| boardWidth      | int       | Defines the width of the game board, which is mainly used for centering the game camera.|
| boardHeight     | int       | Similar to the boardWidth but for height |
| backgroundColor | HEX color | Defines the background color of the game board. |
| turnDisplayX    | int       | Sets the X-coordinate of the turnDisplay (shows the active player) |
| turnDisplayY    | int       | Sets the Y-coordinate of the turnDisplay |
| hoverForBank    | bool      | Determins whether the user must hover the banks to change the value |    

#### Entity
The entity has the following parameters:

| Parameter       | Values        | Comments |
|-----------------|---------------|----------|
| id              | string        | Defines the name ID of the entity, which is currently only used for readabillity |
| img             | string (path) | The path to the image (will be changed to relative to game dir) |
| x               | int           | The x-cord |
| y               | int           | The y-cord |
| draggable       | bool          | Changes whether the entity can be dragged around |

#### Common Player Info
The common player info object has the following parameters:
| Parameter       | Values        | Comments |
|-----------------|---------------|----------|
| hasAccounts     | bool          | Enables the accounts in the game |
| accountBalance  | int           | Sets the start account balance |

#### Player Info
The player info object has the following parameters:
| Parameter       | Values        | Comments |
|-----------------|---------------|----------|
| x               | int           | The player starting x-pos |
| y               | int           | The player starting y-pos |
| color           | HEX color     | Sets the players color |


#### Dice Info
The dice info object has the following parameters:
| Parameter       | Values          | Comments |
|-----------------|-----------------|----------|
| x               | int             | The dice x-pos |
| y               | int             | The dice y-pos |
| min             | int > max > 255 | Sets the minimum value of the dice |
| max             | int > 255       | Sets the maximum value of the dice |

#### Label
The label object has the following parameters:
| Parameter       | Values           | Comments |
|-----------------|------------------|----------|
| x               | int              | The dice x-pos |
| y               | int              | The dice y-pos |
| text            | string           | The displayed text |
| fontSize        | int > 255        | Sets the font size |
| align           | string (L, C, R) | Sets the text align with L for left, C for centered and R for right |
