/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <fstream>

#include <boost/property_tree/json_parser.hpp>

#include "main-controller_impl.h"

namespace bpt = boost::property_tree;

NAMESPACE__THITTAM__START

MainControllerImpl::MainControllerImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

void
MainControllerImpl::start (void)
{
  m_project = m_project_factory->create ();
  m_project_controller = m_project_ui_factory->create (m_project.get ());
  m_view->attach_content (m_project_controller->view_widget ());

  m_view->show ();
}

void
MainControllerImpl::view_close_pressed (void)
{
  if (m_project->dirty ())
    {
      if (!confirm_data_discard ())
        {
          return;
        }
    }

  m_app->quit ();
}

void
MainControllerImpl::view_file_new_pressed (void)
{
  if (m_project->dirty ())
    {
      if (!confirm_data_discard ())
        {
          return;
        }
    }

  m_file_name.clear ();
  m_project_controller.reset ();
  m_project.reset ();

  m_project = m_project_factory->create ();
  m_project_controller = m_project_ui_factory->create (m_project.get ());
  m_view->attach_content (m_project_controller->view_widget ());
}

void
MainControllerImpl::view_file_open_pressed (void)
{
  if (m_project->dirty ())
    {
      if (!confirm_data_discard ())
        {
          return;
        }
    }

  std::string file_name;
  bool ret = m_view->get_file_to_open (&file_name);
  if (! ret)
  {
    return;
  }

  // todo: Check if we have proper access permissions to read the file.

  if (! m_project_factory->verify (file_name))
  {
    std::ostringstream os;
    os << "File " << file_name << " is not a valid thittam file.";
    m_view->show_error (os.str ());
    return;
  }

  m_project_controller.reset ();
  m_project.reset ();

  m_file_name = file_name;
  m_project = m_project_factory->create (file_name);
  m_project_controller = m_project_ui_factory->create (m_project.get ());
  m_view->attach_content (m_project_controller->view_widget ());
}

void
MainControllerImpl::view_file_save_pressed (void)
{
  if (m_file_name.empty ())
  {
    std::string file_name;
    bool ret = m_view->get_file_to_save (&file_name);
    if (! ret)
    {
      return;
    }

    if (! can_save_to (file_name))
    {
      std::ostringstream os;
      os << "Cannot save to " << file_name;
      m_view->show_error (os.str ());
      return;
    }

    m_file_name = file_name;
  }

  do_save ();
}

void
MainControllerImpl::view_file_save_as_pressed (void)
{
  std::string file_name;
  bool ret = m_view->get_file_to_save_as (&file_name);
  if (! ret)
  {
    return;
  }

  if (! can_save_to (file_name))
  {
    std::ostringstream os;
    os << "Cannot save to " << file_name;
    m_view->show_error (os.str ());
    return;
  }

  m_file_name = file_name;
  do_save ();
}

bool
MainControllerImpl::confirm_data_discard (void)
{
  std::string file_name ("Untitled");
  std::ostringstream os;

  if (m_file_name.empty () == false)
    {
      file_name = m_file_name;
    }
  os << "The document [" << file_name << "] is modified";

  auto ret = m_view->confirm_data_discard (
    os.str (), "Do you want to discard the changes?");
  return ret;
}

bool
MainControllerImpl::can_save_to (const std::string & file_name)
{
  // todo: Check if we have write permissions to the given file
  return true;
}

void
MainControllerImpl::do_save (void)
{
  auto root = m_project->serialize ();
  {
    std::ofstream ofile (m_file_name, std::ios::binary);
    bpt::write_json (ofile, root);
  }
  m_project->clear_dirty ();
}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
