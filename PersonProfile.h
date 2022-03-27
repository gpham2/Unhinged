#ifndef PERSON_PROFILE
#define PERSON_PROFILE

#include <string>
#include "RadixTree.h"
#include "provided.h"

class PersonProfile
{
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();

	// accessors
	std::string GetName() const;
	std::string GetEmail() const;
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;

	// mutators
	void AddAttValPair(const AttValPair& attval);

private:
	std::string m_name;
	std::string m_email;
	int m_numPairs;
	RadixTree<bool> m_tree;
	std::vector<AttValPair> m_vector;
};


#endif //  !PERSON_PROFILE

