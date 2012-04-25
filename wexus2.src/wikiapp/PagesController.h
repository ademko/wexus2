
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#ifndef __INCLUDED_WIKIAPP_PAGESCONTROLLER_H__
#define __INCLUDED_WIKIAPP_PAGESCONTROLLER_H__

#include <wexus/Controller.h>
#include <wexus/MarkDown.h>

#include <wikiapp/Page.h>

namespace wikiapp
{
  class PagesController;
}

class wikiapp::PagesController : public wexus::Controller
{
  public:
    // no index controller

    void show(void);
    void showHtml(void);

    void edit(void);
    void editHtml(void);

  protected:
    Page dm_page;
};

#endif

