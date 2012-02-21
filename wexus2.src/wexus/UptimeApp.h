
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#ifndef __INCLUDED_WEXUS_UPTIMEAPP_H__
#define __INCLUDED_WEXUS_UPTIMEAPP_H__

#include <wexus/Application.h>
#include <wexus/Controller.h>

namespace wexus
{
  class UptimeApp;
  class UptimeController;
}

/**
 * A small app that does reports system uptiem and other sysadmin stuff.
 *
 * @author Aleksander Demko
 */ 
class wexus::UptimeApp : public wexus::Application
{
  public:
    /// normal ctor
    UptimeApp(void);
};

class wexus::UptimeController : public wexus::Controller
{
  public:
    void index(void);
};

#endif

