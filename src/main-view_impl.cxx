/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <boost/filesystem.hpp>

#include "main-view_impl.h"


MainViewImpl::MainViewImpl (HLogPtr logger,
                            Glib::RefPtr<Gtk::Builder> builder,
                            std::shared_ptr<ReqTreeFactory> req_tree_factory,
                            std::shared_ptr<ReqTreeView> req_tree_view)
  : m_logger (logger),
    m_req_tree_factory (req_tree_factory),
    m_req_tree_view (req_tree_view)
{
  builder->get_widget ("main-window", m_window);
  m_window->signal_hide ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_close));

  Gtk::MenuItem * menuitem;
  builder->get_widget ("menu-file-new", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_new));

  builder->get_widget ("menu-file-open", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_open));

  builder->get_widget ("menu-file-save", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_save));

  builder->get_widget ("menu-file-save-as", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_save_as));

  builder->get_widget ("menu-file-export-all", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_export_all));

  builder->get_widget ("menu-file-export-topics", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_file_export_topics));

  builder->get_widget ("menu-file-quit", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (this, &MainViewImpl::cb_on_close));

  m_req_tree = m_req_tree_factory->create ();
  m_req_tree_view->load (m_req_tree);

  m_window->show ();
}

void
MainViewImpl::cb_on_file_new (void)
{
  if (m_req_tree->is_dirty ())
    {
      if (!confirm_data_discard ())
        {
          return;
        }
    }

  m_req_tree = m_req_tree_factory->create ();
  m_file_name.clear ();
  update_title ();
}

void
MainViewImpl::cb_on_file_open (void)
{
  if (m_req_tree->is_dirty ())
    {
      if (!confirm_data_discard ())
        {
          return;
        }
    }

  Gtk::FileChooserDialog dlg
    (*m_window, "Open file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dlg.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dlg.add_button (Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  auto filter = Gtk::FileFilter::create ();
  filter->set_name ("thittam files");
  filter->add_pattern ("*.thm");
  dlg.add_filter (filter);

  filter = Gtk::FileFilter::create ();
  filter->set_name ("All files");
  filter->add_pattern ("*");
  dlg.add_filter (filter);

  auto ret = dlg.run ();
  if (ret == Gtk::RESPONSE_OK)
    {
      m_file_name = dlg.get_filename ();
      /* todo: continue here */
    }
}

void
MainViewImpl::cb_on_file_save (void)
{

}

void
MainViewImpl::cb_on_file_save_as (void)
{

}

void
MainViewImpl::cb_on_file_export_all (void)
{

}

void
MainViewImpl::cb_on_file_export_topics (void)
{

}

bool
MainViewImpl::confirm_data_discard (void)
{
  std::string file_name ("Untitled");
  std::ostringstream os;

  if (m_file_name.empty () == false)
    {
      file_name = m_file_name;
    }
  os << "The document [" << file_name << "] is modified";

  Gtk::MessageDialog dlg
    (*m_window, os.str (), false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO);
  dlg.set_secondary_text ("Do you want to discard the changes?");
  auto ret = dlg.run ();
  if (ret == Gtk::RESPONSE_YES)
    {
      return true;
    }
  return false;
}

void
MainViewImpl::update_title (void)
{

}



/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
