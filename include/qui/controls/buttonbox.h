#pragma once
#include "container_control.h"

namespace qui
{
	enum button_type : unsigned int
	{
		BUTTON_OK		  = 1 << 0,
		BUTTON_CANCEL	  = 1 << 1,
		BUTTON_SAVE		  = 1 << 2,
		BUTTON_DISCARD	  = 1 << 3,
		BUTTON_YES		  = 1 << 4,
		BUTTON_NO		  = 1 << 5,
		BUTTON_TYPE_COUNT = 6
	};

	/// <summary>
	/// Control for showing standard buttons such as "OK" or "CANCEL"
	/// </summary>
	class buttonbox : public container_control
	{
	private:
		unsigned int m_button_types;
		
	private:
		button_type selected_button_type();

		void call_on_enter() override;
		void call_on_update();

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="button_types">Buttons to be displayed. Enter like "BUTTON_x | BUTTON_y"</param>
		/// <param name="callback">Function to be called when one of the buttons is pressed</param>
		/// <param name="title">Text shown above control</param>
		buttonbox(std::string name, container_control* parent, std::string title, unsigned int button_types, std::function<void(buttonbox*, button_type)> callback);

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;

		std::function<void(buttonbox*, button_type)> on_enter;
		std::function<void(buttonbox*, button_type)> on_update;
	};
}
