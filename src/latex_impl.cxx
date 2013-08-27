/* Copyright (C) 2012,2013 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#include "latex_impl.h"

const char * LINK_ENTRY_TEMPLATE = "\\hyperref[req:%(reqid)]{%(reqid)}";
const char * REQ_ENTRY_TEMPLATE = \
  "\\%(top_level){%(reqid): %(title)}\n"
  "\\label{req:%(reqid)}\n"
  "\\begin{tabular}{ >{\\bfseries}r p{12cm} }\n"
  "  Id: & %(reqid) \\\\\n"
  "  Title: & %(title) \\\\\n"
  "  Description: & %(description) \\\\\n"
  "  Parent: & %(parent_link) \\\\\n"
  "  Children: & %(children_links_list) \\\\\n"
  "  Depends: & %(depends_links_list) \\\\\n"
  "\\end{tabular}\n\n";

const char * ENUM_ITEM_TEMPLATE = \
  "  \\item \\hyperref[req:%(reqid)]{%(reqid)}: %(title)\n";

LatexImpl::LatexImpl (HLogPtr logger) :
  m_logger (logger)
{

}

void
LatexImpl::generate_flat (std::shared_ptr<Requirement> req,
                          const std::string & top_level, std::ofstream * ofile)
{
  generator (req, top_level, ofile);
  auto end = req->children_cend ();
  for (auto it = req->children_cbegin (); it != end; ++it)
    {
      generate_flat (*it, top_level, ofile);
    }
}

void
LatexImpl::generate_topic_hierarchy (std::shared_ptr<Requirement> req,
                                     std::ofstream * ofile)
{
  std::map<std::string, std::string> params;
  params["reqid"] = req->id ();
  params["title"] = req->title ();
  if (req->id () != "root")
    {
      auto data = expand_template (ENUM_ITEM_TEMPLATE, params);
      ofile->write (data.c_str (), data.size ());
    }

  std::string be ("\\begin{enumerate}\n");
  std::string ee ("\\end{enumerate}\n");
  if (req->children ()->size () > 0)
    {
      ofile->write (be.c_str (), be.size ());
      auto end = req->children_cend ();
      for (auto it = req->children_cbegin (); it != end; ++it)
        {
          generate_topic_hierarchy (*it, ofile);
        }
      ofile->write (ee.c_str (), ee.size ());
    }
}

void
LatexImpl::generator (std::shared_ptr<Requirement> req,
                      const std::string & top_level, std::ofstream * ofile)
{
  if (req->id () == "root")
    {
      return;
    }
  std::map<std::string, std::string> params;
  params["reqid"] = req->id ();
  params["title"] = req->title ();
  params["description"] = req->description ();

  auto parent = req->parent ();
  std::string str_plink ("None");
  if (parent)
    {
      if (parent->id () != "root")
        {

          str_plink = expand_template (LINK_ENTRY_TEMPLATE, params);
        }
    }
  params["parent_link"] = str_plink;
  params["depends_links_list"] = generate_list (req->depends_cbegin (),
                                                req->depends_cend (), params);
  params["children_links_list"] = generate_list (req->children_cbegin (),
                                                 req->children_cend (), params);
  params["top_level"] = top_level;
  auto data = expand_template (REQ_ENTRY_TEMPLATE, params);
  ofile->write (data.c_str (), data.size ());
}

std::string
LatexImpl::generate_list (Requirement::requirement_list_t::const_iterator begin,
                          Requirement::requirement_list_t::const_iterator end,
                          const std::map<std::string, std::string> & params)
{
  std::vector<std::string> slist;
  for (auto it = begin; it != end; ++it)
    {
      slist.push_back (expand_template (LINK_ENTRY_TEMPLATE, params));
    }
  if (slist.size () == 0)
    {
      return "None";
    }
  return join (slist.begin (), slist.end (), ",");
}

std::string
LatexImpl::expand_template (const std::string & tmpl_str,
                            const std::map<std::string, std::string> & params)
{
  std::stringstream ss_data, ss_token;
  bool token_identifier_found = false;
  bool token_start_found = false;
  const char token_identifier = '%';
  const char token_start = '(';
  const char token_end = ')';
  auto it = tmpl_str.cbegin ();
  auto end = tmpl_str.cend ();
  while (it != end)
    {
      if (*it == token_identifier)
        {
          if (token_identifier_found == false)
            {
              token_identifier_found = true;
              ss_token.clear ();
              ss_token.str ("");
              ++it;
              continue;
            }
          else
            {
              ASSERT ((false), "Extra token identifier found inside a token");
            }
        }
      if (token_identifier_found)
        {
          if (token_start_found == false)
            {
              if (*it == token_start)
                {
                  token_start_found = true;
                }
              else
                {
                  ASSERT ((false), "Token start missing after identifier");
                }
            }
          else
            {
              if (*it == token_end)
                {
                  /* This will throw and die if the key is not in
                     params */
                  ss_data << params.at (ss_token.str ());
                  token_identifier_found = false;
                  token_start_found = false;
                }
              else
                {
                  ss_token << *it;
                }
            }
        }
      else
        {
          ss_data << *it;
        }
      ++it;
    }
  return ss_data.str ();
}

/*
  Local Variables:
  mode: c++
  indent-tabs-mode: nil
  End:
*/
