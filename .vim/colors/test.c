/*--------------------------------*-C-*---------------------------------*
 * File:    command.c
 *----------------------------------------------------------------------*
 *
 * All portions of code are copyright by their respective author/s.
 * Copyright (c) 1992        John Bovey <jdb@ukc.ac.uk>
 * Copyright (c) 1994        Robert Nation <nation@rocket.sanders.lockheed.com>
 * Copyright (c) 1995        Garrett D'Amore <garrett@netcom.com>
 * Copyright (c) 1995        Steven Hirsch <hirsch@emba.uvm.edu>
 * Copyright (c) 1995        Jakub Jelinek <jj@gnu.ai.mit.edu>
 * Copyright (c) 1997        MJ Olesen <olesen@me.queensu.ca>
 * Copyright (c) 1997        Raul Garcia Garcia <rgg@tid.es>
 * Copyright (c) 1997,1998   Oezguer Kesim <kesim@math.fu-berlin.de>
 * Copyright (c) 1998-2001   Geoff Wing <gcw@pobox.com>
 * Copyright (c) 1998        Alfredo K. Kojima <kojima@windowmaker.org>
 * Copyright (c) 2001        Marius Gedminas <marius.gedminas@uosis.mif.vu.lt>
 * Copyright (c) 2003        Rob McMullen <robm@flipturn.org>
 * Copyright (c) 2004        Terry Griffin <griffint@pobox.com>
 * Copyright (c) 2005        Johann 'Mykraverk' Oskarsson
 *                                              <johann@myrkraverk.com>
 * Copyright (c) 2004-2006   Jingmin Zhou <jimmyzhou@users.sourceforge.net>
 * Copyright (c) 2005-2006   Gautam Iyer <gi1242@users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *----------------------------------------------------------------------*/

#include "../config.h"
#include "rxvt.h"
+--  3 lines: #if 0 OBSOLETE HOTKEY CODE ---------------------------------------

#ifdef DEBUG_VERBOSE
# define DEBUG_LEVEL 1
#else
# define DEBUG_LEVEL 0
#endif


#if DEBUG_LEVEL
# define DBG_MSG(d,x) if(d <= DEBUG_LEVEL) fprintf x
#else
# define DBG_MSG(d,x)
#endif


#ifdef USE_DEADKEY
/*
** Deadkey sequences table.
*/
// {{{1
typedef struct _DeadKeyChar {
    KeySym      ks;     /* keysym */
    KeySym      dk;     /* accent */
    KeySym      ach;    /* accent keysym */
} DeadKeyChar;
// }}}1
static DeadKeyChar  dkc_tab[] = {
    {XK_A, XK_grave,        XK_Agrave},
    {XK_A, XK_acute,        XK_Agrave},
    {XK_A, XK_apostrophe,   XK_Aacute},
    {XK_A, XK_asciicircum,  XK_Acircumflex},
    {XK_A, XK_asciitilde,   XK_Atilde},
    {XK_A, XK_quotedbl,     XK_Adiaeresis},

    {XK_a, XK_grave,        XK_agrave},
    {XK_a, XK_acute,        XK_agrave},
    {XK_a, XK_apostrophe,   XK_aacute},
    {XK_a, XK_asciicircum,  XK_acircumflex},
    {XK_a, XK_asciitilde,   XK_atilde},
    {XK_a, XK_quotedbl,     XK_adiaeresis},

    {XK_C, XK_grave,        XK_Ccedilla},
    {XK_C, XK_acute,        XK_Ccedilla},

    {XK_c, XK_grave,        XK_ccedilla},
    {XK_c, XK_acute,        XK_ccedilla},

    {XK_E, XK_grave,        XK_Egrave},
    {XK_E, XK_acute,        XK_Eacute},
    {XK_E, XK_apostrophe,   XK_Eacute},
    {XK_E, XK_asciicircum,  XK_Ecircumflex},
    {XK_E, XK_quotedbl,     XK_Ediaeresis},

    {XK_e, XK_grave,        XK_egrave},
    {XK_e, XK_acute,        XK_eacute},
    {XK_e, XK_apostrophe,   XK_eacute},
    {XK_e, XK_asciicircum,  XK_ecircumflex},
    {XK_e, XK_quotedbl,     XK_ediaeresis},

    {XK_I, XK_grave,        XK_Igrave},
    {XK_I, XK_acute,        XK_Iacute},
    {XK_I, XK_apostrophe,   XK_Iacute},
    {XK_I, XK_asciicircum,  XK_Icircumflex},
    {XK_I, XK_quotedbl,     XK_Idiaeresis},

    {XK_i, XK_grave,        XK_igrave},
    {XK_i, XK_acute,        XK_iacute},
    {XK_i, XK_apostrophe,   XK_iacute},
    {XK_i, XK_asciicircum,  XK_icircumflex},
    {XK_i, XK_quotedbl,     XK_idiaeresis},

    {XK_N, XK_asciitilde,   XK_Ntilde},
    {XK_n, XK_asciitilde,   XK_ntilde},

    {XK_O, XK_grave,        XK_Ograve},
    {XK_O, XK_acute,        XK_Oacute},
    {XK_O, XK_apostrophe,   XK_Oacute},
    {XK_O, XK_asciicircum,  XK_Ocircumflex},
    {XK_O, XK_asciitilde,   XK_Otilde},
    {XK_O, XK_quotedbl,     XK_Odiaeresis},

    {XK_o, XK_grave,        XK_ograve},
    {XK_o, XK_acute,        XK_oacute},
    {XK_o, XK_apostrophe,   XK_oacute},
    {XK_o, XK_asciicircum,  XK_ocircumflex},
    {XK_o, XK_asciitilde,   XK_otilde},
    {XK_o, XK_quotedbl,     XK_odiaeresis},

    {XK_U, XK_grave,        XK_Ugrave},
    {XK_U, XK_acute,        XK_Uacute},
    {XK_U, XK_apostrophe,   XK_Uacute},
    {XK_U, XK_asciicircum,  XK_Ucircumflex},
    {XK_U, XK_quotedbl,     XK_Udiaeresis},

    {XK_u, XK_grave,        XK_ugrave},
    {XK_u, XK_acute,        XK_uacute},
    {XK_u, XK_apostrophe,   XK_uacute},
    {XK_u, XK_asciicircum,  XK_ucircumflex},
    {XK_u, XK_quotedbl,     XK_udiaeresis},

    {XK_Y, XK_acute,        XK_Yacute},
    {XK_Y, XK_apostrophe,   XK_Yacute},

    {XK_y, XK_acute,        XK_yacute},
    {XK_y, XK_apostrophe,   XK_yacute},
    {XK_y, XK_quotedbl,     XK_ydiaeresis},

    {0, 0, 0},
};

# define DEADKEY_CHAR_NUMBER        (int)((sizeof(dkc_tab) / sizeof(DeadKeyChar)))

#endif  /* USE_DEADKEY */



/*--------------------------------------------------------------------*
 *         BEGIN `INTERNAL' ROUTINE PROTOTYPES                        *
 *--------------------------------------------------------------------*/
void           rxvt_process_keypress         (rxvt_t*, XKeyEvent*);
void           rxvt_clean_cmd_page           (rxvt_t*);
int            rxvt_find_cmd_child           (rxvt_t*, int*);
void           rxvt_check_cmdbuf             (rxvt_t*, int);
unsigned char  rxvt_cmd_getc                 (rxvt_t*, int* page);
#ifdef POINTER_BLANK
void           rxvt_pointer_blank            (rxvt_t*, int);
#endif
void           rxvt_mouse_report             (rxvt_t*, const XButtonEvent*);
void           rxvt_set_bg_focused           (rxvt_t*, int, Bool);
#if defined(MOUSE_WHEEL) && defined(MOUSE_SLIP_WHEELING)
void           rxvt_process_keyrelease       (rxvt_t*, XKeyEvent*);
#endif
void           rxvt_scrollbar_dispatcher     (rxvt_t*, int, XButtonEvent*);
void           rxvt_process_buttonpress      (rxvt_t*, int, XButtonEvent*);
#ifdef MOUSE_WHEEL
void           rxvt_process_wheel_button     (rxvt_t*, int, XButtonEvent*);
#endif
void           rxvt_process_buttonrelease    (rxvt_t*, int, XButtonEvent*);
void           rxvt_process_clientmessage    (rxvt_t*, XClientMessageEvent*);
void           rxvt_process_visibilitynotify (rxvt_t*, XVisibilityEvent*);
#ifdef MONITOR_ENTER_LEAVE
void           rxvt_process_enter            (rxvt_t*, XCrossingEvent*);
void           rxvt_process_leave            (rxvt_t*, XCrossingEvent*);
#endif
void           rxvt_process_focusin          (rxvt_t*, XFocusChangeEvent*);
void           rxvt_process_focusout         (rxvt_t*, XFocusChangeEvent*);
int            rxvt_calc_colrow              (rxvt_t* r, unsigned int width, unsigned int height);
void           rxvt_resize_sub_windows       (rxvt_t* r);
void           rxvt_resize_on_configure      (rxvt_t* r, unsigned int width, unsigned int height);
#ifndef NO_FRILLS
Bool           getWMStruts                   (Display *dpy, Window w, CARD32 *left, CARD32 *right, CARD32 *top, CARD32 *bottom);
#endif
void           rxvt_process_configurenotify  (rxvt_t*, XConfigureEvent*);
void           rxvt_process_selectionnotify  (rxvt_t*, XSelectionEvent*);
void           rxvt_process_propertynotify   (rxvt_t*, XEvent*);
void           rxvt_process_expose           (rxvt_t*, XEvent*);
void           rxvt_process_motionnotify     (rxvt_t*, XEvent*);
void           rxvt_process_x_event          (rxvt_t*, XEvent*);
#ifdef PRINTPIPE
void           rxvt_process_print_pipe       (rxvt_t*, int);
#endif
void           rxvt_process_nonprinting      (rxvt_t*, int, unsigned char);
void           rxvt_process_escape_vt52      (rxvt_t*, int, unsigned char);
void           rxvt_process_escape_seq       (rxvt_t*, int);
void           rxvt_process_csi_seq          (rxvt_t*, int);
#ifndef NO_FRILLS
void           rxvt_process_window_ops       (rxvt_t*, int, const int*, unsigned int);
#endif
unsigned char* rxvt_get_to_st                (rxvt_t*, int, unsigned char*);
void           rxvt_process_dcs_seq          (rxvt_t*, int);
void           rxvt_process_osc_seq          (rxvt_t*, int);
void           rxvt_xwsh_seq                 (rxvt_t*, int, const char*);
void           rxvt_process_xwsh_seq         (rxvt_t*, int);
int            rxvt_privcases                (rxvt_t*, int, int, unsigned long);
void           rxvt_process_terminal_mode    (rxvt_t*, int, int, int, unsigned int, const int*);
void           rxvt_process_sgr_mode         (rxvt_t*, int, unsigned int, const int*);
void           rxvt_process_graphics         (rxvt_t*, int);
/*--------------------------------------------------------------------*
 *         END   `INTERNAL' ROUTINE PROTOTYPES                        *
 *--------------------------------------------------------------------*/



+--630 lines: Process keysyms between 0xff00 and 0xffff ------------------------


+--523 lines: Convert the keypress event into a string -------------------------


+--887 lines: rxvt_cmd_write(), rxvt_cmd_getc() --------------------------------


