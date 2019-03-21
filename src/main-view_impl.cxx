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

NAMESPACE__THITTAM__START

namespace bofs = ::boost::filesystem;

MainViewImpl::MainViewImpl (
  hipro::log::Logger* logger,
  Glib::RefPtr<Gtk::Builder> builder)
  : logger (logger),
    m_builder (builder)
{
  builder->get_widget ("project-container", m_container);

  builder->get_widget ("main-window", m_window);
  m_window->signal_hide ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_close));

  Gtk::MenuItem * menuitem;
  builder->get_widget ("menu-file-new", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_file_new));

  builder->get_widget ("menu-file-open", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_file_open));

  builder->get_widget ("menu-file-save", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_file_save));

  builder->get_widget ("menu-file-save-as", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_file_save_as));

  builder->get_widget ("menu-file-quit", menuitem);
  menuitem->signal_activate ().connect
    (sigc::mem_fun (*this, &MainViewImpl::cb_on_close));

  m_window->set_title ("Untitled");
}

void
MainViewImpl::attach_content (Gtk::Widget* widget)
{
  auto children = m_container->get_children ();
  for (auto child : children)
  {
    m_container->remove (*child);
  }

  m_container->add (*widget);
}

void
MainViewImpl::show (void)
{
  m_window->show ();
}

void
MainViewImpl::cb_on_file_new (void)
{
  m_handler->view_file_new_pressed ();
}

void
MainViewImpl::cb_on_file_open (void)
{
  m_handler->view_file_open_pressed ();
}

void
MainViewImpl::cb_on_file_save (void)
{
  m_handler->view_file_save_pressed ();
}

void
MainViewImpl::cb_on_file_save_as (void)
{
  m_handler->view_file_save_as_pressed ();
}

void
MainViewImpl::cb_on_close (void)
{
  m_handler->view_close_pressed ();
}

bool
MainViewImpl::get_file_to_open (std::string * file_name)
{
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
      *file_name = dlg.get_filename ();
      return true;
    }
  return false;
}

bool
MainViewImpl::get_file_to_save (std::string * file_name)
{
  Gtk::FileChooserDialog dlg (
    *m_window, "Save file", Gtk::FILE_CHOOSER_ACTION_SAVE);
  dlg.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dlg.add_button (Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  dlg.set_current_name("Untitled");

  auto ret = dlg.run ();
  if (ret == Gtk::RESPONSE_OK)
  {
    bofs::path fp (dlg.get_filename ());
    fp.replace_extension (".thm");
    *file_name = fp.c_str ();
    return true;
  }

  return false;
}

bool
MainViewImpl::get_file_to_save_as (std::string * file_name)
{
  Gtk::FileChooserDialog dlg (
    *m_window, "Save as", Gtk::FILE_CHOOSER_ACTION_SAVE);
  dlg.add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dlg.add_button (Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  dlg.set_filename ("Untitled");

  auto ret = dlg.run ();
  if (ret == Gtk::RESPONSE_OK)
    {
      bofs::path fp (dlg.get_filename ());
      fp.replace_extension (".thm");
      *file_name = fp.c_str ();
      return true;
    }

  return false;
}

bool
MainViewImpl::confirm_data_discard (
  const std::string& title, const std::string& description)
{
  Gtk::MessageDialog dlg
    (*m_window, title, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO);
  dlg.set_secondary_text (description);
  auto ret = dlg.run ();
  if (ret == Gtk::RESPONSE_YES)
    {
      return true;
    }
  return false;
}

void
MainViewImpl::show_error (const std::string & msg)
{
  Log_E << "todo: Should show an error-dialog here";
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
