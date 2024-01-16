mod custom_button;
mod commands;

use std::str::from_utf8;
use std::process::Command;
use std::thread;
use std::future::Future;
use std::time::Duration;

//use custom_button::CustomButton;
use gtk::prelude::*;
use gtk::{gio, glib, Application, ApplicationWindow, Button, Orientation, ListBox, Label};
use glib::{clone, timeout_future_seconds};

const APP_ID: &str = "org.gtk_rs.GentooKernelUpgrade";

fn main() -> glib::ExitCode {
    let app = Application::builder().application_id(APP_ID).build();
    app.connect_activate(build_ui);
    app.run()
}


fn build_ui(app: &Application) {

    let button = Button::builder()
        .label("Increase")
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    let list_box = ListBox::builder()
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    for entry in commands::eselect_kernel_list().iter().skip(1) { // get symlink targets and display them
        let label = Label::builder()
            .label(entry)
            .build();
        list_box.append(&label); // i can't believe that actually worked
    }

    let gtk_box = gtk::Box::builder()
        .orientation(Orientation::Vertical)
        .build();

    gtk_box.append(&button);
    gtk_box.append(&list_box);


    let window = ApplicationWindow::builder()
        .application(app)
        .title("Gentoo Kernel Upgrade")
        .child(&gtk_box)
        .build();

    window.present();
}

