/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__ce9f7d80_26dc_11e9_bbf9_448500dfb04c
#define HIPRO__ce9f7d80_26dc_11e9_bbf9_448500dfb04c

#include "resource-view.h"
#include "resource.h"
#include "log.h"

NAMESPACE__THITTAM__START

class ResourceViewImpl : public ResourceView
{
public:
  ResourceViewImpl (
    hipro::log::Logger* logger,
    Glib::RefPtr<Gtk::Builder> builder,
    Gtk::Window* parent);

  /*--- ResourceView interface ---*/
  Gtk::Widget* widget (void)
  {
    return m_top_window;
  }

  void set_handler (ResourceViewCallbacks* handler)
  {
    m_handler = handler;
  }

  void show (void);
  void hide (void);

  void set_short_name (const std::string& short_name);
  void set_long_name (const std::string& long_name);
  void set_cost (double cost);
  void set_description (const std::string& description);

  const std::string& short_name (void) const;
  const std::string& long_name (void) const;
  double cost (void) const;
  const std::string& description (void) const;

private:
  void cb_on_save_clicked (void);
  void cb_on_cancel_clicked (void);

private:
  hipro::log::Logger* logger = nullptr;
  Gtk::Window* m_parent = nullptr;

  ResourceViewCallbacks* m_handler = nullptr;

  Gtk::Entry* m_ent_short_name = nullptr;
  Gtk::Entry* m_ent_long_name = nullptr;
  Gtk::Entry* m_ent_cost = nullptr;
  Gtk::Entry* m_ent_description = nullptr;

  mutable Glib::ustring m_short_name;
  mutable Glib::ustring m_long_name;
  mutable Glib::ustring m_cost;
  mutable Glib::ustring m_description;

  Gtk::Window* m_top_window = nullptr;
};

NAMESPACE__THITTAM__END

#endif // HIPRO__ce9f7d80_26dc_11e9_bbf9_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
