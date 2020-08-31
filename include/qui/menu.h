#pragma once
#include <vector>
#include <unordered_map>
#include "input_control.h"

namespace qui
{
	class control;

	enum nav_keys
	{
		NAV_KEY		= 0xE0,
		ARROW_UP	= 0x48,
		ARROW_LEFT	= 0x4B,
		ARROW_RIGHT = 0x4D,
		ARROW_DOWN	= 0x50
	};

	/// <summary>
	/// QUI foundation class
	/// </summary>
	class menu
	{
	private:
		static std::unordered_map<std::string, control*> m_controls_lookup;
		static bool m_exit;
		static control* m_displayed;

	public:
		static std::string indent;

	private:
		static void draw();
		static void handle_input();
		static void clear_screen();

	public:
		/// <summary>
		/// Initializes the menu
		/// </summary>
		static void init();

		/// <summary>
		/// Draws the menu and starts listening for input
		/// </summary>
		static void exec();

		/// <summary>
		/// Stops drawing and listening for input. Restart by calling exec
		/// </summary>
		static void stop();

		/// <summary>
		/// Closes the console and removes controls
		/// </summary>
		static void exit();

		/// <summary>
		/// Set which control is displayed in the menu
		/// </summary>
		static void set_displayed(control*);

		/// <summary>
		/// Gets the control currently displayed in the menu
		/// </summary>
		static control* displayed_control();

		/// <summary>
		/// Set which control is displayed in the menu
		/// </summary>
		/// <param name="name">Name of the control</param>
		static void set_displayed(std::string name);

		/// <summary>
		/// Adds a control to the menu. Only meant to be used internally
		/// </summary>
		static void add(control*);

		/// <summary>
		/// Removes control from the menu and frees its memory
		/// </summary>
		static void remove(control*);

		/// <summary>
		/// Removes control from the menu
		/// </summary>
		/// <param name="name">Name of the control</param>
		static void remove(std::string name);

		/// <summary>
		/// Gets all created controls in the menu
		/// </summary>
		static std::vector<control*> controls();

		/// <summary>
		/// Checks if control exists in menu
		/// </summary>
		/// <param name="name">Name of the control</param>
		static bool control_exists(std::string name);

		/// <summary>
		/// Gets pointer to control from its name
		/// </summary>
		static control* get(std::string name);

		/// <summary>
		/// Gets pointer to control from its name and casts it to expected control type. In C++20, should add constraint of T having to inherit from control
		/// </summary>
		template<typename control_t>
		static control_t* get_as(std::string name);

		template<typename value_t>
		static value_t get_value(std::string name);
	};

	// templated function definitions

	template<typename control_t>
	static control_t* menu::get_as(std::string name)
	{
		return dynamic_cast<control_t*>(get(name));
	}

	template<typename value_t>
	static value_t menu::get_value(std::string name)
	{
		input_control<value_t>* c = get_as<input_control<value_t>>(name);
		return c->value();
	}
}
