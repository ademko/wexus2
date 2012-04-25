
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#include <wikiapp/PagesController.h>

#include <QDebug>

#include <wexus/Registry.h>
#include <wexus/Widgets.h>

#include <wikiapp/WikiApp.h>

using namespace wexus;
using namespace wikiapp;

void PagesController::show(void)
{
  if (!dm_page.exists(params["id"])) {
//TODO FIX THIS SENDING THING
//SEE WHY ID ISNG GOING
    //redirectTo(pathTo<PagesController>(&PagesController::edit, params));
    redirectTo(pathTo(&PagesController::edit, params));
    return;
  }

  dm_page.find(params["id"]);

  showHtml();
}

void PagesController::edit(void)
{
  if (dm_page.exists(params["id"]))
    dm_page.find(params["id"]);

  editHtml();
}

static wexus::RegisterController<WikiApp, PagesController> r1("pages");

static wexus::RegisterAction<PagesController, &PagesController::show> r101("show");
static wexus::RegisterAction<PagesController, &PagesController::edit> r102("edit");

