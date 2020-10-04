#include "metainfo.hpp"
#include <iostream>

using namespace std;

Error::Error()
	: m_message()
{}

Error::Error(std::string const &str)
	: m_message(str)
{}


char const* Error::what() const noexcept
{
	return m_message.c_str();
}

/*	Получили на вход поток данных.
		Нужно обработать.
			1. Прочесть одну строку
			2. Обновить map:
				a) найти в мапе значению по ключу - первому символу
					Это значение будет содержать multimap<int, int>
					или другими словами Info - кучу строк, вернее не строк
					а пар "длина строки и позиция в файле".
				b) Если такое значение не найдено, то нужно добавить в мапу
					пару ключ-значение, где ключ - это символ по которому искали,
					а значение - пока что пустая мультимапа или же другими
					словами Info. 
				c) Теперь работаем с Info (в случае с пунктом b - работаем с 
					новосозданным Info).
				d) Добавляем в Info пару <длина строки, позиция файле>, но вот
					проблема - позиция в файле уже не верна, так как после пункта 1
					мы изменили позицию "каретки" в файле.Нужно
					запоминать позицию _до_ чтения строки.
			3. Повторить до тех пор, пока поток не достиг конца.
	*/	
void Metainfo::load(string const &filename)
{
	m_filename = filename;

	ifstream input(filename);
	if(!input.is_open())
		throw Error("Cannot open file");
	string buf;
	int pos;
	while(input.good()){
		pos = input.tellg();
		getline(input,buf);
		if(buf.empty())
			continue;

		auto map_it = m_alphabet.find(buf.front());
		if(map_it == m_alphabet.end()){
			auto res = m_alphabet.emplace(buf.front(),Info());
			map_it = res.first;
		}
		auto &info = map_it->second;
		info.emplace(buf.size(),pos);
	}
	
}
void Metainfo::print(char symbol,int length)
{
	auto map_it = m_alphabet.find(symbol);
	if(map_it == m_alphabet.end()){
		cout << "Strings not found" << endl;
		return;
	}
	Info &info = map_it->second;
	auto result = info.equal_range(length);
	if(result.first == info.end()){
		cout << "Strings with certain length not found" << endl;
		return;
	}

	auto it_first = result.first;
	auto it_last = result.second;

	string line;
	ifstream input(m_filename);
	if(!input.is_open()){
		throw Error("Cannot open file");
	}

	for(auto it = it_first ;it != it_last;it++){
		input.seekg(it->second);
		getline(input,line);
		cout << line << endl;
	}




};