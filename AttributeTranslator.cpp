#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream infile(filename);
	if (!infile) return false;
	std::string line;
	while (getline(infile, line))
	{
		// checking if it is empty line
		istringstream iss(line);
		string srcAttr;
		if (!getline(iss, srcAttr, ',')) continue;
		string srcVal;
		string compAttr;
		string compVal;
		getline(iss, srcVal, ',');
		getline(iss, compAttr, ',');
		getline(iss, compVal);

		// inserting into radix tree
		string key = srcAttr + "," + srcVal;
		AttValPair pair(compAttr, compVal);
		std::vector<AttValPair>* vecPtr = m_tree.search(key);
		if (vecPtr == nullptr) m_tree.insert(key, std::vector<AttValPair> {pair});
		else if (std::find(vecPtr->begin(), vecPtr->end(), pair) == vecPtr->end()) vecPtr->push_back(pair);
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair>* v = m_tree.search(source.attribute + "," + source.value);
	if (v == nullptr) return vector<AttValPair>();
	return *v;
}