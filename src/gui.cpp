#include "gui.h"

mmalgo_gui::mmalgo_gui()
{
    builder_main = Gtk::Builder::create();
    path_glade = boost::dll::program_location().parent_path().parent_path().append("share/mmalgo");
    file_mmalgo.str("");
    file_mmalgo << path_glade.string() << "/mmalgo.glade";

    window_main = nullptr;
    button_search = nullptr;
    button_simulate = nullptr;
}

Gtk::Window *mmalgo_gui::mmalgo_main()
{
    try {
        builder_main->add_from_file(file_mmalgo.str());
    } catch(...){
        throw;
    }

    builder_main->get_widget("window_main", window_main);
    if(!window_main){
        delete window_main;
        throw std::runtime_error("Unable to access window_main widget");
    }
    
    builder_main->get_widget("button_search", button_search);
    if(!button_search){
        delete window_main;
        window_main = nullptr;
        throw std::runtime_error("Unable to access button_search widget");
    }
    
    builder_main->get_widget("button_simulate", button_simulate);
    if(!button_search){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        throw std::runtime_error("Unable to access button_simulate widget");
    }

    builder_main->get_widget("entry_folder", entry_folder);
    if(!entry_folder){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        throw std::runtime_error("Unable to access entry_folder widget");
    }

    builder_main->get_widget("radio_first", radio_first);
    if(!radio_first){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        entry_folder = nullptr;
        throw std::runtime_error("Unable to access radio_first widget");
    }

    builder_main->get_widget("radio_next", radio_next);
    if(!radio_next){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        entry_folder = nullptr;
        radio_first = nullptr;
        throw std::runtime_error("Unable to access radio_next widget");
    }

    builder_main->get_widget("radio_best", radio_best);
    if(!radio_best){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        entry_folder = nullptr;
        radio_first = nullptr;
        radio_next = nullptr;
        throw std::runtime_error("Unable to access radio_best widget");
    }

    builder_main->get_widget("radio_worst", radio_worst);
    if(!radio_worst){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        entry_folder = nullptr;
        radio_first = nullptr;
        radio_next = nullptr;
        radio_best = nullptr;
        throw std::runtime_error("Unable to access radio_worst widget");
    }

    builder_main->get_widget("radio_lucky", radio_lucky);
    if(!radio_lucky){
        delete window_main;
        window_main = nullptr;
        button_search = nullptr;
        button_simulate = nullptr;
        entry_folder = nullptr;
        radio_first = nullptr;
        radio_next = nullptr;
        radio_best = nullptr;
        radio_worst = nullptr;
        throw std::runtime_error("Unable to access radio_lucky widget");
    }

    button_search->signal_clicked().connect(
                sigc::mem_fun(*this, &mmalgo_gui::on_button_search_clicked));
    button_simulate->signal_clicked().connect(
                sigc::mem_fun(*this, &mmalgo_gui::on_button_simulate_clicked));

    return window_main;
}

void mmalgo_gui::on_button_search_clicked()
{
    Gtk::FileChooserDialog dialog("Selecione a pasta",
                    Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*window_main);

    dialog.add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::ResponseType::RESPONSE_OK);

    switch(dialog.run()){
    case Gtk::ResponseType::RESPONSE_OK:
        button_simulate->set_sensitive(true);
        entry_folder->set_text(dialog.get_filename());
        break;
    case Gtk::ResponseType::RESPONSE_CANCEL:
    default:
        button_simulate->set_sensitive(false);
        entry_folder->set_text("");
        break;
    }
}

void mmalgo_gui::on_button_simulate_clicked()
{

    try {
        parser.open_list(entry_folder->get_text()+"/listas.txt");
        parser.open_task(entry_folder->get_text()+"/tarefas.txt");
    } catch(const std::runtime_error& ex){
        //Mensagem de erro!!!
    }

    switch(get_selected_radio()){
        case Radio::FIRST:
            manager.run_first(parser);
            break;
        case Radio::NEXT:
            manager.run_next(parser);
            break;
        case Radio::BEST:
            manager.run_best(parser);
            break;
        case Radio::WORST:
            manager.run_worst(parser);
            break;
        case Radio::LUCKY:
            manager.run_lucky(parser);
            break;
    }


    //Show results
}

mmalgo_gui::Radio mmalgo_gui::get_selected_radio()
{
    if(radio_first->get_active())
        return Radio::FIRST;
    else if(radio_next->get_active())
        return Radio::NEXT;
    else if(radio_best->get_active())
        return Radio::BEST;
    else if(radio_worst->get_active())
        return Radio::WORST;
    else
        return Radio::LUCKY;
}