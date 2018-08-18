/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "wbs-controller_impl.h"

NAMESPACE__THITTAM__START

WBSControllerImpl::WBSControllerImpl (hipro::log::Logger* logger)
  : logger (logger)
{

}

void
WBSControllerImpl::view_node_selected (
  std::vector<Task::Path> && path_list)
{
  if (path_list.empty ())
  {
    return;
  }

  m_view->enable_cut (true);
  m_view->enable_copy (true);
  m_view->enable_delete (true);
  m_view->enable_indent_task (true);
  m_view->enable_unindent_task (true);
  m_view->enable_up (true);
  m_view->enable_down (true);

  if (path_list.size () > 1)
  {
    m_view->enable_paste (false);
  }
  else
  {
    m_view->enable_paste (true);
  }

  m_selected_path = path_list[0];
}

void
WBSControllerImpl::view_node_activated (const Task::Path & path)
{

}

void
WBSControllerImpl::view_add_child_clicked (void)
{
  Log_I << "Adding child";
  m_view->add_child (m_selected_path);
  m_view->renumber ();

  // m_wbs->add_child (m_selected_path);
  // m_wbs->renumber ();
}

void
WBSControllerImpl::view_add_sibling_clicked (void)
{

}

void
WBSControllerImpl::view_indent_clicked (void)
{
  Log_I << "[WBSControllerImpl] Indent";

  assert (m_selected_path.parts_length() != 0);
  if (m_selected_path[m_selected_path.parts_length() - 1] == 0)
  {
    // TODO: Put this message in status bar of thittam
    Log_I << "Can't indent first element";
    return;
  }

  m_view->indent(m_selected_path);

  m_view->renumber();
}

void
WBSControllerImpl::view_unindent_clicked (void)
{
  Log_I << "[WBSControllerImpl] Unindent";

  assert (m_selected_path.parts_length() != 0);
  if (m_selected_path.parts_length() < 2)
  {
    // TODO: Put this message in status bar of thittam
    Log_I << "Can't unindent level 1 task";
    return;
  }

  m_view->unindent(m_selected_path);

  m_view->renumber();
}

void
WBSControllerImpl::view_cut_clicked (void)
{

}

void
WBSControllerImpl::view_copy_clicked (void)
{

}

void
WBSControllerImpl::view_paste_clicked (void)
{

}

void
WBSControllerImpl::view_delete_clicked (void)
{

}

void
WBSControllerImpl::view_up_clicked (void)
{

}

void
WBSControllerImpl::view_down_clicked (void)
{

}

void
WBSControllerImpl::view_title_changed (const std::string & text)
{

}

void
WBSControllerImpl::view_effort_changed (const std::string & text)
{

}

NAMESPACE__THITTAM__END

/*
  Local Variables:
  mode: c++
  End:
*/
