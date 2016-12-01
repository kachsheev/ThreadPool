#include "AbstractTest.hpp"

void AbstractTest::isValid(bool valid)
{
	using namespace	std;
	cout << "Valid: ";
	(valid)
		? cout << "true\n"
		: cout << "false\n";
	cout << '\n';

	cout.flush();
}
