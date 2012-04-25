
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#ifndef __INCLUDED_WEBAPPS_WIKIAPP_H__
#define __INCLUDED_WEBAPPS_WIKIAPP_H__

#include <wexus/Application.h>

namespace wikiapp
{
  class WikiApp;
}

/**
 * A basic wiki application.
 *
 * @author Aleksander Demko
 */ 
class wikiapp::WikiApp : public wexus::Application
{
  public:
    WikiApp(void);
};

#endif

