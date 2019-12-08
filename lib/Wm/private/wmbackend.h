/****************************************
 *
 *   INSERT-PROJECT-NAME-HERE - INSERT-GENERIC-NAME-HERE
 *   Copyright (C) 2019 Victor Tran
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * *************************************/
#ifndef WMBACKEND_H
#define WMBACKEND_H

#include <QObject>
#include "../desktopwmwindow.h"

class WmBackend : public QObject
{
        Q_OBJECT
    public:
        explicit WmBackend();

        virtual QList<DesktopWmWindowPtr> openWindows() = 0;
        virtual DesktopWmWindowPtr activeWindow() = 0;
        virtual QStringList desktops() = 0;
        virtual uint currentDesktop() = 0;
        virtual void setCurrentDesktop(uint desktopNumber) = 0;

    signals:
        void windowAdded(DesktopWmWindowPtr window);
        void windowRemoved(DesktopWmWindowPtr window);
        void desktopCountChanged();
        void currentDesktopChanged();
        void activeWindowChanged();

    public slots:
};

#endif // WMBACKEND_H