/* EXTPROTO */
void
rxvt_pointer_unblank(rxvt_t* r, int page)
{
    DBG_MSG( 1, ( stderr, "Unblanking pointer\n"));
    XDefineCursor(r->Xdisplay, PVTS(r, page)->vt, r->term_pointer);
    rxvt_recolour_cursor(r);
#ifdef POINTER_BLANK
    if (!(r->Options & Opt_pointerBlank))
        return;   /* no need to do anything */

    PVTS(r, page)->hidden_pointer = 0;

    if (r->h->pointerBlankDelay > 0)
    {
        struct timeval  tp;

        (void)gettimeofday(&tp, NULL);
        r->h->lastmotion.tv_sec = tp.tv_sec;
        r->h->lastmotion.tv_usec = tp.tv_usec;
    }
#endif
}


#ifdef POINTER_BLANK
/* INTPROTO */
void
rxvt_pointer_blank(rxvt_t* r, int page)
{
    DBG_MSG(1, ( stderr, "Blanking pointer\n"));
    if ((r->Options & Opt_pointerBlank) && (None != r->h->blank_pointer))
    {
        XDefineCursor(r->Xdisplay, PVTS(r, page)->vt,
            r->h->blank_pointer);
        XFlush(r->Xdisplay);
        PVTS(r, page)->hidden_pointer = 1;
    }
}
#endif


/* INTPROTO */
void
rxvt_mouse_report(rxvt_t* r, const XButtonEvent *ev)
{
    int             button_number, key_state = 0;
    int             x, y;

    x = ev->x;
    y = ev->y;
    rxvt_pixel_position(r, &x, &y);

    if (r->h->MEvent.button == AnyButton)
    {
        button_number = 3;
    }
    else
    {
        button_number = r->h->MEvent.button - Button1;
        /* add 0x3D for wheel events, like xterm does */
        if (button_number >= 3)
            button_number += (64 - 3);
    }

    if (AVTS(r)->PrivateModes & PrivMode_MouseX10)
    {
        /*
         * do not report ButtonRelease
         * no state info allowed
         */
        key_state = 0;
        if (button_number == 3)
            return;
    }
    else
    {
        /* XTerm mouse reporting needs these values:
         *   4 = Shift
         *   8 = Meta
         *  16 = Control
         * plus will add in our own Double-Click reporting
         *  32 = Double Click
         */
        key_state = ((r->h->MEvent.state & ShiftMask) ? 4 : 0)
             + ((r->h->MEvent.state & r->h->ModMetaMask) ? 8 : 0)
             + ((r->h->MEvent.state & ControlMask) ? 16 : 0);
#ifdef MOUSE_REPORT_DOUBLECLICK
        key_state += ((r->h->MEvent.clicks > 1) ? 32 : 0);
#endif
    }

#ifdef DEBUG_MOUSEREPORT
    fprintf(stderr, "Mouse [");
    if (key_state & 16)
        fputc('C', stderr);
    if (key_state & 4)
        fputc('S', stderr);
    if (key_state & 8)
        fputc('A', stderr);
    if (key_state & 32)
        fputc('2', stderr);
    fprintf(stderr, "]: <%d>, %d/%d\n",
        button_number,
        x + 1,
        y + 1);
#else
    rxvt_tt_printf(r, ATAB(r), "\033[M%c%c%c",
          (32 + button_number + key_state),
          (32 + x + 1),
          (32 + y + 1));
#endif
}


/*
 * Before calling rxvt_set_bg_focused, bg and ufbg are already restored to
 * correct state
 */
/* INTPROTO */
void
rxvt_set_bg_focused(rxvt_t* r, int page, Bool focus)
{
    XGCValues       gcvalue;


    /* Make sure bg and ufbg are in correct state */
    assert (0 == r->ufbg_switched);
    if (focus)
        rxvt_restore_ufbg_color (r);
    else
        rxvt_switch_ufbg_color (r);
    gcvalue.background = r->PixColors[Color_bg];

# ifdef TRANSPARENT
    if (!(r->Options & Opt_transparent))
# endif /* TRANSPARENT */
#ifdef BACKGROUND_IMAGE
    if (None == PVTS(r, page)->pixmap)
#endif  /* BACKGROUND_IMAGE */
    {
        XSetBackground(r->Xdisplay, r->TermWin.gc,
            r->PixColors[Color_bg]);
        XSetWindowBackground(r->Xdisplay, PVTS(r, page)->vt,
            r->PixColors[Color_bg]);
    }

#ifdef TRANSPARENT
    if (r->Options & Opt_transparent)
        rxvt_check_our_parents(r);
    else
#endif  /* TRANSPARENT */
#ifdef BACKGROUND_IMAGE
    if (None != PVTS(r, page)->pixmap)
    {
        DBG_MSG (1, (stderr, "reset pixmap bg of vt %d\n", page));
        XSetWindowBackgroundPixmap(r->Xdisplay, PVTS(r, page)->vt,
            PVTS(r, page)->pixmap);
    }
#endif  /* BACKGROUND_IMAGE */
    {
        /* Nothing to do, avoid compile error when defined
        ** TRANSPARENT but not BACKGROUND_IMAGE
        */
    }

    /*
    ** Set foreground/background color for GC. This is necessary.
    ** Otherwise, the old color will be used for drawing the 
    ** following text before a color change.
    */
    XSetForeground (r->Xdisplay, r->TermWin.gc, r->PixColors[Color_fg]);
    XSetBackground (r->Xdisplay, r->TermWin.gc, r->PixColors[Color_bg]);

    rxvt_scr_clear(r, page);
    rxvt_scr_touch(r, page, True);
}



/*
** Individual X Event handlers
*/
#if defined(MOUSE_WHEEL) && defined(MOUSE_SLIP_WHEELING)
/* INTPROTO */
void
rxvt_process_keyrelease(rxvt_t* r, XKeyEvent *ev)
{
    DBG_MSG(2, (stderr, "KeyRelease event\n"));
    if (!(ev->state & ControlMask))
        r->h->mouse_slip_wheel_speed = 0;
    else
    {
        KeySym        ks;

        ks = XKeycodeToKeysym(r->Xdisplay, ev->keycode, 0);
        if (ks == XK_Control_L || ks == XK_Control_R)
            r->h->mouse_slip_wheel_speed = 0;
    }
}
#endif



#ifdef HAVE_SCROLLBARS
/* INTPROTO */
void
rxvt_scrollbar_dispatcher (rxvt_t* r, int page, XButtonEvent* ev)
{
    int            reportmode = 0;
    struct rxvt_hidden*    h = r->h;


    if (!h->bypass_keystate)
        reportmode = !!(PVTS(r, page)->PrivateModes & PrivMode_mouse_report);

    scrollbar_setIdle();
    /*
     * Rxvt-style scrollbar:
     * move up if mouse is above slider
     * move dn if mouse is below slider
     *
     * XTerm-style scrollbar:
     * Move display proportional to pointer location
     * pointer near top -> scroll one line
     * pointer near bot -> scroll full page
     */
# ifndef NO_SCROLLBAR_REPORT
    if (reportmode)
    {
        /*
         * Mouse report disabled scrollbar:
         * arrow buttons - send up/down
         * click on scrollbar - send pageup/down
         */
        if (
                (r->scrollBar.style == R_SB_NEXT && scrollbarnext_upButton(ev->y))
                || (r->scrollBar.style == R_SB_RXVT && scrollbarrxvt_upButton(ev->y))
                || (r->scrollBar.style == R_SB_SGI && scrollbarsgi_upButton(ev->y))
           )
        {
            rxvt_tt_printf(r, page, "\033[A");
        }
        else if (
                    (r->scrollBar.style == R_SB_NEXT && scrollbarnext_dnButton(ev->y))
                    || (r->scrollBar.style == R_SB_RXVT
                                && scrollbarrxvt_dnButton(ev->y))
                    || (r->scrollBar.style == R_SB_SGI
                                && scrollbarsgi_dnButton(ev->y))
                )
        {
            rxvt_tt_printf(r, page, "\033[B");
        }
        else
        {
            switch (ev->button)
            {
                case Button2:
                    rxvt_tt_printf(r, page, "\014");
                    break;
                case Button1:
                    rxvt_tt_printf(r, page, "\033[6~");
                    break;
                case Button3:
                    rxvt_tt_printf(r, page, "\033[5~");
                    break;
            }
        }
    }
    else
# endif /* NO_SCROLLBAR_REPORT */
    {
        int       upordown = 0;

        if (r->scrollBar.style == R_SB_NEXT)
        {
            if (scrollbarnext_upButton(ev->y))
                upordown = -1;  /* up */
            else if (scrollbarnext_dnButton(ev->y))
                upordown = 1;   /* down */
        }
        else if (r->scrollBar.style == R_SB_RXVT)
        {
            if (scrollbarrxvt_upButton(ev->y))
                upordown = -1;  /* up */
            else if (scrollbarrxvt_dnButton(ev->y))
                upordown = 1;   /* down */
        }
        else if (r->scrollBar.style == R_SB_SGI)
        {
            if (scrollbarsgi_upButton(ev->y))
                upordown = -1;  /* up */
            else if (scrollbarsgi_dnButton(ev->y))
                upordown = 1;   /* down */
        }

        if (upordown)
        {
#ifndef NO_SCROLLBAR_BUTTON_CONTINUAL_SCROLLING
            h->scroll_arrow_delay = SCROLLBAR_INITIAL_DELAY;
#endif
            if (rxvt_scr_page(r, ATAB(r), upordown < 0?UP:DN,1))
            {
                if (upordown < 0)
                    scrollbar_setUp();
                else
                    scrollbar_setDn();
            }
        }
        else
        {
            switch (ev->button)
            {
                case Button2:
                    switch (h->scrollbar_align)
                    {
                        case R_SB_ALIGN_TOP:
                            h->csrO = 0;
                            break;
                        case R_SB_ALIGN_CENTRE:
                            h->csrO = (r->scrollBar.bot-r->scrollBar.top)/2;
                            break;
                        case R_SB_ALIGN_BOTTOM:
                            h->csrO = r->scrollBar.bot - r->scrollBar.top;
                            break;
                    }

                    if (
                            r->scrollBar.style == R_SB_XTERM
                            || scrollbar_above_slider(ev->y)
                            || scrollbar_below_slider(ev->y)
                       )
                    {
                        rxvt_scr_move_to(r, page,
                            scrollbar_position(ev->y) - h->csrO, scrollbar_size());
                    }
                    scrollbar_setMotion();
                break;

            case Button1:
                if (h->scrollbar_align == R_SB_ALIGN_CENTRE)
                    h->csrO = ev->y - r->scrollBar.top;
                    /* FALLTHROUGH */

            case Button3:
                if (r->scrollBar.style != R_SB_XTERM)
                {
                    if (scrollbar_above_slider(ev->y))
# ifdef RXVT_SCROLL_FULL
                        rxvt_scr_page(r, ATAB(r), UP, r->TermWin.nrow-1);
# else
                        rxvt_scr_page(r, ATAB(r), UP, r->TermWin.nrow/4);
# endif
                    else if (scrollbar_below_slider(ev->y))
# ifdef RXVT_SCROLL_FULL
                        rxvt_scr_page(r, ATAB(r), DN, r->TermWin.nrow - 1);
# else
                        rxvt_scr_page(r, ATAB(r), DN, r->TermWin.nrow / 4);
# endif
                    else
                        scrollbar_setMotion();
                }
                else
                {
                    rxvt_scr_page(r, ATAB(r),
                        (ev->button == Button1 ? DN : UP),
                        (r->TermWin.nrow * scrollbar_position(ev->y)
                            / scrollbar_size()));
                }
                break;
            } /* switch( ev->button ) */
        } /* else */
    }
    return;
}
#endif  /* HAVE_SCROLLBARS */


