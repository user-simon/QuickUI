#pragma once
#include "input_control.h"

namespace qui
{
	class container_control;

	/// <summary>
	/// Control for getting a ON/OFF input
	/// </summary>
	class checkbox : public input_control<bool>
	{
	private:
		bool m_default_val;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="default_val">Default value of the checkbox</param>
		checkbox(std::string name, container_control* parent, std::string title, bool default_value = false);

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
	};
}
