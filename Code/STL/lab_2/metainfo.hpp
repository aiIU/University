#ifndef METAINFO 
#define METAINFO 

#include <map>
#include <fstream>
#include <exception>
#include <string>

class Error : public std::exception
{	
public:
	Error();
	Error(std::string const &);
	virtual char const* what() const noexcept;
private:
	std::string m_message;
};

class Metainfo
{
public:
	void load(std::string const &filename);
	void print(char symbol,int length);

private:
	//typedef multimap<int,int> Info;
	using Info = std::multimap<int,int>;
	std::map<char,Info> m_alphabet; 

	std::string m_filename;

};


















#endif