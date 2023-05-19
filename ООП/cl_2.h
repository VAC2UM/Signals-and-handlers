#ifndef __CL_2__H
#define __CL_2__H
#include "cl_base.h"
class cl_2 : public cl_base
{
public:
	cl_2(cl_base* p_head_object, string s_name, int id = 2);
	void signal(string& text);
	void handler(string text);
};
#endif