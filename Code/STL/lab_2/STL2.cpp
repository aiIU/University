#include<map>
#include<fstream>

using namespace std::

class Metainfo
{
public:
	void load(ifstream &);
	void print(char symbol,int length);

private:
	//typedef multimap<int,int> Info;
	using Info = typename multimap<int,int>;
	map<char,Info> alphabet; 


}