/* INTPROTO */
void
rxvt_process_buttonpress(rxvt_t* r, int page, XButtonEvent *ev)
{
    int                    reportmode = 0, clickintime;
    struct rxvt_hidden*    h = r->h;


    DBG_MSG(2, (stderr, "ButtonPress event\n"));
    h->bypass_keystate = ev->state & (h->ModMetaMask | ShiftMask);
    if (!h->bypass_keystate)
        reportmode = !!(PVTS(r, page)->PrivateModes & PrivMode_mouse_report);

    /*
     * VT window processing of button press
     */
    if (ev->window == PVTS(r, page)->vt)
    {
#ifdef HAVE_MENUBAR
        /* Popup menu on Control click on terminal window. */
        if( ev->state & ControlMask && !r->h->ActiveMenu)
        {
            int button;

            /* In some bizaro world, Button1,2,3 might not be 1,2,3 */
            switch( ev->button )
            {
                case Button1:
                    button = 0; break;

                case Button2:
                    button = 1; break;

                case Button3:
                    button = 2; break;

                default:
                    button = -1;
            }

            if( button >=0 && r->h->popupMenu[button] )
            {
                int     x, y;
                Window  unused_cr;

                r->h->showingMenu |= POPUP_MENU;

                XTranslateCoordinates( r->Xdisplay, ev->window, r->TermWin.parent,
                        ev->x, ev->y, &x, &y, &unused_cr);

                r->h->ActiveMenu = r->h->popupMenu[button];

                r->h->ActiveMenu->x = x;
                r->h->ActiveMenu->y = y;

                XDefineCursor(r->Xdisplay, AVTS(r)->vt, r->h->bar_pointer);
                rxvt_menu_show(r);
                return;
            }
        }
#endif

        clickintime = ev->time - h->MEvent.time < MULTICLICK_TIME;
        if (reportmode)
        {
            /* mouse report from vt window */
            /* save the xbutton state (for ButtonRelease) */
            h->MEvent.state = ev->state;
#ifdef MOUSE_REPORT_DOUBLECLICK
            if (ev->button == h->MEvent.button && clickintime)
            {
                /* same button, within alloted time */
                h->MEvent.clicks++;
                if (h->MEvent.clicks > 1)
                {
                    /* only report double clicks */
                    h->MEvent.clicks = 2;
                    rxvt_mouse_report(r, ev);

                    /* don't report the release */
                    h->MEvent.clicks = 0;
                    h->MEvent.button = AnyButton;
                }
            }
            else
            {
                /* different button, or time expired */
                h->MEvent.clicks = 1;
                h->MEvent.button = ev->button;
                rxvt_mouse_report(r, ev);
            }
#else
            h->MEvent.button = ev->button;
            rxvt_mouse_report(r, ev);
#endif              /* MOUSE_REPORT_DOUBLECLICK */
        }
        else
        {
            if (ev->button != h->MEvent.button)
                h->MEvent.clicks = 0;
            switch (ev->button)
            {
                case Button1:
                    if (h->MEvent.button == Button1 && clickintime)
                        h->MEvent.clicks++;
                    else
                        h->MEvent.clicks = 1;
                    rxvt_selection_click(r, page, h->MEvent.clicks,
                        ev->x, ev->y);
                    h->MEvent.button = Button1;
                    break;

                case Button3:
                    if (h->MEvent.button == Button3 && clickintime)
                        rxvt_selection_rotate(r, page, ev->x, ev->y);
                    else
                        rxvt_selection_extend(r, page, ev->x, ev->y, 1);
                    h->MEvent.button = Button3;
                    break;
            }
        }
        h->MEvent.time = ev->time;
        return;
    }


    /*
     * Tabbar window processing of button press
     */
    if (rxvt_is_tabbar_win (r, ev->window))
        rxvt_tabbar_dispatcher (r, ev);


#ifdef HAVE_SCROLLBARS
    /*
     * Scrollbar window processing of button press
     */
    if (rxvt_is_scrollbar_win (r, ev->window))
        rxvt_scrollbar_dispatcher (r, page, ev);
#endif


#ifdef HAVE_MENUBAR
    /*
     * Menubar window processing of button press
     */
    if (rxvt_is_menubar_win(r, ev->window))
        rxvt_menubar_control(r, ev);
#endif
}



#ifdef MOUSE_WHEEL
/* INTPROTO */
void
rxvt_process_wheel_button(rxvt_t* r, int page, XButtonEvent *ev)
{
    int             i, v;

    v = (ev->button == Button4) ? UP : DN;
    if (ev->state & ShiftMask)
        i = 1;
    else if ((r->Options & Opt_mouseWheelScrollPage))
        i = r->TermWin.nrow - 1;
    else
        i = 5;

# ifdef MOUSE_SLIP_WHEELING
    if (ev->state & ControlMask)
    {
        r->h->mouse_slip_wheel_speed += (v ? -1 : 1);
        r->h->mouse_slip_wheel_delay = SCROLLBAR_CONTINUOUS_DELAY;
    }
# endif

# ifdef JUMP_MOUSE_WHEEL
    rxvt_scr_page(r, ATAB(r), v, i);

#  ifdef XFT_SUPPORT
    /* disable screen refresh if XFT antialias is used to improve performance */
    if (!((r->Options & Opt_xft) && (r->Options2 & Opt2_xftAntialias)))
#  endif    /* XFT_SUPPORT */
        rxvt_scr_refresh(r, page, SMOOTH_REFRESH);
#  ifdef HAVE_SCROLLBARS
    rxvt_scrollbar_update(r, 1);
#  endif    /* HAVE_SCROLLBARS */


# else  /* !JUMP_MOUSE_WHEEL */
    for (; i--;)
    {
        rxvt_scr_page(r, ATAB(r), v, 1);

#  ifdef XFT_SUPPORT
        /* disable screen refresh if XFT antialias is used to improve
         * performance */
        if (!((r->Options & Opt_xft) && (r->Options2 & Opt2_xftAntialias)))
#  endif    /* XFT_SUPPORT */
            rxvt_scr_refresh(r, page, SMOOTH_REFRESH);
#  ifdef HAVE_SCROLLBARS
        rxvt_scrollbar_update(r, 1);
#  endif    /* HAVE_SCROLLBARS */
    }
# endif /* JUMP_MOUSE_WHEEL */
}
#endif  /* MOUSE_WHEEL */


/* INTPROTO */
void
rxvt_process_buttonrelease(rxvt_t* r, int page, XButtonEvent *ev)
{
    int             reportmode = 0;

    if ( r->tabClicked != -1 )
    {
        if ( rxvt_is_tabbar_win( r, ev->window ) )
        {
            rxvt_tabbar_button_release( r, ev );
            return;
        }
        else
            /* User dropped a tab somewhere other than the tabbar */
            r->tabClicked = -1;
    }

    DBG_MSG(2, (stderr, "ButtonRelease event\n"));
    r->h->csrO = 0;        /* reset csr Offset */
    if (!r->h->bypass_keystate)
        reportmode = !!(PVTS(r, page)->PrivateModes & PrivMode_mouse_report);

#ifdef HAVE_SCROLLBARS
    if (scrollbar_isUpDn())
    {
        scrollbar_setIdle();
        rxvt_scrollbar_update(r, 0);
# ifndef NO_SCROLLBAR_BUTTON_CONTINUAL_SCROLLING
        r->h->refresh_type &= ~SMOOTH_REFRESH;
# endif
    }
#endif  /* HAVE_SCROLLBARS */

#ifdef HAVE_MENUBAR
    if( r->h->showingMenu )
    {
        r->h->showingMenu &= ~POPUP_MENU;
        XDefineCursor( r->Xdisplay, AVTS(r)->vt, r->term_pointer);

        rxvt_menu_select(r, ev);
        return;
    }
#endif

#ifdef SELECTION_SCROLLING
    r->h->pending_scroll_selection=0;
#endif  /* SELECTION_SCROLLING */

    if (ev->window == PVTS(r, page)->vt)
    {
        if (ev->subwindow == None)
        {
            if (reportmode)
            {
                /* mouse report from vt window */
                /* don't report release of wheel "buttons" */
                if (ev->button >= 4)
                    return;
#ifdef MOUSE_REPORT_DOUBLECLICK
                /* only report the release of 'slow' single clicks */
                if (
                        r->h->MEvent.button != AnyButton
                        && (
                            ev->button != r->h->MEvent.button
                            || (ev->time - r->h->MEvent.time > MULTICLICK_TIME / 2)
                           )
                   )
                {
                    r->h->MEvent.clicks = 0;
                    r->h->MEvent.button = AnyButton;
                    rxvt_mouse_report(r, ev);
                }
#else   /* MOUSE_REPORT_DOUBLECLICK */
                r->h->MEvent.button = AnyButton;
                rxvt_mouse_report(r, ev);
#endif  /* MOUSE_REPORT_DOUBLECLICK */
                return;
            }
            /*
             * dumb hack to compensate for the failure of click-and-drag
             * when overriding mouse reporting
             */
            if (PVTS(r, page)->PrivateModes & PrivMode_mouse_report
                && r->h->bypass_keystate
                && ev->button == Button1 && r->h->MEvent.clicks <= 1)
                rxvt_selection_extend(r, page, ev->x, ev->y, 0);

            switch (ev->button)
            {
                case Button1:
                case Button3:
                    rxvt_selection_make(r, page, ev->time);
                    break;
                case Button2:
                    rxvt_selection_request(r, page, ev->time, ev->x, ev->y);
                    break;
#ifdef MOUSE_WHEEL
                case Button4:
                case Button5:
                    rxvt_process_wheel_button (r, page, ev);
                    break;
#endif  /* MOUSE_WHEEL */
            }
        }
    }
#ifdef HAVE_MENUBAR
    else if (rxvt_is_menubar_win(r, ev->window))
        rxvt_menubar_control(r, ev);
#endif  /* HAVE_MENUBAR */
}



/* INTPROTO */
void
rxvt_process_clientmessage(rxvt_t* r, XClientMessageEvent* ev)
{
    DBG_MSG(2, (stderr, "ClientMessage event\n"));
    if (ev->format == 32 &&
        (Atom)ev->data.l[0] == r->h->xa[XA_WMDELETEWINDOW])
        rxvt_clean_exit (r);

#ifdef OFFIX_DND
    /* OffiX Dnd (drag 'n' drop) protocol */
    if (
            ev->xclient.message_type == h->xa[XA_DNDPROTOCOL]
            && (
                ev->xclient.data.l[0] == DndFile
                || ev->xclient.data.l[0] == DndDir
                || ev->xclient.data.l[0] == DndLink
               )
       )
    {
        /* Get Dnd data */
        Atom            ActualType;
        int               ActualFormat;
        unsigned char*    data;
        unsigned long Size, RemainingBytes;

        XGetWindowProperty(r->Xdisplay, XROOT,
           r->h->xa[XA_DNDSELECTION], 0L, 1000000L,
           False, AnyPropertyType, &ActualType, &ActualFormat,
           &Size, &RemainingBytes, &data);
        XChangeProperty(r->Xdisplay, XROOT, XA_CUT_BUFFER0,
            XA_STRING, 8, PropModeReplace, data, STRLEN(data));
        rxvt_selection_paste(r, ATAB(r), XROOT, XA_CUT_BUFFER0, True);
        XSetInputFocus(r->Xdisplay, XROOT, RevertToNone, CurrentTime);
    }
#endif      /* OFFIX_DND */
}



