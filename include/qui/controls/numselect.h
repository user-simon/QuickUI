#pragma once
#include "control.h"

namespace qui
{
	class container;

	/// <summary>
	/// Control for getting an integer input
	/// </summary>
	class numselect : public control
	{
	private:
		int m_default_val;
		int m_value;

	public:
		int m_min;
		int m_max;
		int m_step;

	private:
		void clamp_val();

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="min">Min value</param>
		/// <param name="max">Max value</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="default_val">Value that control is initialized with</param>
		/// <param name="step">Indicates the increment/decrement amount</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		numselect(std::string name, container* parent, int min, int max, std::string title = "", int default_val = 0, int step = 1, control* prev_displayed = nullptr);

		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		int value();
		void set_value(int val);

		int min();
		void set_min(int min);

		int max();
		void set_max(int max);

		int step();
		void set_step(int step);

		std::function<void(numselect*)> on_enter;
		std::function<void(numselect*)> on_update;
	};
}
