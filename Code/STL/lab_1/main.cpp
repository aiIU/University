#include <iostream>

#include "Date.hpp"
#include "Calendar.hpp"

int main()
{
	cout << "Please, enter records formatted in \"<person info> : <date of birthday>\"." << endl;
	cout << "Enter 'end' for stop." << endl;
	//size_t i = 0;
	string temp, name;
	Date date;
	Calendar calendar;
	//bool success = false;

	while (cin.good()) {
		cout << "#" << calendar.size() << ". ";
		{
			getline(cin, temp);
			// String like " : "  is minimum requirement,
			// because and personinfo and date must not be nil
			if (temp.size() < 3) { 
				cin.setstate(ios_base::failbit);
				continue;
			}
			size_t delim_pos = temp.find(':');
			if (delim_pos == string::npos) {
				cin.setstate(ios_base::failbit);
				continue;
			}
			name = temp.substr(0, delim_pos);
			try {
				//Date copy;
				date.fromString(temp.substr(delim_pos + 1));
				//date = copy;
				calendar.insert(name,date);
			} catch(DateError const &err) {
				cout << err.what() << endl;
			}
			

		}
			
	} // while(cin.good())
	cin.clear();
	cout << "Calendar was filled on " << calendar.size() << " records." << endl;


	cout << "Calendar contains following elements: \n" ;
	calendar.print();

	cout << "Enter person info for search in calendar: ";
	string personinfo;
	getline(cin, personinfo);

	calendar.find(personinfo);
}