/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082
#define HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082

#include <memory>

#include <gtkmm.h>

#include <boost/signals2.hpp>

#include "common.h"
#include "main-view.h"
#include "req-tree.h"
#include "req-tree-view.h"
#include "latex.h"
#include "log.h"

class MainViewImpl : public MainView
{
public:
  typedef std::shared_ptr<MainViewImpl> ptr_t;

public:
  /*--- ctor/dtor ---*/
  MainViewImpl (hipro::log::Logger* logger,
                Glib::RefPtr<Gtk::Builder> builder,
                std::shared_ptr<ReqTreeFactory> req_tree_factory,
                std::shared_ptr<ReqTreeView> req_tree_view);
  ~MainViewImpl () { }

  /*--- Methods required by the MainView interface ---*/
  signal_close_t & signal_close (void)
  {
    return m_signal_close;
  }

  Gtk::Window * window (void) { return m_window; }

private:
  /*--- Other convenience functions ---*/
  void cb_on_file_new (void);
  void cb_on_file_open (void);
  void cb_on_file_save (void);
  void cb_on_file_save_as (void);
  void cb_on_file_export_all (void);
  void cb_on_file_export_topics (void);
  void cb_on_tree_dirty (void);

  void cb_on_close (void)
  {
    m_signal_close ();
  }

  bool confirm_data_discard (void);
  void update_title (void);

private:
  /*--- Data members ---*/
  hipro::log::Logger* logger;
  std::shared_ptr<ReqTreeFactory> m_req_tree_factory;
  std::shared_ptr<ReqTree> m_req_tree;
  std::shared_ptr<ReqTreeView> m_req_tree_view;
  std::shared_ptr<Latex> m_latex_generator;
  std::string m_file_name;

  signal_close_t m_signal_close;
  Gtk::Window * m_window;
};

#endif // HIPRO_THITTAM__db56ba7c_fd96_11e2_806c_001f3c9e2082

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
