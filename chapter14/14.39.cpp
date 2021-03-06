/*
 * Exercise 14.39: Revise the previous program to report the count of words
 * that are sizes 1 through 9 and 10 or more.
 *
 * By Faisal Saadatmand
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// -1 is the biggest value for size_t
class StringLength {
	public:
		StringLength(std::size_t l, std::size_t u = -1) : lower(l), upper(u) {}
		bool operator()(const std::string &s) const
			{ return s.length() >= lower && s.length() <= upper; }
	private:
		std::size_t lower;
		std::size_t upper;
};

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Usage: " << *argv << " inputFile\n";
		return -1;
	}
	std::ifstream infile(*++argv);
	if (!infile) {
		std::cerr << "Could't open " << *argv << '\n';
		return -1;
	}
	std::vector<std::string> words;
	std::string word;
	std::size_t lower = 1, upper = 9;
	while (infile >> word)
		words.push_back(word);
	auto wc = std::count_if(words.cbegin(), words.cend(),
				StringLength(lower, upper));
	std::cout << wc << ((wc > 1) ? " words are " : " word is ")
		      << "within the bound " << lower << " and " << upper << '\n';
	lower = 10;    // reset limit
	auto wc2 = std::count_if(words.cbegin(), words.cend(),
				StringLength(lower));
	std::cout << wc2 << ((wc2 > 1) ? " words are " : " word is ")
		      << "of size " << lower << " or more\n";
	return 0;
}
