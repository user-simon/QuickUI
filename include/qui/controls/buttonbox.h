#pragma once
#include "container.h"

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
	class buttonbox : public container
	{
	private:
		unsigned int m_button_types;
		
	private:
		button_type selected_button_type();

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="button_types">Buttons to be displayed. Follows format "BUTTON_x | BUTTON_y"</param>
		/// <param name="callback">Function to be called when one of the buttons is pressed</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		buttonbox(std::string name, container* parent, unsigned int  button_types, std::function<void(buttonbox*, button_type)> callback, std::string title = "", control* prev_displayed = nullptr);

		void draw() override;
		void handle_input(int key, int nav) override;

		std::function<void(buttonbox*, button_type)> on_enter;
		std::function<void(buttonbox*, button_type)> on_update;
	};
}
