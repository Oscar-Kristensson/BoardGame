# Games
## Installation
TBD

## Structure
Each game is contained in a folder, which must contain a game.txt file. 

### Game Data File
The game data file defines the behavior of the game. The game is based on a similar syntax to classes, with each class creating an "object" in the game of one of the following types:

* **Game Info** - Defines the size of the game board etc
* **Entity** - Creates "entities" that have an image and is shown on the game board.

This is an example of how the game.txt file could look:

``` txt
GameInfo,
    boardWidth=8000,
    boardHeight=8000,
    backgroundColor=7dcfe7;

Entity, id=Background, img=assets/WorldGame/map.png, x=0, y=0;

CommonPlayerInfo, hasAccounts=true, accountBalance=100;

```

#### Game Info
The game info object has the following parameters:

| Parameter       | Values    | Comments |
|-----------------|-----------|----------|
| boardWidth      | int       | Defines the width of the game board, which is mainly used for centering the game camera.|
| boardHeight     | int       | Similar to the boardWidth but for height |
| backgroundColor | HEX color | Defines the background color of the game board. |


#### Entity
The entity has the following parameters:

| Parameter       | Values        | Comments |
|-----------------|---------------|----------|
| id              | string        | Defines the name ID of the entity, which is currently only used for readabillity |
| img             | string (path) | The path to the image (will be changed to relative to game dir) |
| x               | int           | The x-cord |
| y               | int           | The y-cord |

#### Common Player Info
The common player info object has the following parameters:
| Parameter       | Values        | Comments |
|-----------------|---------------|----------|
| hasAccounts     | bool          | Enables the accounts in the game |
| accountBalance  | int           | Sets the start account balance |