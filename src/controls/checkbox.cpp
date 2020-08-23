#include "pch.h"
#include "qui.h"
using namespace qui;

checkbox::checkbox(std::string name, container* parent, std::string title, bool default_val, control* prev_displayed)
	: control(name, parent, title, prev_displayed)
{
	m_default_val = default_val;
	m_value = default_val;
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
		if (on_enter)
			on_enter(this);

		m_value = !m_value;
	}
	else
	{
		return;
	}

	if (on_update)
		on_update(this);
}

void checkbox::reset()
{
	m_value = m_default_val;
}

bool checkbox::value()
{
	return m_value;
}

void checkbox::set_value(bool val)
{
	m_value = val;
}
