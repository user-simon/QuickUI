#pragma once
#include "container_control.h"

namespace qui
{
	class page;

	class tab_control : public container_control
	{
	public:
		tab_control(std::string name, container_control* parent, std::string title, std::vector<page*> pages = {});

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
	};
}
