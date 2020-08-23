#pragma once
#include "control.h"

namespace qui
{
	class optionselect;

	/// <summary>
	/// Control used in optionselect controls
	/// </summary>
	class option : public control
	{
	private:
		unsigned int m_index;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="index">Index of option in optionselect list</param>
		/// <param name="text">Text displayed on the option</param>
		option(std::string name, optionselect* parent, unsigned int index, std::string text = "");

		void draw() override;
		void handle_input(int key, int nav) override {};

		unsigned int index();
	};
}
