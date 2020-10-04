#include <iostream>
#include <string>

#include "Calendar.hpp"
#include "Date.hpp"


size_t Calendar::size() const
{
	return m_storage.size();	
}

void Calendar::insert(string const &name,Date const &date) 
{
	
	m_storage.emplace(name, date);
}


void Calendar::print() const
{
	if (m_storage.empty()) {
		cout << "Calendar is empty." << endl;
		return;
	}
	for (multimap<string, Date>::const_iterator it = m_storage.begin(); it != m_storage.end(); ++it)
		cout << it->first << " : " << it->second.toString() << endl;
	/*
	for (auto const &record : m_storage) // range-based cycle
		cout << record.first << " : " << record.second.toString << endl;
	*/
}

void Calendar::find(string const &personinfo) const
{
	//pair<multimap<string,Date>::const_iterator,multimap<string,Date>::const_iterator> 
	auto const result = m_storage.equal_range(personinfo);
	if (result.first == m_storage.end()) {
		cout << "Not found." << endl;
		return;
	}
	for (auto it = result.first; it != result.second; ++it) {
		cout << it->first << " : " << it->second.toString() << endl;
	}
}

