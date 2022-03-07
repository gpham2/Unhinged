#ifndef RADIX_TREE
#define RADIX_TREE

#include <string>
#include <vector>


// class declaration
template <class ValueType>
class RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;

private:

	// struct implementation
	struct Node
	{
		Node(std::string string, ValueType value, bool isWord)
		{
			m_isWord = isWord;
			m_string = string;
			m_value = value;
		}

		Node(bool isWord)
		{
			m_isWord = isWord;
		}

		std::string m_string;
		ValueType m_value;
		std::vector<Node*> m_children;
		bool m_isWord;
	};

	Node* m_head;

	// helper functions
	int getMismatchingIndex(std::string word, std::string otherWord)
	{
		int len = word.size() < otherWord.size() ? word.size() : otherWord.size();
		for (int i = 0; i < len; i++)
		{
			if (word.at(i) != otherWord.at(i))
				return i;
		}
		return -1;
	}

	void destroy(Node* node)
	{
		if (node == nullptr) return;

		for (typename std::vector<Node*>::iterator it = node->m_children.begin(); it != node->m_children.end();it++)
		{
			destroy(*it);
		}
		delete node;
	}

};

template <class ValueType>
RadixTree<ValueType>::RadixTree()
{
	m_head = new Node(false);
	m_head->m_children.push_back(nullptr);
}

template <class ValueType>
RadixTree<ValueType>::~RadixTree()
{
	destroy(m_head);
	m_head = nullptr;
}

template <class ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
	if (key == "") return;
	Node* curr = m_head;
	int index = 0;
	while (index < key.size())
	{
		char transition = key.at(index);
		std::string currStr = key.substr(index);
		if (curr->m_children[0] == nullptr) curr->m_children.pop_back();

		// Checks for the Node child that contains the transition letter if such exist
		Node* childNode = nullptr;
		typename std::vector<Node*>::iterator it = curr->m_children.begin();
		for (; it != curr->m_children.end(); it++)
		{
			if ((*it)->m_string.at(0) == transition)
			{
				childNode = (*it);
				break;
			}
		}

		// If there is no associated next node with the first char of curr string, then add the rest of string
		if (childNode == nullptr)
		{
			curr->m_children.push_back(new Node(currStr, value, true));
			curr->m_children[curr->m_children.size() - 1]->m_children.push_back(nullptr);
			return;
		}

		// If there is an associated next node, then get the index of missmatch
		int indexToSplit = getMismatchingIndex(currStr, childNode->m_string);
		if (indexToSplit == -1)
		{
			// if word-to-insert is within an already existing word
			if (currStr.size() < childNode->m_string.size())
			{
				std::string suffixStr = childNode->m_string.substr(currStr.size());
				curr->m_children.erase(it);
				childNode->m_string = suffixStr;
				Node* addedNode = new Node(currStr, value, true);
				curr->m_children.push_back(addedNode);
				addedNode->m_children.push_back(childNode);
				return;
			}

			// if they are the same word
			else if (currStr.size() == childNode->m_string.size())
			{
				childNode->m_value = value;
				childNode->m_isWord = true;
				return;
			}

			// if word-to-insert encompasses an already existing word
			else indexToSplit = childNode->m_string.size();
		}
		// Create Node split at point where characters differ
		else
		{
			if (childNode->m_children[0] == nullptr) childNode->m_children.pop_back();
			std::string suffixStr = childNode->m_string.substr(indexToSplit);
			childNode->m_string = childNode->m_string.substr(0, indexToSplit);
			childNode->m_isWord = false;
			childNode->m_children.push_back(new Node(suffixStr, childNode->m_value, true));
			childNode->m_children[childNode->m_children.size() - 1]->m_children.push_back(nullptr);
		}
		curr = childNode;
		index += indexToSplit;
	}
}

template <class ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	if (m_head == nullptr) return nullptr;
	Node* curr = m_head;
	int index = 0;

	// Goes through RadixTree
	while (index < key.size())
	{
		char transition = key.at(index);
		Node* childNode = nullptr;
		for (Node* child : curr->m_children)
		{
			if (child != nullptr && child->m_string.at(0) == transition)
				childNode = child;
		}

		// If no sequence matches key then return nullptr
		if (childNode == nullptr)
			return nullptr;

		std::string currStr = key.substr(index);
		if (currStr.find(childNode->m_string, 0) != 0)
			return nullptr;

		index += childNode->m_string.size();
		curr = childNode;
	}
	return curr->m_isWord == true ? &(curr->m_value) : nullptr;
}

#endif // !RADIX_TREE



