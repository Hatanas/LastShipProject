#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

//CSVファイルを読み込んで文字列の表を作るクラスです。
//読み込めるファイル
/*1バイトで1文字asciiコードのみ
区切文字  ','  '\t'  ';'
行終端文字 '\n'
読込文字  '0' ~ '9'
         'a' ~ 'z'
         'A' ~ 'Z'
		 '.',  '\\',  '/',  ' ',  '_'  '%'  '-'  '('  ')'  '['  ']'
これ以外は無視されます。
*/
//作成される表
/*文字列の2次元配列(vector<vector<string>>)ができます。
行数は行終端文字の数+1と同じだけあり, 各行の列数はその行の区切文字の数+1です。
*/

//使い方
//sample.csv
/*00!,01",02#,03$,04%,05&,06',07(,08)
10-,11^,12\,13=,14~,15|
20@,21[,22`,23{
30;,31:,32],33+,35*,36}
40,,41.,42/,43\,44<,45>,46?,47_
40J,41u,42n,43p,44a,45k,46u
*/
//main.cpp
/*
#include <iostream>
#include "CSVReader.h"

int main()
{
	CSVReader reader;
	std::vector<std::vector<std::string>> table;
	std::vector<std::vector<std::string>>::iterator colamnI;
	std::vector<std::string>::iterator cellJ;

	reader.read("sample.csv");
	table = reader.getTable();

	for (colamnI = table.begin(); colamnI != table.end(); ++colamnI){
		std::cout << "要素数" << colamnI->size() << ":";
		for (cellJ = colamnI->begin(); cellJ != colamnI->end(); ++cellJ){
			std::cout << *cellJ << " ";
		}
		std::cout << std::endl;
	}

	return 0;	
}
*/
/*
#include <algorithm>
#include <iostream>
#include "CSVReader.h"

typedef CSVReader::CSVTable::value_type ColamnType;
typedef ColamnType::value_type CellType;

int main()
{
	auto writeCell = [](CellType cell)
	{
		std::cout << cell << " ";
	};
	auto writeColamn = [writeCell](ColamnType colamn)
	{
		std::cout << "要素数" << colamn.size() << ":";
		std::for_each(colamn.begin(), colamn.end(), writeCell);
		std::cout << std::endl;
	};

	CSVReader reader("sample.csv");
	reader.read();
	CSVReader::CSVTable table = reader.getTable();
	std::for_each(table.begin(), table.end(), writeColamn);

	return 0;
}
*/
//実行結果
/*
要素数9:00 01 02 03 04% 05 06 07( 08)
要素数6:10- 11 12\ 13 14 15
要素数4:20 21[ 22 23
要素数7:30  31 32] 33 35 36
要素数9:40  41. 42/ 43\ 44 45 46 47_
要素数7:40J 41u 42n 43p 44a 45k 46u
*/

//区切文字や行終端文字や読込文字を変えることができます。
/*
CSVReader::Discriminationを継承して
isCharactor,isDerimiter,isTerminatorをオーバーライドし
setDiscriminationのテンプレート引数に渡します。
読込文字を数字のみ,区切文字を','のみとする例
	class IsNumber : public CSVReader::Discrimination
	{
	public:
		bool isCharactor(char c){ return '0' <= c && c <= '9'; }
		bool isDerimiter(char c){ return c == ','; }
	};
	reader.setDiscrimination<IsNumber>();
*/

class CSVReader
{
public:
	typedef std::vector<std::vector<std::string>> CSVTable;
	class Discrimination
	{
	public:
		Discrimination(){}
		~Discrimination(){}
		virtual bool isCharactor(char c)
		{
			return ('a' <= c && c <= 'z') ||
				('A' <= c && c <= 'Z') ||
				('0' <= c && c <= '9') ||
				c == '/' ||
				c == '\\' ||
				c == '_' ||
				c == ' ' ||
				c == '.' ||
				c == '%' ||
				c == '(' ||
				c == ')' ||
				c == '-' ||
				c == '[' ||
				c == ']';
		}
		virtual bool isDerimiter(char c){
			return c == ',' ||
				c == '\t' ||
				c == ';';
		}
		virtual bool isTerminator(char c){ return c == '\n'; }
	};
private:
	std::string path_m;
	CSVTable table_m;
	std::unique_ptr<Discrimination> discrimination_m;
public:
	explicit CSVReader(const std::string &filePath) : CSVReader()
	{
		path_m = filePath;
		read(filePath);
	}
	CSVReader()
	{
		setDiscrimination<Discrimination>();
	}
	~CSVReader(){}
	bool read();
	bool read(const std::string &filename){
		path_m = filename;
		return read();
	}
	CSVTable getTable(){ return table_m; }
	template<class D>
	void setDiscrimination(){ discrimination_m = std::make_unique<D>(); }
};

