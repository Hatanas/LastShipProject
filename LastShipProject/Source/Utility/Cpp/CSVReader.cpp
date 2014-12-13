#include "./../CSVReader.h"
#include "DxLib.h"

bool CSVReader::read()
{
	table_m.clear();
	table_m.push_back(std::vector<std::string>(1, std::string()));
	std::ifstream file(path_m, std::ios::binary);
	int i = 0, j = 0;
	char c;

	while (!file.eof()){
		if (!file.good()){ return false; }
		file.read(&c, 1);
		if (!file.eof()){
			if (discrimination_m->isCharactor(c)){
				table_m.at(i).at(j) += c;
			}
			else if (discrimination_m->isDerimiter(c)){
				table_m.at(i).push_back(std::string());
				++j;
			}
			else if (discrimination_m->isTerminator(c)){
				table_m.push_back(
					std::vector<std::string>(1, std::string()));
				++i; j = 0;
			}
			else{}
		}
	}

	return true;
}
