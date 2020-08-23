#pragma once
#include "container.h"

namespace qui
{
	class option;

	/// <summary>
	/// Control for getting a choice between different options
	/// </summary>
	class optionselect : public container
	{
	private:
		void add_option(std::string name, unsigned int index, std::string text, void* data = nullptr);

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Option names</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="prev_displayed">Only sete when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		optionselect(std::string name, container* parent, std::vector<std::string> options, std::string title = "", control* prev_displayed = nullptr);

		/// <summary>
		/// Alternate constructor for having data associated with each option
		/// </summary>
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Option names and pointers to associated data</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="prev_displayed">Only sete when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		optionselect(std::string name, container* parent, std::vector<std::pair<std::string, void*>> options, std::string title = "", control* prev_displayed = nullptr);

		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		std::function<void(optionselect*, option*)> on_enter;
		std::function<void(optionselect*, option*)> on_update;
	};
}
