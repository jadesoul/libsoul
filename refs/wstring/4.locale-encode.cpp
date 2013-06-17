#include <iostream>
#include <locale>
#include <exception>
#include <stdexcept>
using namespace std;

int main(int argc, char** argv) {
	try {
		locale l(argv[1]);
		cout << "Set locale to " << l.name() << " works" << endl;
		cout.imbue(l);
	} catch (std::runtime_error& e) {
		cout << argv[1] << " : " << e.what() << endl;
	}
}


