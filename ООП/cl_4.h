#ifndef __CL_4__H
#define __CL_4__H
#include "cl_base.h"
class cl_4 : public cl_base {
public:
	cl_4(cl_base* p_head_object, string s_name, int id = 4);
	void signal(string& text);
	void handler(string text);
};
#endif