#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "config.h"
#include <random>
#include <algorithm>

std::string permute(std::string text, unsigned int seed, unsigned int blen) {
    std::vector<std::string> blocks;
    std::default_random_engine e1(seed);
    for(int i = 0; i < text.size();) {
        std::poisson_distribution<int> uniform_dist(blen>text.size()-i?text.size()-i:blen);
        int rand = -1;
        while(rand < 0 || rand > text.size()-i) {
            rand = uniform_dist(e1);
        }
        blocks.push_back(text.substr(i,rand));
        i += rand;
    }
    std::shuffle(blocks.begin(),blocks.end(),e1);
    std::string ret;
    for(auto& block : blocks) {
        ret += block;
    }
    return ret;
}

int main(int argc, char** argv) {
    std::vector<std::string> positional;
    std::random_device r;
    unsigned int seed = r();
    unsigned int blocklen = 4;
    bool STDIN = false;
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            if(strcmp(argv[i], "--help") == 0) {
                std::cout << "Usage: permute [OPTION]... [TEXT]...\nRandomly permutes a string of characters\n\nWith no TEXT or when TEXT is -, read standard input.\n\n  -b, --block\t\tSet average block length (default: 4)\n      --help\t\tShow this help.\n  -s, --seed\t\tSet random seed\n      --version\t\tShow version information\n";
                exit(0);
            }
            else if(strcmp(argv[i], "--version") == 0) {
                std::cout << "Permute v" << VERSION_MAJOR << "." << VERSION_MINOR << ", kamray 2019\n";
                exit(0);
            }
            else if(strcmp(argv[i], "--seed") == 0 || strcmp(argv[i], "-s") == 0) {
                try {
                    seed = std::stoul(std::string(argv[++i]));
                }
                catch (const std::exception& e) {
                    std::cerr << "permute: invalid value '" << argv[i] << "'\nSeed values must be base-10 numerical\n";
                    exit(1);
                }
            }
            else if(strcmp(argv[i], "--block") == 0 || strcmp(argv[i], "-b") == 0) {
                try {
                    blocklen = std::stoul(std::string(argv[++i]));
                }
                catch (const std::exception& e) {
                    std::cerr << "permute: invalid value '" << argv[i] << "'\nBlock length must be base-10 numerical\n";
                    exit(1);
                }
            }
            else if(argv[i][1] == '\0') {
                //this is fine
            }
            else {
                std::cerr<< "permute: unrecognized option '" << argv[i] << "'\n";
                exit(1);
            }
        }
        else {
            positional.emplace_back(argv[i]);
        }
    }
    std::string text;
    for(auto& arg : positional) {
        if(arg == "-") {
            if(positional.size() == 1) {
                STDIN = true;
                continue;
            }
        }
        text += arg + " ";
    }
    if(positional.size() == 0) {
        STDIN = true;
    } else {
        std::cout << permute(text, seed, blocklen) << "\n";
    }

    if(STDIN) {
        while(! std::cin.eof()) {
            std::getline(std::cin,text);
            std::cout << permute(text, seed, blocklen) << ((text.size() == 0)? "":"\n");
            text = "";
        }
    }
}
