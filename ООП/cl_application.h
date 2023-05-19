#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
class cl_application : public cl_base //��� ���������� ������ �������� �������� � �������� ��������� ������� ������������ ������ ����������.
{
	//����� ������� ���������� ����������� �� �������� �����
public:
	cl_application(cl_base* p_head_object);
	//�����������
	void build_tree_objects();
	//����� ���������� ��������� ������ �������� �������� (��������������� ������������ �������)
	int exec_app();
	//����� ������� ����������	void signal(string& text);
	void handler(string text);
	TYPE_SIGNAL get_method(int id);
	TYPE_HANDLER get_handler(int id);
};
#endif