#include "pch.h"
#include "qui.h"
using namespace qui;

button::button(std::string name, container_control* parent, std::function<void(control*)> callback, std::string text) :
	control(name, parent, text)
{
	on_enter = callback;
}

button::button(std::string name, container_control* parent, std::string text) :
	control(name, parent, text)
{
	
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
		call_on_enter();
	}
}
