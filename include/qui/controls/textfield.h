#pragma once
#include "control.h"

namespace qui
{
	/// <summary>
	/// Control for getting text input. Password input also supported through the hide flag
	/// </summary>
	class textfield : public control
	{
	private:
		std::string m_value;
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
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		textfield(std::string name, container* parent, std::string title = "", bool hide = false, control* prev_displayed = nullptr);
		
		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		std::string value();
		void set_value(std::string value);

		bool hidden();
		void set_hidden(bool hide_chars);

		std::function<void(textfield*)> on_enter;
		std::function<void(textfield*)> on_update;
	};
}
