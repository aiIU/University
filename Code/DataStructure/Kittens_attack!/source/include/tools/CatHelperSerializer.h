#pragma once

class CatHelper;
struct CatReaction;

class CatHelperSerializer
{
public:
	CatHelperSerializer(CatHelper * catHelper);
	~CatHelperSerializer();

	bool LoadFromMemory(const char * data);
	bool Load(const string & filename);
	bool Save(const string & filename);

	string Error() const { return m_error; }
	
private:
	struct Impl;
	
	CatHelper *				m_catHelper;
	string					m_error;
	unique_ptr<Impl>		m_pImpl;
};