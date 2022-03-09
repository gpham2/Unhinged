#include "MatchMaker.h"
#include <unordered_map>


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_data(&mdb), m_translator(&at) {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
	if (threshold < 1) threshold = 1;
	// find the person based on email
	PersonProfile person = *m_data->GetMemberByEmail(email);

	// get all attribute-value pairs associated with that person
	std::vector<AttValPair> attValList;
	for (int i = 0; i < person.GetNumAttValPairs(); i++)
	{
		AttValPair p;
		person.GetAttVal(i, p);
		attValList.push_back(p);
	}
	
	std::vector<AttValPair> compatibleSet;
	for (int i = 0; i < attValList.size(); i++)
	{
		std::vector<AttValPair> miniList = m_translator->FindCompatibleAttValPairs(attValList[i]);
		for (int i = 0; i < miniList.size(); i++)
		{
			if (std::find(compatibleSet.begin(), compatibleSet.end(), miniList[i]) == compatibleSet.end())
				compatibleSet.push_back(miniList[i]);
		}
	}
	


	std::unordered_map<std::string, int> partnerMap;
	// find collection of members that have each such compatible attribute-value pair
	for (AttValPair i : compatibleSet)
	{
		std::vector<std::string> matches = m_data->FindMatchingMembers(i);
		for (int i = 0; i < matches.size(); i++)
		{
			std::string m = matches[i];
			if (m == email) continue;
			if (partnerMap.find(m) == partnerMap.end()) partnerMap[m] = 1;
			else partnerMap[matches[i]]++;
		}
	}


	// iterate over map and reorder
	std::vector<EmailCount> res;

	for (auto it : partnerMap)
	{
		// turn into EmailCount format
		if (it.second < threshold) continue;
		res.push_back(EmailCount(it.first, it.second));
	}


	// sorting res vector

	sortMatches(res, 0, res.size() - 1);
	return res;
}


void MatchMaker::sortMatches(std::vector<EmailCount>& v, int low, int high) const
{

	if (low >= high)
		return;
	int p = partition(v, low, high);

	// Sorting the left part
	sortMatches(v, low, p - 1);

	// Sorting the right part
	sortMatches(v, p + 1, high);

}

void MatchMaker::swap(EmailCount& a, EmailCount& b) const
{
	EmailCount t(a.email, a.count);
	a.email = b.email;
	a.count = b.count;
	b.email = t.email;
	b.count = t.count;
}


int MatchMaker::partition(std::vector<EmailCount>& v, int low, int high) const
{
	EmailCount pivot = v[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot

		if (!aLessThanB(v[j], pivot))
		{
			i++; // increment index of smaller element
			swap(v[i], v[j]);
		}
	}
	swap(v[i + 1], v[high]);
	return (i + 1);
}



bool MatchMaker::aLessThanB(EmailCount& a, EmailCount& b) const
{
	if (a.count < b.count) return true;
	else if (a.count == b.count && a.email > b.email) return true;
	return false;
}