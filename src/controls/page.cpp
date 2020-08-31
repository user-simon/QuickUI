#include "pch.h"
#include "qui.h"
using namespace qui;

page::page(std::string name, std::string title, control* prev_displayed) :
	control(name, nullptr, title, prev_displayed)
{	

}

void page::draw_title()
{
	if (!title().empty())
	{
		std::cout << menu::indent << title() << std::endl;
		std::cout << menu::indent << std::string(title().length(), '-');
	}
}

void page::draw()
{
	draw_title();

	for (control* c : m_controls)
	{
		std::cout << std::endl << std::endl;
		c->draw();
	}
}

void page::handle_input(int key, int nav)
{
	if (nav == ARROW_UP)
	{
		if (m_cursor != m_controls.begin())
			m_cursor--;
	}
	else if (nav == ARROW_DOWN || key == VK_TAB)
	{
		if (m_cursor != std::prev(m_controls.end()))
			m_cursor++;
	}
	else if (key == VK_RETURN && on_enter)
	{
		on_enter(this);
	}
	else
	{
		selected_control()->handle_input(key, nav);
	}
}

void page::reset()
{
	for (control* c : m_controls)
		c->reset();

	m_cursor = m_controls.begin();
}
