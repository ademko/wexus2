
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#ifndef __INCLUDED_WIKIAPP_PAGE_H__
#define __INCLUDED_WIKIAPP_PAGE_H__

#include <wexus/ActiveFile.h>

namespace wikiapp
{
  class Page;
}

class wikiapp::Page : public wexus::ActiveFile
{
  public:
    // this is just the id (filename) with some translations
    // like underscores to spaces
    QString title;

  public:
    /// uninitilized page
    Page(void);

  protected:
    virtual bool onLoad(const QString &fullfilename);
};

#endif

