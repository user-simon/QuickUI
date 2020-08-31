#include "pch.h"
#include "qui.h"
using namespace qui;

control::control(std::string name, container_control* parent, std::string title, control* prev_displayed)
{
	m_name = name;
	m_parent = parent;
	m_title = title;
	m_prev_displayed = prev_displayed;

	// automatically add control to parent and menu when created
	menu::add(this);
	
	if (m_parent)
		m_parent->add(this);
}

void control::draw_indent()
{
	std::string indent = menu::indent;

	if (is_selected())
		indent[indent.length() * 0.75] = '|';

	std::cout << indent;
}

void control::draw_title()
{
	if (!m_title.empty())
		std::cout << menu::indent << m_title << std::endl;
}

void control::call_on_enter()
{
	if (on_enter)
		on_enter(this);
}

std::string control::name()
{
	return m_name;
}

container_control* control::parent()
{
	return m_parent;
}

std::string control::title()
{
	return m_title;
}

void control::set_title(std::string title)
{
	m_title = title;
}

control* control::prev_displayed()
{
	return m_prev_displayed;
}

void control::set_prev_displayed(control* prev_displayed)
{
	m_prev_displayed = prev_displayed;
}

void* control::data()
{
	return m_data;
}

void control::set_data(void* data)
{
	m_data = data;
}

bool control::is_selected()
{
	return this == m_parent->selected_control();
}
