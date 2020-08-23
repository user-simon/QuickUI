#include <qui/qui.h>
using namespace qui;

void on_login(control* sender);
void create_controls();

// application entry-point
int main()
{
	// initialize the menu
	menu::init();

	create_controls();

	// set the control to be displayed in the menu to the login form page
	menu::set_displayed("login_form");

	// start drawing and listening for input
	menu::exec();
}

void create_controls()
{
	// pages are used to display a set of arbitrary controls in the menu at once
	// indenting with brackets under page creation is just used to make the code more readable by clearly showing which controls are part of what page
	page* login_form = new page("login_form", "Login form");
	{
		// controls are automatically added to the menu and their parent when created
		new textfield("text_username", login_form, "Username");

		// hide = true hides the characters when sensitive information has to be entered
		new textfield("text_password", login_form, "Password", true);

		// buttons accept a function to be called when the button is "pressed"
		new button("button_login", login_form, on_login, "Login");

		// all controls, including pages, have on_enter callbacks
		// i.e it will always call this callback when the user is on the login_form page and presses enter
		login_form->on_enter = on_login;
	}

	page* control_panel = new page("control_panel", "Control panel");
	{

	}
}

// gets called when the button "button_login" is pressed
void on_login(control* sender)
{
	// gets textfields from the menu
	textfield* text_username = menu::get_as<textfield>("text_username");
	textfield* text_password = menu::get_as<textfield>("text_password");

	// gets values of textfields
	std::string username = text_username->value();
	std::string password = text_password->value();

	// super secure account details check
	if (username == "admin" && password == "password1")
		menu::set_displayed("control_panel");
}

