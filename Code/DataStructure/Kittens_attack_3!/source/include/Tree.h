#pragma once

class ScopeMeasuringHelper;

class PerfomanceHelper
{
public:
	enum Id
	{
		LEFT_ROTATION,
		RIGHT_ROTATION,
		MIN_VALUE_SEARCH,
		TOTAL_FUNCTION_EXECUTION,
		_ID_COUNT
	};

	PerfomanceHelper();
	
	void Reset();
	ScopeMeasuringHelper CreateMeasurement(Id id, bool withTime = true);
	int64_t GetElapsedTime(Id id) const { return m_elapsedTimes[id]; }
	int64_t GetEnterFunctionCounter(Id id) const { return m_enterFunctionCounters[id]; }
	
	void UpdateElapsedTime(Id id, int64_t ms);
	void EnterFunction(Id id);
	void SetEnterFunctionCounter(Id id, int64_t n);
	
private:	
	vector<int64_t>		m_enterFunctionCounters;
	vector<int64_t>		m_elapsedTimes;
};

class ScopeMeasuringHelper
{
public:
	ScopeMeasuringHelper(PerfomanceHelper * debug, PerfomanceHelper::Id id, bool withTime);
	~ScopeMeasuringHelper();
	
private:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	
	TimePoint				m_startPoint;
	PerfomanceHelper *		m_perfomanceHelper = nullptr;
	PerfomanceHelper::Id	m_id;
	bool					m_withTime = true;
};

struct TreeNode
{	
	int			value	= 0;
	TreeNode *	left	= nullptr;
	TreeNode *	right	= nullptr;
	int			height	= 0;
	
	mutable PerfomanceHelper	* __debug = nullptr;
};

inline void swap(TreeNode & lhs, TreeNode & rhs) noexcept;

class Tree
{
public:
	Tree();
	
	Tree(const Tree & other);
	Tree & operator=(const Tree &);
	Tree(Tree && other) noexcept;
	Tree & operator=(Tree &&) noexcept;
	~Tree();

	inline friend void swap(Tree & lhs, Tree & rhs) noexcept;

	bool Insert(int value);
	void Remove(int value);	
	const TreeNode * Find(int value) const;

	bool IsEmpty() const { return m_size == 0; }
	int Size() const { return m_size; }

	PerfomanceHelper * GetPerfomanceInfo() const { return m_perfomanceHelper; }

private:	
	const TreeNode* FindRec(const TreeNode* node, int value) const;
	
	TreeNode *	m_root = nullptr;
	int			m_size = 0;
	
	PerfomanceHelper * m_perfomanceHelper = nullptr;
};