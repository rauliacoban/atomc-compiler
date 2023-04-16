#pragma once
#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <mutex>
//#define NO_DEBUG 
/*uncomment line above to turn off logging messages
or
compile with -DNO_DEBUG

alternatively, to toggle logging for specific code segments use: 
#define NO_DEBUG
// logging messages here
#undef NO_DEBUG 
*/

//#define NO_FILE_DEBUG

//#define SHOW_THREADS

extern std::ofstream fout;
extern std::mutex mu_fout;
extern std::mutex mu_cout;

#if defined(NO_DEBUG)
#define LOG(msg) {}
#define LOGLINE(msg) {}
#define LOGEXECUTE(msg) {}
#define LOGFLUSH {}
#define LOGNEWLINE {}
#else
#define LOG(msg) {std::cout << msg;}
#define LOGLINE(msg) {mu_cout.lock(); std::cout << msg << std::endl; mu_cout.unlock();}
#define LOGLINE_CHANNEL(index, msg) {mu_cout.lock(); std::cout << "CH[" << index << "] " << msg << std::endl; mu_cout.unlock();}
#define LOGEXECUTE(msg) { msg;}
#define LOGFLUSH {std::cout.flush();}
#define LOGNEWLINE {std::cout << std::endl;}
#endif

#if defined(NO_FILE_DEBUG)
#define FILELOG(msg) {}
#define FILELOGLINE(msg) {}
#define FILELOGLINE_CHANNEL(index, msg) {}
#define FILETIMESTAMP(time, msg) {}
#define FILELOGEXECUTE(msg) {}
#define FILELOGFLUSH {}
#define FILELOGNEWLINE {}
#else
#define FILELOG(msg) {fout << msg; fout.flush();}
#define FILELOGLINE(msg) {mu_fout.lock(); fout << msg << "\n"; mu_fout.unlock();}
#define FILELOGLINE_CHANNEL(index, msg) {mu_fout.lock(); fout << "CH[" << index << "] " << msg << "\n"; mu_fout.unlock();}
#define FILETIMESTAMP(time, msg) {mu_fout.lock(); fout << std::fixed << std::setprecision(5) << "[" << time << "] "<< std::setprecision(2) << msg << "\n"; mu_fout.unlock();}
#define FILELOGEXECUTE(msg) { msg; fout.flush();}
#define FILELOGFLUSH {fout.flush();}
#define FILELOGNEWLINE {fout << "\n"; fout.flush();}
#endif

#endif
