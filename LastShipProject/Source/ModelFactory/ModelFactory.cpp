#include "ModelFactory.h"

bool ModelFactory::readCSV(const std::string &filePath, CSVTable &table)
{
	CSVReader reader;

	if (reader.read(filePath) == false){ return false; }
	table = reader.getTable();
	
	return true;
}

int ModelFactory::loadModels(CSVTable &table)
{
	std::string modelName;
	int i = 0;
	int handle;
	int size = resizeTable(table);
	if (size <= 0){ return -1; }

	for (int i = 0; i < size;++i){
		modelName = table.at(i).at(0);
		handle = MV1LoadModel(table.at(i).at(1).c_str());
		mapNameHandle_m.insert(
			std::make_pair(modelName, handle));
	}

	return 0;
}

int ModelFactory::resizeTable(CSVTable &table)
{
	CSVTable::iterator begin = table.begin(), end = table.end();

	begin = std::remove_if(begin, end, [](CSVTable::value_type &value) -> bool
	{
		return value.size() != 2;
	});
	table.erase(begin, end);

	return table.size() >= 1 ? table.size() : -1;
}

int ModelFactory::createMap(const std::string &csvFilePath)
{
	CSVTable table;

	if (readCSV(csvFilePath, table) == false){ return false; }

	if (loadModels(table) != 0){ return false; }

	return true;
}

int ModelFactory::getHandle(const std::string &modelName)
{
	std::map<std::string, int>::iterator handle;
	if ((handle = mapNameHandle_m.find(modelName))
		== mapNameHandle_m.end()){ return -1; }

	return MV1DuplicateModel(handle->second);

}


