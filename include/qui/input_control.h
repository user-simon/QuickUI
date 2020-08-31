#pragma once
#include "control.h"

namespace qui
{
	template<typename value_t>
	class input_control : public virtual control
	{
	private:
		value_t m_default_value;

	protected:
		value_t m_value;

	protected:
		input_control() {}

		input_control(value_t default_value)
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
		virtual value_t value()
		{
			return m_value;
		}

		virtual void set_value(value_t value)
		{
			m_value = value;
		}

		virtual void reset() override
		{
			set_value(m_default_value);
		}

		std::function<void(input_control*, value_t)> on_enter;
		std::function<void(input_control*, value_t)> on_update;
	};
}
