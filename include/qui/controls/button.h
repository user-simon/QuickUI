#pragma once
#include "control.h"

namespace qui
{
	class container_control;

	/// <summary>
	/// Control which performs an action when it is selected and the user presses enter
	/// </summary>
	class button : public control
	{
	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="text">Text shown on control</param>
		button(std::string name, container_control* parent, std::string text);

		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="callback">Function to be called when the button is pressed</param>
		/// <param name="text">Text shown on control</param>
		button(std::string name, container_control* parent, std::string text, std::function<void(control*)> callback);
		
		// control overrides

		virtual void draw() override;
		virtual void handle_input(int key, int nav) override;
	};
}
