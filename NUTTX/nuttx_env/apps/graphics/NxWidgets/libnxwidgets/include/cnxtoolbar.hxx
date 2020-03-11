/****************************************************************************
 * apps/graphics/NxWidgets/libnxwidgets/include/cnxtoolbar.hxx
 *
 *   Copyright (C) 2012, 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX, NxWidgets, nor the names of its contributors
 *    me be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __APPS_GRAPHICS_NXWIDGETS_INCLUDECNXTOOLBAR_HXX
#define __APPS_GRAPHICS_NXWIDGETS_INCLUDECNXTOOLBAR_HXX

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>

#include <nuttx/nx/nxglib.h>
#include <nuttx/nx/nx.h>
#include <nuttx/nx/nxtk.h>

#include "ccallback.hxx"
#include "inxwindow.hxx"
#include "cnxtkwindow.hxx"

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Implementation Classes
 ****************************************************************************/

#if defined(__cplusplus)

namespace NXWidgets
{
  class CWidgetControl;
  struct SBitmap;

  /**
   * This class defines operations on a the toolbar in a framed NX window.
   * There are three instances that represent an NX window from the
   * perspective of NXWidgets.
   *
   * - There is one widget control instance per NX window,
   * - One CCallback instance per window,
   * - One window instance.
   *
   * There a various kinds of of window instances, but each inherits
   * (1) CCallback and dispatches the Windows callbacks and (2) INxWindow
   * that describes the common window behavior.
   */

  class CNxToolbar : protected CCallback, public INxWindow
  {
  private:
    CNxTkWindow    *m_nxTkWindow;    /**< Parent framed window instance. */
    NXTKWINDOW      m_hNxTkWindow;   /**< Parent framed window handle. */
    CWidgetControl *m_widgetControl; /**< Controlling widget for the toolbar */
    nxgl_coord_t    m_height;        /**< The toolbar height */

  public:

    /**
     * Constructor.  Creates an uninitialized instance of the CNxToolbar
     * object.  The open() method must be called to initialize the instance.
     *
     * @param pNxTkWindow Parent framed window instance
     * @param hNxTkWindow Parent framed window NX handler
     * @param widgetControl Controlling widget for this toolbar.
     * @param height The height of the toolbar.
     */

    CNxToolbar(CNxTkWindow *pNxTkWindow, NXTKWINDOW hNxTkWindow,
               CWidgetControl *pWidgetControl, nxgl_coord_t height);

    /**
     * Destructor.
     */

    ~CNxToolbar(void);

    /**
     * Creates a new toolbar.  Toolbar creation is separate from
     * object instantiation so that failures can be reported.
     *
     * @return True if the toolbar was successfully created.
     */

    bool open(void);

    /**
     * Each implementation of INxWindow must provide a method to recover
     * the contained CWidgetControl instance.
     *
     * @return The contained CWidgetControl instance
     */

    CWidgetControl *getWidgetControl(void) const;

    /**
     * Request the position and size information of the toolbar. The values
     * will be returned asynchronously through the client callback method.
     * The GetPosition() method may than be called to obtain the positional
     * data as provided by the callback.
     *
     * @return True on success, false on any failure.
     */

    bool requestPosition(void);

    /**
     * Get the position of the toolbar (as reported by the NX callback).
     *
     * @return The position.
     */

    bool getPosition(FAR struct nxgl_point_s *pPos);

    /**
     * Get the size of the toolbar (as reported by the NX callback).
     *
     * @return The size.
     */

    bool getSize(FAR struct nxgl_size_s *pSize);

    /**
     * Set the position and size of the toolbar.  The position of
     * the toolbar is fixed at the top of the parent framed window.
     *
     * @param pPos The new position of the toolbar.
     * @return Always returns false.
     */

    bool setPosition(FAR const struct nxgl_point_s *pPos);

    /**
     * Set the position and size of the toolbar.  The position of
     * the toolbar is fixed at the top of the parent framed window.
     *
     * @param pPos The new position of the toolbar.
     * @return Always returns false.
     */

    bool setSize(FAR const struct nxgl_size_s *pSize);

    /**
     * Bring the toolbar to the top of the display.  The toolbar is
     * a component of the containing, parent, framed window.  It
     * cannot be raised separately.
     *
     * @return Always returns false.
     */

    bool raise(void);

    /**
     * Lower the toolbar to the bottom of the display.  The toolbar is
     * a component of the containing, parent, framed window.  It
     * cannot be lowered separately.
     *
     * @return Always returns false.
     */

