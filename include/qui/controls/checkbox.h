#pragma once
#include "control.h"

namespace qui
{
	class container;

	/// <summary>
	/// Control for getting a ON/OFF input
	/// </summary>
	class checkbox : public control
	{
	private:
		bool m_default_val;
		bool m_value;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="default_val">Default value of the checkbox</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		checkbox(std::string name, container* parent, std::string title = "", bool default_val = false, control* prev_displayed = nullptr);

		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		bool value();
		void set_value(bool val);

		std::function<void(checkbox*)> on_enter;
		std::function<void(checkbox*)> on_update;
	};
}