/* INTPROTO */
void
rxvt_process_visibilitynotify(rxvt_t* r, XVisibilityEvent* ev)
{
    DBG_MSG(2, (stderr, "VisibilityNotify event\n"));
    switch (ev->state)
    {
        case VisibilityUnobscured:
            r->h->refresh_type = FAST_REFRESH;
            break;
        case VisibilityPartiallyObscured:
            r->h->refresh_type = SLOW_REFRESH;
            break;
        default:
            r->h->refresh_type = NO_REFRESH;
            break;
    }
}



#ifdef MONITOR_ENTER_LEAVE
/* INTPROTO */
void
rxvt_process_enter (rxvt_t* r, XCrossingEvent* ev)
{
    if (ev->window == r->TermWin.parent)
    {
        DBG_MSG(1, (stderr, "Enter event\n"));
        r->TermWin.enter = 1;
    }
}


/* INTPROTO */
void
rxvt_process_leave (rxvt_t* r, XCrossingEvent* ev)
{
    if (ev->window == r->TermWin.parent)
    {
        DBG_MSG(1, (stderr, "Leave event\n"));
        r->TermWin.enter = 0;
    }
}
#endif  /* MONITOR_ENTER_LEAVE */


/* INTPROTO */
void
rxvt_process_focusin (rxvt_t* r, XFocusChangeEvent* ev)
{
    if (ev->window == r->TermWin.parent)
    {
#ifdef OFF_FOCUS_FADING
        register int  changed = 0;
#endif

        DBG_MSG(2, (stderr, "FocusIn event\n"));
        r->TermWin.focus = 1;
        r->h->want_refresh = 1; /* Cursor needs to be refreshed */

#ifdef USE_XIM
        if (r->h->Input_Context != NULL)
            XSetICFocus(r->h->Input_Context);
#endif

        /* if we have switched bg/ufbg color, restore it */
        rxvt_restore_ufbg_color (r);
#ifdef OFF_FOCUS_FADING
        /* if we have switched to off-focus color, restore it */
        changed = rxvt_restore_pix_color (r);
#endif

        if (
                ISSET_PIXCOLOR(r->h, Color_ufbg)
#ifdef OFF_FOCUS_FADING
                || (r->h->rs[Rs_fade] && changed)
#endif
           )
        {
            /* before calling rxvt_set_bg_focused, bg and ufbg are
            ** already restored to correct state */
            rxvt_set_bg_focused(r, ATAB(r), True);
        }
    }

}



/* INTPROTO */
void
rxvt_process_focusout (rxvt_t* r, XFocusChangeEvent* ev)
{
    if (ev->window == r->TermWin.parent)
    {
#ifdef OFF_FOCUS_FADING
        register int  changed = 0;
#endif

        DBG_MSG(2, (stderr, "FocusOut event\n"));
        r->TermWin.focus = 0;
        r->h->want_refresh = 1; /* Cursor needs to be refreshed */

#ifdef USE_XIM
        if (r->h->Input_Context != NULL)
            XUnsetICFocus(r->h->Input_Context);
#endif

        /* if we have switched bg/ufbg color, restore it */
        rxvt_restore_ufbg_color (r);
#ifdef OFF_FOCUS_FADING
        /* if we are using on-focus color, switch it */
        changed = rxvt_switch_pix_color (r);
#endif

        if (
                ISSET_PIXCOLOR(r->h, Color_ufbg)
#ifdef OFF_FOCUS_FADING
                || (r->h->rs[Rs_fade] && changed)
#endif
           )
        {
            /* before calling rxvt_set_bg_focused, bg and ufbg are
            ** already restored to correct state */
            rxvt_set_bg_focused(r, ATAB(r), False);
        }
    }
}



#if 0
/* 2006-01-07 gi1242: Old "smart" resize code which we no longer need */
/* Resize windows on showing/hiding sub windows */
/* EXTPROTO */
void
rxvt_resize_on_subwin (rxvt_t* r, resize_reason_t reason)
{
    unsigned int    w = r->szHint.width, h = r->szHint.height;
    unsigned int    old_width = r->szHint.width,
                    old_height = r->szHint.height;

    DBG_MSG(1, (stderr, "rxvt_resize_on_subwin\n"));
    rxvt_recalc_szhint (r, reason, &w, &h);

    /*
     * Move the window so hiding / showing the tabbar doesn't take you off
     * screen. We should not move the window here, but only on ConfigureNotify
     * events
     */
    if( r->Options2 & Opt2_smartResize )
    {
        /*
        ** resize by Marius Gedminas <marius.gedminas@uosis.mif.vu.lt>
        ** reposition window on resize depending on placement on screen
        */
        int             x, y, x1, y1;
        int             dx, dy;
        unsigned int    unused_w1, unused_h1, unused_b1, unused_d1;
        Window          unused_cr;

        XTranslateCoordinates(r->Xdisplay, r->TermWin.parent, XROOT,
            0, 0, &x, &y, &unused_cr);
        XGetGeometry(r->Xdisplay, r->TermWin.parent, &unused_cr,
            &x1, &y1, &unused_w1, &unused_h1, &unused_b1, &unused_d1);
        /*
        ** if XROOT isn't the parent window, a WM will probably have
        ** offset our position for handles and decorations. Counter
        ** it.
        */
        if (x1 != x || y1 != y)
        {
            x -= x1;
            y -= y1;
        }

        x1 = (DisplayWidth(r->Xdisplay, XSCREEN) - old_width) / 2;
        y1 = (DisplayHeight(r->Xdisplay, XSCREEN) - old_height) / 2;
        dx = old_width - w;
        dy = old_height - h;

        /* Check position of the center of the window */
        if (x < x1)     /* left half */
            dx = 0;
        else if (x == x1)   /* exact center */
            dx /= 2;
        if (y < y1)     /* top half */
            dy = 0;
        else if (y == y1)   /* exact center */
            dy /= 2;

        /* Only move the window if we stay completely onscreen */
        x1 = x + dx;
        y1 = y + dy;

        fprintf( stderr, "smart moving to (%d, %d, %u, %u)\n", x1, y1, w, h);
        if( x1 >= 0 && x1 + w <= DisplayWidth( r->Xdisplay, XSCREEN)
                && y1 >= 0 && y1 + h <= DisplayHeight( r->Xdisplay, XSCREEN))
        {
            XMoveWindow(r->Xdisplay, r->TermWin.parent, x1, y1);
        }
    }
}
#endif


/*
 * Recalculate and set the szHint upon changes of menubar/scrollbar/tabbar or
 * font. szHint.width and height are not modified, but the XResizeWindow is
 * called. The szHint.width and height will be correctly updated on
 * ConfigureNotify events.
 *
 * reason:  reason we want to resize the window.
 */
/* INTPROTO */
void
rxvt_resize_on_subwin (rxvt_t* r, resize_reason_t reason)
{
    /*
     * Store the old width and height
     */
    unsigned oldWidth  = r->szHint.width;
    unsigned oldHeight = r->szHint.height;

    switch (reason)
    {
#ifdef HAVE_MENUBAR
        case HIDE_MENUBAR:
            r->szHint.base_height -= rxvt_menubar_rheight (r);
            r->szHint.min_height  -= rxvt_menubar_rheight (r);
            r->szHint.height      -= rxvt_menubar_rheight (r);
            break;
        case SHOW_MENUBAR:
            r->szHint.base_height += rxvt_menubar_rheight (r);
            r->szHint.min_height  += rxvt_menubar_rheight (r);
            r->szHint.height      += rxvt_menubar_rheight (r);
            break;
#endif  /* HAVE_MENUBAR */

        case HIDE_TABBAR:
            r->szHint.base_height -= rxvt_tabbar_rheight (r);
            r->szHint.min_height  -= rxvt_tabbar_rheight (r);
            r->szHint.height      -= rxvt_tabbar_rheight (r);
            break;
        case SHOW_TABBAR:
            r->szHint.base_height += rxvt_tabbar_rheight (r);
            r->szHint.min_height  += rxvt_tabbar_rheight (r);
            r->szHint.height      += rxvt_tabbar_rheight (r);
            break;

#ifdef HAVE_SCROLLBARS
        case HIDE_SCROLLBAR:
            r->szHint.base_width -= rxvt_scrollbar_rwidth (r);
            r->szHint.min_width  -= rxvt_scrollbar_rwidth (r);
            r->szHint.width      -= rxvt_scrollbar_rwidth (r);
            break;
        case SHOW_SCROLLBAR:
            r->szHint.base_width += rxvt_scrollbar_rwidth (r);
            r->szHint.min_width  += rxvt_scrollbar_rwidth (r);
            r->szHint.width      += rxvt_scrollbar_rwidth (r);
            break;
#endif  /* HAVE_SCROLLBARS */

        case RESIZE_FONT:
            /* Calculate the base width and height */
            r->szHint.base_width  = 2 * r->TermWin.int_bwidth;
            r->szHint.base_height = 2 * r->TermWin.int_bwidth;
#ifdef HAVE_SCROLLBARS
            if( rxvt_scrollbar_visible( r) )
                r->szHint.base_width += rxvt_scrollbar_width (r);
#endif
#ifdef HAVE_MENUBAR
            if( rxvt_menubar_visible(r) )
                r->szHint.base_height += rxvt_menubar_height (r);
#endif
            if( rxvt_tabbar_visible( r ) )
                r->szHint.base_height += rxvt_tabbar_height (r);

            /* Set the terminal incremental width and height */
#ifndef NO_FRILLS
            if( r->Options2 & Opt2_smoothResize )
            {
                r->szHint.width_inc = 1;
                r->szHint.height_inc = 1;
            }
            else
#endif
            {
                r->szHint.width_inc = r->TermWin.fwidth;
                r->szHint.height_inc = r->TermWin.fheight;
            }

            /* Set the terminal minimal width and height */
            r->szHint.min_width = r->szHint.base_width + r->TermWin.fwidth;
            r->szHint.min_height = r->szHint.base_height + r->TermWin.fheight;

            /* Calculate new height and width */
            r->szHint.width  = r->szHint.base_width +
                    Width2Pixel(r->TermWin.ncol);
            r->szHint.height = r->szHint.base_height +
                    Height2Pixel(r->TermWin.nrow);

            /*
             * Just incase the window is not resized by the WM, then we still need
             * to refresh the screen.
             */
            r->h->want_resize |= FORCE_REFRESH;
            break;

        default:
            assert (0);  /* should not reach here */
            return ;
    }

    /* Reset WMNormal Hints. We need not worry about r->szHint.flags */
    XSetWMNormalHints (r->Xdisplay, r->TermWin.parent, &(r->szHint));

    /* Set the terminal window starting position */
    if (!(r->Options & Opt_scrollBar_right))
        r->h->window_vt_x = (r->Options & Opt_scrollBar_right) ?
            0 : r->szHint.base_width - 2*r->TermWin.int_bwidth;

    r->h->window_vt_y = r->szHint.base_height - 2*r->TermWin.int_bwidth;
    if (r->Options2 & Opt2_bottomTabbar)
        r->h->window_vt_y -= rxvt_tabbar_height (r);

    /*
     * Now we can resize the window The resize request might not always succeed.
     * If the window is already maximized, then (most?) WMs do nothing on the
     * below call. So when we recieve a ConfigureNotify event, we'll think we've
     * not moved or resized, and will erroriously not update our TermWin.ncols
     * etc.
     */
    XResizeWindow(r->Xdisplay, r->TermWin.parent,
            r->szHint.width, r->szHint.height);

    /*
     * We get around this error by setting want_resize. In configure notify
     * events, if this variable is set, we resize the window regardless of
     * wether it apears to be in the same position or not.
     */
    r->h->want_resize |= FORCE_RESIZE;

#ifndef NO_FRILLS
    while(  r->Options2 & Opt2_smartResize )
    {
        /*
         * Let's attempt to move the window so we don't push part of it off
         * screen.
         */

        CARD32   left, right, top, bottom;
        int        wx, wy;          /* pos of window with decorations */
        unsigned wwidth, wheight; /* dim of window with decorations */

        int   newx = r->szHint.x,   /* new location to move to */
            newy = r->szHint.y;

        unsigned  dspw = DisplayWidth(  r->Xdisplay, XSCREEN),
                    dsph = DisplayHeight( r->Xdisplay, XSCREEN);

        int    dx = (int) r->szHint.width - (int) oldWidth,
             dy = (int) r->szHint.height- (int) oldHeight;


        if( !getWMStruts( r->Xdisplay, r->TermWin.parent,
                &left, &right, &top, &bottom)) break;

        wx = r->szHint.x - left;
        wy = r->szHint.y - top;
        wwidth  = r->szHint.width  + left + right;
        wheight = r->szHint.height + top + bottom;

        /*
         * Now the position of the window with decorations is in wx, wy,
         * wwidth, wheight.
         */
        DBG_MSG(1, (stderr, "Strut: (%lu, %lu %lu, %lu), "
                            "Geometry: %ux%u+%d+%d, Change: (%d, %d)\n",
            left, right, top, bottom, wwidth, wheight, wx, wy, dx, dy ));

        /*
         * Try and move us back on screen, if we resized off it.
         */
        if( wwidth >= dspw || wheight >= dsph ) break;

        if( wx < 0 && wx + dx >= 0) newx = left;
        else if( wx + (int) wwidth > (int) dspw
                && wx + (int) wwidth - dx <= (int) dspw )
            newx = dspw - wwidth + left;

        if( wy < 0 && wy + dy >= 0) newy = top;
        else if( wy + (int) wheight > (int) dsph
                && wy + (int) wheight - dy <= (int) dsph)
            newy = dsph - wheight + top;

        if(
                (newx != r->szHint.x || newy != r->szHint.y) /* moved */
                && newx - (int) left >=0        /* onscreen */
                && newx - (int) left + (int) wwidth <= dspw
                && newy - (int) top >=0
                && newy - (int) top + (int) wheight <= dsph
          )
        {
            DBG_MSG( 1, (stderr, "Smart move to %ux%u+%d+%d\n",
                r->szHint.width, r->szHint.height, newx, newy));
            XMoveWindow( r->Xdisplay, r->TermWin.parent,
                    newx, newy);
        }
        break;
    }
#endif

    /* 
     * According to X Reference, we should only trust the size of a Window
     * through ConfigureNotify event, or through XGet... functions. So here we
     * must not change the window size till we receive a ConfigureNotify event.
     */
    r->szHint.width = oldWidth;
    r->szHint.height = oldHeight;
}


