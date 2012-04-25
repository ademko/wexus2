
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#include <wikiapp/WikiApp.h>

#include <wexus/VarPath.h>

using namespace wexus;

wikiapp::WikiApp::WikiApp(void)
{
  RouteBuilder b(*this);

  b.addStandardRoutes();
  b.addMatch("/", key("controller","pages") + key("action","show") + key("id", "index.txt"));
}

static wexus::RegisterApp<wikiapp::WikiApp> r1("ca.demko.wiki");

