// generated by Fast Light User Interface Designer (fluid) version 2.0000

#ifndef widget_panel_h
#define widget_panel_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tabs.H>
extern void propagate_tabs(Fl_Tabs*, void*);
extern Fl_Tabs *panel_tabs;
#include <FL/Fl_Group.H>
extern void propagate_group(Fl_Group*, void*);
#include <FL/Fl_Input.H>
extern void label_cb(Fl_Input*, void*);
#include <FL/Fl_Button.H>
extern void align_cb(Fl_Button*, void*);
#include <FL/Fl_Box.H>
extern Fl_Box *image_label;
extern void image_cb(Fl_Button*, void*);
#include <FL/Fl_Light_Button.H>
extern void visible_cb(Fl_Light_Button*, void*);
extern void active_cb(Fl_Light_Button*, void*);
extern void resizable_cb(Fl_Light_Button*, void*);
extern void hotspot_cb(Fl_Light_Button*, void*);
#include "Shortcut_Button.h"
extern void shortcut_in_cb(Shortcut_Button*, void*);
extern void xclass_cb(Fl_Input*, void*);
extern void tooltip_cb(Fl_Input*, void*);
#include <FL/Fl_Value_Input.H>
extern void slider_size_cb(Fl_Value_Input*, void*);
extern void min_cb(Fl_Value_Input*, void*);
extern void max_cb(Fl_Value_Input*, void*);
extern void step_cb(Fl_Value_Input*, void*);
extern void value_cb(Fl_Value_Input*, void*);
extern void image_inlined_cb(Fl_Light_Button*, void*);
extern Fl_Light_Button *include_image_button;
extern void non_modal_cb(Fl_Light_Button*, void*);
extern void modal_cb(Fl_Light_Button*, void*);
extern void border_cb(Fl_Light_Button*, void*);
#include <FL/Fl_Choice.H>
extern Fl_Menu_Item labeltypemenu[];
extern void labeltype_cb(Fl_Choice*, void*);
extern Fl_Menu_Item fontmenu[];
extern void labelfont_cb(Fl_Choice*, void*);
extern void labelsize_cb(Fl_Value_Input*, void*);
extern void textfont_cb(Fl_Choice*, void*);
extern void textsize_cb(Fl_Value_Input*, void*);
extern Fl_Menu_Item boxmenu[];
extern void box_cb(Fl_Choice*, void*);
extern void color_cb(Fl_Light_Button*, void*);
extern void labelcolor_cb(Fl_Light_Button*, void*);
extern void color2_cb(Fl_Light_Button*, void*);
extern void textcolor_cb(Fl_Light_Button*, void*);
extern void highlightcolor_cb(Fl_Light_Button*, void*);
extern void selected_textcolor_cb(Fl_Light_Button*, void*);
extern void color3_cb(Fl_Light_Button*, void*);
extern void default_cb(Fl_Button*, void*);
extern void highlight_label_color_cb(Fl_Light_Button*, void*);
extern void name_cb(Fl_Input*, void*);
extern void name_public_cb(Fl_Light_Button*, void*);
extern void v_input_cb(Fl_Input*, void*);
extern Fl_Input *v_input[4];
extern Fl_Box *callback_label;
extern void callback_cb(Fl_Input*, void*);
extern void user_data_cb(Fl_Input*, void*);
extern Fl_Menu_Item whenmenu[];
extern void when_cb(Fl_Choice*, void*);
extern void user_data_type_cb(Fl_Input*, void*);
extern void when_button_cb(Fl_Light_Button*, void*);
extern void subclass_cb(Fl_Input*, void*);
extern void subtype_cb(Fl_Choice*, void*);
extern int overlays_invisible;
extern void overlay_cb(Fl_Light_Button*, void*);
extern Fl_Light_Button *overlaybutton;
extern void cancel_cb(Fl_Button*, void*);
#include <FL/Fl_Return_Button.H>
extern void ok_cb(Fl_Return_Button*, void*);
Fl_Window* make_widget_panel();
#endif
