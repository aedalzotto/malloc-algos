#include <gtkmm.h>
#include <boost/dll/runtime_symbol_info.hpp>


//#include <iostream>

class mmalgo_gui {
public:
    mmalgo_gui();
    Gtk::Window *mmalgo_main();

private:
    void on_button_search_clicked();
    void on_button_simulate_clicked();

    Glib::RefPtr<Gio::Application> app;
    Glib::RefPtr<Gtk::Builder> builder_main;
    boost::filesystem::path path_glade;
    std::stringstream file_mmalgo;

    Gtk::Window *window_main;
    Gtk::Button *button_search;
    Gtk::Button *button_simulate;
    Gtk::Entry *entry_folder;

};