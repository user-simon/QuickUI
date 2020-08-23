#include "pch.h"
#include "qui.h"
using namespace qui;

multiselect::multiselect(std::string name, container* parent, std::vector<std::string> options, std::string title, control* prev_displayed) 
	: container(name, parent, title, prev_displayed)
{
	for (unsigned int i = 0; i < options.size(); i++)
		new checkbox(name + std::to_string(i), this, options[i]);
}

void multiselect::draw()
{
	draw_title();

	for (control* c : controls())
	{
		checkbox* option = (checkbox*)c;
		draw_indent();

		std::string prefix = "  ";

		if (is_selected() && option->is_selected())
			prefix += " ";
		
		if (option->value())
			prefix[0] = '~';
			
		std::cout << prefix << c->title() << std::endl;
	}
}

void multiselect::handle_input(int key, int nav)
{
	if (handle_nav(nav))
	{
		if (on_update)
			on_update(this);
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

void multiselect::reset()
{
	for (control* c : m_controls)
		c->reset();
}

void multiselect::set_options(std::vector<std::string> options)
{
	// remove previous options
	if (m_controls.size())
	{
		for (control* c : m_controls)
			delete c;

		m_controls.clear();
	}

	for (unsigned int i = 0; i < options.size(); i++)
		new checkbox(name() + std::to_string(i), this, options[i]);
}

std::vector<bool> multiselect::values()
{
	std::vector<bool> val;

	for (control* c : m_controls)
	{
		checkbox* cb = (checkbox*)c;
		val.push_back(cb->value());
	}
	return val;
}
