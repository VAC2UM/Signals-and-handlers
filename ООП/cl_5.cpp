#include "cl_4.h"
cl_4::cl_4(cl_base* p_head_object, string s_name, int id) :cl_base(p_head_object,
	s_name, id)
{}
void cl_4::signal(string& text) {
	text += " (class: 4)";
	cout << endl << "Signal from " << get_absolute_path();
}
void cl_4::handler(string text) {
	cout << endl << "Signal to " << get_absolute_path() << " Text: " << text;
}
