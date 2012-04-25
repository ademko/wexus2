
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#include <wikiapp/Page.h>

#include <QDebug>

#include <wexus/Application.h>
#include <wexus/Context.h>

wikiapp::Page::Page(void)
  : ActiveFile(
      wexus::Context::application()->settings()["appdir"].toString(),
      QRegExp("*.txt", Qt::CaseInsensitive, QRegExp::Wildcard))
{
}

bool wikiapp::Page::onLoad(const QString &fullfilename)
{
  if (id.isEmpty())
    return true;

  title = id;

  return true;
}

