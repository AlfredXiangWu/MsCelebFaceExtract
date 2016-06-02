#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <opencv2/opencv.hpp>

#include "MsCelebFaceExtract.h"
#include "stdafx.h"
#include "base64.h"

#define _MAX_PATH 1024
#define DEBUG 1

using namespace std;
using namespace cv;

int ReadTSV(const string source_path, 
            const string save_root_path, 
            const string log_path) {

    ifstream tsv(source_path.c_str());
    ofstream log_list(log_path.c_str());
    string img_path;

    if(!tsv) {
        cout << "Error loading TSV file: " << source_path << endl;
    } else {
        cout << "TSV file " << source_path << " opened." << endl;
    }

    string line;
    while(getline(tsv, line)) {
        ReadLine(line, save_root_path, &img_path);
        cout << img_path << " is complete." << endl;
        log_list << img_path << endl;
    }
    log_list.close();
    tsv.close();
}

int ReadLine(string line, const string save_root_path, string *img_path) {
    vecS str;
    boost::split(str, line, boost::is_any_of("\t"));

    const string freebase_mid = str[0];
    const string img_name = str[1] + "-" + str[4] + ".jpg";
    string img_base64 = str[6];

    size_t output_length;
    get_decode_output(img_base64.c_str(), img_base64.size() - 1, &output_length);
    unsigned char* img_data = (unsigned char*)malloc(output_length);
    base64_decode(img_base64.c_str(), img_data, img_base64.size() - 1, &output_length);
    Mat imgbuf(1, output_length, CV_8UC1, img_data);
    Mat img = imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);

    const string save_path = save_root_path + freebase_mid + '/' + img_name;
    char dir[_MAX_PATH];
    get_dir_from_filename(save_path.c_str(), dir);
    create_directory(dir);

    imwrite(save_path, img);

    *img_path = freebase_mid + '/' + img_name;

    free(img_data);
    return 0;
}

int main() {
    const string tsv_path = "../../MsCelebV1-Faces-Aligned.tsv";
    const string save_path = "/home/xiang.wu/data/MsCelebV1_Faces_Aligned/MsCelebV1-Faces-Aligned/";
    const string log_path = "/home/xiang.wu/data/MsCelebV1_Faces_Aligned/log.txt";

    int ret = ReadTSV(tsv_path, save_path, log_path);
}
