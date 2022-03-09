#ifndef ATTRIBUTE_TRANSLATOR
#define ATTRIBUTE_TRANSLATOR

#include <string>
#include <vector>
#include <unordered_set>
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

	// DELETE
	void printRadix()
	{
		for (auto& i : m_tree.print())
		{
			std::cout << "Source: " << i.first << std::endl;
			std::cout << "Compatible: " << std::endl;
			for (int j = 0; j < i.second.size(); j++)
			{
				std::cout << i.second[j].attribute << "->" << i.second[j].value << std::endl;
			}
			std::cout << "\n";
		}
	}




private:
	RadixTree<std::vector<AttValPair>> m_tree;


};
#endif // !ATTRIBUTE_TRANSLATOR