/* Resize windows on changing fonts */
/* INTPROTO */
void
rxvt_resize_on_font (rxvt_t* r, char* fontname)
{
    DBG_MSG(1, (stderr, "rxvt_resize_on_font\n"));

#ifdef XFT_SUPPORT
    /* if use freetype font, disallow resize by now ;-) */
    if ((r->Options & Opt_xft) && r->TermWin.xftfont)
        if (!rxvt_change_font_xft (r, fontname))
            return ;
    if (!(r->Options & Opt_xft))
#endif  /* XFT_SUPPORT */
    /* X11 font resize */
    if (!rxvt_change_font_x11 (r, fontname))
        return ;

    rxvt_resize_on_subwin (r, RESIZE_FONT);
}



/*
** Recalculate the window col/row upon window resizing
*/
/* INTPROTO */
int
rxvt_calc_colrow (rxvt_t* r, unsigned int width, unsigned int height)
{
    unsigned int   ncol, nrow;


    assert (0 != r->TermWin.fwidth);
    assert (0 != r->TermWin.fheight);

    /* Do nothing if size does not change, unless we requested the resize. */
    if ( !r->h->want_resize &&
            r->szHint.width == width && r->szHint.height == height)
        return 0;

    DBG_MSG(1, (stderr, "Recalc row/col of (%d, %d)\n", width, height));
    ncol = Pixel2Width (width - r->szHint.base_width);
    nrow = Pixel2Height (height - r->szHint.base_height);
    MAX_IT(ncol, 1);
    MAX_IT(nrow, 1);

    r->h->prev_ncol = r->TermWin.ncol;
    r->h->prev_nrow = r->TermWin.nrow;
    r->TermWin.ncol = ncol;
    r->TermWin.nrow = nrow;

    /* 
     * According to X Reference, we should only trust the size of a Window
     * through ConfigureNotify event, or through XGet... functions. This
     * function should only be called from ConfigureNotify event handler
     */
    r->szHint.width = width;
    r->szHint.height = height;

    return ((r->h->prev_ncol != r->TermWin.ncol) ||
            (r->h->prev_nrow != r->TermWin.nrow));
}


/* INTPROTO */
void
rxvt_resize_sub_windows (rxvt_t* r)
{
    register int   i;


    DBG_MSG(1, (stderr, "rxvt_resize_sub_windows\n"));

#ifdef HAVE_SCROLLBARS
    rxvt_scrollbar_resize(r);
#endif
#ifdef HAVE_MENUBAR
    rxvt_menubar_resize(r);
#endif
    rxvt_tabbar_resize (r);

    for (i = 0; i <= LTAB(r); i ++)
    {
        XMoveResizeWindow (r->Xdisplay, PVTS(r, i)->vt,
            r->h->window_vt_x, r->h->window_vt_y,
            VT_WIDTH(r), VT_HEIGHT(r));
    }
}


/* Resize windows on configurenotify event */
/* INTPROTO */
void
rxvt_resize_on_configure (rxvt_t* r, unsigned int width, unsigned int height)
{
    register int   i = 0;
    unsigned int   old_width = r->szHint.width,
                    old_height = r->szHint.height;
    int                fix_screen;


    DBG_MSG(2, (stderr, "rxvt_resize_on_configure\n"));
    /* update ncol/nrow of new window */
    fix_screen = rxvt_calc_colrow (r, width, height);

    /*
     * Check for refresh. If called XResizeWindow, and the WM politely refused
     * to resize window, then we should still process the resize event.
     */
    if (r->h->want_resize ||
            old_width != r->szHint.width || old_height != r->szHint.height)
        rxvt_resize_sub_windows (r);

    if (fix_screen)
    {
        for (i = 0; i <= LTAB(r); i ++)
        {
            int          curr_screen = -1;
            RUINT16T    old_ncol;

            /*
             * Update previous columns and rows for each VT. We need these
             * copies so that rxvt_scr_reset can work for each VT. If all VT
             * only share one copy, the first VT that calls rxvt_scr_reset will
             * update it, thus other VT will not correctly adjust their
             * column/row.
             */
            PVTS(r, i)->prev_nrow = r->h->prev_nrow;
            PVTS(r, i)->prev_ncol = r->h->prev_ncol;
            old_ncol = PVTS(r, i)->prev_ncol;

            rxvt_scr_clear(r, i);
#ifdef BACKGROUND_IMAGE
            rxvt_resize_pixmap(r, i);
#endif

            curr_screen = rxvt_scr_change_screen(r, i, PRIMARY);
            /* scr_reset only works on the primary screen */
            rxvt_scr_reset(r, i);
            if (curr_screen >= 0)
            {
                /* this is not the first time through */
                rxvt_scr_change_screen(r, i, curr_screen);
                rxvt_selection_check(r, i, (old_ncol != r->TermWin.ncol ? 4 : 0));
            }
        }
    }

#ifdef USE_XIM
    rxvt_IM_resize(r);
#endif
}


/*
 * Get the size of the borders the Window Manager might have put around the
 * window. Returns true if it succeeded reading the struts. Else returns false,
 * and puts 0 in left / right / top / bottom.
 */
#ifndef NO_FRILLS
Bool getWMStruts( Display *dpy, Window w,
        CARD32 *left, CARD32 *right, CARD32 *top, CARD32 *bottom)
{

    Atom atom;
    static const int natoms = 2;
    static const char *atomName[2] = {
        "_KDE_NET_WM_FRAME_STRUT",
        "_NET_FRAME_EXTENTS"};
    int i;

    Atom            type;
    int                format;
    unsigned long  nitems, bytes_after;

    CARD32  *struts; /* left, right, top and bottom borders */

    /*
     * Initialize return values to 0, just incase we can't read the window
     * property.
     */
    *left = *right = *top = *bottom = 0;

    /* Now try and read the property */
    for( i=0; i < natoms; i++)
    {
        if( (atom = XInternAtom( dpy, atomName[i], False))
                == None) continue;

        if( XGetWindowProperty( dpy, w, atom,
                0,      // offset
                4,      // length
                False,  // Delete?
                XA_CARDINAL,    // Type
                &type, &format, &nitems, &bytes_after, // return values
                (unsigned char **) &struts) != Success )
            continue;

        if( type == XA_CARDINAL && bytes_after == 0)
        {
            *left   = struts[0];
            *right  = struts[1];
            *top    = struts[2];
            *bottom = struts[3];

            DBG_MSG( 1, (stderr, "Got struts %lu, %lu, %lu, %lu from %s\n",
                    *left, *right, *top, *bottom, atomName[i]));
            /*
             * Don't check future atomName's
             */
            i = natoms;
        }

        XFree( struts);
    }
    return i == natoms + 1;
}
#endif

/* INTPROTO */
void
rxvt_process_configurenotify (rxvt_t* r, XConfigureEvent* ev)
{
    unsigned int   height, width;

    if (ev->window != r->TermWin.parent)
        return;

    DBG_MSG(2, (stderr, "ConfigureNotify event\n"));
    do             /* Wrap lots of configures into one */
      {
        width = ev->width;
        height = ev->height;
      }
    while ( XCheckTypedWindowEvent(r->Xdisplay, ev->window,
                    ConfigureNotify, (XEvent*) ev));

    /*
     * Remember the position of the window. Make sure that we remember the
     * position relative to the root window (for root transparency). Notice this
     * position will be offset by the Window manager.
     */
    XTranslateCoordinates(r->Xdisplay, r->TermWin.parent, XROOT,
        0, 0, &r->szHint.x, &r->szHint.y, &ev->window);

    DBG_MSG(1, (stderr, "Geometry: %ux%u+%d+%d\n",
        width, height, r->szHint.x, r->szHint.y));

    if (
            r->h->want_resize
            || r->szHint.width != width || r->szHint.height != height
       )
    {

        rxvt_resize_on_configure (r, width, height);
    }
#if DEBUG_LEVEL
    else
    {
        DBG_MSG(1, (stderr, "Size: Not resizing\n"));
    }
#endif

    if( (r->h->want_resize & ~FORCE_REFRESH) )
    {
        r->h->want_resize = 0;

        DBG_MSG( 2, ( stderr, "Forcing refresh (from want_resize)\n"));

#if defined(HAVE_LIBXRENDER) && (defined(BACKGROUND_IMAGE) || defined(TRANSPARENT))
        /*
         * Background images tinted with XRender need to be refreshed on hide /
         * show of sub windows.
         */
        rxvt_refresh_bg_image( r, ATAB(r), False );
#else
        /*
         * Otherwise we should refresh the screen. A lazy refresh is enough, as
         * we will recieve expose events shortly.
         */
        /* rxvt_src_clear required? */
        rxvt_scr_touch( r, ATAB(r), False);
#endif
    }

#ifdef TRANSPARENT
    /*
     * Check to see if the previous position we grabbed the background is
     * different from the current window position. If yes, then update
     * everything.
     */
    if (r->Options & Opt_transparent)
    {
        if(
                !r->h->bgGrabbed
                || r->h->prevPos.x != r->szHint.x
                || r->h->prevPos.y != r->szHint.y
                || r->h->prevPos.width != width
                || r->h->prevPos.height != height
          )
        {
            /*
             * Rather than refresh our background pixmap now (which is laggy as
             * hell), generate a timeout. So if the user is dragging this
             * window, we won't refresh our background unless he stops for a
             * certain ammount of time.
             */
            if( !r->h->bgRefreshInterval)
            {
                DBG_MSG( 3, ( stderr, "refreshing parents...\n"));
                if( rxvt_check_our_parents(r) )
                {
                    r->h->want_resize = 0;
                    r->h->want_full_refresh = 1;
                }
            }
            else
            {
                DBG_MSG( 3, ( stderr,
                            "Setting timeout for parent refresh.\n"));
                gettimeofday( &r->h->lastCNotify, NULL);
            }
        }
    }
#endif
}


