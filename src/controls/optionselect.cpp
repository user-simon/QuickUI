#include "pch.h"
#include "qui.h"
using namespace qui;

optionselect::optionselect(std::string name, container_control* parent, std::vector<std::string> options, std::string title)
	: control(name, parent, title)
{
	for (unsigned int i = 0; i < options.size(); i++)
		add_option(name + std::to_string(i), i, options[i]);
}

optionselect::optionselect(std::string name, container_control* parent, std::vector<std::pair<std::string, void*>> options, std::string title)
	: control(name, parent, title)
{
	for (unsigned int i = 0; i < options.size(); i++)
		add_option(name + std::to_string(i), i, options[i].first, options[i].second);
}

optionselect::optionselect(std::string name, container_control* parent, std::string title)
	: control(name, parent, title)
{
	
}

void optionselect::add_option(std::string name, unsigned int index, std::string text, void* data)
{
	option* o = new option(name, this, index, text);
	o->set_data(data);
}

unsigned int optionselect::index()
{
	return value()->index();
}

void optionselect::set_index(unsigned int index)
{
	if (index < m_controls.size())
		m_cursor = m_controls.begin() + index;
}

void optionselect::draw()
{
	draw_title();

	control* last_control = *std::prev(m_controls.end());

	for (control* c : m_controls)
	{
		draw_indent();
		c->draw();

		if (c != last_control)
			std::cout << std::endl;
	}
}

void optionselect::handle_input(int key, int nav)
{
	if (handle_nav(nav))
		call_on_update();
	else if (key == VK_RETURN)
		call_on_enter();
}

option* optionselect::value()
{
	return (option*)*m_cursor;
}

void optionselect::reset()
{
	set_index(0);
}
