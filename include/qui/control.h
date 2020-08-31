#pragma once
#include <string>
#include <functional>

namespace qui
{
	class container_control;

	/// <summary>
	/// Generic base class for all controls
	/// </summary>
	class control
	{
	private:
		std::string m_name;
		container_control* m_parent;
		void* m_data;
		control* m_prev_displayed;
		std::string m_title;

	protected:
		control() {}

		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		control(std::string name, container_control* parent, std::string title, control* prev_displayed = nullptr);
		
		virtual void draw_indent();
		virtual void draw_title();

		virtual void call_on_enter();

	public:
		/// <summary>
		/// Draws the control. Only meant to be used internally
		/// </summary>
		virtual void draw() {};

		/// <summary>
		/// Processes a key input. Only meant to be used internally
		/// </summary>
		virtual void handle_input(int key, int nav) {};

		/// <summary>
		/// Resets the control to its initial state
		/// </summary>
		virtual void reset() {};

		std::string name();
		container_control* parent();

		std::string title();
		void set_title(std::string title);

		control* prev_displayed();
		void set_prev_displayed(control* prev_displayed);

		void* data();
		void set_data(void* data);

		bool is_selected();

		std::function<void(control*)> on_enter;
	};
}
