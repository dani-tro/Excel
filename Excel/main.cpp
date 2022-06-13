#include <iostream>
#include <iomanip>


#include "RPN.h"
#include "String.h"
#include "Formula.h"

int main()
{
	/*
	
	RPN a{"3 4 2 * 1 5 - / 2 3 ^ ^ +"};
	String a{"1342.626"};
	std::cout << a.get_value().value() << std::endl;
	
	*/

	

	std::string a = "=+1+2+3+4";
	Cell* ptr = new Formula(a);
	std::cout << ptr -> get_value().value() << std::endl;
	ptr->println();
	return 0;
}

/*


3 + ( ( 4 * 2 ) / ( 1 - 5 ) ) ^ ( 2 ^ 3 )

3 4 2 * 1 5 - / 2 3 ^ ^ +    vqrnoto ot magito

3 4 2 * 1 5 - / 2 3 ^ ^ +

*/