/* INTPROTO */
void
rxvt_process_selectionnotify (rxvt_t* r, XSelectionEvent* ev)
{
    DBG_MSG(2, (stderr, "SelectionNotify event\n"));
    if (r->h->selection_wait == Sel_normal)
        rxvt_selection_paste(r, ev->requestor, ev->property, True);
}


/* INTPROTO */
void
rxvt_process_propertynotify (rxvt_t* r, XEvent* ev)
{
#ifdef TRANSPARENT
    int wantRefresh = 0;   /* Want transparency refresh */
#endif

#if DEBUG_LEVEL
    char *name;
    DBG_MSG( 2, (stderr, "Property notify event:"));
#endif

    assert( ev->type == PropertyNotify );
    /*
     * Wrap all property notify events in one loop. This is *required* so that
     * we don't run the transparency updates too often (or worse still, with a
     * bad pixmap).
     */
    do
      {
#if DEBUG_LEVEL
        name = XGetAtomName( r->Xdisplay, ev->xproperty.atom);
        DBG_MSG( 2, (stderr, "%s(%08lx) ", name, ev->xproperty.atom ));

        XFree( name);
#endif

        if (
                ev->xproperty.atom == r->h->xa[XA_VT_SELECTION]
                && ev->xproperty.state == PropertyNewValue
           )
        {
            rxvt_selection_property(r, ev->xproperty.window, ev->xproperty.atom);
        }

#ifdef TRANSPARENT
        else if (
                    r->h->xa[XA_XROOTPMAPID] != None
                    && r->h->xa[XA_XSETROOTID] != None
                    && (
                        ev->xproperty.atom == r->h->xa[XA_XROOTPMAPID]
                        || ev->xproperty.atom == r->h->xa[XA_XSETROOTID]
                       )
                )
        {
            /*
             * If user used some Esetroot compatible prog to set the root bg,
             * use the property to determine the pixmap.  We use it later on.
             */
            if( !wantRefresh)
            {
                /*
                 * A few programs (fvwm-root for instance) use the XSETROOTID
                 * property to indicate changes in transparency (they set it to
                 * none when the background is a solid color). So we have to
                 * listen for both properties.
                 *
                 * fvwm-root (and some other badly behaved programs) do NOT grab
                 * the server when setting the above atoms. Thus while our event
                 * queue might be empty now, we might get a PropertyNotify event
                 * setting one of the above atoms shortly. Thus we introduce a
                 * delay here (eliminates flicker). Notice that this will NOT
                 * introduce a delay when listening for other properties.
                 */
                DBG_MSG( 1, (stderr, "(sleeping ... "));
#ifdef HAVE_NANOSLEEP
                struct timespec rqt;
                rqt.tv_sec = 0;
                rqt.tv_nsec = 10000000; /* 10 ms */
                nanosleep(&rqt, NULL);
#else
                sleep( 1);
#endif
                DBG_MSG( 1, (stderr, "done) "));
            }
            wantRefresh = 1;
        }

#endif /* TRANSPARENT */
      }
    while( XCheckTypedEvent( r->Xdisplay, PropertyNotify, ev) );

#if DEBUG_LEVEL
    fputc( '\n', stderr);
#endif
#ifdef TRANSPARENT
    if( wantRefresh)
    {
        /*
         * Refresh bg vars EVEN if we're not transparent. Thus if we toggle
         * transparency later on we don't have to worry about it
         */
        refreshRootBGVars( r );
        if (r->Options & Opt_transparent)
        {
            /*
             * Let rxvt_check_our_parents worry about refreshRootBGVars failing.
             */
            rxvt_check_our_parents(r);
            r->h->want_full_refresh = 1;
        }
    }
#endif      /* TRANSPARENT */
}


/*
 * ev must either be Expose or GraphicsExpose.
 */
/* INTPROTO */
void
rxvt_process_expose (rxvt_t* r, XEvent* ev)
{
    int            page = ATAB(r);
    Window      win = (ev->type == Expose ?
                        ev->xexpose.window : ev->xgraphicsexpose.drawable );

    DBG_MSG(2, (stderr, "Got %s event.\n",
                ev->type == Expose ? "Expose" : "GraphicsExpose"));
    if (win == PVTS(r, page)->vt)
    {
        /*
         * We need to be clever about exposes (especially under oober slow Xft).
         * We group exposes, and clip to the appropriate locations.
         */

        if( r->h->refreshRegion == None )
        {
            r->h->refreshRegion = XCreateRegion();
            DBG_MSG( 3, ( stderr, "Created clip region %p\n",
                        r->h->refreshRegion));
            /* Will be freed when rxvt_scr_refresh completes */
        }

        do
          {
            XRectangle rect;

            if( ev->type == Expose)
            {
                rect.x      = ev->xexpose.x;
                rect.y      = ev->xexpose.y;
                rect.width  = ev->xexpose.width;
                rect.height = ev->xexpose.height;
            }
            else
            {
                rect.x      = ev->xgraphicsexpose.x;
                rect.y      = ev->xgraphicsexpose.y;
                rect.width  = ev->xgraphicsexpose.width;
                rect.height = ev->xgraphicsexpose.height;
            }

            XUnionRectWithRegion( &rect, r->h->refreshRegion,
                    r->h->refreshRegion);
            rxvt_scr_expose(r, page,
                    rect.x, rect.y, rect.width, rect.height,
                    False); /* Don't generate a screen refresh */


            DBG_MSG( 3, ( stderr, "Adding [%ux%u+%d+%d] to expose region\n",
                    rect.width, rect.height, rect.x, rect.y));
          }
        while(
                XCheckTypedWindowEvent( r->Xdisplay, win, Expose, ev)
                || XCheckTypedWindowEvent( r->Xdisplay, win, GraphicsExpose, ev)
             );

        r->h->refresh_type |= CLIPPED_REFRESH;
        r->h->want_clip_refresh = 1;
    }
    else
    {
        XEvent      unused_xevent;

#ifdef DEBUG_VERBOSE
        /* Debug message */
        if (rxvt_is_tabbar_win (r, win))
        {
            DBG_MSG(2, (stderr, "Expose event on tabbar\n"));
        }
# ifdef HAVE_SCROLLBARS
        else if (rxvt_is_scrollbar_win (r, win))
        {
            DBG_MSG(2, (stderr, "Expose event on scrollbar\n"));
        }
# endif
# ifdef HAVE_MENUBAR
        else if (rxvt_is_menubar_win (r, win))
        {
            DBG_MSG(2, (stderr, "Expose event on menubar\n"));
        }
# endif
#endif  /* DEBUG */

        if (rxvt_is_tabbar_win(r, win) && rxvt_tabbar_visible (r))
        {
            rxvt_tabbar_expose(r, ev);
            return;
        }

        /* fetch all expose events if possible */
        while(    XCheckTypedWindowEvent(r->Xdisplay, win,
                    Expose, &unused_xevent) ||
                XCheckTypedWindowEvent( r->Xdisplay, win,
                    GraphicsExpose, &unused_xevent)
             );

#ifdef HAVE_SCROLLBARS
        if ( rxvt_is_scrollbar_win (r, win) && rxvt_scrollbar_visible (r))
        {
            scrollbar_setIdle();
            rxvt_scrollbar_update(r, 0);
            return;
        }
#endif
#ifdef HAVE_MENUBAR
        if (rxvt_is_menubar_win(r, win) && rxvt_menubar_visible (r))
        {
            rxvt_menubar_expose(r);
            return;
        }
#endif
        /* Not reached */
    }
}


/* INTPROTO */
void
rxvt_process_motionnotify (rxvt_t* r, XEvent* ev)
{
    int                page = ATAB(r);
    Window          unused_root, unused_child;
    int                unused_root_x, unused_root_y;
    unsigned int   unused_mask;


    DBG_MSG(2, (stderr, "MotionNotify event\n"));
#ifdef POINTER_BLANK
    if ((r->Options & Opt_pointerBlank) && PVTS(r, page)->hidden_pointer)
        rxvt_pointer_unblank (r, page);
#endif
#ifdef HAVE_MENUBAR
    if (rxvt_is_menubar_win(r, ev->xmotion.window))
    {
        rxvt_menubar_control(r, &(ev->xbutton));
        return;
    }

    if (r->h->showingMenu )
    {
        rxvt_menu_select( r, &(ev->xbutton));
        return;
    }
#endif

    if ((PVTS(r, page)->PrivateModes & PrivMode_mouse_report) &&
        !(r->h->bypass_keystate))
        return;

    if (ev->xany.window == PVTS(r, page)->vt)
    {
        if ((ev->xbutton.state & (Button1Mask | Button3Mask)))
        {
            while (XCheckTypedWindowEvent(r->Xdisplay, PVTS(r, page)->vt,
                MotionNotify, ev))
                ;
            XQueryPointer(r->Xdisplay, PVTS(r, page)->vt,
                &unused_root, &unused_child,
                &unused_root_x, &unused_root_y,
                &(ev->xbutton.x), &(ev->xbutton.y),
                &unused_mask);
#ifdef MOUSE_THRESHOLD
            /* deal with a `jumpy' mouse */
            if ((ev->xmotion.time - r->h->MEvent.time) > MOUSE_THRESHOLD)
            {
#endif
                rxvt_selection_extend(r, page,
                    (ev->xbutton.x), (ev->xbutton.y),
                    (ev->xbutton.state & Button3Mask) ? 2 : 0);
#ifdef SELECTION_SCROLLING
                if (
                        ev->xbutton.y<r->TermWin.int_bwidth
                        || Pixel2Row(ev->xbutton.y)>(r->TermWin.nrow-1)
                   )
                {
                    int dist;

                    r->h->pending_scroll_selection=1;

                    /*
                    ** don't clobber the current delay if we are
                    ** already in the middle of scrolling.
                    */
                if (r->h->scroll_selection_delay<=0)
                    r->h->scroll_selection_delay = SCROLLBAR_CONTINUOUS_DELAY;

                    /*
                    ** save the event params so we can highlight
                    ** the selection in the pending-scroll loop
                    */
                r->h->selection_save_x = ev->xbutton.x;
                r->h->selection_save_y = ev->xbutton.y;
                r->h->selection_save_state = (ev->xbutton.state & Button3Mask) ? 2 : 0;

                    /* calc number of lines to scroll */
                    if (ev->xbutton.y<r->TermWin.int_bwidth)
                    {
                        r->h->scroll_selection_dir = UP;
                        dist = r->TermWin.int_bwidth - ev->xbutton.y;
                    }
                    else
                    {
                        r->h->scroll_selection_dir = DN;
                        dist = ev->xbutton.y -
                        (r->TermWin.int_bwidth + VT_HEIGHT(r));
                    }
                    r->h->scroll_selection_lines=(Pixel2Height(dist)/
                        SELECTION_SCROLL_LINE_SPEEDUP)+1;
                    MIN_IT(r->h->scroll_selection_lines,
                        SELECTION_SCROLL_MAX_LINES);
                }
                else
                {
                    /*
                    ** we are within the text window, so we
                    ** shouldn't be scrolling
                    */
                    r->h->pending_scroll_selection = 0;
                }
#endif
#ifdef MOUSE_THRESHOLD
            }
#endif
        }
    }
#ifdef HAVE_SCROLLBARS
    else if (
                rxvt_is_scrollbar_win (r, ev->xany.window)
                && scrollbar_isMotion()
            )
    {
        while (
                XCheckTypedWindowEvent(r->Xdisplay,
                    r->scrollBar.win, MotionNotify, ev)
              )
            ;

        XQueryPointer(r->Xdisplay, r->scrollBar.win,
            &unused_root, &unused_child,
            &unused_root_x, &unused_root_y,
            &(ev->xbutton.x), &(ev->xbutton.y),
            &unused_mask);
        rxvt_scr_move_to(r, page,
            scrollbar_position(ev->xbutton.y) - r->h->csrO,
            scrollbar_size());
        rxvt_scr_refresh(r, page, r->h->refresh_type & ~CLIPPED_REFRESH);
        r->h->refresh_limit = 0;
        rxvt_scrollbar_update(r, 1);
    }
#endif
}

