/* Copyright (C) 2008-2018 HiPro IT Solutions Private Limited,
 * Chennai. All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@hipro.co.in. */

#ifndef HIPRO__69867568_a3e0_11e8_8d95_448500dfb04c
#define HIPRO__69867568_a3e0_11e8_8d95_448500dfb04c

#include <assert.h>
#include <vector>
#include <iostream>

#include "_namespace.h"

NAMESPACE__THITTAM__START

class WBSPath
{
public:
  WBSPath ()
  {
    m_parts.reserve (10);
  }

  WBSPath (const WBSPath & other)
  {
    m_parts = other.m_parts;
  }

  WBSPath (WBSPath && other)
  {
    m_parts = std::move (other.m_parts);
  }

  const std::vector<int> & parts (void) const
  {
    return m_parts;
  }

  void push_back (int index)
  {
    m_parts.push_back (index);
  }

  size_t parts_length (void) const
  {
    return m_parts.size ();
  }

  void operator= (const WBSPath & other)
  {
    m_parts = other.parts ();
  }

  void operator= (WBSPath&& other)
  {
    m_parts = std::move (other.m_parts);
  }

  bool operator== (const WBSPath & right) const
  {
    return m_parts == right.parts ();
  }

  bool operator!= (const WBSPath & right) const
  {
    return m_parts != right.parts ();
  }

  bool empty (void) const
  {
    return m_parts.empty ();
  }

  void clear (void)
  {
    m_parts.clear ();
  }

  int operator[](size_t index) const
  {
    return m_parts[index];
  }

  int last_part (void) const
  {
    return m_parts.back ();
  }

  WBSPath next_sibling() const
  {
    assert (! m_parts.empty ());

    WBSPath new_path (*this);
    auto &x = new_path.m_parts[this->parts_length() - 1];
    x = x + 1;

    return new_path;
  }

  WBSPath previous_sibling() const
  {
    assert (! m_parts.empty ());

    WBSPath new_path (*this);
    auto &x = new_path.m_parts[this->parts_length() - 1];

    assert (x != 0);
    x = x - 1;

    return new_path;
  }

  WBSPath parent (void) const
  {
    WBSPath parent_path;
    if (! this->empty ())
    {
      for (size_t i = 0; i < (m_parts.size () - 1); ++i)
      {
        parent_path.push_back (m_parts[i]);
      }
    }
    return parent_path;
  }

private:
  std::vector<int> m_parts;
};


std::ostream& operator << (std::ostream & os, const WBSPath & path);


NAMESPACE__THITTAM__END

#endif // HIPRO__69867568_a3e0_11e8_8d95_448500dfb04c

/*
  Local Variables:
  mode: c++
  End:
*/
