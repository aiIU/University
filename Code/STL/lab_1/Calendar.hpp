#include <map>

#include "Date.hpp"


using namespace std;

class Calendar
{
public:
	size_t size() const;
	void insert(string const &name,Date const &date);
	void print() const;
	void find(string const &) const;
private:
	multimap<string, Date> m_storage;
};