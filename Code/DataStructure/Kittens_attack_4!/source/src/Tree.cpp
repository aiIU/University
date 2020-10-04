#include "pch.h"

#include "Tree.h"

int height(TreeNode *N)
{
	return N ? N->height : 0;
}

void updateHeight(TreeNode * N)
{
	N->height = std::max(height(N->left), height(N->right)) + 1;
}

// A utility function to right 
// rotate subtree rooted with y 
// See the diagram given above. 
TreeNode *rightRotate(TreeNode *y)
{
	auto measurement = y->__debug->CreateMeasurement(PerfomanceHelper::RIGHT_ROTATION, false);
	
	TreeNode *x = y->left;
	TreeNode *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights
	updateHeight(y);
	updateHeight(x);

	// Return new root 
	return x;
}

// A utility function to left 
// rotate subtree rooted with x 
// See the diagram given above. 
TreeNode *leftRotate(TreeNode *x)
{
	auto measurement = x->__debug->CreateMeasurement(PerfomanceHelper::LEFT_ROTATION, false);
	TreeNode *y = x->right;
	TreeNode *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	// Update heights
	updateHeight(x);
	updateHeight(y);

	// Return new root 
	return y;
}

// Get Balance factor of node N 
int getBalance(TreeNode *N)
{
	if (N == nullptr)
		return 0;
	return height(N->left) - height(N->right);
}

// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree. 
TreeNode* insert(TreeNode* node, int key)
{
	/* 1. Perform the normal BST insertion */
	if (node == nullptr)
		return new TreeNode{ key, nullptr, nullptr, 1};
	
	auto measurement = node->__debug->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, false);
	
	if (key < node->value)
	{
		node->left = insert(node->left, key);
		node->left->__debug = node->__debug;
	}	
	else if (key > node->value)
	{
		node->right = insert(node->right, key);
		node->right->__debug = node->__debug;
	}
	else // Equal keys are not allowed in BST 
	{
		assert(false && "Equal keys are not allowed in BST!");
		return node;
	}
	
	/* 2. Update height of this ancestor node */
	updateHeight(node);
	
	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->value)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && key > node->right->value)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && key > node->left->value)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->value)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
		
	/* return the (unchanged) node pointer */
	return node;
}

/* Given a non-isEmpty binary FindItem tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
TreeNode * minValueNode(TreeNode* node)
{
	auto measurement = node->__debug->CreateMeasurement(PerfomanceHelper::MIN_VALUE_SEARCH, false);
	TreeNode* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != nullptr)
		current = current->left;

	return current;
}

// https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
// Recursive function to delete a node  
// with given key from subtree with  
// given root. It returns root of the  
// modified subtree.  
TreeNode* remove(TreeNode* root, int key)
{	
	// STEP 1: PERFORM STANDARD BST DELETE  
	if (root == nullptr)
		return root;
	
	auto measurement = root->__debug->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, false);

	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree  
	if (key < root->value)
	{
		root->left = remove(root->left, key);
	}
	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (key > root->value)
	{
		
		root->right = remove(root->right, key);
	}
	// if key is same as root's key, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child  
		if ((root->left == nullptr) ||
			(root->right == nullptr))
		{
			TreeNode *temp = root->left ? root->left : root->right;

			// No child case  
			if (temp == nullptr)
			{
				temp = root;
				root = nullptr;
			}
			else // One child case  
				*root = *temp; // Copy the contents of  
							   // the non-isEmpty child  
			delete temp;
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			TreeNode* temp = minValueNode(root->right);

			// Copy the inorder successor's  
			// data to this node  
			root->value = temp->value;

			// Delete the inorder successor  
			root->right = remove(root->right,
				temp->value);
		}
	}

	// If the tree had only one node 
	// then return  
	if (root == nullptr)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
	root->height = 1 + std::max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced)  
	int balance = getBalance(root);

	// If this node becomes unbalanced,  
	// then there are 4 cases  

	// Left Left Case  
	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case  
	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case  
	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case  
	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}


ScopeMeasuringHelper::ScopeMeasuringHelper(PerfomanceHelper* debug, PerfomanceHelper::Id id, bool withTime)
	: m_perfomanceHelper(debug)
	, m_id(id)
	, m_withTime(withTime)
{
	if (m_perfomanceHelper)
	{
		m_perfomanceHelper->EnterFunction(id);	
	}
	if (withTime)
	{
		m_startPoint = Clock::now();	
	}
}

ScopeMeasuringHelper::~ScopeMeasuringHelper()
{
	if (m_perfomanceHelper && m_withTime)
	{
		auto mcs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - m_startPoint).count();
		m_perfomanceHelper->UpdateElapsedTime(m_id, mcs);
	}
}

PerfomanceHelper::PerfomanceHelper()
{
	Reset();
}

void PerfomanceHelper::Reset()
{
	m_enterFunctionCounters.clear();
	m_elapsedTimes.clear();
	
	m_enterFunctionCounters.resize(Id::_ID_COUNT, 0);
	m_elapsedTimes.resize(Id::_ID_COUNT, 0);
}

ScopeMeasuringHelper PerfomanceHelper::CreateMeasurement(Id id, bool withTime /* = true */)
{
	 return ScopeMeasuringHelper(this, id, withTime);
}

