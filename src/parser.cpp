#include "game.h"

namespace BoardGame {
    namespace parser {

        BoardGame::EntityType getEntityTypeFromName(std::string& entityTypeString)
        {
            auto it = BoardGame::entityMap.find(entityTypeString);
            if (it != BoardGame::entityMap.end())
                return it->second;
            else
                return Unkown;
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
            BoardGame::EntityType entityType;


            std::string str()
            {
                std::string entityTypeString;
                

                std::string s = "Command Data\n|-- Entity: " + std::to_string(entityType) + ", " + getNameFromEntityType(entityType);
                return s;
            };
        };

        std::string extractStartWord(std::string& string)
        {
            std::istringstream iss(string);
            std::string command;
            
            iss >> command;

            return command;
        };


        


        commandData parseCommand(std::string& commandLine)
        {
            std::cout << "Parsing line:" << commandLine << std::endl;

            std::string entityTypeString = extractStartWord(commandLine);
            
            BoardGame::EntityType entityType = getEntityTypeFromName(entityTypeString);

            commandData commandData = { entityType };
            return commandData;
        };



        void ping()
        {
            std::cout << "Hello World from parser" << std::endl;
        };


        void readFile(const std::filesystem::path& path)
        {
            std::ifstream file(path);
            
            if (!file.is_open())
            {
                std::cerr << "Failed to open file" << std::endl;
                return;
            };


            std::string line;
            while (std::getline(file, line))
            {
                commandData cd = parseCommand(line);
                std::cout << cd.str() << std::endl;
            };
            

            file.close();
        };
    };
};
