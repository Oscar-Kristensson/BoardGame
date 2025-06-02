#include "game.h"

namespace BoardGame {
    namespace parser {

        BoardGame::EntityType getEntityTypeFromName(std::string& entityTypeString)
        {
            auto it = BoardGame::entityMap.find(entityTypeString);
            if (it != BoardGame::entityMap.end())
                return it->second;
            else
                return TypeUnkown;
        };

        std::string getNameFromEntityType(BoardGame::EntityType entityType)
        {
            for (const auto& pair : BoardGame::entityMap) {
                if (pair.second == entityType)
                    return pair.first;
            }
            return "Unknown";
        };

        struct commandData
        {
            BoardGame::EntityType commandType;
            std::map<std::string, std::string> argumentMap;

            std::string str()
            {
                std::string entityTypeString;
                

                std::string s = "Command Data\n|-- Type: " + std::to_string(commandType) + ", " + getNameFromEntityType(commandType);
                for (const auto& pair : argumentMap) {
                    s += "\n|-- " + pair.first + ": " + pair.second;
                    
                }
                return s;
            };
        };

        CommonPlayerInfo createCommonPlayerInfoObject(const commandData& cd)
        {
            if (cd.commandType != TypeCommonPlayerInfo)
                std::cerr << "Trying to create CommonPlayerInfo from a " << cd.commandType << "object" << std::endl;

            bool usePlayerAccounts = BoardGame::utils::convertToBool(cd.argumentMap.at("hasAccounts"));

            int playerAccountStartValue = 0;
            BoardGame::utils::convertToInt(cd.argumentMap.at("accountBalance"), playerAccountStartValue);

            CommonPlayerInfo playerInfo = { usePlayerAccounts, playerAccountStartValue };

            return playerInfo;
        }

        PlayerInfo createPlayerInfoObject(const commandData& cd)
        {
            if (cd.commandType != TypePlayerInfo)
                std::cerr << "Trying to create PlayerInfo from a " << cd.commandType << "object" << std::endl;


            int x = 0;
            int y = 0;

            if (cd.argumentMap.find("x") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("x"), x);
            else
                std::cout << "Warning: Trying to create a player with out an x parameter" << std::endl;


            if (cd.argumentMap.find("y") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("y"), y);
            else
                std::cout << "Warning: Trying to create a player with out a y parameter" << std::endl;


            std::string colorString = "ff00aa";
            if (cd.argumentMap.find("color") != cd.argumentMap.end())
                colorString = cd.argumentMap.at("color");
            else
                std::cout << "Warning: Trying to create a player with out a color parameter" << std::endl;

            Color color = BoardGame::utils::convertHEXToRGB(colorString);

            PlayerInfo playerInfo = { x, y, color };

            std::cout << "Creating player" << std::endl;

            return playerInfo;
        }


        GameInfo createGameInfoObject(const commandData& cd)
        {
            if (cd.commandType != TypeGameInfo)
                std::cerr << "Trying to create GameInfo from a " << cd.commandType << "object" << std::endl;


            uint16_t boardWidth;
            uint16_t boardHeight;
            std::string backgroundColorString = cd.argumentMap.at("backgroundColor");
            BoardGame::utils::convertToUint16(cd.argumentMap.at("boardWidth"), boardWidth);
            BoardGame::utils::convertToUint16(cd.argumentMap.at("boardHeight"), boardHeight);
            Color backgroundColor = BoardGame::utils::convertHEXToRGB(backgroundColorString);

            return { boardWidth, boardHeight, backgroundColor };
        };


        BoardGame::GameEntityData createEntityObject(const commandData& cd)
        {
            if (cd.commandType != TypeEntity)
                std::cerr << "Trying to create Entity from a " << cd.commandType << "object" << std::endl;


            std::filesystem::path imagePath = cd.argumentMap.at("img").c_str();

            int x;
            int y;

            BoardGame::utils::convertToInt(cd.argumentMap.at("x"), x);
            BoardGame::utils::convertToInt(cd.argumentMap.at("y"), y);

            

            return { imagePath, x, y};
        };



