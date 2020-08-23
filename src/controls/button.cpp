#include "pch.h"
#include "qui.h"
using namespace qui;

button::button(std::string name, container* parent, std::string text, control* prev_displayed) :
	control(name, parent, text, prev_displayed)
{

}

button::button(std::string name, container* parent, std::function<void(button*)> callback, std::string text, control* prev_displayed) :
	button(name, parent, text, prev_displayed)
{
	on_enter = callback;
}

void button::draw()
{
	draw_indent();

	if (is_selected())
		std::cout <<  "[ " << title() << " ]";
	else	
		std::cout << "( " << title() << " )";
}

void button::handle_input(int key, int nav)
{
	if (key == VK_RETURN)
	{
		if (on_enter)
			on_enter(this);
	}
}
