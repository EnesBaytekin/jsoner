#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void show_help() {
    cout << "Usage:" << endl;
    cout << "    jsoner <file> <element_path>" << endl;
}

void read_json_file(string file_name) {
    ifstream file(file_name);
    if (!file) {
        cout << "Error: Vould not open file '" << file_name << "'" << endl;
        exit(1);
    }
    char character;
    
    while (file.get(character)) {
        cout << character;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        show_help();
        exit(1);
    }
    read_json_file(argv[1]);
    return 0;
}
