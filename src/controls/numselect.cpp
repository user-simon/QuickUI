#include "pch.h"
#include "qui.h"
using namespace qui;

numselect::numselect(std::string name, container* parent, int min, int max, std::string title, int default_val, int step, control* prev_displayed) : control(name, parent, title, prev_displayed)
{
	m_min = min;
	m_max = max;
	m_default_val = default_val;
	m_step = step;
	m_value = default_val;

	clamp_val();
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

		clamp_val();
	}
}

void numselect::reset()
{
	m_value = m_default_val;
}

void numselect::clamp_val()
{
	m_value = std::clamp(m_value, m_min, m_max);
}

int numselect::value()
{
	return m_value;
}

void numselect::set_value(int val)
{
	m_value = val;
	clamp_val();
}

int numselect::min()
{
	return m_min;
}

void numselect::set_min(int min)
{
	m_min = std::min(min, m_max);
}

int numselect::max()
{
	return m_max;
}

void numselect::set_max(int max)
{
	m_max = std::max(max, m_min);
}

int numselect::step()
{
	return m_step;
}

void numselect::set_step(int step)
{
	m_step = step;
}