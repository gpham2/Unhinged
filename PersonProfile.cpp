#include "PersonProfile.h"
#include <string>

PersonProfile::PersonProfile(std::string name, std::string email)
	: m_name(name), m_email(email), m_numPairs(0) {}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const { return m_name; }
std::string PersonProfile::GetEmail() const { return m_email; }
int PersonProfile::GetNumAttValPairs() const { return m_numPairs; }

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	std::string s = attval.attribute + "," + attval.value;
	if (m_tree.search(s) == nullptr) { m_vector.push_back(attval); m_numPairs++; }
	m_tree.insert(s, true);
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) return false;
	attval.attribute = m_vector[attribute_num].attribute;
	attval.value = m_vector[attribute_num].value;
	return true;
}


