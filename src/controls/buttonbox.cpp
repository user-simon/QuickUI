#include "pch.h"
#include "qui.h"
using namespace qui;

// temporary C++17 solution; C++20 should provide constexpr for normal std::strings
constexpr std::string_view BUTTON_TYPE_TITLES[] = { "OK", "Cancel", "Save", "Discard", "Yes", "No" };

buttonbox::buttonbox(std::string name, container_control* parent, unsigned int button_types, std::function<void(buttonbox*, button_type)> callback, std::string title)
	: control(name, parent, title)
{
	m_button_types = button_types;
	on_enter = callback;

	// create the buttons and store the button type in the generic data variable
	for (size_t i = 0; i < button_type::BUTTON_TYPE_COUNT; i++)
	{
		size_t type = 1 << i;

		if (type & button_types)
		{
			button* b = new button(name + std::to_string(i), this, std::string(BUTTON_TYPE_TITLES[i]));
			b->set_data((void*)type);
		}
	}
}

void buttonbox::call_on_enter()
{
	if (on_enter)
		on_enter(this, selected_button_type());
}

void buttonbox::call_on_update()
{
	if (on_update)
		on_update(this, selected_button_type());
}

void buttonbox::draw()
{
	draw_title();
	draw_indent();

	for (control* c : m_controls)
	{
		if (c->is_selected())
			std::cout << "[ " << c->title() << " ] ";
		else
			std::cout << "( " << c->title() << " ) ";
	}
}

void buttonbox::handle_input(int key, int nav)
{
	if (handle_nav(nav))
		call_on_update();
	else if (key == VK_RETURN)
		call_on_enter();
}

button_type buttonbox::selected_button_type()
{
	return (button_type)(unsigned int)selected_control()->data();
}
