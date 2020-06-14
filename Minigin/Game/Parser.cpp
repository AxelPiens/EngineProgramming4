#include "MiniginPCH.h"
#include "Parser.h"
#include <fstream>

Parser::Parser()
{
}

void Parser::ReadFile(std::string path, int level)
{

    std::fstream file(path, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        std::cout << "FILE NOT OPEN\n";
    }

    file.seekg(std::streamoff(level * std::streamoff(100)));

    for (int l = level; l < level+1; l++)
    {
        for (int j = 0; j < 25; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                unsigned char pChar = {};
                file.read((char*)&pChar, sizeof(unsigned char));

                unsigned int mask;
                for (mask = 0x80; mask != 0; mask >>= 1)
                {
                    if (pChar & mask)
                    {
                        levelData.push_back(1);
                    }
                    else
                    {
                        levelData.push_back(0);
                    }
                }
            }
        }
    }
    file.close();
}

void Parser::GetLevelData(std::vector<int>& leveldata)
{
    leveldata = levelData;
}
