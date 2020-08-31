#pragma once
#include "input_control.h"

namespace qui
{
	/// <summary>
	/// Control for getting text input. Password input also supported through the hide flag
	/// </summary>
	class textfield : public input_control<std::string>
	{
	private:
		std::string::iterator m_cursor;
		bool m_hide;

	private:
		/// <summary>
		/// Finds the first space positioned before the cursor in the value string
		/// </summary>
		std::string::iterator find_space();

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="hide_chars">Toggle to only print asterisks</param>
		textfield(std::string name, container_control* parent, std::string title = "", bool hide = false, std::string default_value = "");
		
		bool hidden();
		void set_hidden(bool hide_chars);

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
		
		// input_control overrides

		void set_value(std::string value) override;
	};
}
