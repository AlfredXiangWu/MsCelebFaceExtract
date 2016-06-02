#ifndef MS_CELEB_FACE_EXTRACT_
#define MS_CELEB_FACE_EXTRACT_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

typedef vector<string> vecS;


int ReadTSV(const string source_path, const string save_root_path, const string log_path);
int ReadLine(string line, const string save_root_path, string *log_list);



#endif // MS_CELEB_FACE_EXTRACT_