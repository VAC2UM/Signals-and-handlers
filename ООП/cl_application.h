#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
class cl_application : public cl_base //Для построения дерева иерархии объектов в качестве корневого объекта используется объект приложение.
{
	//Класс объекта приложения наследуется от базового класа
public:
	cl_application(cl_base* p_head_object);
	//конструктор
	void build_tree_objects();
	//Метод построения исходного дерева иерархии объектов (конструирования моделируемой системы)
	int exec_app();
	//метод запуска приложений	void signal(string& text);
	void handler(string text);
	TYPE_SIGNAL get_method(int id);
	TYPE_HANDLER get_handler(int id);
};
#endif