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
  std::vector<WBS::Path> && path_list)
{
  if (path_list.empty ())
  {
    return;
  }

  m_view->enable_cut (true);
  m_view->enable_copy (true);
  m_view->enable_delete (true);
  m_view->enable_add_sibling (true);
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

  m_selection = path_list;
}

void
WBSControllerImpl::view_node_activated (const WBS::Path & path)
{

}

void
WBSControllerImpl::view_add_child_clicked (void)
{
  WBS::Path parent;
  if (! m_selection.empty ())
  {
    parent = m_selection[0];
  }
  auto child = m_wbs->add_child (parent);
  m_view->add_child (parent, child->id ());
}

void
WBSControllerImpl::view_add_sibling_clicked (void)
{
  ASSERT ((! m_selection.empty ()), "No selection to add-sibling");

  auto child = m_wbs->add_sibling (m_selection[0]);
  m_view->add_sibling (m_selection[0], child->id ());
}

void
WBSControllerImpl::view_indent_clicked (void)
{
  ASSERT ((! m_selection.empty ()), "No selection to indent");

  if (m_wbs->is_first_child (m_selection[0]))
  {
    // todo: beep/status message stating error
    return;
  }

  auto selection = std::move (m_selection);
  auto first_task_path = selection[0];
  auto first_task = m_wbs->get_task (first_task_path);
  auto orig_parent = first_task->parent ();
  auto orig_parent_path = selection[0].parent ();
  auto new_parent_path = selection[0].previous_sibling ();
  auto new_parent = m_wbs->get_task (new_parent_path);

  std::vector<std::shared_ptr<Task>> to_indent;
  size_t path_count = 0;
  for (auto& path : selection)
  {
    auto parent = path.parent ();
    if (parent != orig_parent_path)
    {
      break;
    }

    auto task = m_wbs->get_task (path);
    to_indent.push_back (task);
    path_count ++;
  }

  for (auto task: to_indent)
  {
    m_view->remove (first_task_path);
    orig_parent->remove_child (task);
    new_parent->add_child (task);
    m_view->add_child (
      new_parent_path, task->id (), task->title (), task->work ());
  }
}

void
WBSControllerImpl::view_unindent_clicked (void)
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
