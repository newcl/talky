#include "../inc/util.h"
#include <sstream>


string __ITOA(int i){
	ostringstream oss;
    oss << i;
    return oss.str();
}