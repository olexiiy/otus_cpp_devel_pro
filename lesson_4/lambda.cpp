#include <iostream>


struct SomeStruct {

	auto make_me_lambda_0(std::string str_param, int int_param) {
		
		float pi = 3.1415;
		// Warning - here pi is a local variable
		// and it is captured by reference
		// do not do this!

		
		return [str = std::move(str_param), i = int_param, this, &pi](){
			std::cout << "Hello from lambda0!" << std::endl;
			std::cout << "Member = " << m_member << std::endl;
		};
	}

	auto make_me_lambda_1(std::string str_param, int int_param) {
		float pi = 3.1415;
		return [str = std::move(str_param), i = int_param, *this, pi](){
			std::cout << "Hello from lambda0!" << std::endl;
			std::cout << "Member = " << m_member << std::endl;
		};
	}

	int m_member = 42;
};





int main() {
	SomeStruct some;

	{
		std::string str_param = "Test";
		int int_param = 42;
		auto lambda0 = some.make_me_lambda_0(str_param, int_param);
		lambda0();
		some.m_member++;
		lambda0();
	}

	{
		std::string str_param = "Test";
		int int_param = 42;
		auto lambda1 = some.make_me_lambda_1(str_param, int_param);
		lambda1();
		some.m_member++;
		lambda1();
	}

	return 0;
}