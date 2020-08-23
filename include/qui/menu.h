#pragma once
#include <string>
#include <vector>
#include <unordered_map>

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
		/// Stops drawing and listening for input
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
		/// Gets pointer to control from its name
		/// </summary>
		static control* get(std::string name);

		/// <summary>
		/// Gets pointer to control from its name and casts it to expected control type. In C++20, should add constraint of T having to inherit from control
		/// </summary>
		template<typename T>
		static T* get_as(std::string name);
	};

	// templated function definitions

	template<typename T>
	static T* menu::get_as(std::string name)
	{
		return (T*)get(name);
	}
}
