#pragma once

class GeneratorId
{
public:
	int GetMaximumId() const { return m_maximum; }
	int Next();
	void Free(unsigned id);

private:
	unsigned 		m_maximum {100};
	set<unsigned>	m_ids;
	std::mt19937	m_randomGenerator;
};