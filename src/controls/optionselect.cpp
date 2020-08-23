#include "pch.h"
#include "qui.h"
using namespace qui;

optionselect::optionselect(std::string name, container* parent, std::vector<std::string> options, std::string title, control* prev_displayed)
	: container(name, parent, title, prev_displayed)
{
	for (unsigned int i = 0; i < options.size(); i++)
		add_option(name + std::to_string(i), i, options[i]);
}

optionselect::optionselect(std::string name, container* parent, std::vector<std::pair<std::string, void*>> options, std::string title, control* prev_displayed)
	: container(name, parent, title, prev_displayed)
{
	for (unsigned int i = 0; i < options.size(); i++)
		add_option(name + std::to_string(i), i, options[i].first, options[i].second);
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
	{
		if (on_update)
			on_enter(this, (option*)selected_control());
	}
	else if (key == VK_RETURN)
	{
		if (on_enter)
			on_enter(this, (option*)selected_control());
	}
}

void optionselect::reset()
{
	m_cursor = m_controls.begin();
}

void optionselect::add_option(std::string name, unsigned int index, std::string text, void* data)
{
	option* o = new option(name, this, index, text);
	o->set_data(data);
}
