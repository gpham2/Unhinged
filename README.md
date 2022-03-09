# Unhinged
A Project From UCLA's CS32 class. All code were written by me except for Provided.h and main.cpp. The text files "members.txt" and "translator.txt" were given by the instructors (to self-test our project). How the project works:
  1. Given a text file of member profiles (members.text), the code can find all compatible partners (above a given integer threshold) for an individual
  2. Compatibility is determined by how similar each profile's attributes are.
  3. For example, if person A's attribute is "Hobby: Walking" and person B's attribute is "Trait: Active", then those two receive a point of compatibility.
  4. This attribute mapping can be done in "translator.txt".
  5. Code is implemented using a RadixTree data structure (which is like a super optimized trie).
  6. Supports up to 100k profile members and optimized to run fast.
