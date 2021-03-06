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
#include "waylandscreenbackend.h"

#include <tlogger.h>
#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include "waylandscreen.h"

struct WaylandScreenBackendPrivate {
    WaylandScreenBackend* parent;
    wl_display* display;
    wl_seat* seat;

    QMap<zwlr_output_head_v1*, WaylandScreen*> heads;
};

WaylandScreenBackend::WaylandScreenBackend() : ScreenBackend() {
    d = new WaylandScreenBackendPrivate();

    d->parent = this;
    d->display = reinterpret_cast<wl_display*>(qApp->platformNativeInterface()->nativeResourceForIntegration("display"));

    wl_registry_listener listener = {
        [](void* data, wl_registry * registry, quint32 name, const char* interface, quint32 version) {
            WaylandScreenBackendPrivate* backend = static_cast<WaylandScreenBackendPrivate*>(data);
            if (strcmp(interface, zwlr_output_manager_v1_interface.name) == 0) {
                backend->parent->QtWayland::zwlr_output_manager_v1::init(registry, name, version);
            } else if (strcmp(interface, wl_seat_interface.name) == 0) {
                wl_seat* seat = static_cast<wl_seat*>(wl_registry_bind(registry, name, &wl_seat_interface, std::min(version, static_cast<quint32>(1))));
                backend->seat = seat;
            }
        },
        [](void* data, wl_registry * registry, quint32 name) {
            Q_UNUSED(data)
            Q_UNUSED(registry)
            Q_UNUSED(name)
        }
    };

    wl_registry* registry = wl_display_get_registry(d->display);
    wl_registry_add_listener(registry, &listener, d);
    wl_display_roundtrip(d->display);

    if (!this->QtWayland::zwlr_output_manager_v1::isInitialized()) {
        tWarn("WaylandScreenBackend") << "The compositor doesn't support the wlr-output-management protocol";
    }
    wl_registry_destroy(registry);
}

WaylandScreenBackend::~WaylandScreenBackend() {
    delete d;
}

bool WaylandScreenBackend::isSuitable() {
    return QGuiApplication::platformName().startsWith(QLatin1String("wayland"), Qt::CaseInsensitive);
}

QList<SystemScreen*> WaylandScreenBackend::screens() {
    QList<SystemScreen*> screens;
    for (WaylandScreen* screen : d->heads.values()) {
        screens.append(screen);
    }
    return screens;
}

SystemScreen* WaylandScreenBackend::primaryScreen() {
    //TODO: Implement
    return nullptr;
}

int WaylandScreenBackend::dpi() const {
    //TODO: Implement
    return 96;
}

void WaylandScreenBackend::setDpi(int dpi) {
    //TODO: Implement
}

void WaylandScreenBackend::zwlr_output_manager_v1_head(zwlr_output_head_v1* head) {
    d->heads.insert(head, new WaylandScreen(head));
}

void WaylandScreenBackend::zwlr_output_manager_v1_done(uint32_t serial) {
}

void WaylandScreenBackend::zwlr_output_manager_v1_finished() {
}
