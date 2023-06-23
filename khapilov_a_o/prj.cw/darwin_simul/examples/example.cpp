#include <pl_he_pr_simul/pl_he_pr_simul.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


int main(int argc, char* argv[]) {
    std::string iPath = "save.txt";
    if (argc >= 3) {
        std::cout << "Incorrent number of arguments. Must be 0 or 1";
        return -1;
    }
    if (argc == 2) {
        iPath = argv[1];
    }
    std::ifstream istrm(iPath);

    ds::DarwinSimulator<Plant, Herbivore, Predator> s;
    istrm >> s;

    const int wid = s.getWidth();
    const int hei = s.getHeight();

    sf::RenderWindow w(sf::VideoMode(wid, hei), sf::String("msg"), sf::Style::Titlebar | sf::Style::Close);
    std::chrono::time_point prevRealTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point currRealTime = std::chrono::high_resolution_clock::now();
    while (w.isOpen()) {
        currRealTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currRealTime - prevRealTime).count() >= 16) {
            prevRealTime = std::chrono::high_resolution_clock::now();

            sf::Event event;
            while (w.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) w.close();
            }

            w.clear(sf::Color::White);

            sf::CircleShape cir;

            const std::vector<Plant*> plnts = s.get<Plant>();
            cir.setFillColor(sf::Color::Green);
            for (Plant* plnt : plnts) {
                cir.setPosition(sf::Vector2f(plnt->getX(), plnt->getY()));
                cir.setRadius(plnt->radius());
                cir.setOutlineColor(sf::Color::Magenta);
                cir.setOutlineThickness(1);
                w.draw(cir);
            }
            cir.setOutlineThickness(0);

            const std::vector<Herbivore*> hrbvrs = s.get<Herbivore>();
            for (Herbivore* hrbvr : hrbvrs) {
                cir.setFillColor(sf::Color(hrbvr->viewRange / std::max(wid, hei) * 255, hrbvr->speed / std::min(wid, hei) * 255 * 4, hrbvr->danger));
                cir.setPosition(sf::Vector2f(hrbvr->getX(), hrbvr->getY()));
                cir.setRadius(hrbvr->radius());
                w.draw(cir);
            }

            const std::vector<Predator*> prdtrs = s.get<Predator>();
            for (Predator* prdtr : prdtrs) {
                cir.setFillColor(sf::Color(prdtr->viewRange / std::max(wid, hei) * 255, prdtr->speed / std::min(wid, hei) * 255 * 4, prdtr->danger));
                cir.setPosition(sf::Vector2f(prdtr->getX(), prdtr->getY()));
                cir.setRadius(prdtr->radius());
                cir.setOutlineColor(sf::Color::Black);
                cir.setOutlineThickness(3);
                w.draw(cir);
            }
            w.display();
        }
        s.update();
    }
    return 0;
}