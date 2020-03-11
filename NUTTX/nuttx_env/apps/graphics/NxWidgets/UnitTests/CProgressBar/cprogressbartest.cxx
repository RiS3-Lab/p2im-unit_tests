/////////////////////////////////////////////////////////////////////////////
// apps/graphics/NxWidgets/UnitTests/ProgressBar/cprogressbartest.cxx
//
//   Copyright (C) 2012 Gregory Nutt. All rights reserved.
//   Author: Gregory Nutt <gnutt@nuttx.org>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the
//    distribution.
// 3. Neither the name NuttX, NxWidgets, nor the names of its contributors
//    me be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
// AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Included Files
/////////////////////////////////////////////////////////////////////////////

#include <nuttx/config.h>

#include <nuttx/init.h>
#include <cstdio>
#include <cerrno>
#include <debug.h>

#include <nuttx/nx/nx.h>
#include <nuttx/nx/nxfonts.h>

#include "nxconfig.hxx"
#include "cbgwindow.hxx"
#include "cprogressbartest.hxx"

/////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Private Classes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Private Data
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Public Data
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Public Function Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CProgressBarTest Method Implementations
/////////////////////////////////////////////////////////////////////////////

// CProgressBarTest Constructor

CProgressBarTest::CProgressBarTest()
{
  // Initialize state data

  m_widgetControl = (CWidgetControl *)NULL;
  m_bgWindow      = (CBgWindow *)NULL;
}

// CProgressBarTest Descriptor

CProgressBarTest::~CProgressBarTest(void)
{
  disconnect();
}

// Connect to the NX server

bool CProgressBarTest::connect(void)
{
  // Connect to the server

  bool nxConnected = CNxServer::connect();
  if (nxConnected)
    {
      // Set the background color

      if (!setBackgroundColor(CONFIG_CPROGRESSBARTEST_BGCOLOR))
        {
          printf("CProgressBarTest::connect: setBackgroundColor failed\n");
        }
    }

  return nxConnected;
}

// Disconnect from the NX server

void CProgressBarTest::disconnect(void)
{
  // Close the window

  if (m_bgWindow)
    {
      delete m_bgWindow;
      m_bgWindow = (CBgWindow *)NULL;
    }

  // Free the widget control instance

  if (m_widgetControl)
    {
      delete m_widgetControl;
      m_widgetControl = (CWidgetControl *)NULL;
    }

  // And disconnect from the server

  CNxServer::disconnect();
}

// Create the background window instance.  This function illustrates
// the basic steps to instantiate any window:
//
// 1) Create a dumb CWigetControl instance
// 2) Pass the dumb CWidgetControl instance to the window constructor
//    that inherits from INxWindow.  This will "smarten" the CWidgetControl
//    instance with some window knowlede
// 3) Call the open() method on the window to display the window.
// 4) After that, the fully smartened CWidgetControl instance can
//    be used to generate additional widgets by passing it to the
//    widget constructor

bool CProgressBarTest::createWindow(void)
{
  // Initialize the widget control using the default style

  m_widgetControl = new CWidgetControl((CWidgetStyle *)NULL);

  // Get an (uninitialized) instance of the background window as a class
  // that derives from INxWindow.

  m_bgWindow = getBgWindow(m_widgetControl);
  if (!m_bgWindow)
    {
      printf("CProgressBarTest::createWindow: Failed to create CBgWindow instance\n");
      disconnect();
      return false;
    }

  // Open (and initialize) the window

  bool success = m_bgWindow->open();
  if (!success)
    {
      printf("CProgressBarTest::createWindow: Failed to open background window\n");
      disconnect();
      return false;
    }

  return true;
}

// Create a bar in the center of the window

CProgressBar *CProgressBarTest::createProgressBar(void)
{
  // Get the size of the display

  struct nxgl_size_s windowSize;
  if (!m_bgWindow->getSize(&windowSize))
    {
      printf("CProgressBarTest::createProgressBar: Failed to get window size\n");
      disconnect();
      return false;
    }

  // Put the bar in the center of the display

  nxgl_coord_t barWidth  = windowSize.w >> 1;
  nxgl_coord_t barX      = windowSize.w >> 2;

  nxgl_coord_t barHeight = 16;
  nxgl_coord_t barY      = (windowSize.h - barHeight) >> 1;

  // Create the bar

  CProgressBar *bar = new CProgressBar(m_widgetControl,
                                       barX, barY,
                                       barWidth, barHeight);
  if (!bar)
    {
      printf("CProgressBarTest::createProgressBar: Failed to create CProgressBar\n");
      disconnect();
    }
  return bar;
}

// (Re-)draw the bar.

void CProgressBarTest::showProgressBar(CProgressBar *bar)
{
  bar->enable();        // Un-necessary, the widget is enabled by default
  bar->enableDrawing();
  bar->redraw();
}
