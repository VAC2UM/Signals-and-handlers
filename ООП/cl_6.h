#ifndef __CL_6__H
#define __CL_6__H
#include "cl_base.h"
class cl_6 : public cl_base
{
public:
	cl_6(cl_base* p_head_object, string s_name, int id = 6);
	void signal(string& text);
	void handler(string text);
};
#endif
