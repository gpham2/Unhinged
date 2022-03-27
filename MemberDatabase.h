#ifndef MEMBER_DATABASE
#define MEMBER_DATABASE

#include <string>
#include "RadixTree.h"
#include "provided.h"
#include "PersonProfile.h"


class MemberDatabase
{
public:
	MemberDatabase() {};
	~MemberDatabase() {};
	bool LoadDatabase(std::string filename);

	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;

private:
	RadixTree<PersonProfile*> m_tree;
	RadixTree<std::vector<std::string>> m_attValTree;
};



#endif // !MEMBER_DATABASE

