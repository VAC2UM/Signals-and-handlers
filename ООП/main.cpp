#include <iostream>
#include "cl_application.h"
using namespace std;
int main() {
    cl_application  ob_cl_application(nullptr);
    ob_cl_application.build_tree_objects();
    return ob_cl_application.exec_app();
}
