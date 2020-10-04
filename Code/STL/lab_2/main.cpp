#include <iostream>
#include "metainfo.hpp"

using namespace std;

int main(int argc, char const *argv[])
{	

	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " filename " << endl;
		return 1;
	}
	
	string filename = argv[1]; 

	Metainfo metainfo;
	try { 
		metainfo.load(filename);
		char symbol;
		int length;
		cout << "Enter first symbol: ";
		cin >> symbol;
		cout <<"Enter string length: ";
		cin >> length;
		metainfo.print(symbol,length);
	} catch(Error const &err){
		cerr << err.what() << endl;
	}

}
