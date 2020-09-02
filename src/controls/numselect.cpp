#include "pch.h"
#include "qui.h"
using namespace qui;

numselect::numselect(std::string name, container_control* parent, std::string title, int min, int max, int default_value, int step)
	: control(name, parent, title), input_control(default_value)
{
	m_min = min;
	m_max = max;
	m_step = step;
}

void numselect::clamp_value()
{
	m_value = std::clamp(m_value, m_min, m_max);
}

int numselect::min()
{
	return m_min;
}

void numselect::set_min(int min)
{
	m_min = std::min(min, m_max);
	clamp_value();
}

int numselect::max()
{
	return m_max;
}

void numselect::set_max(int max)
{
	m_max = std::max(max, m_min);
	clamp_value();
}

int numselect::step()
{
	return m_step;
}

void numselect::set_step(int step)
{
	m_step = step;
}

void numselect::draw()
{
	draw_title();
	draw_indent();

	std::cout << "< " << m_value << " >";
}

void numselect::handle_input(int key, int nav)
{
	if (nav)
	{
		if (nav == ARROW_LEFT)
			m_value -= m_step;
		else if (nav == ARROW_RIGHT)
			m_value += m_step;

		clamp_value();
	}
}

void numselect::set_value(int val)
{
	m_value = val;
	clamp_value();
}
