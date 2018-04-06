#include <gtkmm/filechooserdialog.h>
#include <string>
#include <iomanip>
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
        throw std::runtime_error("Unable to access window_main widget");
    }
    
    builder_main->get_widget("button_search", button_search);
    if(!button_search){
        delete window_main;
        throw std::runtime_error("Unable to access button_search widget");
    }
    
    builder_main->get_widget("button_simulate", button_simulate);
    if(!button_search){
        delete window_main;
        throw std::runtime_error("Unable to access button_simulate widget");
    }

    builder_main->get_widget("entry_folder", entry_folder);
    if(!entry_folder){
        delete window_main;
        throw std::runtime_error("Unable to access entry_folder widget");
    }

    builder_main->get_widget("radio_first", radio_first);
    if(!radio_first){
        delete window_main;
        throw std::runtime_error("Unable to access radio_first widget");
    }

    builder_main->get_widget("radio_next", radio_next);
    if(!radio_next){
        delete window_main;
        throw std::runtime_error("Unable to access radio_next widget");
    }

    builder_main->get_widget("radio_best", radio_best);
    if(!radio_best){
        delete window_main;
        throw std::runtime_error("Unable to access radio_best widget");
    }

    builder_main->get_widget("radio_worst", radio_worst);
    if(!radio_worst){
        delete window_main;
        throw std::runtime_error("Unable to access radio_worst widget");
    }

    builder_main->get_widget("radio_lucky", radio_lucky);
    if(!radio_lucky){
        delete window_main;
        throw std::runtime_error("Unable to access radio_lucky widget");
    }

    builder_main->get_widget("dialog_results", dialog_results);
    if(!dialog_results){
        delete window_main;
        throw std::runtime_error("Unable to access dialog_results widget");
    }

    builder_main->get_widget("label_algo_res", label_algo_res);
    if(!label_algo_res){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_algo widget");
    }

    builder_main->get_widget("label_folder_res", label_folder_res);
    if(!label_folder_res){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_folder_res widget");
    }

    builder_main->get_widget("label_time", label_time);
    if(!label_time){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_time widget");
    }

    builder_main->get_widget("label_unalloced", label_unalloced);
    if(!label_unalloced){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_unalloced widget");
    }

    builder_main->get_widget("label_search", label_search);
    if(!label_search){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_search widget");
    }

    builder_main->get_widget("label_frag", label_frag);
    if(!label_frag){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access label_frag widget");
    }

    builder_main->get_widget("text_holes", text_holes);
    if(!text_holes){
        delete window_main;
        delete dialog_results;
        throw std::runtime_error("Unable to access text_holes widget");
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
        Gtk::MessageDialog dialog(*window_main, "ERRO", Gtk::MESSAGE_ERROR);
        dialog.set_secondary_text(ex.what());
        dialog.run();
        return;
    }

    std::string algo;
    switch(get_selected_radio()){
        case Radio::FIRST:
            manager.run_first(parser);
            algo = "First-fit";
            break;
        case Radio::NEXT:
            manager.run_next(parser);
            algo = "Next-fit";
            break;
        case Radio::BEST:
            manager.run_best(parser);
            algo = "Best-fit";
            break;
        case Radio::WORST:
            manager.run_worst(parser);
            algo = "Worst-fit";
            break;
        case Radio::LUCKY:
            manager.run_lucky(parser);
            algo = "Lucky-fit";
            break;
    }

    show_results(algo);

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

void mmalgo_gui::show_results(std::string algo)
{
    std::vector<std::string> paths = parser.explode(entry_folder->get_text(), '/');
    std::stringstream tmp;

    label_algo_res->set_text(algo);
    label_folder_res->set_text(paths[paths.size()-1]);
    label_search->set_text(std::to_string(manager.get_searched()));
    label_time->set_text(std::to_string(manager.get_runtime()));
    tmp << std::fixed << std::setprecision(2) << (double)manager.get_unalloced()/parser.get_task_number()*100; 
    label_unalloced->set_text(tmp.str());
    tmp.str("");
    tmp << std::fixed << std::setprecision(2) << (double)manager.get_hole_number()/parser.get_task_number()*100; 
    label_frag->set_text(tmp.str());

    tmp.str("");
    std::vector<std::pair<unsigned int, unsigned int> > holes = manager.get_hole_info();

    for(auto& it : holes){
        tmp << it.second;

        if(it.second == 1)
            tmp << " buraco";
        else
            tmp << " buracos";
            
        tmp << " de tamanho " << it.first << std::endl;
    }
    Glib::RefPtr<Gtk::TextBuffer> buffer_log;
    buffer_log = Gtk::TextBuffer::create();

    buffer_log->set_text(tmp.str());
    text_holes->set_buffer(buffer_log);

    dialog_results->set_transient_for(*window_main);
    dialog_results->show_all();

}