        StartMenuInfo createStartMenuInfoObject(const commandData& cd)
        {
            if (cd.commandType != TypeStartMenuInfo)
                std::cerr << "Trying to create StartMenuInfoOjbect from a " << cd.commandType << "object" << std::endl;


            std::string backgroundColorString = cd.argumentMap.at("backgroundColor");
            Color backgroundColor = BoardGame::utils::convertHEXToRGB(backgroundColorString);

            return { backgroundColor };
        };











        std::pair<std::string, std::string> convertStringArgumentToStringPair(const std::string& stringPair)
        {
            size_t pos = stringPair.find('=');  // Find position of '='

            std::string left;
            std::string right;

            if (pos != std::string::npos) {  // Check if '=' was found
                left = stringPair.substr(0, pos);          // Part before '='
                right = stringPair.substr(pos + 1);        // Part after '='
            }
            else {
                std::cout << "'=' not found in string." << std::endl;
            }

            return { left, right};
        };
        

        commandData parseCommand(std::string& commandLine)
        {
            uint8_t argumentNumber = 0;
            
            std::string argumentName;
               
            std::ostringstream argument;


            std::map<std::string, std::string> argumentMap;

            for (uint16_t charNumber = 0; charNumber < commandLine.length(); charNumber++)
            {
                
                char character = commandLine.at(charNumber);

                switch (character)
                {
                case ' ':
                    break;
                case '\n':
                    break;
                case ',':
                    if (argumentNumber == 0)
                        argumentName = argument.str();
                    else
                    {
                        std::pair<std::string, std::string> argumentPair = convertStringArgumentToStringPair(argument.str());
                        argumentMap.insert(argumentPair);
                    }
                    
                    // Clears the argument
                    argument.clear();
                    argument.str("");
                    argumentNumber++;
                    break;

                default:
                    argument << character;
                    break;
                }
            }

            // Print the last argument after the loop if there's any content in the argument
            if (!argument.str().empty())
            {
                std::pair<std::string, std::string> argumentPair = convertStringArgumentToStringPair(argument.str());
                argumentMap.insert(argumentPair);
            };


            BoardGame::EntityType entityType = getEntityTypeFromName(argumentName);

            commandData commandData = { entityType, argumentMap };
            return commandData;
        };


        BoardGame::GameConfigData loadGameData(const std::filesystem::path& path)
        {
            BoardGame::GameInfo gameInfo = { 2000, 2000 , Color(255, 255, 255)};
            BoardGame::StartMenuInfo startMenuInfo = { Color(255, 255, 255)};
            std::vector<BoardGame::GameEntityData> entities;
            BoardGame::CommonPlayerInfo commonPlayerInfo = { false, 0};
            std::vector<BoardGame::PlayerInfo> players;

            bool hasGameInfo = false;
            bool hasStartMenuInfo = false;

            std::ifstream file(path);
            
            if (!file.is_open())
            {
                std::cerr << "Failed to open file" << std::endl;
                return { gameInfo };
            };


            std::string line;
            while (std::getline(file, line, ';'))
            {
                // Skips lines empty lines and comments (;#)
                if (line[0] == '#' || line == "\n")
                    continue;

                commandData cd = parseCommand(line);



                switch (cd.commandType)
                {
                case TypeGameInfo:
                    hasGameInfo = true;
                    gameInfo = createGameInfoObject(cd);
                    break;

                case TypeStartMenuInfo:
                    hasStartMenuInfo = true;
                    startMenuInfo = createStartMenuInfoObject(cd);
                    break;

                case TypeEntity:
                    entities.push_back(createEntityObject(cd));
                    break;
                    
                case TypeCommonPlayerInfo:
                    commonPlayerInfo = createCommonPlayerInfoObject(cd);
                    break;

                case TypePlayerInfo:
                    players.emplace_back(createPlayerInfoObject(cd));

                default:
                    break;
                }
                
            };
            

            file.close();

            return { gameInfo, startMenuInfo, entities,  commonPlayerInfo, players };
        };
    };
};
