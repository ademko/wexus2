
/*
 * Copyright (c) 2011 Aleksander B. Demko
 * This source code is distributed under the MIT license.
 * See the accompanying file LICENSE.MIT.txt for details.
 */

// this file is solely for doxygen
// it contains no code

/**
  \page wexususerpage Wexus User Reference

  This page contains help on various modules and
  parameters available in the stock wexusserver
  system.

  \section wexusserversec wexusserver program

  You run wexusserver like so:
  \code
    wexusserver sitedir
  \endcode

  If the sitedir doesn't contain any site.ini or app.ini files,
  it will be hosted using the basic file server module.

  \section siteinisec site.ini

  The root sitedir may contain a \b site.ini file. This file contains site-wide
  options.

    - \b httpport (default 8080) The http port to use.
    - \b httpthreads (default 4) The default number of worker threads to use.


  \section appinisec app.ini

  Any subdirectory of the sitedir may have an \b app.ini file.
  This will launch one or more apps in the give directory.

  The ini file has sections, one per app. You start a new section with [brackets].
  You can put a descriptive name within the [brackets]. The apps
  will be loaded in a sorted order.

  Common user settings:
   - \b app Required. The app type to launch. See \ref wexusappspage
   - \b headerdir (default headers/) Sets common files below.

  Common files:
   - \b database.sqlite The default sqlite3 database to use for core functions.
   - \b headers/ directory. Can contain \b header.html and \b footer.html
     which will be used as a common header and footer for all output.

  For programmers, there are some computed fields to: \b mountpoint (e.g. blog),
  \b appdir (the current dir), and \b sitedir (the sitedir)


  Example app.ini:

  \code

  [1redirector]

  app = ca.demko.redirect

  link1 = "/src dest"

  [2fileer]

  app = ca.demko.file

  [3mainblooger]

  app = ca.demko.blog

  \endcode

 */

/**
  \page wexusappspage Wexus Apps

  Stock apps that can be started by app.ini.

  \section cademkofileapp Static File Server

  Type \b ca.demko.file

  Serves static files directory the user. Useful for .html, .jpg
  (and other images), etc.

  Options:
   - \b dir1 \b dir2 \b dir3 etc. (default dir1=.) One or more directories to server.
     They are all relative to the app.ini directory.
   - \b options1 etc. (default empty). Provides a space-separated list
     of options for each corresponding directory. This string can contain
     any of the following:
       - \b IndexHtml Show index.html files if present.
       - \b AutoDirIndex Automatically generate directory listings when needed.
       - \b AllowAllMimeTypes Server all files, not just a safe subset.

  \section cademkoredirectapp Redirector

  Type \b ca.demko.redirect

  Redirects some URLs to some other URLs. Useful for transitions
  and building permanent links.

  Options:
   - \b link1 \b link2 etc. (no default, e.g. "/src dest").
     Specifies one or more redirect mappings. The mappins are of
     the form "/src dest". This will remap the given \b src
     url to the \b dest url. The dest url can be relative or
     absolute.
 
 \section cademkoblogapp Blog Host

 Type \b ca.demko.blog

 A simply web log (blog) server.

 This will server all the markdown-formatted \b .txt files in
 the \b appdir as blog entries. The filenames should be of the
 form \b YYYYMM_title.txt or \b YYYYMMDD_title.txt

 \section cademkouptimeapp Uptime Status

 A very simply app that reports the uptime and load of the machine.

 */

/**
  \page wexustutorialpage Wexus Programmer's Tutorial

  This tutorial will quickly cover how to make a quick Wexus app.
  This tutorial was made while building the wexus::UptimeApp application,
  so you can open the source files for that and follow along.

  \section newappsec Creating your Application object

  An application object represents the persistent state
  your application needs between controller calls. Many applications
  don't need to put any additional logic in their application
  objects, but they provide a handy server when they are needed.

  Create your application class by deriving from wexus::Application
  You don't need to to implement any of the methods, but you
  should probably provide a constructor:

  \code
  class wexus::UptimeApp : public wexus::Application
  {
    public:
      /// normal ctor
      UptimeApp(void);
  };
  \endcode

  You must also register your application. You do this in your .cpp
  file by instantiating a small static class, providing your 
  class type and a unique string describing the string.
  You can embed your organizations domain name (in reverse order)
  to help make your name unique.
  
  See the example:

  \code
  static wexus::RegisterApp<wexus::UptimeApp> r1("ca.demko.uptime");
  \endcode

  Note that the instance name of this object ("r1" in this case)
  is not used anywhere, so we typically give them short, arbitrary names.

  \section newcontrollersec Creating a Controller object

  Now you will need one or more controller objects.
  Typically, you register one or more methods of your
  controller objects as "actions" for URLs. When a web user
  accesses one of those URLs, the appropriate controller 
  object is instantiated and the desired method is then called.

  Controller objects are not persistent - they are instantiated
  and destroyed per call.

  Here is an example of a declaration of a Controller and one method:

  \section newrendersec Rendering HTML

  \code
  class wexus::UptimeController : public wexus::Controller
  {
    public:
      void index(void);
  };
  \endcode

  And the implementation of the method:

  \code
  void UptimeController::index(void)
  {
    htmlOutput() << "Hello, world";
  }
  \endcode

  Finally, we need to register the controller, and bind it to the application type.
  We also need to register each action method. Again, the instance names of these
  objects are arbitrary:

  \code
  static wexus::RegisterController<wexus::UptimeApp, wexus::UptimeController> r2("home");
  static wexus::RegisterAction<wexus::UptimeController, &wexus::UptimeController::index> r100("index");
  \endcode

  We can now compile and run the application. Simply:
   - Simply make an app.ini file that loads
   - Run "wexusserver dir", where dir is the directory containing the app.ini. It could be
     "." (the current directory).
   - Load http://localhost:8080/home/index in your web browser.
   - Alternatively, Load http://localhost:8080/home This works because "index"
     is the default action of any controller.
   - Alternatively, Load http://localhost:8080/ This works because "home"
     is the default controller of an application

  Here is the app.ini

  \code
  [myappinstance]
  app = ca.demko.uptime
  \endcode

 */
