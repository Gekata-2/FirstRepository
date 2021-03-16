#include <iostream>
#include "MainConstantsEnum.h"
#include "AtomicTextLink.h"
int main()
{
	char string_1[20];
	TAtomicTextLink test_text;
	test_text.InitializationMemorySystem();
	test_text.PrintFreeLink();
	std::cout << "Hello World!\n";
}
