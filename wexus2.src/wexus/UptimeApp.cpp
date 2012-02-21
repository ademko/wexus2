
/*
 * Copyright (c) 2012 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

#include <wexus/UptimeApp.h>

#include <wexus/HTTPServer.h>

#include <QFile>
#include <QTextStream>
#include <QDebug>

using namespace wexus;

UptimeApp::UptimeApp(void)
{
}

void UptimeController::index(void)
{
  Context::reply().setContentType("text/plain");

  double uptime = 0;    // in days

  // read in various files
  {
    QFile infile("/proc/uptime");

    if (infile.open(QIODevice::ReadOnly)) {
      QTextStream s(&infile);

      int uptime_seconds;

      s >> uptime_seconds;
      if (s.status() == QTextStream::Ok)
        uptime = uptime_seconds / (24.0 * 60 * 60);   // convert seconds to days
    }
  }

  // read the loads
  double load[3] = {0, 0, 0};

  {
    QFile infile("/proc/loadavg");

    if (infile.open(QIODevice::ReadOnly)) {
      QTextStream s(&infile);

      s >> load[0] >> load[1] >> load[2];   // ignore errors
    }
  }

  QDateTime n = QDateTime::currentDateTime();

  output() << n.toString("yyyy-MM-dd hh:mm") << " " << uptime << " " << load[0] << " " << load[1] << " " << load[2];
}

static wexus::RegisterApp<wexus::UptimeApp> r1("ca.demko.uptime");

static wexus::RegisterController<wexus::UptimeApp, wexus::UptimeController> r2("home");
static wexus::RegisterAction<wexus::UptimeController, &wexus::UptimeController::index> r100("index");

