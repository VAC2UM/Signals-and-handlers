#include "cl_application.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include "queue"
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object)
{
	//реализация конструктора
}
void cl_application::build_tree_objects()
{
	int i_class;
	cl_base* p_head = this;
	string s_head_name, s_sub_name, from_path, to_path;
	cin >> s_sub_name;
	this->set_name(s_sub_name);
	while (true) {
		cin >> s_head_name;
		if (s_head_name == "endtree") {
			break;
		}
		cin >> s_sub_name >> i_class;
		if (s_sub_name.find("/") != string::npos || s_sub_name.find(".") !=
			string::npos) {
			continue;
		}
		p_head = p_head->find_obj_by_coord(s_head_name);
		if (p_head != nullptr) {
			if (p_head->get_sub_object(s_sub_name)) {
				continue;
			}
			switch (i_class) {
			case 2:
				new cl_2(p_head, s_sub_name); break;
			case 3:
				new cl_3(p_head, s_sub_name); break;
			case 4:
				new cl_4(p_head, s_sub_name); break;
			case 5:
				new cl_5(p_head, s_sub_name); break;
			case 6:
				new cl_6(p_head, s_sub_name); break;
			default:
				break;
			}
		}
		else {
			cout << "Object tree";
			this->print_tree_from_current();
			cout << endl << "The head object " << s_head_name << " is not found";
			exit(1);
		}
	}
	while (true) {
		cin >> from_path;
		if (from_path == "end_of_connections") {
			break;
		}
		cin >> to_path;
		p_head = p_head->find_obj_by_coord(from_path);
		p_head->set_connect(get_method(p_head->get_class_id()),
			find_obj_by_coord(to_path), get_handler(find_obj_by_coord(to_path) -> get_class_id()));
	}
}
int cl_application::exec_app()
{
	int RON;
	//для установки состояния объекта
	cl_base* p_obj = this;
	cl_base* path_obj;
	string command, path, delname, text, from_path, to_path;
	cout << "Object tree";
	this->print_tree_from_current();
	turn_on_tree();
	while (true) {
		cin >> command;
		if (command == "END") {
			break;
		}
		else if (command == "EMIT") {
			//выдает сигнал от заданного по координате объекта
			cin >> path;
			getline(cin, text);
			path_obj = find_obj_by_coord(path);
			if (path_obj == nullptr) {
				cout << endl << "Object " << path << " not found";
			}
			else {
				path_obj->emit_signal(get_method(path_obj -> get_class_id()), text);
			}
		}
		else if (command == "SET_CONNECT") {
			cin >> from_path;
			cin >> to_path;
			path_obj = p_obj->find_obj_by_coord(from_path);
			if (path_obj == nullptr) {
				cout << endl << "Handler object " << to_path << " not found";
			}
			else if (p_obj->find_obj_by_coord(to_path) == nullptr) {
				cout << endl << "Handler object " << to_path << " not found";
			}
			else {
				path_obj->set_connect(get_method(path_obj -> get_class_id()), find_obj_by_coord(to_path), get_handler(find_obj_by_coord(to_path)->get_class_id()));
			}
		}
		else if (command == "DELETE_CONNECT") {
			cin >> from_path;
			cin >> to_path;
			path_obj = find_obj_by_coord(from_path);
			if (path_obj == nullptr) {
				cout << endl << "Object " << from_path << " not found";
			}
			else if (find_obj_by_coord(to_path) == nullptr) {
				cout << endl << "Handler object " << to_path << " not found";
			}
			else {
				path_obj->delete_connect(get_method(path_obj -> get_class_id()), find_obj_by_coord(to_path), get_handler(find_obj_by_coord(to_path)->get_class_id()));
			}
		}
		else if (command == "SET_CONDITION") {
			//устанавливает состояние объекта
				cin >> path;
			cin >> RON;
			if (find_obj_by_coord(path) == nullptr) {
				cout << endl << "Object " << path << " not found";
			}
			else {
				find_obj_by_coord(path)->r_point(RON);
			}
		}
	}
	return 0;
}
void cl_application::signal(string& text) {
	text += " (class: 1)";
	cout << endl << "Signal from " << get_absolute_path();
}
void cl_application::handler(string text) {
	cout << endl << "Signal to " << get_absolute_path() << " Text: " << text;
}
TYPE_SIGNAL cl_application::get_method(int id) {
	//метод получения указателя на метод сигнала класса по номеру
		switch (id) {
		case 1:
			return SIGNAL_D(cl_application::signal); break;
		case 2:
			return SIGNAL_D(cl_2::signal); break;
		case 3:
			return SIGNAL_D(cl_3::signal); break;
		case 4:
			return SIGNAL_D(cl_4::signal); break;
		case 5:
			return SIGNAL_D(cl_5::signal); break;
		case 6:return SIGNAL_D(cl_6::signal); break;
		default:
			return nullptr;
			break;
		}
}
TYPE_HANDLER cl_application::get_handler(int id) {
	//метод получения указателя на метод обработчика класса по номеру
		switch (id) {
		case 1:
			return HENDLER_D(cl_application::handler); break;
		case 2:
			return HENDLER_D(cl_2::handler); break;
		case 3:
			return HENDLER_D(cl_3::handler); break;
		case 4:
			return HENDLER_D(cl_4::handler); break;
		case 5:
			return HENDLER_D(cl_5::handler); break;
		case 6:
			return HENDLER_D(cl_6::handler); break;
		default:
			return nullptr;
			break;
		}
}