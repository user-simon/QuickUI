# QUI

This library is meant to provide a simple to make, simple to use UI for use in C++ applications.
Out of the box it includes various common controls as well as good infrastructure to create custom controls for use in the menu.

All controls have an associated string referred to as their name which serves as an internal identifier. This allows you to get any control from the menu by providing its name.

### Pages

Controls are typically organized in different so called pages, where one page represents a set of controls to be drawn at once. For example, one might have a login-page containing two textfields, leading to a main page where the main functionality of the application is accessed through a different set of controls. 

In a page, the end-user can use the arrow-up and arrow-down keys to change the focused control. If such functionality is not neccessary, it is also possible to draw just one control at once without dealing with pages.

# Controls
Controls have callbacks in the form of an std::function which can be set to any applicable function. The parameters of the std::function vary from control to control. All controls have an on_enter-callback which gets called when the control is focused and the enter-key is pressed.

There are two built-in control types which extend the functionality of the basic control - input controls and container controls. Input controls have a user-enterable value of a templated type. As such they have an extra on_update-callback and their callbacks have an extra parameter containing the current value of the control. Container controls are controls which contain other controls. Oftentimes, these have to allow the end-user to focus one out of several controls and as such they have a control iterator. Since the arrow-up and arrow-down keys are reserved for inter-control navigation, the arrow-left and arrow-right keys are used in container controls intsead.

### Button
Just utilizes the "on_enter"-callback. 

### Buttonbox
Displays a set of different standard buttons next to each other. The buttons which can be used are:
* OK
* Cancel
* Save
* Discard
* Yes
* No

### Checkbox
Gets a true/false input from the user.

### Multiselect
Gets several true/false inputs from the user. Is essentially a checkbox list.

### Numselect
Gets a numerical value from the user with customizable range and step-size.

### Optionselect
Allows the user to select one of several different alternatives.

### Textfield
Gets text input from the user. Mid-text cursor and CTRL + Backspace as well as password input is supported.

# Usage
### Setting up
* Download a release or build the project yourself.
* Add the include folder to your project's additional include directories
* Add the configuration-specific folders under lib to your project's additional library directories
* Add "qui.lib" to your project's additional dependencies

### Getting started

To use QUI normally, simply add `#include <qui/qui.h>`. This exposes all of the functionality in QUI. If for some reason you'd prefer to create your own controls but still use the QUI base, you can instead do `#include <qui/base.h>` which exposes only the basic functionality of QUI.

```cpp
#include <qui/qui.h>
using namespace qui;

// forward declared functions
void goto_next_page(control* sender);
void set_new_title(control* sender);

// application entry-point
int main()
{
	// the first thing you have to do is initialize the menu
	menu::init();

	// all controls need a unique name by which they can be referred to later in the application's lifetime, here the name is set to "main_page"
	page* main_page = new page("main_page", "Test application :)");

	// controls are added to their parents and to the menu in their constructors to allow for cleaner code
	// the on_enter-callback is set to the goto_next_page function
	new button("button_next_page", main_page, goto_next_page, "Next Page");

	// cleaner but optional syntax which clearly groups controls in different pages
	page* second_page = new page("second_page", "Here's a page two");
	{
		new textfield("text_page_title", second_page, "Enter new page title");
		new button("button_update_title", second_page, set_new_title, "Update title");
	}

	// sets the active page to the main page
	menu::set_displayed(main_page);

	// start drawing and listening for input
	menu::exec();

	// call exit at the end to clean up resources
	menu::exit();
}

void goto_next_page(control* sender)
{
	// use name specified for the second page to change the displayed page
	menu::set_displayed("second_page");
}

// gets called when the button "button_update_title" gets pressed
void set_new_title(control* sender)
{
	// gets value of textfield
	std::string new_title = menu::get_value<std::string>("text_page_title");

	// gets a pointer to the second page from its name
	page* second_page = menu::get_as<page>("second_page");
	
	// update title to the one specified by the user
	second_page->set_title(new_title);
}
```

For further reference, see the demo.

# Todo
* Add Linux support through replacing or providing alternatives to Windows-specific sections such as clearing the console and setting the console size
* Add a tab_control which would allow the user to intuitively switch between different labeled pages, much like tabs in a browser
* Allow the user to enter the value in a numselect via means of keyboard input

## Known issues
* Controls can go out of bounds on either axes. Fixing requires calculating the width and height of all controls in a page and setting the console size accordingly
