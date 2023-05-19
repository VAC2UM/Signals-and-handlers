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
	//Наименование объекта (строкового типа)
	cl_base* p_head_object;
	//указатель на головной объект для текущего объекта
	vector<cl_base*> p_sub_objects;
	//Вектор указателей на объекты, подчиненные к текущему объекту в дереве иерархии
	vector<cl_base*>::iterator child_iterator;
	vector<str_connect*> connects;
	int state = 0;
	int class_id;
	//Параметризированный конструктор с параметрами: указатель на объект базового класса,
	cl_base(cl_base* p_head_object, string s_name = "Base object", int id = 1);
	//содержащий адрес головного объекта в дереве иерархии строкового типа и наименование создаваемого объекта(знач.по умолчанию)
	~cl_base();
	//Метод редактирования имени объекта	bool set_name(string s_new_name);
	//Один параметр строкового типа содержит новое имя объекта. Если нет дубляжа имени подчиненных объектов у головного,
		//то редактирует имя и возвращает значение "Истина", иначе - "Ложь"
	string get_name();
	//Метод получения имени объекта
	cl_base* get_head();
	//Метод получения указателя на головной объект текущего объекта
	void print_tree();
	//Метод вывода наименований объектов в дереве иерархии слева направо и сверху вниз
		//Метод получения указателя на непосредственно подчиненный объект по его имени.
	cl_base* get_sub_object(string s_name);
	//Если объект не найден, то возращает nullptr. Один параметр строкового типа содержит имя искомого подчиненного объекта
	
	//-------------------------КВ2
	int count(string s_name);
	//вспомогательный метод подсчитывающий кол-во вхождений объектов с данным именем от текущего узла
	cl_base* search_object(string s_name);
	//метод осуществляет поиск объекта по имени от текущего
	//и возвращает указатель на первое вхождение объекта с треб.именем
	cl_base* find_object_from_current(string s_name);
	//метод для обхода счетчика при рекурсии
	cl_base* find_object_from_root(string s_name);
	void print_tree_from_current(string tab = "");
	void print_rpoint_and_tree_from_root(string tab = "");
	void r_point(int r_num);
	//---------------------------------КВ3
	cl_base* find_child(string s_name);
	cl_base* find_obj_by_coord(string s_coord);
	cl_base* get_root();
	bool set_head(cl_base* obj);
	void delete_obj(string s_name);
	bool search_obj_in_branch_point(cl_base* obj);
	cl_base* find_obj_by_name_in_branch(cl_base* obj);	//----------------------------------КВ4
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER
		p_ob_hendler);
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER
		p_ob_hendler);
	void turn_on_tree();
	string get_absolute_path(); //метод получения абсолю
	int get_class_id();
};
#endif