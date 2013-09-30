/* Height tests */
//#include "./tests/height.h"

/* Unit tests */
#include "./tests/unit.h"

/* Speed tests */
#include "./tests/speed.h"

/* Extra tests */
#include "./tests/extra.h"


int main() {
	//unit();
	//speed();
	//extra();

	rbmap<char, int> m;
	m['z'] = 1;
	m.erase('z');
	std::string a = "abracadabra";
	for (int i = 0; i < a.size(); i++) {
		m[a.at(i)]++;
	}
	for (rbmap<char, int>::iterator it = m.begin(); it != m.end(); it++) {
		std::cout << (*it).first << " -> " << (*it).second << std::endl;
	}

	std::cout << std::endl;

	rbmultimap<char, int> mm;
	for (int i = 0; i < a.size(); i++) {
		mm.insert(std::pair<char, int>(a.at(i), i));
	}
	for (rbmultimap<char, int>::iterator mit = mm.begin(); mit != mm.end(); mit++) {
		std::cout << (*mit).first << " -> " << (*mit).second << std::endl;
	}

	return 0;
}