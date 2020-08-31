#include "pch.h"
#include "qui.h"
using namespace qui;

option::option(std::string name, optionselect* parent, unsigned int index, std::string text)
	: control(name, parent, text, nullptr)
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
