#include "pch.h"
#include "qui.h"
using namespace qui;

container::container(std::string name, container* parent, std::string title, control* prev_displayed)
	: control(name, parent, title, prev_displayed)
{

}

void container::add(control* c)
{
	m_controls.push_back(c);
	m_cursor = m_controls.begin();
}

void container::remove(control* c)
{
	std::vector<control*>::iterator it = std::find(m_controls.begin(), m_controls.end(), c);

	if (it != m_controls.end())
	{
		m_controls.erase(it);
		m_cursor = m_controls.begin();
	}
}

void container::remove(std::string name)
{
	if (control* c; c = menu::get(name))
		remove(c);
}

bool container::handle_nav(int nav)
{
	if (nav == ARROW_LEFT)
	{
		if (m_cursor != m_controls.begin())
			m_cursor--;
	}
	else if (nav == ARROW_RIGHT)
	{
		if (m_cursor != std::prev(m_controls.end()))
			m_cursor++;
	}
	else
	{
		return false;
	}
	return true;
}

control* container::selected_control()
{
	return *m_cursor;
}

std::vector<control*> container::controls()
{
	return m_controls;
}

unsigned int container::selected_index()
{
	return m_cursor - m_controls.begin();
}
