#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

//CSV�t�@�C����ǂݍ���ŕ�����̕\�����N���X�ł��B
//�ǂݍ��߂�t�@�C��
/*1�o�C�g��1����ascii�R�[�h�̂�
��ؕ���  ','  '\t'  ';'
�s�I�[���� '\n'
�Ǎ�����  '0' ~ '9'
         'a' ~ 'z'
         'A' ~ 'Z'
		 '.',  '\\',  '/',  ' ',  '_'  '%'  '-'  '('  ')'  '['  ']'
����ȊO�͖�������܂��B
*/
//�쐬�����\
/*�������2�����z��(vector<vector<string>>)���ł��܂��B
�s���͍s�I�[�����̐�+1�Ɠ�����������, �e�s�̗񐔂͂��̍s�̋�ؕ����̐�+1�ł��B
*/

//�g����
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
		std::cout << "�v�f��" << colamnI->size() << ":";
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
		std::cout << "�v�f��" << colamn.size() << ":";
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
//���s����
/*
�v�f��9:00 01 02 03 04% 05 06 07( 08)
�v�f��6:10- 11 12\ 13 14 15
�v�f��4:20 21[ 22 23
�v�f��7:30  31 32] 33 35 36
�v�f��9:40  41. 42/ 43\ 44 45 46 47_
�v�f��7:40J 41u 42n 43p 44a 45k 46u
*/

//��ؕ�����s�I�[������Ǎ�������ς��邱�Ƃ��ł��܂��B
/*
CSVReader::Discrimination���p������
isCharactor,isDerimiter,isTerminator���I�[�o�[���C�h��
setDiscrimination�̃e���v���[�g�����ɓn���܂��B
�Ǎ������𐔎��̂�,��ؕ�����','�݂̂Ƃ����
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

