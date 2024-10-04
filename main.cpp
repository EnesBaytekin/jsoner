#include <iostream>
#include "tokenizer.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        utils::show_help();
        return 1;
    }
    vector<token> tokens = tokenize_json_file(argv[1]);
    for (token t : tokens) {
        cout << "<";
        switch (t.type) {
            case 0:  cout << "STRING";           break;
            case 1:  cout << "NUMBER";           break;
            case 2:  cout << "TRUE";             break;
            case 3:  cout << "FALSE";            break;
            case 4:  cout << "NULL";             break;
            case 5:  cout << "OBJECT_OPEN";      break;
            case 6:  cout << "OBJECT_CLOSE";     break;
            case 7:  cout << "ARRAY_OPEN";       break;
            case 8:  cout << "ARRAY_CLOSE";      break;
            case 9:  cout << "COLUMN";           break;
            case 10: cout << "COMMA";            break;
        }
        cout << ": " << t.value << "> ";
    }
    return 0;
}
