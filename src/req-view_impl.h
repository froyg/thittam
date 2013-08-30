/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__0a4bd086_ff51_11e2_9e6b_68a3c42125fd
#define HIPRO_THITTAM__0a4bd086_ff51_11e2_9e6b_68a3c42125fd

#include <memory>

#include <gtkmm.h>

#include "common.h"
#include "req-view.h"

class ReqViewImpl : public ReqView
{
public:
  /* ------- ctor/dtor ------- */
  ReqViewImpl (HLogPtr logger);
  ~ReqViewImpl () {}

  /* ------- Methods required by interface ------- */
  int show (void);
  int show (std::shared_ptr<Requirement> req);
  void hide (void);
  std::string title (void);
  std::string description (void);
  std::string work (void);

private:
  HLogPtr m_logger;
  std::unique_ptr<Gtk::Dialog> m_dlg_main;

  Gtk::Label * m_lbl_reqid;
  Gtk::Entry * m_ent_title;
  Gtk::Entry * m_ent_work;
  Glib::RefPtr<Gtk::TextBuffer> m_tb_description;
};

#endif // HIPRO_THITTAM__0a4bd086_ff51_11e2_9e6b_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
