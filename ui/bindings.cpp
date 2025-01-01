#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "display.hpp"
#include "../game/game.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pacman, m) {
    py::class_<GameState>(m, "GameState")
        .def(py::init<>())
        .def("game_over",&GameState::isGameOver)
        .def("get_score", &GameState::getScore);

    py::class_<Display>(m, "Display")
        .def(py::init<GameState*>())
        .def("running", &Display::running)
        .def("update", &Display::update)
        .def("render", &Display::render)
        .def("step",&Display::step)
        .def("pacman_contained", &Display::pacmanContainedInCell)
        .def("get_screenshot", [](Display &self) { 
            sf::Image screenshot = self.getScreenshot();
            const sf::Uint8* pixels = screenshot.getPixelsPtr();
            int width = screenshot.getSize().x;
            int height = screenshot.getSize().y;
            return py::array_t<uint8_t>({height, width, 4}, pixels); // Convert to NumPy array
        });
}
