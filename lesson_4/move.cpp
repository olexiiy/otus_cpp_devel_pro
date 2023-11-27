#include <iostream>
#include <string>

void example1() {
	std::cout << "\nexample1" << std::endl;

	std::string name{"Vasia"};

	std::move(name);

	std::cout << name << std::endl; // ?
}

void example2() {
	std::cout << "\nexample2" << std::endl;

	std::string name{"Vasia"};

	std::string str = std::move(name);

	std::cout << name << std::endl; // ?
}

void example3() {
	std::string str; // std::string::string() - default ctor call

	// str = "Hello" + ", World" + "!";
	// Compile time error - there is no operator+ for const char *

	str = std::string{"Hello"} + ", World" + "!"; // Good now

	// Possible implementation
	{
		std::string temp_hello = std::string{"Hello"};
		std::string temp_world = std::string{", World"};
		std::string temp_excl = std::string{"!"};

		std::string temp1 = temp_hello + temp_world; // copy or move?
		std::string temp2 = temp1 + temp_excl; // copy or move?

		str = temp2; // copy or move?
	}
}

int main(int, char *[]) {

	example1();

	example2();

	example3();

	return 0;
}