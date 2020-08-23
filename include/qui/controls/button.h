#pragma once
#include <functional>

#include "control.h"

namespace qui
{
	class container;

	/// <summary>
	/// Control which performs an action when it is selected and the user presses enter
	/// </summary>
	class button : public control
	{
	public:
		button(std::string name, container* parent, std::string text, control* prev_displayed = nullptr);

		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="text">Text shown on control</param>
		/// <param name="callback">Function to be called when the button is pressed</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		button(std::string name, container* parent, std::function<void(button*)> callback, std::string text, control* prev_displayed = nullptr);
		
		virtual void draw() override;
		virtual void handle_input(int key, int nav) override;

		std::function<void(button*)> on_enter;
	};
}
