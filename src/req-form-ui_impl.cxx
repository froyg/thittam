/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include <gtkmm.h>

#include <boost/filesystem.hpp>

#include "req-form-ui_impl.h"

namespace bofs = ::boost::filesystem;

ReqFormUIImpl::ReqFormUIImpl (HLogPtr logger) :
  m_logger (logger)
{
  bofs::path builder_file (bofs::path (RESOURCE_DIR) /
                           bofs::path ("req-form.glade"));
  auto builder = Gtk::Builder::create_from_file (builder_file.c_str ());
  Gtk::Dialog * dlg;
  builder->get_widget ("dlg-requirement-form", dlg);
  m_dlg_main = std::unique_ptr<Gtk::Dialog> (dlg);

  m_dlg_main->add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  m_dlg_main->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  m_dlg_main->set_default_response (Gtk::RESPONSE_OK);

  builder->get_widget ("form-lbl-reqid", m_lbl_reqid);
  builder->get_widget ("form-ent-title", m_ent_title);
  Gtk::TextView * tv;
  builder->get_widget ("form-tv-description", tv);
  m_tb_description = tv->get_buffer ();
}

int
ReqFormUIImpl::show (void)
{
  m_lbl_reqid->set_label ("New");
  m_ent_title->set_text ("");
  m_tb_description->set_text ("");
  return m_dlg_main->run ();
}

int
ReqFormUIImpl::show (Requirement::ptr_t req)
{
  m_lbl_reqid->set_label (req->id ());
  m_ent_title->set_text (req->title ());
  m_tb_description->set_text (req->description ());
  return m_dlg_main->run ();
}

std::string
ReqFormUIImpl::title (void)
{
  return m_ent_title->get_text ();
}

std::string
ReqFormUIImpl::description (void)
{
  auto start_it = m_tb_description->begin ();
  auto end_it = m_tb_description->end ();
  return m_tb_description->get_text (start_it, end_it, false);
}

void
ReqFormUIImpl::hide (void)
{
  m_dlg_main->hide ();
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
