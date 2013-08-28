/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO_THITTAM__9e1f695c_0ed9_11e3_a8a9_68a3c42125fd
#define HIPRO_THITTAM__9e1f695c_0ed9_11e3_a8a9_68a3c42125fd

#include <memory>
#include <string>

#include "common.h"
#include "latex.h"
#include "requirement.h"

class LatexImpl : public Latex
{
public:
  /*--- ctor/dtor ---*/
  LatexImpl (HLogPtr logger);
  ~LatexImpl () {}

  /*--- methods required by the Latex interface ---*/
  void generate_flat (
    std::shared_ptr<Requirement> req, const std::string & top_level,
    std::ofstream * ofile);

  void generate_topic_hierarchy (
    std::shared_ptr<Requirement> req, std::ofstream * ofile);

private:
  void generator (std::shared_ptr<Requirement> req,
                  const std::string & top_level, std::ofstream * ofile);

  std::string generate_list (
    Requirement::requirement_list_t::const_iterator begin,
    Requirement::requirement_list_t::const_iterator end,
    const std::map<std::string, std::string> & params);

  std::string expand_template (
    const std::string & templ_str,
    const std::map<std::string, std::string> & params);

  /* Given a string this function escapes all the special characters
   * which have meaning in LaTex */
  std::string escape_symbols (const std::string & raw_string);

  /* Python equivalent join operation
   * Courtesy: http://stackoverflow.com/a/6098417 */
  template <typename Iter>
  std::string join (Iter begin, Iter end, const std::string & separator)
  {
    std::stringstream result;
    if (begin != end)
      {
        result << *begin++;
      }
    while (begin != end)
      {
        result << separator << *begin++;
      }
    return result.str ();
  }

private:
  HLogPtr m_logger;
};

#endif // HIPRO_THITTAM__9e1f695c_0ed9_11e3_a8a9_68a3c42125fd

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
