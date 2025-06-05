#include "game.h"

namespace BoardGame {
    namespace parser {

        /**
         * @brief Matches the entity name (used in the text file) with its type (used in the parser to identify)
         * @param entityTypeString -  the entity name (ex GameInfo)
         * @return The entity type (TypeUnkown, TypeGameInfo etc)
         */
        BoardGame::EntityType getEntityTypeFromName(std::string& entityTypeString)
        {
            auto it = BoardGame::entityMap.find(entityTypeString);
            if (it != BoardGame::entityMap.end())
                return it->second;
            else
                return TypeUnkown;
        };

        /**
         * @brief Matches the entity name (used in the text file) with its type (used in the parser to identify)
         * @param entityType - The entity type (the id used by the parser)
         * @return The entity name (used in the text file)
         */
        std::string getNameFromEntityType(BoardGame::EntityType entityType)
        {
            for (const auto& pair : BoardGame::entityMap) {
                if (pair.second == entityType)
                    return pair.first;
            }
            return "Unknown";
        };

        /**
         * @brief Stores the data from a single line
         * 
         * The data is stored with its commandType (TypeUnkown, TypeGameInfo etc) and a map <key, value>
         */
        struct commandData
        {
            BoardGame::EntityType commandType;
            std::map<std::string, std::string> argumentMap;

            std::string str()
            {
                std::string entityTypeString;
                

                // std::string s = "Command Data\n|-- Type: " + std::to_string(commandType) + ", " + getNameFromEntityType(commandType);
                std::string s = std::to_string(commandType) + ", " + getNameFromEntityType(commandType);
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


            int turnDisplayX = 150;
            int turnDisplayY = 20;
            int bankDisplayX = 300;
            int bankDisplayY = 20;

            if (cd.argumentMap.find("turnDisplayX") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("turnDisplayX"), turnDisplayX);

            if (cd.argumentMap.find("turnDisplayY") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("turnDisplayY"), turnDisplayY);

            if (cd.argumentMap.find("bankDisplayX") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("bankDisplayX"), bankDisplayX);

            if (cd.argumentMap.find("bankDisplayY") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("bankDisplayY"), bankDisplayY);





            return { 
                boardWidth, 
                boardHeight, 
                backgroundColor, 
                turnDisplayX, 
                turnDisplayY, 
                bankDisplayX, 
                bankDisplayY 
            };
        };


        GameEntityData createEntityObject(const commandData& cd)
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


        DiceInfo createDiceInfoObject(const commandData& cd)
        {
            if (cd.commandType != TypeDiceInfo)
                std::cerr << "Trying to create DiceInfoObject from a " << cd.commandType << "object" << std::endl;

            int x = 0;
            int y = 0;
            uint8_t min = 0;
            uint8_t max = 0;

            if (cd.argumentMap.find("x") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("x"), x);

            if (cd.argumentMap.find("y") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("y"), y);

            if (cd.argumentMap.find("min") != cd.argumentMap.end())
                BoardGame::utils::convertToUint8(cd.argumentMap.at("min"), min);

            if (cd.argumentMap.find("max") != cd.argumentMap.end())
                BoardGame::utils::convertToUint8(cd.argumentMap.at("max"), max);


            DiceInfo diceInfo = { x, y, min, max };
            return diceInfo;
        }

        LabelInfo createLabelInformationObject(const commandData& cd)
        {
            if (cd.commandType != TypeLabel)
                std::cerr << "Trying to create LabelObject from a " << cd.commandType << "object" << std::endl;

            std::string textString;

            if (cd.argumentMap.find("text") != cd.argumentMap.end())
                textString = cd.argumentMap.at("text");

            else
                textString = "label";


            int x = 0;
            if (cd.argumentMap.find("x") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("x"), x);

            int y;
            if (cd.argumentMap.find("y") != cd.argumentMap.end())
                BoardGame::utils::convertToInt(cd.argumentMap.at("y"), y);

            uint8_t fontSize = 30;
            if (cd.argumentMap.find("fontSize") != cd.argumentMap.end())
                BoardGame::utils::convertToUint8(cd.argumentMap.at("fontSize"), fontSize);

            TextAlignment textAlignment;

            if (cd.argumentMap.find("align") == cd.argumentMap.end())
                textAlignment = Left;
            else
                if (cd.argumentMap.at("align") == "C")
                    textAlignment = Centered;
                else if (cd.argumentMap.at("align") == "L")
                    textAlignment = Left;
                else if (cd.argumentMap.at("align") == "R")
                    textAlignment = Right;
                else
                    textAlignment = Left;


            return { textString, x, y, fontSize, textAlignment };

        }










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
            std::vector<BoardGame::DiceInfo> die;
            std::vector<BoardGame::LabelInfo> labels;

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
#if _DEBUG
                std::cout << "Processed line: " << line << '\n' << cd.str() << '\n' << std::endl;
#endif


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
                    break;

                case TypeDiceInfo:
                    die.emplace_back(createDiceInfoObject(cd));
                    break;

                case TypeLabel:
                    labels.emplace_back(createLabelInformationObject(cd));
                    break;

                default:
                    break;
                }
                
            };
            

            file.close();

            return { gameInfo, startMenuInfo, entities,  commonPlayerInfo, players, die, labels };
        };
    };
};
