#include <boost/dll/runtime_symbol_info.hpp>
#include <gtkmm.h>
#include <iostream>
#include "management.h"
#include "gui.h"

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "aedalzotto.mmalgo");

    mmalgo_gui gui;

    try {
        app->run(*gui.mmalgo_main());
    } catch(const Glib::FileError& ex){
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    } catch(const Glib::MarkupError& ex){
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    } catch(const Gtk::BuilderError& ex){
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    } catch(const std::runtime_error& ex){
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    return 0;

}