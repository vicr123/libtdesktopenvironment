/****************************************
 *
 *   INSERT-PROJECT-NAME-HERE - INSERT-GENERIC-NAME-HERE
 *   Copyright (C) 2021 Victor Tran
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
#include "layershellwindow.h"

#include <private/qwaylandwindow_p.h>
#include "private/layershellsurface.h"

struct LayerShellWindowPrivate {
    LayerShellSurface* surface;
};

LayerShellWindow* LayerShellWindow::forWindow(QWindow* window) {
    QtWaylandClient::QWaylandWindow* waylandWindow = dynamic_cast<QtWaylandClient::QWaylandWindow*>(window->handle());
    if (!waylandWindow) return nullptr;

    LayerShellSurface* surface = qobject_cast<LayerShellSurface*>(waylandWindow->shellSurface());
    if (!surface) return nullptr;

    return new LayerShellWindow(surface);
}

LayerShellWindow::~LayerShellWindow() {
    delete d;
}

void LayerShellWindow::setLayer(Layer layer) {
    d->surface->setLayer(layer);
}

void LayerShellWindow::setExclusiveZone(quint32 exclusiveZone) {
    d->surface->setExclusiveZone(exclusiveZone);
}

void LayerShellWindow::setAnchors(Anchors anchors) {
    d->surface->setAnchor(anchors);
}

void LayerShellWindow::setKeyboardInteractivity(KeyboardInteractivity interactivity) {
    d->surface->setKeyboardInteractivity(interactivity);
}

LayerShellWindow::LayerShellWindow(LayerShellSurface* surface) : QObject(surface) {
    d = new LayerShellWindowPrivate();
    d->surface = surface;
}
