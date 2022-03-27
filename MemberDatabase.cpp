#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>


bool MemberDatabase::LoadDatabase(std::string filename)
{
	std::ifstream infile(filename);
	if (!infile) return false;
	std::string name;
	while (getline(infile, name))
	{
		// collects name, email, and attVal count
		std::string email;
		std::string count;;
		getline(infile, email);
		if (m_tree.search(email) != nullptr) return false;
		getline(infile, count);

		// input attVals in for PersonProfile object
		int pairsLeft = stoi(count);
		PersonProfile* p = new PersonProfile(name, email);
		std::string att;
		std::string val;
		for (int i = 0; i < pairsLeft; i++)
		{
			std::string line;
			getline(infile, line);
			std::istringstream iss(line);
			getline(iss, att, ',');
			getline(iss, val);
			p->AddAttValPair(AttValPair(att, val));


			// mapping attVal pair to emails
			std::string key = att + "," + val;
			std::vector<std::string>* vecPtr = m_attValTree.search(key);
			if (vecPtr == nullptr) m_attValTree.insert(key, std::vector<std::string>{email});
			else vecPtr->push_back(email);

		}
		m_tree.insert(email, p);
		getline(infile, name);
	}
	return true;
}


const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	PersonProfile** p = m_tree.search(email);
	if (p == nullptr) return nullptr;
	return const_cast<PersonProfile*> (*p);
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::vector<std::string>* vecPtr = m_attValTree.search(input.attribute + "," + input.value);
	if (vecPtr == nullptr) return std::vector<std::string>();
	return *vecPtr;
}