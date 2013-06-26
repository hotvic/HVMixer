#include <iostream>
#include "hvmixer.h"


namespace HVMixer {

TrayIcon::TrayIcon()
: bmixer1(Gtk::ORIENTATION_VERTICAL),
  bmixer2(Gtk::ORIENTATION_VERTICAL),
  volume1(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 5.0, 100.0)),
  volume2(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 5.0, 100.0)),
  mixer1(volume1, Gtk::ORIENTATION_VERTICAL),
  mixer2(volume2, Gtk::ORIENTATION_VERTICAL),
  openmixer (*Gtk::manage(
        new Gtk::Image(Gtk::Stock::EXECUTE, Gtk::ICON_SIZE_MENU)),
    "Launch Mixer"),
  settings (*Gtk::manage(
        new Gtk::Image(Gtk::Stock::PREFERENCES, Gtk::ICON_SIZE_MENU)),
    "Settings"),
  quit (Gtk::Stock::QUIT)
{
    set("audio-volume-medium");

    // signals
    volume1->signal_value_changed().connect(
        sigc::mem_fun(*this, &TrayIcon::on_changed_volume1));
    volume2->signal_value_changed().connect(
        sigc::mem_fun(*this, &TrayIcon::on_changed_volume2));
    
    signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_signal));
    signal_popup_menu().connect(
        sigc::mem_fun(*this, &TrayIcon::on_popup_signal));
        
    openmixer.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_openmixer));
    settings.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_settings));
    quit.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_quit));
    
    // packing
    Gtk::Box hbox(Gtk::ORIENTATION_HORIZONTAL);
    bmixer1.pack_start(mixer1, true, false);
    bmixer2.pack_start(mixer2, true, false);
    hbox.pack_start(bmixer1, true, false);
    hbox.pack_start(bmixer2, true, false);
    
    popup.add(hbox);
    popup.show_all();
    
    menu.append(openmixer);
    menu.append(settings);
    menu.append(quit);
    menu.show_all();
}

TrayIcon::~TrayIcon()
{
    
}

void TrayIcon::on_changed_volume1()
{
    
}

void TrayIcon::on_changed_volume2()
{
    
}

void TrayIcon::on_activate_signal()
{
    popup.popup();
}

void TrayIcon::on_popup_signal(guint button, guint32 time)
{
    menu.popup(button, time);
}

void TrayIcon::on_activate_openmixer()
{
    Glib::spawn_command_line_async("gnome-alsamixer");
}

void TrayIcon::on_activate_settings()
{
    SettingsWindow sw;
    
    sw.opensw();
}

void TrayIcon::on_activate_quit()
{
    Gtk::Main::quit();
}


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

    /* default values, change not implemented yet! */
    mixername1.set_text("Master");
    mixername2.set_text("Master Surround");
    /* end default values */
    
    set_size_request(300, 500);
    Content->show_all();
}

int SettingsWindow::opensw()
{
    return run();
}

SettingsWindow::~SettingsWindow()
{
}

}
