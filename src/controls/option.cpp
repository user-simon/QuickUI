#include "pch.h"
#include "qui.h"
using namespace qui;

option::option(std::string name, optionselect* parent, std::string text, unsigned int index)
	: control(name, parent, text)
{
	m_index = index;
}

unsigned int option::index()
{
	return m_index;
}

void option::draw()
{
	if (is_selected())
		std::cout << "* " << title();
	else	
		std::cout << "  " << title();
}
