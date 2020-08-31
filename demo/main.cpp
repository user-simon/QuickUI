#include <qui/qui.h>
using namespace qui;

//
// example application demonstrating some of the basic functionality of qui
// because of a lack of creativity, this doesn't really represent a realistic usage scenario but hey
//

void on_server_select(control* sender, option* select_option);
void on_login(control* sender);
void create_controls();

// application entry-point
int main()
{
	// initializes the menu
	menu::init();

	// controls can be created at any point in the application's lifetime, here most of the controls are created at once for readability
	create_controls();

	// set the control to be displayed in the menu to the login form page using its internal name
	menu::set_displayed("login_form");

	// starts drawing and listening for input
	menu::exec();

	// frees the controls and closes the console
	menu::exit();
}

void create_controls()
{
	// indenting with brackets under page creation is just used to make the code more readable by clearly showing which controls are part of what page
	page* login_form = new page("login_form", "Login form");
	{
		new textfield("text_username", login_form, "Username");
		new textfield("text_password", login_form, "Password", true);
		new button("button_login", login_form, on_login, "Login");
	}

	// create second page with servers to be interacted with
	page* control_panel = new page("control_panel", "Control panel");
	{
		optionselect* select_servers = new optionselect("select_servers", control_panel, { "Server 1", "Server 2", "Server 3" }, "Servers");
		select_servers->on_enter = on_server_select;
	}
}

void on_server_select(control* sender, option* select_option)
{
	std::string name = "server_page" + select_option->index();
	
	// create page if hasn't previously been created
	if (!menu::control_exists(name))
	{
		// create page to display options for server
		// prev_displayed is set to "control_panel" page: when escape is pressed the control_panel will be displayed
		page* server = new page(name, select_option->title(), menu::get("control_panel"));
		{
			new button("button_server_restart", server, "Restart");
			new button("button_server_start", server, "Start");
			new button("button_server_stop", server, "Stop");
		}
	}

	menu::set_displayed(name);
}

// gets called when the button "button_login" is pressed
void on_login(control* sender)
{
	// get values of textfields
	std::string username = menu::get_value<std::string>("text_username");
	std::string password = menu::get_value<std::string>("text_password");

	// super secure account details check to change the page
	if (username == "admin" && password == "password1")
		menu::set_displayed("control_panel");
}
