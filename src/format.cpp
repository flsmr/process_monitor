#include <string>
#include <math.h>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    long hours, minutes;
    minutes = floor(seconds/60.0f);
    hours = floor(minutes/60.0f);

    string hourstxt, minutestxt, secondstxt;
    secondstxt = std::to_string(seconds%60).c_str();
    minutestxt = std::to_string(minutes%60).c_str();
    hourstxt   = std::to_string(hours%60).c_str();
    return hourstxt + ":" + minutestxt + ":" + secondstxt;
}