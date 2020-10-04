#ifndef DATE_HPP
#define DATE_HPP

#include <exception>
#include <string>


class DateError : public std::exception
{	
public:
	DateError();
	DateError(std::string const &);

	virtual char const* what() const noexcept;
private:
	std::string m_message;
};

class Date
{
public:
	Date();
	Date(int day,int month,int year);

	std::string toString() const;
	void fromString(std::string const &str);
	void swap(Date &) noexcept;
private: 
	int m_day;
	int m_month;
	int m_year;
private:
	void check();
};


#endif