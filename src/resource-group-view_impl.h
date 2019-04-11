/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__5e10ef32_27a8_11e9_b4cc_448500dfb04c
#define HIPRO__5e10ef32_27a8_11e9_b4cc_448500dfb04c

#include "log.h"
#include "resource-group-view.h"
#include "resource-group.h"

NAMESPACE__THITTAM__START

class ResourceGroupViewImpl : public ResourceGroupView
{
public:
  ResourceGroupViewImpl(hipro::log::Logger* logger,
    Glib::RefPtr<Gtk::Builder> builder,
    Gtk::Window* parent);

  /*--- ResourceGroupView interface ---*/
  Gtk::Widget*
  widget(void)
  {
    return m_top_window;
  }

  void
  set_handler(ResourceGroupViewCallbacks* handler)
  {
    m_handler = handler;
  }

  void
  show(void);
  void
  hide(void);

  void
  enable_save(bool f);

  void
  set_name(const std::string& _name);
  void
  set_description(const std::string& description);

  const std::string&
  name(void) const;
  const std::string&
  description(void) const;

private:
  void
  cb_on_save_clicked(void);
  void
  cb_on_cancel_clicked(void);
  void
  cb_on_group_name_changed(void);

private:
  hipro::log::Logger* logger = nullptr;
  Gtk::Window* m_parent = nullptr;

  Gtk::Button* save_btn = nullptr;

  ResourceGroupViewCallbacks* m_handler = nullptr;

  Gtk::Entry* m_ent_name = nullptr;
  Gtk::Entry* m_ent_description = nullptr;

  mutable Glib::ustring m_name;
  mutable Glib::ustring m_description;

  Gtk::Window* m_top_window = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__5e10ef32_27a8_11e9_b4cc_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
