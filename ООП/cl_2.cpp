#include "cl_2.h"
cl_2::cl_2(cl_base* p_head_object, string s_name, int id):cl_base(p_head_object,s_name, id){}

void cl_2::signal(string& text) {
	text += " (class: 2)";
	cout << endl << "Signal from " << get_absolute_path();
}
void cl_2::handler(string text) {
	cout << endl << "Signal to " << get_absolute_path() << " Text: " << text;
}