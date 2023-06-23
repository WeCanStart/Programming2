#include <pl_he_pr_simul/pl_he_pr_simul.hpp>
#include <iostream>
#include <fstream>
#include <string>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


int main(int argc, char* argv[]) {
    std::string oPath = "save.txt";
    if (argc >= 3) {
        std::cout << "Incorrent number of arguments. Must be 0 or 1";
        return -1;
    }
    if (argc == 2) {
        oPath = argv[1];
    }
    std::ofstream ostrm(oPath);

    const int wid = 768;
    const int hei = 768;

    ds::DarwinSimulator<Plant, Herbivore, Predator> s(0.01, wid, hei, 0);

    for (double i = 0; i < wid; i += 100) {
        for (double j = 0; j < hei; j += 100) {
            s.addAlive(Herbivore{ 50, i, j, std::max(wid, hei) * dis(gen), std::min(wid, hei) / 4 * dis(gen), 255 * dis(gen), 3 });
        }
    }
    s.addAlive(Predator{ 100, wid / 2, hei / 2, std::max(wid, hei) * dis(gen), std::min(wid, hei) / 4 * dis(gen), 255 * dis(gen), 3 });

    ostrm << s;
    return 0;
}