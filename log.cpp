#include "log.hpp"

std::ofstream fout("debug.txt");
std::mutex mu_fout;
std::mutex mu_cout;