    bool lower(void);

    /**
     * Each window implementation also inherits from CCallback.  CCallback,
     * by default, forwards NX keyboard input to the various widgets residing
     * in the window. But NxTerm is a different usage model; In this case,
     * keyboard input needs to be directed to the NxTerm character driver.
     * This method can be used to enable (or disable) redirection of NX
     * keyboard input from the window widgets to the NxTerm
     *
     * @param handle.  The NXTERM handle.  If non-NULL, NX keyboard
     *    input will be directed to the NxTerm driver using this
     *    handle;  If NULL (the default), NX keyboard input will be
     *    directed to the widgets within the window.
     */

#ifdef CONFIG_NXTERM_NXKBDIN
    inline void redirectNxTerm(NXTERM handle)
    {
      setNxTerm(handle);
    }
#endif

    /**
     * Set an individual pixel in the toolbar with the specified color.
     *
     * @param pPos The location of the pixel to be filled.
     * @param color The color to use in the fill.
     *
     * @return True on success; false on failure.
     */

    bool setPixel(FAR const struct nxgl_point_s *pPos,
                  nxgl_mxpixel_t color);

    /**
     * Fill the specified rectangle in the toolbar with the specified color.
     *
     * @param pRect The location to be filled.
     * @param color The color to use in the fill.
     *
     * @return True on success; false on failure.
     */

    bool fill(FAR const struct nxgl_rect_s *pRect,
              nxgl_mxpixel_t color);

    /**
     * Get the raw contents of graphic memory within a rectangular region. NOTE:
     * Since raw graphic memory is returned, the returned memory content may be
     * the memory of windows above this one and may not necessarily belong to
     * this window unless you assure that this is the top window.
     *
     * @param rect The location to be copied
     * @param dest - The describes the destination bitmap to receive the
     *   graphics data.
     */

    void getRectangle(FAR const struct nxgl_rect_s *rect, struct SBitmap *dest);

    /**
     * Fill the specified trapezoidal region in the toolbar with the specified
     * color.
     *
     * @param pClip Clipping rectangle relative to toolbar (may be null).
     * @param pTrap The trapezoidal region to be filled.
     * @param color The color to use in the fill.
     *
     * @return True on success; false on failure.
     */

    bool fillTrapezoid(FAR const struct nxgl_rect_s *pClip,
                       FAR const struct nxgl_trapezoid_s *pTrap,
                       nxgl_mxpixel_t color);

    /**
     * Fill the specified line in the toolbar with the specified color.
     *
     * @param vector - Describes the line to be drawn
     * @param width  - The width of the line
     * @param color  - The color to use to fill the line
     * @param caps   - Draw a circular cap on the ends of the line to suppor
     *                 better line joins
     *
     * @return True on success; false on failure.
     */

    bool drawLine(FAR struct nxgl_vector_s *vector,
                  nxgl_coord_t width, nxgl_mxpixel_t color,
                  enum ELineCaps caps);

    /**
     * Draw a filled circle at the specified position, size, and color.
     *
     * @param center The window-relative coordinates of the circle center.
     * @param radius The radius of the rectangle in pixels.
     * @param color The color of the rectangle.
     */

    bool drawFilledCircle(struct nxgl_point_s *center, nxgl_coord_t radius,
                          nxgl_mxpixel_t color);

    /**
     * Move a rectangular region within the toolbar.
     *
     * @param pRect Describes the rectangular region to move.
     * @param pOffset The offset to move the region.
     *
     * @return True on success; false on failure.
     */

    bool move(FAR const struct nxgl_rect_s *pRect,
              FAR const struct nxgl_point_s *pOffset);

    /**
     * Copy a rectangular region of a larger image into the rectangle in the
     * specified toolbar.
     *
     * @param pDest Describes the rectangular on the display that will receive
     * the bitmap.
     * @param pSrc The start of the source image.
     * @param pOrigin the pOrigin of the upper, left-most corner of the full
     * bitmap. Both pDest and pOrigin are in toolbar coordinates, however,
     * pOrigin may lie outside of the display.
     * @param stride The width of the full source image in bytes.
     *
     * @return True on success; false on failure.
     */

    bool bitmap(FAR const struct nxgl_rect_s *pDest,
                FAR const void *pSrc,
                FAR const struct nxgl_point_s *pOrigin,
                unsigned int stride);
  };
}

#endif // __cplusplus

#endif // __APPS_GRAPHICS_NXWIDGETS_INCLUDECNXTOOLBAR_HXX

