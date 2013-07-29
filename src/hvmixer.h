#include <gtkmm.h>
#include "settings.h"

#ifndef HVMIXER_H
#define HVMIXER_H

namespace HVMixer {

class TrayIcon : public Gtk::StatusIcon
{
public:
    TrayIcon();
    virtual ~TrayIcon();


protected:
    // first shown
    bool first_shown;

    // settings handler
    Settings * settings;

    // helpers
    void position_window();

    // signal handlers
    void on_popup(guint button, guint32 time);
    bool on_button_release(GdkEventButton * event);
    bool on_leave(GdkEventCrossing* event);
    void on_activate_openmixer();
    void on_activate_settings();
    void on_activate_quit();

    // widgets
    Gtk::Window scale_window;
    Gtk::Box hscales, vbox1, vbox2;
    Glib::RefPtr<Gtk::Adjustment> adj1, adj2;
    Gtk::Scale scale1, scale2;
    Gtk::Label label1, label2;
    Gtk::Menu menu;
    Gtk::ImageMenuItem openmixer, settingsdlg, quit;
};

class SettingsWindow : public Gtk::Dialog
{
public:
    SettingsWindow();
    virtual ~SettingsWindow();
    std::string get_mixer_element_1_value();
    std::string get_mixer_element_2_value();
    int opensw(Settings * sets);

protected:
    // settings handler
    Settings * settings;
    // Signal handlers
    void on_cancel_clicked();
    void on_save_clicked();

    // Widgets
    Gtk::Box boxmixer1, boxmixer2;
    Gtk::Label lblmixer1, lblmixer2;
    Gtk::Entry mixername1, mixername2;
};

}

#endif // HVMIXER_H
