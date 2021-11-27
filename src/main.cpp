#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char * argv[])
{
    json j;
    std::fstream file("res/en.json", std::ios::in);
    file >> j;

    std::cout << j["test"] << std::endl;
    
    return 0;
}