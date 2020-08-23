#pragma once
#include "container.h"

namespace qui
{
	/// <summary>
	/// Control for getting multiple ON/OFF inputs
	/// </summary>
	class multiselect : public container
	{
	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Titles of the options to be displayed in the control</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		multiselect(std::string name, container* parent, std::vector<std::string> options, std::string title = "", control* prev_displayed = nullptr);

		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		void set_options(std::vector<std::string> options);

		std::vector<bool> values();

		std::function<void(multiselect*)> on_enter;
		std::function<void(multiselect*)> on_update;
	};
}
