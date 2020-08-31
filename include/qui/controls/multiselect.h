#pragma once
#include "container_control.h"
#include "input_control.h"

namespace qui
{
	/// <summary>
	/// Control for getting multiple ON/OFF inputs
	/// </summary>
	class multiselect : public container_control, public input_control<std::vector<bool>>
	{
	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Titles of the options to be displayed in the control</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		multiselect(std::string name, container_control* parent, std::vector<std::string> options, std::string title = "", std::vector<bool> default_value = {});
		
		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
		
		// input_control overrides
		
		void reset() override;
		std::vector<bool> value() override;
	};
}
