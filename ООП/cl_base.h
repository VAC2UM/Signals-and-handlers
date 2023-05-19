#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f)
#define HENDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

class cl_base;
typedef void (cl_base ::* TYPE_SIGNAL) (string&);
typedef void (cl_base ::* TYPE_HANDLER) (string);

struct str_connect {
	TYPE_SIGNAL p_signal;
	cl_base* p_cl_base;
	TYPE_HANDLER p_hendler;
};

class cl_base {
public:
	string s_name;
	cl_base* p_head_object;
	vector<cl_base*> p_sub_objects;
	vector<cl_base*>::iterator child_iterator;
	vector<str_connect*> connects;
	int state = 0;
	int class_id;
	cl_base(cl_base* p_head_object, string s_name = "Base object", int id = 1);
	~cl_base();
	bool set_name(string s_new_name);
	string get_name();
	cl_base* get_head();
	void print_tree();
	cl_base* get_sub_object(string s_name);
	int count(string s_name);
	cl_base* search_object(string s_name);
	cl_base* find_object_from_current(string s_name);
	cl_base* find_object_from_root(string s_name);
	void print_tree_from_current(string tab = "");
	void print_rpoint_and_tree_from_root(string tab = "");
	void r_point(int r_num);
	cl_base* find_child(string s_name);
	cl_base* find_obj_by_coord(string s_coord);
	cl_base* get_root();
	bool set_head(cl_base* obj);
	void delete_obj(string s_name);
	bool search_obj_in_branch_point(cl_base* obj);
	cl_base* find_obj_by_name_in_branch(cl_base* obj);
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_hendler);
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_hendler);
	void turn_on_tree();
	string get_absolute_path();þ
	int get_class_id();
};
#endif
