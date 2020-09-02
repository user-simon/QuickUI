# QUI

This library is meant to provide a simple to make, simple to use UI for use in C++ applications.
Out of the box it includes various common controls as well as good infrastructure to create custom controls for use in the menu.

All controls have an associated string referred to as their name which serves as an internal identifier. This allows you to get any control from the menu by providing its name.

When pressing the escape-key the currently displayed control is set to whichever the previously displayed control was.

QUI has no dependencies, though at the moment it does require Windows for console-manipulations. This is eventually going to be rectified.

### Pages

Controls are typically organized in different so called pages, where one page represents a set of controls to be drawn at once. For example, one might have a login-page containing two textfields, leading to a main page where the main functionality of the application is accessed through a different set of controls. 

In a page, the end-user can use the arrow-up and arrow-down keys to change the focused control. If such functionality is not neccessary, it is also possible to draw just one control at once without dealing with pages.

# Controls
Controls have callbacks in the form of an std::function which can be set to any applicable function. The parameters of the std::function vary from control to control. All controls have an on_enter-callback which gets called when the control is focused and the enter-key is pressed.

There are two built-in control types which extend the functionality of the basic control - input controls and container controls. Input controls have a user-enterable value of a templated type. As such they have an extra on_update-callback and their callbacks have an extra parameter containing the current value of the control. Container controls are controls which contain other controls. Oftentimes, these have to allow the end-user to focus one out of several controls and as such they have a control iterator. Since the arrow-up and arrow-down keys are reserved for inter-control navigation, the arrow-left and arrow-right keys are used in container controls instead.

Controls are automatically added to both their parent and to the menu when they are created, this is to minimize the code required to use the library.

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
Gets text input from the user. Mid-text cursor and CTRL + Backspace as well as password inputs are supported.

# Usage
### Setting up
* Download a release or build the project yourself.
* Add the include folder to your project's additional include directories
* Add the configuration-specific folders under lib to your project's additional library directories
* Add "qui.lib" to your project's additional dependencies

### Getting started

To use QUI normally, simply add `#include <qui/qui.h>`. This exposes all of the functionality in QUI. If for some reason you'd prefer to create your own controls but still use the QUI base, you can instead do `#include <qui/base.h>` which exposes only the basic functionality of QUI.

To "start" the menu, you first have to initialize and execute the menu.

```cpp
qui::menu::init();
qui::menu::exec();
```

### Example

It is recommended that the first control is created before the menu is executed. In this example, we'll have a button in a page which brings the user to the next page. Since controls are automatically added to both their parent and to the menu, all that has to be done to add a new control to the menu is allocate memory for it and optionally provide a pointer to a parent.

The function `menu::exit()` has to be called at the end of the UI's life-cycle which cleans up resources and closes the console.

```cpp
#include <qui/qui.h>
using namespace qui;

void goto_next_page(control* sender);
void set_new_title(control* sender);

int main()
{
	menu::init();
	
	// recommended syntax for creating controls
	page* main_page = new page("main_page", "Test application :)");
	{
		new button("button_next_page", main_page, "Next Page", goto_next_page);
	}
	
	// it's generally better to initialize all controls at once to avoid creating the same control multiple times later on
	page* second_page = new page("second_page", "Here's page two");
	{
		new textfield("text_page_title", second_page, "Enter new page title");
		new button("button_update_title", second_page, "Update title", set_new_title);
	}

	menu::set_displayed(main_page);
	
	// exec 
	menu::exec();
	menu::exit();
}
```

The button has a callback set to the function "goto_next_page". Let's add a definition for this. The parameters for a normal control's callback simply consist of a pointer to whichever control called the callback. This allows the code to distinguish between different controls, should multiple controls have the same callback. Here, we'll make the callback set the page to a different one. 

The next page is displayed through referencing it by its internal name, in this case "second_page".

```cpp
void goto_next_page(control* sender)
{
	menu::set_displayed("second_page");
}
```

The second page has a textfield and a button. For this example, we'll make the end-user able to set the title of the page to whatever they enter in the textfield. The button "button_update_title" has the callback function "set_new_title":

```cpp
void set_new_title(control* sender)
{
	// you can get values of input controls through the `menu::get_value()` function, though you have to provide the expected input value type
	std::string new_title = menu::get_value<std::string>("text_page_title");
	
	// get pointer to the second page and update the title
	page* second_page = menu::get_as<page>("second_page");
	second_page->set_title(new_title);
}
```

### Full example code
```cpp
#include <qui/qui.h>
using namespace qui;

void goto_next_page(control* sender)
{
	menu::set_displayed("second_page");
}

void set_new_title()
{
	// you can get values of input controls through the `menu::get_value()` function, though you have to provide the expected input value type
	std::string new_title = menu::get_value<std::string>("text_page_title");
	
	// get pointer to the second page and update the title
	page* second_page = menu::get_as<page>("second_page");
	second_page->set_title(new_title);
}

int main()
{
	menu::init();
	
	// recommended syntax for creating controls
	page* main_page = new page("main_page", "Test application :)");
	{
		new button("button_next_page", main_page, "Next Page", goto_next_page);
	}
	
	// it's generally better to initialize all controls at once to avoid creating the same control multiple times later on
	page* second_page = new page("second_page", "Here's page two");
	{
		new textfield("text_page_title", second_page, "Enter new page title");
		new button("button_update_title", second_page, "Update title", set_new_title);
	}

	menu::set_displayed(main_page);
	menu::exec();
	menu::exit();
}
```

For further reference, see the demo.

# Todo
* Add Linux support through replacing or providing alternatives to Windows-specific sections such as clearing the console and setting the console size
* Add a tab_control which would allow the user to intuitively switch between different labeled pages, much like tabs in a browser
* Allow the user to enter the value in a numselect via means of keyboard input

## Known issues
* Controls can go out of bounds on either axes. Fixing requires calculating the width and height of all controls in a page and setting the console size accordingly
