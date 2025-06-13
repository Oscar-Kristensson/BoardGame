# BoardGame docs
BoardGame is built up on the following structure:
> NOTE <br>
> Is a bit outdated

![A graphic of how the program works](./content/programStructure.svg)



## Parser
The parser reads textfiles and returns a data strucutre read from that file.   

## Asset Manager
Loads the textures and manages the data

- Has a interface for loading textures
- Hands over pointers
- Each texture has both an number and a string ID