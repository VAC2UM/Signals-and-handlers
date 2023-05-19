#include "cl_3.h"
cl_3::cl_3(cl_base* p_head_object, string s_name, int id):cl_base(p_head_object, s_name, id)
{}
void cl_3::signal(string& text) {
	text += " (class: 3)";
	cout << endl << "Signal from " << get_absolute_path();
}
void cl_3::handler(string text) {
	cout << endl << "Signal to " << get_absolute_path() << " Text: " << text;
}