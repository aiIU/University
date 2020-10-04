#include <sstream>
//#include <cstdio>
#include <utility>
#include <iomanip>

#include "Date.hpp"

using namespace std;

DateError::DateError()
	: m_message("Date format is incorrect")
{}

DateError::DateError(std::string const &str)
	: m_message(str)
{}

char const* DateError::what() const noexcept
{
	return m_message.c_str();
}


Date::Date()
{
	m_day = 1;
	m_month = 1;
	m_year = 1970;
}

Date::Date(int day,int month,int year)
	: m_day(day)
	, m_month(month)
	, m_year(year)
{
	check();	
}

void Date::check()
{
	if (m_year < 1970 || m_year > 2018)
		throw DateError("incorrect year");
    
	if (m_month <= 0 || m_month > 12)
		throw DateError("incorrect month");

	if (m_day <= 0 || m_day > 31)
		throw DateError("incorrect day");
	
	const bool isUsualYear = (m_year % 4 != 0) || (m_year % 400 != 0 && m_year % 100 == 0);

	if (m_month == 2 && isUsualYear && m_day > 28)
		throw DateError("incorrect day because the year is a leap year");
	
	if (m_month == 2 && !isUsualYear && m_day > 29)
		throw DateError("incorrect day because the year is a usual year");
}

/*std::string Date::toString()
{
	std::string result(11,'\0');
	
	std::sprintf(&result.front(),"%d.%d.%d",m_day,m_month,m_year);
	return result;

	char* result = new char[11];
	std::sprintf(result ,"%d.%d.%d",m_day,m_month,m_year);
	result[10] = '\0';
	std::string s(result);
	delete[] result;

	return s;

}
void Date::fromString(string const &str)
{	
	int temp = std::sscanf(str.c_str(),"%d.%d.%d",m_day,m_month,m_year);
	if(temp != 3)
		throw DateError();
	else check();
}
*/

void Date::fromString(std::string const &str)
{
	//Date copy(*this);

	std::istringstream stream(str);
	
	stream >> m_day;
	if(stream.fail()) {
		throw DateError();
	}
	
	stream.ignore(1, '.');
	
	stream >> m_month;
	if(stream.fail()) {
		throw DateError();
	}

	stream.ignore(1, '.');

	stream >> m_year;
	if(stream.fail()) {
		throw DateError();
	}

	check();
}

std::string Date::toString() const 
{
	std::ostringstream stream;
	stream 
		<< setw(2) << setfill('0') << m_day << '.'
		<< setw(2) << setfill('0') << m_month << '.'
		<< m_year;
	return stream.str();
}

void Date::swap(Date &other) noexcept
{
	std::swap(m_day, other.m_day);
	std::swap(m_month, other.m_month);
	std::swap(m_year, other.m_year);
}