void PerfomanceHelper::UpdateElapsedTime(Id id, int64_t ms)
{
	m_elapsedTimes[id] += ms;
}

void PerfomanceHelper::EnterFunction(Id id)
{
	m_enterFunctionCounters[id] += 1;
}

void PerfomanceHelper::SetEnterFunctionCounter(Id id, int64_t n)
{
	m_enterFunctionCounters[id] = n;
}

void swap(TreeNode& lhs, TreeNode& rhs) noexcept
{
	using std::swap;
	swap(lhs.value, rhs.value);
	swap(lhs.height, rhs.height);
	swap(lhs.left, rhs.left);
	swap(lhs.right, rhs.right);
}

Tree::Tree()
{
	m_perfomanceHelper = new PerfomanceHelper();
}

Tree::Tree(const Tree & other)
	: Tree()
{
	if (other.m_root == nullptr)
	{
		return;
	}
	
	std::queue<TreeNode *> nodes;
	nodes.push(other.m_root);
	while (!nodes.empty())
	{
		auto node = nodes.front();
		nodes.pop();
		if (node->left)
		{
			nodes.push(node->left);
		}
		if (node->right)
		{
			nodes.push(node->right);
		}
		Insert(node->value);
	}	
}

Tree& Tree::operator=(const Tree & other)
{
	Tree temp(other);
	swap(*this, temp);
	return *this;
}

void swap(Tree& lhs, Tree& rhs) noexcept
{
	using std::swap;
	swap(lhs.m_root, rhs.m_root);
	swap(lhs.m_size, rhs.m_size);
}

Tree::Tree(Tree && other) noexcept
{
	swap(*this, other);
}

Tree& Tree::operator=(Tree && other) noexcept
{
	Tree temp(std::move(other));
	swap(*this, temp);
	return *this;
}

Tree::~Tree()
{
	delete m_perfomanceHelper;
	
	if (!m_root)
	{
		return;
	}

	std::deque<TreeNode *> toRemove;
	toRemove.push_back(m_root);
	while (!toRemove.empty())
	{
		auto node = toRemove.front();
		toRemove.pop_front();
		if (node->left)
		{
			toRemove.push_back(node->left);
		}
		if (node->right)
		{
			toRemove.push_back(node->right);
		}
		delete node;
	}

	m_root = nullptr;
	m_size = 0;
}

bool Tree::Insert(int value)
{
	auto measurement = m_perfomanceHelper->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, true);
	
	m_root = insert(m_root, value);
	m_size += 1;

	if (m_size == 1)
	{
		m_root->__debug = m_perfomanceHelper;
	}
	
	return true;
}

void Tree::Remove(int value)
{	
	auto measurement = m_perfomanceHelper->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, true);
	
	m_root = remove(m_root, value);
	m_size -= 1;
}

const TreeNode* Tree::FindRec(const TreeNode* node, int value) const
{
	auto measurement = m_perfomanceHelper->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, false);
	if (node)
	{
		if (value < node->value)
		{
			return FindRec(node->left, value);
		}
		else if (value > node->value)
		{
			return FindRec(node->right, value);
		}
		else
		{
			return node;
		}
	}
	return nullptr;
}

const TreeNode * Tree::Find(int value) const
{
	auto measurement = m_perfomanceHelper->CreateMeasurement(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION, true);
	return FindRec(m_root, value);
}