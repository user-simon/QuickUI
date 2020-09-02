#include "pch.h"
#include "qui.h"
using namespace qui;

multiselect::multiselect(std::string name, container_control* parent, std::string title, std::vector<std::string> options, std::vector<bool> default_value)
	: control(name, parent, title), input_control(default_value)
{
	for (unsigned int i = 0; i < options.size(); i++)
		new checkbox(name + std::to_string(i), this, options[i]);
}

void multiselect::draw()
{
	draw_title();

	for (control* c : controls())
	{
		checkbox* option = dynamic_cast<checkbox*>(c);
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
	if (handle_navigation(nav))
		call_on_update();
	else if (key == VK_RETURN && on_enter)
		call_on_enter();
	else
		selected_control()->handle_input(key, nav);
}

void multiselect::reset()
{
	for (control* c : m_controls)
		c->reset();
}

std::vector<bool> multiselect::value()
{
	std::vector<bool> val;

	for (control* c : m_controls)
	{
		checkbox* cb = dynamic_cast<checkbox*>(c);
		val.push_back(cb->value());
	}
	return val;
}