+--202 lines: process an X event -----------------------------------------------

+--110 lines: print pipe -------------------------------------------------------


/* *INDENT-OFF* */
enum {
    C1_40 = 0x40,
        C1_41 , C1_BPH, C1_NBH, C1_44 , C1_NEL, C1_SSA, C1_ESA,
    C1_HTS, C1_HTJ, C1_VTS, C1_PLD, C1_PLU, C1_RI , C1_SS2, C1_SS3,
    C1_DCS, C1_PU1, C1_PU2, C1_STS, C1_CCH, C1_MW , C1_SPA, C1_EPA,
    C1_SOS, C1_59 , C1_SCI, C1_CSI, CS_ST , C1_OSC, C1_PM , C1_APC
};
/* *INDENT-ON* */


+-- 51 lines: process non-printing single characters ---------------------------


+-- 82 lines: process VT52 escape sequences ------------------------------------


+--162 lines: process escape sequences -----------------------------------------


+--353 lines: process CONTROL SEQUENCE INTRODUCER (CSI) sequences `ESC[' -------


#ifndef NO_FRILLS
/* ARGSUSED */
/* INTPROTO */
void
rxvt_process_window_ops(rxvt_t* r, int page, const int *args, unsigned int nargs)
{
    int                    x, y;
    unsigned int       w, h;
    XWindowAttributes   wattr;
    Window              wdummy;


    if (nargs == 0)
        return;
    switch (args[0])
    {
        /* commands */
        case 1:           /* deiconify window */
            XMapWindow (r->Xdisplay, r->TermWin.parent);
            break;
        case 2:           /* iconify window */
            XIconifyWindow (r->Xdisplay, r->TermWin.parent,
                DefaultScreen(r->Xdisplay));
            break;
        case 3:           /* set position (pixels) */
            XMoveWindow (r->Xdisplay, r->TermWin.parent, args[1], args[2]);
            break;
        case 4:           /* set size (pixels) */
            w = (unsigned int) args[2];
            h = (unsigned int) args[1];
            XResizeWindow (r->Xdisplay, r->TermWin.parent, w, h);
            r->h->want_resize = 1;
            break;
        case 5:           /* raise window */
            XRaiseWindow (r->Xdisplay, r->TermWin.parent);
            break;
        case 6:           /* lower window */
            XLowerWindow (r->Xdisplay, r->TermWin.parent);
            break;
        case 7:           /* refresh window */
            rxvt_scr_touch (r, page, True);
            break;
        case 8:           /* set size (chars) */
            w = (unsigned int) (Width2Pixel(args[2]) + r->szHint.base_width);
            h = (unsigned int) (Height2Pixel(args[1]) + r->szHint.base_height);
            XResizeWindow (r->Xdisplay, r->TermWin.parent, w, h);
            r->h->want_resize = 1;
            break;
        default:
            if (args[0] >= 24)
            {
                /* set height (chars) */
                w = (unsigned int) r->szHint.width;
                h = (unsigned int) (args[1] * r->TermWin.fheight + r->szHint.base_height);
                XResizeWindow (r->Xdisplay, r->TermWin.parent, w, h);
                r->h->want_resize = 1;
            }
            break;

        /* reports - some output format copied from XTerm */
        case 11:          /* report window state */
            XGetWindowAttributes(r->Xdisplay, r->TermWin.parent, &wattr);
            rxvt_tt_printf(r, page, "\033[%dt",
                wattr.map_state == IsViewable ? 1 : 2);
            break;
        case 13:          /* report window position */
            XGetWindowAttributes(r->Xdisplay, r->TermWin.parent, &wattr);
            XTranslateCoordinates(r->Xdisplay, r->TermWin.parent,
                wattr.root, -wattr.border_width, -wattr.border_width,
                &x, &y, &wdummy);
            rxvt_tt_printf(r, page, "\033[3;%d;%dt", x, y);
            break;
        case 14:          /* report window size (pixels) */
            XGetWindowAttributes(r->Xdisplay, r->TermWin.parent, &wattr);
            rxvt_tt_printf(r, page, "\033[4;%d;%dt", wattr.height,
                wattr.width);
            break;
        case 18:          /* report window size (chars) */
            rxvt_tt_printf(r, page, "\033[8;%d;%dt", r->TermWin.nrow,
                r->TermWin.ncol);
            break;
    }
}
#endif  /* NO_FRILLS */


/*----------------------------------------------------------------------*/
/*
 * get input up until STRING TERMINATOR (or BEL)
 * ends_how is terminator used.  returned input must be free()d
 */
/* INTPROTO */
unsigned char  *
rxvt_get_to_st(rxvt_t* r, int page, unsigned char *ends_how)
{
    int                readpage = page;
    int                seen_esc = 0;   /* seen escape? */
    unsigned int   n = 0;
    unsigned char* s;
    unsigned char   ch, string[STRING_MAX];
#ifdef DEBUG
    clock_t        checksum = PVTS(r, page)->checksum;
#endif  /* DEBUG */


    for (; (ch = rxvt_cmd_getc(r, &readpage));)
    {
        assert (readpage == page);
        assert (checksum == PVTS(r, page)->checksum);
        if (ch == C0_BEL ||
            ch == CHAR_ST ||
            (ch == 0x5c && seen_esc))    /* 7bit ST */
            break;
        if (ch == C0_ESC)
        {
            seen_esc = 1;
            continue;
        }
        else if (ch == '\t')
            ch = ' ';    /* translate '\t' to space */
        else if (ch < 0x08 || (ch > 0x0d && ch < 0x20))
        {
            /* return NULL;  */ /* other control character - exit */

            /*
            ** NO! See http://vt100.net/emu/dec_ansi_parser for reason.
            ** I am not sure what to do with CAN or SUB, but the rest
            ** should be *ignored* - I will try to find out what to do
            ** with CAN and SUB.
            **            - Johann 'Mykraverk' Oskarsson
            **              <johann@myrkraverk.com>
            */
            continue; /* do nothing */
        }

        if (n < sizeof(string) - 1)
            string[n++] = ch;

        seen_esc = 0;
    }

    string[n++] = '\0';
    if ((s = (unsigned char UNTAINTED *) STRNDUP (string, n)) == NULL)
        return NULL;
    *ends_how = (ch == 0x5c ? C0_ESC : ch);

    return s;
}


/*----------------------------------------------------------------------*/
/*
 * process DEVICE CONTROL STRING `ESC P ... (ST|BEL)' or `0x90 ... (ST|BEL)'
 */
/* INTPROTO */
void
rxvt_process_dcs_seq(rxvt_t* r, int page)
{
    unsigned char  eh, *s;

    /* Not handled yet */
    s = rxvt_get_to_st (r, page, &eh);
    if (s)
        free(s);
    return;
}

/*----------------------------------------------------------------------*/
/*
 * process OPERATING SYSTEM COMMAND sequence `ESC ] Ps ; Pt (ST|BEL)'
 */
/* INTPROTO */
void
rxvt_process_osc_seq (rxvt_t* r, int page)
{
    int                readpage = page;
    unsigned char  ch, eh, *s;
    int                arg;
#ifdef DEBUG
    clock_t        checksum = PVTS(r, page)->checksum;
#endif  /* DEBUG */


    ch = rxvt_cmd_getc(r, &readpage);
    assert (page == readpage);
    assert (checksum == PVTS(r, page)->checksum);
    for (arg = 0; isdigit(ch); ch = rxvt_cmd_getc(r, &readpage))
    {
        assert (page == readpage);
        assert (checksum == PVTS(r, page)->checksum);
        arg = arg * 10 + (ch - '0');
    }

    if (ch == ';')
    {
        s = rxvt_get_to_st(r, page, &eh);
        if (s)
        {
            /*
            ** rxvt_menubar_dispatch() violates the constness of the
            ** string, so do it here
            */
            /* XXX: currently disabled due to security concerns */
            if (arg == XTerm_Menu)
                /* rxvt_menubar_dispatch(r, (char *)s) */;
            else
                rxvt_xterm_seq(r, page, arg, (char *)s, eh);
            free(s);
        }
    }
}


/*
 * Xwsh escape sequences: ESC P Ps.y;Pt ESC \
 *       1 = change title
 *       3 = change iconName
 *       4 = set text color by string
 *       5 = set page color by string
 *       6 = set selection text color by string
 *       7 = set selection page color by string
 *       8 = set cursor text color by string
 *       9 = set cursor page color by string
 *      10 = set half intensity by string
 *      11 = set bold intensity by string
 *     101 = bind string to key Ps+1 and pass as value
 *     103 = bind string to key Ps+1 and pass s function
 */
/* INTPROTO */
void
rxvt_xwsh_seq(rxvt_t* r, int op, const char *str)
{
    assert(str != NULL);
    switch (op)
    {
        case Xwsh_title:
            rxvt_set_term_title (r, (const unsigned char*) str);
            break;
        case Xwsh_iconName:
            rxvt_set_icon_name (r, (const unsigned char*) str);
            break;
        case Xwsh_textColor:
            break;
        case Xwsh_pageColor:
            break;
        case Xwsh_selTextColor:
            break;
        case Xwsh_selPageColor:
            break;
        case Xwsh_cursorTextColor:
            break;
        case Xwsh_cursorPageColor:
            break;
        case Xwsh_halfIntColor:
            break;
        case Xwsh_boldIntColor:
            break;
        case Xwsh_bindStrKeyVal:
            break;
        case Xwsh_bindStrKeyFunc:
            break;
    }
}


