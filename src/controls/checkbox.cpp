#include "pch.h"
#include "qui.h"
using namespace qui;

checkbox::checkbox(std::string name, container_control* parent, std::string title, bool default_value)
	: control(name, parent, title), input_control(default_value)
{
	
}

void checkbox::draw()
{
	draw_indent();
	std::cout << (m_value ? "[ON]" : "[OFF]") << " " << title();
}

void checkbox::handle_input(int key, int nav)
{
	if (key == VK_RETURN || key == VK_SPACE || nav == ARROW_LEFT || nav == ARROW_RIGHT)
	{
		m_value = !m_value;

		call_on_update();

		if (key == VK_RETURN)
			call_on_enter();
	}
}
