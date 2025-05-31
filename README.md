# BoardGame
TBD

## Usage and installation
### VS 2022
Run the following script:

``` bash
scripts/vs
```

The script will run cmake automatically and remove the old files. After running the script, open the generated solution file in VS and compile as normal. Make sure to have the raylib.lib file in the lib directory (it should be there by default, but can be ([downloaded here](https://github.com/raysan5/raylib/releases/tag/5.5))). Open the 


### MinGW
Run the following scripts:

``` bash
scripts/mingw
```

Make sure to get the raylib library ([download here](https://github.com/raysan5/raylib/releases/tag/5.5)) for the MinGW compiler and put it in the lib folder. The executable should be outputed in build/game.exe

### Cmake
Run cmake :)

Also, rember to link to raylib.

### Generate Assets
(This is game specific and should not be here)
Currently all assets are created as SVG:s. To render them out you can use the following python scripts:
``` bash
python scripts/renderAssets.py
```
The script requires inkscape to be installed and that the correct path is in the script.

## Usage
To use the app, install a game by moving it to the games folder. Then launch the executable and select the game. Change the number of players with the K and L keys. Click enter to launch the game. 

Once in the game:

* Use the Arrowkeys to move around the viewport
* Use the mousewheel to zoom
* Use Q and W to change which players turn it is
* If applicable to the game, change the players balance with the O and P keys. Use the SHIFT to change by 10 and CTRL + SHIFT to change by 100. 


## Licenses
TBD

## Authors
- [@Oscar-Kristensson](https://github.com/Oscar-Kristensson)
