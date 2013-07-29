#include <iostream>
#include "hvmixer.h"

namespace HVMixer {

TrayIcon::TrayIcon()
: scale_window(Gtk::WINDOW_POPUP),
  hscales(Gtk::ORIENTATION_HORIZONTAL),
  vbox1(Gtk::ORIENTATION_VERTICAL),
  vbox2(Gtk::ORIENTATION_VERTICAL),
  adj1(Gtk::Adjustment::create(50.0, 0.0, 100.0)),
  adj2(Gtk::Adjustment::create(50.0, 0.0, 100.0)),
  scale1(adj1, Gtk::ORIENTATION_VERTICAL),
  scale2(adj2, Gtk::ORIENTATION_VERTICAL),
  label1("1"),
  label2("2"),
  openmixer (*Gtk::manage(
        new Gtk::Image(Gtk::Stock::EXECUTE, Gtk::ICON_SIZE_MENU)),
    "Launch Mixer"),
  settingsdlg (*Gtk::manage(
        new Gtk::Image(Gtk::Stock::PREFERENCES, Gtk::ICON_SIZE_MENU)),
    "Settings"),
  quit (Gtk::Stock::QUIT)
{
    set("audio-volume-medium");
    // load settings
    settings = new Settings();

    // mixers window
    scale_window.set_default_size(80, 200);
    scale_window.set_decorated(false);

    scale1.set_inverted(true);
    scale2.set_inverted(true);

    vbox1.pack_start(scale1, true, true);
    vbox1.pack_start(label1, false, false);
    vbox2.pack_start(scale2, true, true);
    vbox2.pack_end(label2, false, false);
    hscales.pack_start(vbox1, true, true);
    hscales.pack_start(vbox2, true, true);
    hscales.show_all();
    scale_window.add(hscales);

    // signals
    signal_button_release_event().connect(
        sigc::mem_fun(*this, &TrayIcon::on_button_release));
    signal_popup_menu().connect(
        sigc::mem_fun(*this, &TrayIcon::on_popup));

    openmixer.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_openmixer));
    settingsdlg.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_settings));
    quit.signal_activate().connect(
        sigc::mem_fun(*this, &TrayIcon::on_activate_quit));

    scale_window.signal_leave_notify_event().connect(
        sigc::mem_fun(*this, &TrayIcon::on_leave));

    // packing
    menu.append(openmixer);
    menu.append(settingsdlg);
    menu.append(quit);
    menu.show_all();
}

TrayIcon::~TrayIcon()
{
    delete settings;
}

void
TrayIcon::position_window()
{
    Glib::RefPtr<Gdk::Screen> screen;
    Gdk::Rectangle area;
    Gtk::Orientation orientation;
    gint x, y;

    get_geometry(screen, area, orientation);

    // x centered, x - width / 2
    x = area.get_x() - 80/2;
    // y below, y + 5 + icon height
    y = area.get_y() + 5 + area.get_height();

    scale_window.move(x, y);
}

bool
TrayIcon::on_button_release(GdkEventButton * event)
{
    if (event->button == 1) {
        position_window();
        scale_window.set_visible(!scale_window.get_visible());
    }
    // enable Gdk::LEAVE_NOTIFY_MASK, this must be done after window be shown
    Glib::RefPtr<Gdk::Window> gdksw(scale_window.get_window());
    gdksw->set_events(gdksw->get_events() | Gdk::LEAVE_NOTIFY_MASK);

    return true;
}

bool
TrayIcon::on_leave(GdkEventCrossing* event)
{
    scale_window.hide(false);
    return true;
}

void
TrayIcon::on_popup(guint button, guint32 time)
{
    menu.popup(button, time);
}

void
TrayIcon::on_activate_openmixer()
{
    Glib::spawn_command_line_async("gnome-alsamixer");
}

void
TrayIcon::on_activate_settings()
{
    SettingsWindow sw;

    switch (sw.opensw(settings)) {
    case Gtk::RESPONSE_APPLY:
        settings->setValue("mixer_element_1", sw.get_mixer_element_1_value());
        settings->setValue("mixer_element_2", sw.get_mixer_element_2_value());
        break;
    }
}

void
TrayIcon::on_activate_quit()
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

    mixername1.set_text(settings->getValue("mixer_element_1"));
    mixername2.set_text(settings->getValue("mixer_element_2"));

    set_size_request(300, 500);
    Content->show_all();
}

int
SettingsWindow::opensw(Settings * sets)
{
    settings = sets;
    return run();
}

SettingsWindow::~SettingsWindow()
{
}

std::string
SettingsWindow::get_mixer_element_1_value()
{
    return mixername1.get_text();
}

std::string
SettingsWindow::get_mixer_element_2_value()
{
    return mixername2.get_text();
}

}
