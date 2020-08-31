#pragma once
#include "control.h"

namespace qui
{
	template<typename T>
	class input_control : public virtual control
	{
	private:
		T m_default_value;

	protected:
		T m_value;

	protected:
		input_control() {}

		input_control(T default_value)
		{
			m_default_value = default_value;
			set_value(default_value);
		}

		void call_on_enter() override
		{
			if (on_enter)
				on_enter(this, value());
		}

		void call_on_update()
		{
			if (on_update)
				on_update(this, value());
		}

	public:
		virtual T value()
		{
			return m_value;
		}

		virtual void set_value(T value)
		{
			m_value = value;
		}

		virtual void reset() override
		{
			set_value(m_default_value);
		}

		std::function<void(input_control*, T)> on_enter;
		std::function<void(input_control*, T)> on_update;
	};
}