/* INTPROTO */
void
rxvt_process_xwsh_seq (rxvt_t* r, int page)
{
    int                readpage = page;
    unsigned char   ch, string[STRING_MAX];
    int             arg;
#ifdef DEBUG
    clock_t        checksum = PVTS(r, page)->checksum;
#endif  /* DEBUG */


    ch = rxvt_cmd_getc (r, &readpage);
    assert (page == readpage);
    assert (checksum == PVTS(r, page)->checksum);
    for (arg = 0; isdigit((int) ch); ch = rxvt_cmd_getc(r, &readpage))
    {
        assert (page == readpage);
        assert (checksum == PVTS(r, page)->checksum);
        arg = arg * 10 + (ch - '0');
    }

    if (ch == '.')
    {
        if ((ch = rxvt_cmd_getc(r, &readpage)) == 'y')
        {
            int             n = 0;

            assert (page == readpage);
            assert (checksum == PVTS(r, page)->checksum);
            while ((ch = rxvt_cmd_getc(r, &readpage)) != '\033')
            {
                assert (page == readpage);
                assert (checksum == PVTS(r, page)->checksum);
                if (ch)
                {
                    if (ch == '\t')
                        ch = ' '; /* translate '\t' to space */
                    else if (ch < ' ')
                        return;   /* control character - exit */

                    if (n < sizeof(string) - 1)
                        string[n++] = ch;
                }
            }

            if ((ch = rxvt_cmd_getc(r, &readpage)) == '\\')
            {
                assert (page == readpage);
                assert (checksum == PVTS(r, page)->checksum);
                string[n] = '\0';
                rxvt_xwsh_seq(r, arg, (char*) string);
            }
        }
    }
}


/*
 * XTerm escape sequences: ESC ] Ps;Pt (ST|BEL)
 *     0 = change iconName/title
 *     1 = change iconName
 *     2 = change title
 *     4 = change color
 *    12 = change text color
 *    13 = change mouse foreground color 
 *    17 = change highlight character colour
 *    18 = change bold character color
 *    19 = change underlined character color 
 *    46 = change logfile (not implemented)
 *    50 = change font
 *
 * rxvt extensions:
 *    10 = menu (may change in future) (DISABLED)
 *    20 = bg pixmap
 *    39 = change default fg color
 *    49 = change default bg color
 *    55 = dump scrollback buffer and all of screen
 */
/* EXTPROTO */
void
rxvt_xterm_seq(rxvt_t* r, int page, int op, const char *str, unsigned char resp __attribute__((unused)))
{
    int            color;
    char       *buf, *name;
#if defined(TRANSPARENT) || defined(BACKGROUND_IMAGE)
    int            changed = 0;
# ifdef TINTING_SUPPORT
    int            shade;
# endif
#endif


    assert(str != NULL);
    switch (op)
    {
        case XTerm_name:
            rxvt_set_term_title(r, (const unsigned char*) str);
            /* FALLTHROUGH */
        case XTerm_iconName:
            rxvt_set_icon_name(r, (const unsigned char*) str);
            if (r->Options2 & Opt2_syncTabIcon)
                rxvt_tabbar_set_title (r, ATAB(r),
                        (const unsigned char TAINTED*) str);
            break;
        case XTerm_title:
#ifndef SET_TAB_TITLE_NOT_WIN_TITLE
            rxvt_set_term_title(r, (const unsigned char*) str);
#endif
#ifdef SET_TAB_TITLE_ON_XTERM_SEQUENCE
            rxvt_tabbar_set_title (r, page, (const unsigned char TAINTED*) str);
#endif
            break;
        case XTerm_Color:
            for (buf = (char *)str; buf && *buf;)
            {
                if ((name = STRCHR(buf, ';')) == NULL)
                    break;
                *name++ = '\0';
                color = atoi(buf);
                if (color < 0 || color >= TOTAL_COLORS)
                    break;
                if ((buf = STRCHR(name, ';')) != NULL)
                    *buf++ = '\0';
                rxvt_set_window_color(r, color + minCOLOR, name);
            }
            break;
#ifndef NO_CURSORCOLOR
        case XTerm_Color_cursor:
            rxvt_set_window_color(r, Color_cursor, str);
            break;
#endif
        case XTerm_Color_pointer:
            rxvt_set_window_color(r, Color_pointer, str);
            break;
#ifndef NO_BOLD_UNDERLINE_REVERSE
        case XTerm_Color_BD:
            rxvt_set_window_color(r, Color_BD, str);
            break;
        case XTerm_Color_UL:
            rxvt_set_window_color(r, Color_UL, str);
            break;
        case XTerm_Color_RV:
            rxvt_set_window_color(r, Color_RV, str);
            break;
#endif

        case XTerm_Menu:
            /*
             * rxvt_menubar_dispatch() violates the constness of the string,
             * so DON'T do it here.
             *
             * 2006-03-13 gi1242: Plus it's a security risk. Only interactive users
             * should control menus.
             */
            break;

#ifdef BACKGROUND_IMAGE
        case XTerm_Pixmap:
            if (*str != ';')
            {
                /* reset to default scaling */
                rxvt_scale_pixmap(r, page, "");
                /* change pixmap */
                rxvt_load_bg_pixmap(r, page, str);
                rxvt_scr_touch(r, page, True);
            }
            while ((str = STRCHR(str, ';')) != NULL)
            {
                str++;
                changed += rxvt_scale_pixmap(r, page, str);
            }
            if (changed)
            {
                rxvt_resize_pixmap(r, page);
                rxvt_scr_touch(r, page, True);
            }
            break;
#endif

        case XTerm_restoreFG:
            rxvt_set_window_color(r, Color_fg, str);
            break;
        case XTerm_restoreBG:
            rxvt_set_window_color(r, Color_bg, str);
            break;
        case XTerm_logfile:
            /* TODO Write code */
            break;
        case XTerm_font:
            rxvt_resize_on_font (r, (char*) str);
            break;

        /* 2006-03-14 gi1242 XXX: Why is this commented again? */
#if 0
        case XTerm_dumpscreen:
            {
                int          fd;
                if ((fd=open(str, O_RDWR | O_CREAT | O_EXCL, 0600))>=0)
                {
                    rxvt_scr_dump(r, page, fd);
                    close(fd);
                }
            }
            break;
#endif

        /*
         * Mrxvt extension to set tab title and terminal title
         * Example: echo "\e]61;newtitle\a"
         */
        case Xterm_tabterm:
            rxvt_set_term_title(r, (const unsigned char*) str);
            /* FALLTHROUGH */
        case Xterm_tab:
            rxvt_tabbar_set_title (r, page, (const unsigned char TAINTED*) str);
            break;

        /*
         * 2006-02-20 gi1242: These escape sequences are disabled for a possible
         * security flaw. A malicious user might be able to send a few escape
         * sequences through a text file, giving him more control than he should
         * have over the tabs.
         *
         * On that note, even the escape sequences for hiding or showing the tabbar
         * / scroll bar / menubar have been disabled. These aren't really a security
         * risk, however the user can access these functions through either keyboard
         * macros, or the popup menu, so these are really just code bloat :).
         *
         * Only the local user should be able to create / close / move tabs.
         */
+-- 84 lines: #if 0 DISABLED FOR SECURITY REASONS ------------------------------

        /*
         * 2006-03-13 gi1242: The following are not security risks, but are
         * unnecessary. Only an interactive user needs such control, and he can have
         * it using macros / menus.
         */
+-- 13 lines: #if 0 DISABLED because macros are more useful --------------------

#ifdef MULTICHAR_SET
        case Xterm_encode:
            /* We only change encoding method, but not font ;-) */
            rxvt_set_multichar_encoding (r, str);
            break;
#endif  /* MULTICHAR_SET */

        case Xterm_opacity:
            if (None != r->h->xa[XA_NET_WM_WINDOW_OPACITY])
            {
                int     oldopacity = r->TermWin.opacity;
                int     tmp;

                if ('-' == *str && (char) 0 == *(str+1))
                {
                    /* handle '-' only, remember it's opposite  */
                    tmp = (r->h->rs[Rs_opacityDegree]) ?
                            r->TermWin.opacity_degree : 1;
                }
                else if ('+' == *str && (char) 0 == *(str+1))
                {
                    /* handle '+' only, remember it's opposite  */
                    tmp = (r->h->rs[Rs_opacityDegree]) ?
                            -(r->TermWin.opacity_degree) : -1;
                }
                else
                {
                    /* other cases, remember it's opposite  */
                    tmp = 100 - atoi (str);
                    /* only change opacity when it is valid */
                    if (tmp < 0 || tmp > 100)
                        tmp = oldopacity;
                }
                if ('-' == *str || '+' == *str)
                    /* use input as offset */
                    r->TermWin.opacity += tmp;
                else
                    /* use input as absolute value */
                    r->TermWin.opacity = tmp;
                if (r->TermWin.opacity < 0)
                    r->TermWin.opacity = 0;
                if (r->TermWin.opacity > 100)
                    r->TermWin.opacity = 100;
                /* only change opacity when it has changed */
                if (r->TermWin.opacity != oldopacity)
                    rxvt_set_opacity (r);
            }
            break;

        case Xterm_tabfg:
        case Xterm_tabbg:
        case Xterm_itabfg:
        case Xterm_itabbg:
            rxvt_tabbar_change_color (r, op, str);
            break;

#if defined(TRANSPARENT) || defined(BACKGROUND_IMAGE)
# ifdef TINTING_SUPPORT
        case Xterm_tint:
            if (ISSET_PIXCOLOR (r->h, Color_tint) &&
                r->h->rs[Rs_shade])
                rxvt_set_window_color(r, Color_tint, str);
            break;

        case Xterm_bgfade:    /* Make bgfade behave like shade */
        case Xterm_shade:
            if (!ISSET_PIXCOLOR (r->h, Color_tint) ||
                !r->h->rs[Rs_shade])
                break;

            if( *str == '+' || *str == '-' )
            {
                /* Relative shade level */
                shade = (100 - r->TermWin.shade) + atoi(str);
            }
            else
                /* Absolute shade level */
                shade = atoi (str);

            if (shade >=0 && shade <= 100)
            {
                shade = 100 - shade;    /* reverse it */
                changed = (r->TermWin.shade != shade);
                r->TermWin.shade = shade;
            }

            if (changed)
            {
                /* shade value is changed, need to refresh terminals */
                rxvt_refresh_bg_image (r, page, False);
            }
            break;
# endif /* TINTING_SUPPORT */
#endif  /* TRANSPARENT || BACKGROUND_IMAGE */

+-- 14 lines: #if 0 OBSOLETE HOTKEY CODE ---------------------------------------

        case Xterm_termenv:
            PVTS(r, page)->termenv = rxvt_get_termenv ((const char*) str);
            break;

        default:
            break;
    }
}
/*----------------------------------------------------------------------*/


+--255 lines: process DEC private mode sequences `ESC [ ? Ps mode' -------------

+--133 lines: process sgr sequences --------------------------------------------

+-- 31 lines: process Rob Nation's own graphics mode sequences -----------------

/* ------------------------------------------------------------------------- */

+--303 lines: Read and process output from the application ---------------------




#define UNICODE
#include <windows.h>

int main(int argc, char **argv)
{
    int speed1 = 0, speed2 = 0, speed = 0;
    printf("Set Mouse Speed by Maverick\n");

    SystemParametersInfo(SPI_GETMOUSESPEED, 0, &speed, 0);
    printf("Current speed: %2d\n", speed);

    if (argc == 1) return 0;
    if (argc >= 2) sscanf(argv[1], "%d", &speed1);
    if (argc >= 3) sscanf(argv[2], "%d", &speed2);

    if (argc == 2)
    { // set speed to fixed value
      speed = speed1;
    }
}


