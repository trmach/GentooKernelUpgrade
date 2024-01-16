use std::cell::Cell;
use once_cell::sync::Lazy;
use glib::subclass::Signal;
use gtk::glib;
use gtk::glib::Properties;
use gtk::prelude::*;
use gtk::subclass::prelude::*;

#[derive(Properties, Default)]
#[properties(wrapper_type = super::CustomButton)]
pub struct CustomButton {
    #[property(get, set)]
    number: Cell<i32>
}

#[glib::object_subclass]
impl ObjectSubclass for CustomButton {
    const NAME: &'static str = "BitchAss";
    type Type = super::CustomButton;
    type ParentType = gtk::Button;
}

#[glib::derived_properties]
impl ObjectImpl for CustomButton {
    fn constructed(&self) {
        self.parent_constructed();

        let obj = self.obj();
        obj.bind_property("number", obj.as_ref(), "label")
            .sync_create()
            .build();
    }
    fn signals() -> &'static [Signal] {
        static SIGNALS: Lazy<Vec<Signal>> = Lazy::new(|| {
            vec![Signal::builder("max-number-reached")
                .param_types([i32::static_type()])
                .build()]
        });
        SIGNALS.as_ref()
    }
}

impl WidgetImpl for CustomButton {}

static MAX_NUMBER: i32 = 8;

impl ButtonImpl for CustomButton {
    fn clicked(&self) {
        let n = self.obj().number() + 1;
        let obj = self.obj();

        if n == MAX_NUMBER {
            obj.emit_by_name::<()>("max-number-reached", &[&n]);
            obj.set_number(0);
        } else {
            obj.set_number(n);
        }
    }
}


