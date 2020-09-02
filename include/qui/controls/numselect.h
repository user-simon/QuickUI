#pragma once
#include "input_control.h"

namespace qui
{
	class container_control;

	/// <summary>
	/// Control for getting an integer input
	/// </summary>
	class numselect : public input_control<int>
	{
	private:
		int m_min;
		int m_max;
		int m_step;

	private:
		void clamp_value();

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="min">Min value</param>
		/// <param name="max">Max value</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="default_val">Value that control is initialized with</param>
		/// <param name="step">Indicates the increment/decrement amount</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		numselect(std::string name, container_control* parent, std::string title, int min, int max, int default_val = 0, int step = 1);

		int min();
		void set_min(int min);

		int max();
		void set_max(int max);

		int step();
		void set_step(int step);

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
		
		// input_control overrides
		
		void set_value(int value) override;
	};
}
