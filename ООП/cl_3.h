#ifndef __CL_3__H
#define __CL_3__H
#include "cl_base.h"
class cl_3 : public cl_base
{
public:
	cl_3(cl_base* p_head_object, string s_name, int id = 3);
	void signal(string& text);
	void handler(string text);
};
#endif