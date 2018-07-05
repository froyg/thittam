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
  // auto path = m_model->convert_gtk_tree_iter_to_wbs_path (it);
  // m_current_selection = path;

  // if (m_wbs->is_first_child (path))
  // {
  //   m_view->enable_indent_button (false);
  //   m_view->enable_move_up_button (false);
  // }
  // else
  // {
  //   m_view->enable_indent_button (true);
  //   m_view->enable_move_up_button (true);
  // }

  // if (m_wbs->is_last_child (path))
  // {
  //   m_view->enable_move_down_button (false);
  // }
  // else
  // {
  //   m_view->enable_move_down_button (true);
  // }

  // if (m_wbs->is_top_level (path))
  // {
  //   m_view->enable_unindent_button (false);
  // }
  // else
  // {
  //   m_view->enable_unindent_button (true);
  // }
}

void
WBSControllerImpl::view_node_activated (const Task::Path & path)
{

}

void
WBSControllerImpl::view_add_child_clicked (void)
{

}

void
WBSControllerImpl::view_add_sibling_clicked (void)
{

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
WBSControllerImpl::view_indent_clicked (void)
{

}

void
WBSControllerImpl::view_unindent_clicked (void)
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
