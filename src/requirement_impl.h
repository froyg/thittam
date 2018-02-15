/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd
#define HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd

#include <vector>
#include <cmath>

#include <boost/algorithm/string.hpp>

#include "common.h"
#include "requirement.h"
#include "log.h"

class RequirementImpl : public std::enable_shared_from_this<RequirementImpl>,
                        public Requirement
{
public:
  /* ------- ctor/dtor ----------- */
  RequirementImpl (hipro::log::Logger* logger)
  : logger (logger)
  { }
  ~RequirementImpl () {}

  /* ------- Methods required by the interface ----------- */
  const std::string & id (void) const
  {
    return m_id;
  }

  const std::string & title (void) const
  {
    return m_title;
  }

  const std::string & description (void) const
  {
    return m_description;
  }

  const std::string & work (void) const
  {
    return m_work;
  }

  int work_in_minutes (void) const
  {
    return m_work_minutes;
  }

  std::shared_ptr<Requirement> parent (void) const
  {
    return m_parent.lock ();
  }

  bool has_children (void) const
  {
    return m_children.size () > 0;
  }

  void set_title (const std::string & title)
  {
    m_title = title;
  }

  void set_description (const std::string & description)
  {
    m_description = description;
  }

  void set_work (const std::string & work)
  {
    /* Parse the string and calaculate work in minutes and save
     * it. Fix the string if the string has some fixable errors. Else
     * set the work string as 1d */
    std::stringstream ss;
    auto it = work.cbegin ();
    auto end = work.cend ();
    int minutes = 0;
    bool fix_work_string = false;
    try
      {
        while (it != end)
          {
            float val = 0;
            if (*it == 'd')
              {
                /* Days: 8 hours per day */
                val = std::stof (ss.str ());
                ss.str ("");
                if (val <= 0)
                  {
                    fix_work_string = true;
                  }
                else
                  {
                    minutes += val * 8 * 60;
                  }
              }
            else if (*it == 'w')
              {
                /* Week: 5 days per week */
                val = std::stof (ss.str ());
                ss.str ("");
                if (val <= 0)
                  {
                    fix_work_string = true;
                  }
                else
                  {
                    minutes += val * 5 * 8 * 60;
                  }
              }
            else if (*it == 'm')
              {
                /* Month: 22 days per month */
                val = std::stof (ss.str ());
                ss.str ("");
                if (val <= 0)
                  {
                    fix_work_string = true;
                  }
                else
                  {
                    minutes += val * 22 * 8 * 60;
                  }
              }
            else if (*it == 'h')
              {
                /* Hours: 1 hour is standard 60 minutes */
                val = std::stof (ss.str ());
                ss.str ("");
                if (val <= 0)
                  {
                    fix_work_string = true;
                  }
                else
                  {
                    minutes +=  val * 60;
                  }
              }
            else
              {
                ss << *it;
              }
            ++it;
          }
        m_work = work;
      }
    catch ( ... )
      {
        /* std::stof will throw two exceptions namely
         * std::invalid_argument, std::out_of_range. So we catch all
         * exceptions here. For this condition we set the value to 1
         * day */
        minutes = 1 * 8 * 60;
        m_work = "1d";
      }
    if (minutes == 0)
      {
        /* This can occur when the user gives just spaces, stof will
           not fail rather it will give zero */
        minutes = 1 * 8 * 60;
        m_work = "1d";
      }
    else
      {
        if (fix_work_string)
          {
            /* minutes calculated is not zero but there are some empty
               parts in the string we have to fix it. Eg: " m 5d" */
            m_work = fix_string (work);
          }
      }

    m_work_minutes = minutes;
  }

  requirement_list_t::const_iterator children_cbegin (void) const
  {
    return m_children.cbegin ();
  }

  requirement_list_t::const_iterator children_cend (void) const
  {
    return m_children.cend ();
  }

  requirement_list_t::const_iterator depends_cbegin (void) const
  {
    return m_depends.cbegin ();
  }

  requirement_list_t::const_iterator depends_cend (void) const
  {
    return m_depends.cend ();
  }

  boost::property_tree::ptree dump (void)
  {
    boost::property_tree::ptree pt;
    pt.put ("reqid", m_id);
    pt.put ("title", m_title);
    pt.put ("description", m_description);
    pt.put ("work", m_work);
    boost::property_tree::ptree child_array;
    for (auto req : m_children)
      {
        child_array.push_back
          (std::make_pair ("", boost::property_tree::ptree(req->id ())));
      }
    pt.put_child ("children", child_array);

    boost::property_tree::ptree depend_array;
    for (auto req : m_depends)
      {
        depend_array.push_back
          (std::make_pair ("", boost::property_tree::ptree(req->id ())));
      }
    pt.put_child ("depends", depend_array);
    return pt;
  }

  void set_id (const std::string & id)
  {
    m_id = id;
  }

  void set_parent (std::shared_ptr<Requirement> parent)
  {
    m_parent = parent;
  }

  requirement_list_t * children (void)
  {
    return &m_children;
  }

  requirement_list_t * depends (void)
  {
    return &m_depends;
  }

private:
  std::string fix_string (const std::string & work_str)
  {
    std::stringstream ss_part, ss_full;
    auto it = work_str.cbegin ();
    auto end = work_str.cend ();
    /* If the conversion fails this method will die */
    while (it != end)
      {
        float val = 0;
        if ((*it == 'd') || (*it == 'w') || (*it == 'm') || (*it == 'h'))
          {
            auto val_str = ss_part.str ();
            ss_part.str ("");
            ss_part.clear ();
            val = std::stof (val_str);
            if (val > 0)
              {
                ss_full << val_str << *it;
              }
            else
              {
                ss_full << " ";
              }
          }
        else
          {
            ss_part << *it;
          }
        ++it;
      }
    auto work = ss_full.str ();
    boost::algorithm::trim (work);
    return work;
  }

private:
  hipro::log::Logger* logger;

  std::string m_id;
  std::string m_title;
  std::string m_description;
  std::string m_work;
  int m_work_minutes;

  std::weak_ptr<Requirement> m_parent;
  std::vector<std::shared_ptr<Requirement>> m_children;
  std::vector<std::shared_ptr<Requirement>> m_depends;
};

class RequirementFactoryImpl : public RequirementFactory
{
public:
  RequirementFactoryImpl (hipro::log::Logger* logger)
  : logger (logger)
  {
  }

  std::shared_ptr<Requirement> create (void)
  {
    return std::make_shared<RequirementImpl> (logger);
  }

  std::shared_ptr<Requirement>
  create (const std::string & title, const std::string & description,
          const std::string & work)
  {
    auto obj = std::make_shared<RequirementImpl> (logger);
    obj->set_title (title);
    obj->set_description (description);
    obj->set_work (work);
    return obj;
  }

  std::shared_ptr<Requirement>
  create (const std::string & id, const std::string & title,
          const std::string & description, const std::string & work)
  {
    auto obj = std::make_shared<RequirementImpl> (logger);
    obj->set_id (id);
    obj->set_title (title);
    obj->set_description (description);
    obj->set_work (work);
    return obj;
  }

private:
  hipro::log::Logger* logger;
};

#endif // HIPRO_THITTAM__5dd9f5ac_00e6_11e3_beb6_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  tab-width: 4
  c-file-style: "gnu"
  End:
*/
