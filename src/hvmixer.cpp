#include "hvmixer.h"
#include <gtkmm/main.h>
#include <iostream>

namespace HVMixer {

SettingsWindow::SettingsWindow()
: lblmixer1("1. Mixer Element:"),
  lblmixer2("2. Mixer Element:")
{

    Gtk::Box *Content = get_vbox();

    boxmixer1.pack_start(lblmixer1, true, false);
    boxmixer1.pack_end(mixername1, true, true);
    
    boxmixer2.pack_start(lblmixer2, true, false);
    boxmixer2.pack_end(mixername2, true, true);
    
    add_button(Gtk::Stock::APPLY, Gtk::RESPONSE_APPLY);
    add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_CANCEL);
    
    
    Content->pack_start(boxmixer1, true, false);
    Content->pack_start(boxmixer2, true, false);

    set_size_request(300, 500);
    Content->show_all();
}

int SettingsWindow::opensw()
{
    return run();
}

SettingsWindow::~SettingsWindow()
{
    destroy();
}

}
