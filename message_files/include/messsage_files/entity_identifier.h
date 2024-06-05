#define TARGET 0
#define BASE_STATION 1
#define UAV 2
#define SOLUTION 3
#include <string.h>

int name_to_id(std::string&& name) {
    if (name == "uav") return UAV;
    else if (name == "target") return TARGET;
    else if (name == "bs") return BASE_STATION;
    else if (name == "solution") return SOLUTION;
    else return -1;
}


/**
 * TODO: refine visualization (which and where SCPs drawn, network)
 * TODO: relation between UAV pos and UAV goal
*/