#include "cl_base.h"
#include <queue>
cl_base::cl_base(cl_base* p_head_object, string s_name, int id) {
	this->p_head_object = p_head_object;
	this->s_name = s_name;
	this->state = 0;
	this->class_id = id;
	if (p_head_object != nullptr) {
			p_head_object->p_sub_objects.push_back(this);
	}
}
cl_base::~cl_base() {
	for (int i = 0; i < p_sub_objects.size(); i++) {
		delete p_sub_objects[i];
	}
}
string cl_base::get_name() {
	return s_name;
}
cl_base* cl_base::get_head() {
		return p_head_object;
}
cl_base* cl_base::get_sub_object(string s_name) {
	for (int i = 0; i < p_sub_objects.size(); i++) {
			if (p_sub_objects[i]->get_name() == s_name) {
				return p_sub_objects[i];
			}
	}
	return nullptr;
}
void cl_base::print_tree() {
		if (!p_sub_objects.empty()) {
			cout << endl << get_name();
			for (int i = 0; i < p_sub_objects.size(); i++) {
				cout << " " << p_sub_objects[i]->get_name();
				p_sub_objects[i]->print_tree();
			}
		}
}
bool cl_base::set_name(string s_new_name) {
		if (get_head() != nullptr) {
				for (int i = 0; i < get_head()->p_sub_objects.size(); i++) {
						if (get_head()->p_sub_objects[i]->get_name() == s_new_name) {
							return false;
						}
				}
		}
	this->s_name = s_new_name;
	return true;
}
int cl_base::count(string s_name) {
		int counter = 0;
	if (this->get_name() == s_name) {
		counter++;
	}
	for (auto p_sub_object : p_sub_objects) {
		counter += p_sub_object->count(s_name);
	}
	return counter;
}
cl_base* cl_base::search_object(string s_name) {
	if (this->count(s_name) != 1) {
		return nullptr;
	}
	if (this->get_name() == s_name) {
		return this;
	}
	cl_base* pruf = nullptr;
	for (int i = 0; i < p_sub_objects.size(); i++) {
		pruf = p_sub_objects[i]->search_object(s_name);
		if (pruf != nullptr) {
			break;
		}
	}
	return pruf;
}
cl_base* cl_base::find_object_from_current(string s_name) {
		return search_object(s_name);
}
cl_base* cl_base::find_object_from_root(string s_name) {
		cl_base* temp = this;
	while (temp->get_head() != nullptr) {
		temp = temp->get_head();
	}
	return temp->find_object_from_current(s_name);
}
void cl_base::r_point(int r_num) {
		bool all_parents_ready = true;
	if (this->get_head() != nullptr) {
		cl_base* current_obj = this->get_head();
		while (current_obj != nullptr) {
			if (current_obj->state == 0) {
				all_parents_ready = false;
				break;
			}
			current_obj = current_obj->get_head();
		}
	}
	if (all_parents_ready || r_num == 0) {
		this->state = r_num;
		if (r_num == 0) {
			for (auto p_sub_object : p_sub_objects) {
				p_sub_object->r_point(0);
			}
		}
	}
}
void cl_base::print_tree_from_current(string tab) {
	cout << endl << tab << this->s_name;
	for (auto p_sub_object : p_sub_objects) {
		p_sub_object->print_tree_from_current(tab + " ");
	}
}
void cl_base::print_rpoint_and_tree_from_root(string tab) {
	string s;
	if (this->state != 0) {
		s = " is ready";
	}
	else {
		s = " is not ready";
	}
	cout << tab << this->s_name << s;
	for (auto p_sub_object : p_sub_objects) {
		cout << endl;
		p_sub_object->print_rpoint_and_tree_from_root(tab + " ");
	}
}
cl_base* cl_base::find_child(string s_name) {
	for (int i = 0; i < p_sub_objects.size(); i++) {
		if (p_sub_objects[i]->s_name == s_name) {
			return p_sub_objects[i];
		}
	}
	return nullptr;
}
cl_base* cl_base::get_root() {
	cl_base* p_root = this;
	while (p_root->get_head() != nullptr) {
		p_root = p_root->get_head();
	}
	return p_root;
}
cl_base* cl_base::find_obj_by_coord(string s_coord) {
		if (s_coord == "/") {
			return get_root();
		}
	if (s_coord == ".") {
		return this;
	}
	if (s_coord[0] == '.') {
		return this->search_object(s_coord.substr(1));
	}
	if (s_coord.find("//") == 0) {
		return get_root()->search_object(s_coord.substr(2));
	}
	if (s_coord[0] == '/') {
		return get_root()->find_obj_by_coord(s_coord.substr(1));
	}
	int buf = s_coord.size();
	for (int i = 0; i < s_coord.size(); i++) {
		if (s_coord[i] == '/') {
			buf = i;
			break;
		}
	}
	string str = s_coord.substr(0, buf);
	for (int i = 0; i < this->p_sub_objects.size(); i++) {
		if (p_sub_objects[i]->get_name() == str) {
			if (buf == s_coord.size()) {
				return p_sub_objects[i];
			}
			return p_sub_objects[i]->find_obj_by_coord(s_coord.substr(buf + 1));
		}
	}
	return nullptr;
}
bool cl_base::set_head(cl_base* obj) {
	if (obj->find_child(this->get_name())) {
		return true;
	}
	obj->p_sub_objects.push_back(this);
		for (auto it = this->get_head()->p_sub_objects.begin(); it != this -> get_head()->p_sub_objects.end(); it++) {
			if (*it == this) {
				this->get_head()->p_sub_objects.erase(it);
				break;
			}
		}
	return false;
}
void cl_base::delete_obj(string s_name) {
	cl_base* del = this->find_object_from_root(s_name);
	if (del == nullptr) {
		return;
	}
	for (this->p_head_object->child_iterator = p_sub_objects.begin(); this -> p_head_object->child_iterator != p_sub_objects.end(); this->p_head_object -> child_iterator++) {
		if (*this->p_head_object->child_iterator == del) {
			p_sub_objects.erase(this->p_head_object->child_iterator);
			return;
		}
	}
}
bool cl_base::search_obj_in_branch_point(cl_base* obj) {
	while (obj->get_head() != nullptr) {
		if (obj == this) {
				return true;
		}
		obj = obj->get_head();
	}
	return false;
}
cl_base* cl_base::find_obj_by_name_in_branch(cl_base* obj) {
	queue<cl_base*> qu;
	cl_base* buf = nullptr;
	qu.push(this);
	while (!qu.empty()) {
		if (qu.front()->get_name() == s_name) {
			if (buf == nullptr) {
				buf = qu.front();
			}
			else {
				return buf;
			}
		}
		for (auto p_sub_object : qu.front()->p_sub_objects) {
			qu.push(p_sub_object);
		}
		qu.pop();
	}
	return nullptr;
}
void cl_base::set_connect(TYPE_SIGNAL signal, cl_base* p_object, TYPE_HANDLER
	p_ob_hendler) {
		str_connect* p_value;
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == signal && connects[i]->p_cl_base ==
			p_object && connects[i]->p_hendler == p_ob_hendler) {
			return;
		}
	}
	p_value = new str_connect();
	p_value->p_signal = signal;
	p_value->p_cl_base = p_object;
	p_value->p_hendler = p_ob_hendler;
	connects.push_back(p_value);
}
void cl_base::emit_signal(TYPE_SIGNAL signal, string& s_command) {
		if (!this->state) {
			return;
		}
	TYPE_HANDLER handler;
	cl_base* p_object;
	(this->*signal)(s_command);
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == signal) {
			handler = connects[i]->p_hendler;
			p_object = connects[i]->p_cl_base;
			if (connects[i]->p_cl_base->state) {
				(p_object->*handler)(s_command);
			}
		}
	}
}
void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER
	p_ob_hendler) {
		for (int i = 0; i < connects.size(); i++) {
			if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base ==
				p_object && connects[i]->p_hendler == p_ob_hendler) {
				connects.erase(connects.begin() + i);
				return;
			}
		}
}
string cl_base::get_absolute_path() {
	string path;
	cl_base* p_obj = this;
	while (p_obj->p_head_object != nullptr) {
		path = "/" + p_obj->get_name() + path;
		p_obj = p_obj->p_head_object;
	}
	if (path == "") {
		path = "/";
	}
	return path;
}
void cl_base::turn_on_tree() {
		state = 1;
	for (int i = 0; i < p_sub_objects.size(); i++) {
		p_sub_objects[i]->turn_on_tree();
	}
}
int cl_base::get_class_id() {
	return class_id;
}
