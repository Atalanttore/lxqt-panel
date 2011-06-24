/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/projects/razor-qt/
 *
 * Copyright: 2011 Razor team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef RAZORTASKBUTTON_H
#define RAZORTASKBUTTON_H

#include <QtGui/QToolButton>
#include <QtCore/QHash>
#include <QtGui/QProxyStyle>

#include <X11/X.h>
#include <X11/Xlib.h>

class QPainter;
class QPalette;

class ElidedButtonStyle: public QProxyStyle
{
public:
    ElidedButtonStyle(QStyle* style=0): QProxyStyle(style) {}

    void drawItemText(QPainter* painter, const QRect& rect, int flags,
                      const QPalette & pal, bool enabled, const QString & text,
                      QPalette::ColorRole textRole = QPalette::NoRole ) const;
};


class RazorTaskButton : public QToolButton
{
    Q_OBJECT
public:
    explicit RazorTaskButton(const Window window, QWidget *parent = 0);
    virtual ~RazorTaskButton();

    bool isAppHidden() const;
    bool isApplicationActive() const;
    Window windowId() const { return mWindow; }

    QSize   sizeHint() const;
    static void unCheckAll();
    int desktopNum() const;

public slots:
    void raiseApplication();
    void minimizeApplication();
    void maximizeApplication();
    void deMaximizeApplication();
    void shadeApplication();
    void unShadeApplication();
    void closeApplication();
    void moveApplicationToDesktop();
    void setApplicationLayer();

    void handlePropertyNotify(XPropertyEvent* event);

protected:
    void nextCheckState();
    void contextMenuEvent( QContextMenuEvent* event);

    void updateText();
    void updateIcon();

private:
    Window mWindow;
    static RazorTaskButton* mCheckedBtn;
    ElidedButtonStyle mStyle;

private slots:
    void btnClicked(bool checked);
    void checkedChanged(bool checked);
};

typedef QHash<Window,RazorTaskButton*> RazorTaskButtonHash;

#endif // RAZORTASKBUTTON_H