#pragma once
class Parser
{
public:
	Parser();
	~Parser() = default;

	Parser(Parser&& other) noexcept = delete;
	Parser& operator=(const Parser& other) = delete;
	Parser& operator=(Parser&& other) noexcept = delete;
	void ReadFile(std::string file, int level);
	void GetLevelData(std::vector<int>& leveldata);
private:
	std::vector<int> levelData;
};

