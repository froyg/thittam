/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd
#define HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>

class Requirement
{
public:
  typedef std::vector< std::shared_ptr<Requirement> > requirement_list_t;

public:
  /*--- Public interface ---*/
  virtual const std::string & id (void) const = 0;
  virtual const std::string & title (void) const = 0;
  virtual const std::string & description (void) const = 0;
  virtual const std::string & work (void) const = 0;
  virtual int work_in_minutes (void) const = 0;
  virtual std::shared_ptr<Requirement> parent (void) const = 0;
  virtual bool has_children (void) const = 0;

  virtual void set_title (const std::string & title) = 0;
  virtual void set_description (const std::string & description) = 0;
  virtual void set_work (const std::string & work) = 0;

  virtual requirement_list_t::const_iterator children_cbegin (void) const = 0;
  virtual requirement_list_t::const_iterator children_cend (void) const = 0;
  virtual requirement_list_t::const_iterator depends_cbegin (void) const = 0;
  virtual requirement_list_t::const_iterator depends_cend (void) const = 0;

  virtual boost::property_tree::ptree dump (void) = 0;

  /*--- Interface for ReqTree ---*/
  virtual void set_id (const std::string & id) = 0;
  virtual void set_parent (std::shared_ptr<Requirement> parent) = 0;
  virtual requirement_list_t * children (void) = 0;
  virtual requirement_list_t * depends (void) = 0;

  /* virtual dtor */
  virtual ~Requirement () {}
};

class RequirementFactory
{
public:
  /* virtual dtor */
  virtual ~RequirementFactory () {}

  virtual std::shared_ptr<Requirement> create (void) = 0;

  virtual std::shared_ptr<Requirement>
  create (const std::string & title, const std::string & description,
          const std::string & work) = 0;

  virtual std::shared_ptr<Requirement>
  create (const std::string & id, const std::string & title,
          const std::string & description, const std::string & work) = 0;

};

#endif // HIPRO_THITTAM__7c81bf88_fe59_11e2_934c_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
