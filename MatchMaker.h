#ifndef MATCH_MAKER
#define MATCH_MAKER

#include "MemberDatabase.h"
#include "AttributeTranslator.h"


class MatchMaker
{
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker() {};

	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;

private:
	const MemberDatabase* m_data;
	const AttributeTranslator* m_translator;

	void sortMatches(std::vector<EmailCount>& v, int start, int end) const;
	void swap(EmailCount& a, EmailCount& b) const;
	int partition(std::vector<EmailCount>& v, int start, int end) const;
	bool aLessThanB(EmailCount& a, EmailCount& b) const;

};



#endif // !MATCH_MAKER

