#ifndef ATTRIBUTE_TRANSLATOR
#define ATTRIBUTE_TRANSLATOR

#include <string>
#include <vector>
#include <algorithm>
#include "RadixTree.h"
#include "provided.h"

class AttributeTranslator
{
public:
	AttributeTranslator() {};
	~AttributeTranslator() {};

	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<std::vector<AttValPair>> m_tree;

};
#endif // !ATTRIBUTE_TRANSLATOR