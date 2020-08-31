#pragma once
#include "container_control.h"

namespace qui
{
	class option;

	/// <summary>
	/// Control for getting a choice between different options
	/// </summary>
	class optionselect : public container_control, public input_control<option*>
	{
	private:
		// hide set_value function as selected option has to be set using index
		void set_value(option*) override {}

		void add_option(std::string name, unsigned int index, std::string text, void* data = nullptr);

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Option names</param>
		/// <param name="title">Text shown above control</param>
		optionselect(std::string name, container_control* parent, std::vector<std::string> options, std::string title = "");

		/// <summary>
		/// Alternate constructor for having data associated with each option
		/// </summary>
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="options">Option names and pointers to associated data</param>
		/// <param name="title">Text shown above control</param>
		optionselect(std::string name, container_control* parent, std::vector<std::pair<std::string, void*>> options, std::string title = "");

		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown above control</param>
		optionselect(std::string name, container_control* parent, std::string title = "");

		unsigned int index();
		void set_index(unsigned int index);

		// control methods

		void draw() override;
		void handle_input(int key, int nav) override;

		// input_control methods

		option* value() override;
		void reset() override;
	};
}
