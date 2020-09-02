#include "pch.h"
#include "qui.h"
using namespace qui;

std::unordered_map<std::string, control*> menu::m_controls_lookup;
bool menu::m_exit;
control* menu::m_displayed;
std::vector<control*> menu::m_displayed_path;
std::string menu::m_indent;

void menu::init()
{
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// remove scrollbars
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console_handle, &csbi);
	SHORT console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	SHORT console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	SetConsoleScreenBufferSize(console_handle, {console_width, console_height});
	
	// calculate indent based on console width
	m_indent = std::string(console_width * 0.07f, ' ');

	// hide console cursor
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(console_handle, &info);
}

void menu::exec()
{
	m_exit = false;

	while (!m_exit)
	{
		if (m_displayed)
		{
			clear_screen();
			draw();
			handle_input();
		}
	}
}

void menu::stop()
{
	m_exit = true;
}

void menu::exit()
{
	stop();

	for (auto& [name, control] : m_controls_lookup)
		delete control;

	m_controls_lookup.clear();
	ExitProcess(0);
}

void menu::draw()
{
	std::cout << std::endl << std::endl << std::endl;
	m_displayed->draw();
}

void menu::handle_input()
{
	// _getch allows you to get keyboard input without printout in the console
	const int key = _getch();

	// if key press has a certain command key value, a second call to _getch will reveal which command key was pressed (such as arrow keys)
	const int nav = (key == NAV_KEY) ? _getch() : NULL;

	if (key == VK_ESCAPE)
	{
		goto_last_control();
	}
	else
	{
		m_displayed->handle_input(key, nav);
	}
}

void menu::clear_screen()
{
	// alternatives to this causes the menu to not draw while a key is held down
	// should refactor
	system("cls");
}

void menu::goto_last_control()
{
	if (m_displayed_path.size() > 1)
	{
		m_displayed = *(m_displayed_path.end() - 2);
		m_displayed_path.pop_back();
	}
}

void menu::set_displayed(control* c)
{
	m_displayed = c;
	m_displayed_path.push_back(c);
}

void menu::set_displayed(std::string name)
{
	if (control* c; c = get(name))
		set_displayed(c);
}

void menu::add(control* c)
{
	// if the menu has a control with the same name, replace it with the new one
	if (control_exists(c->name()))
		remove(c->name());

	m_controls_lookup.emplace(c->name(), c);
}

void menu::remove(control* c)
{
	m_controls_lookup.erase(c->name());
	c->parent()->remove(c);
	delete c;
}

void menu::remove(std::string name)
{
	if (control* c; c = get(name))
		remove(c);
}

control* menu::displayed_control()
{
	return m_displayed;
}

std::vector<control*> menu::controls()
{
	std::vector<control*> controls;

	for (auto& [name, control] : m_controls_lookup)
		controls.push_back(control);

	return controls;
}

bool menu::control_exists(std::string name)
{
	return m_controls_lookup.count(name);
}

std::string menu::indent()
{
	return m_indent;
}

control* menu::get(std::string name)
{
	if (control_exists(name))
		return m_controls_lookup[name];

	return nullptr;
}
