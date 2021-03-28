#include <iostream>
#include "MainConstantsEnum.h"
#include "AtomicTextLink.h"
#include "Text.h"
int main()
{
	TextString test_string;
	test_string[0] = 'M';
	TAtomicTextLink Atom(test_string, NULL, NULL);
	PTAtomicTextLink p_test_text= &Atom;
	p_test_text->InitializationMemorySystem();
	p_test_text->PrintFreeLink();
	
	TText Text(p_test_text);

	std::cout<<Text.GoFirstLink()<<" "<<Text.GoDownLink()<<" "<<Text.GoPrevLink()<<std::endl;
	//delete p_test_text;
	Text.GoFirstLink();
	std::cout << "Hello World!\n";
}




