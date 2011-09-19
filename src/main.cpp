#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>

#include "common.hpp"

#include "view.hpp"
#include "controller.hpp"

Model model;

int main(int argc, char** argv)
{
    std::string model_file = "models/horse";
    bool dvorak = false;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[1], "--dvorak", 8) == 0) {
            dvorak = true;
        } else {
            model_file = std::string(argv[i]);
        }
    }

    model = Model(model_file);
    controller_init(argc, argv, dvorak);
    controller_run();
}
