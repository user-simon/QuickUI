#pragma once
#include <vector>
#include "control.h"

namespace qui
{
	/// <summary>
	/// Base class for controls that contain other controls
	/// </summary>
	class container_control : public virtual control
	{
	protected:
		std::vector<control*> m_controls;
		std::vector<control*>::iterator m_cursor;

	protected:
		bool handle_navigation(int nav);

	protected:
		container_control() {}

	public:
		/// <summary>
		/// Adds a control to container
		/// </summary>
		virtual void add(control* control);

		/// <summary>
		/// Removes control from container. Does not remove control from menu or free its memory
		/// </summary>
		virtual void remove(control* control);

		/// <summary>
		/// Removes control from container. Does not remove control from menu or free its memory
		/// </summary>
		/// <param name="name">Name of the control</param>
		void remove(std::string name);

		control* selected_control();
		std::vector<control*> controls();

		unsigned int selected_index();
	};
}
