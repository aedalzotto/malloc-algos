#ifndef MMALGO_GUI_H
#define MMALGO_GUI_H

#include <gtkmm.h>
#include <boost/dll/runtime_symbol_info.hpp>

#include "management.h"

#include <iostream>

class mmalgo_gui {
public:
    mmalgo_gui();
    Gtk::Window *mmalgo_main();

private:

    enum Radio {
        FIRST,
        NEXT,
        BEST,
        WORST,
        LUCKY
    };

    void on_button_search_clicked();
    void on_button_simulate_clicked();
    Radio get_selected_radio();
    void show_results(std::string algo);

    Glib::RefPtr<Gtk::Builder> builder_main;
    boost::filesystem::path path_glade;
    std::stringstream file_mmalgo;

    Gtk::Window *window_main;
    Gtk::Button *button_search;
    Gtk::Button *button_simulate;
    Gtk::Entry *entry_folder;

    Gtk::RadioButton *radio_first;
    Gtk::RadioButton *radio_next;
    Gtk::RadioButton *radio_best;
    Gtk::RadioButton *radio_worst;
    Gtk::RadioButton *radio_lucky;

    Gtk::Dialog *dialog_results;
    Gtk::Button *button_close;
    Gtk::Label *label_algo_res;
    Gtk::Label *label_unalloced;
    Gtk::Label *label_time;
    Gtk::Label *label_folder_res;
    Gtk::Label *label_search;
    Gtk::Label *label_frag;
    Gtk::TextView *text_holes;


    mmalgo_parser parser;
    mmalgo_rithm manager;

};

#endif