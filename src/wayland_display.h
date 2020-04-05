// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <EGL/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>

#include <memory>
#include <string>

#include "flutter_application.h"
#include "wayland_pointer_event.h"
#include "macros.h"

namespace flutter {

class WaylandDisplay : public FlutterApplication::RenderDelegate {
 public:

  void SetPointerEventDelegate(EventPointerDelegate& event_pointer_delegate) {
    event_pointer_delegate_ = event_pointer_delegate;
  }

  WaylandDisplay(size_t width, size_t height);

  ~WaylandDisplay();

  bool IsValid() const;

  bool Run();

 private:
  static const wl_registry_listener kRegistryListener;
  static const wl_shell_surface_listener kShellSurfaceListener;
  static const wl_pointer_listener kPointerListener;
  static const wl_seat_listener kSeatListener;
  bool valid_ = false;
  const int screen_width_;
  const int screen_height_;
  wl_display* display_ = nullptr;
  wl_registry* registry_ = nullptr;
  wl_compositor* compositor_ = nullptr;
  wl_shell* shell_ = nullptr;
  wl_shell_surface* shell_surface_ = nullptr;
  wl_surface* surface_ = nullptr;
  wl_egl_window* window_ = nullptr;
  EGLDisplay egl_display_ = EGL_NO_DISPLAY;
  EGLSurface egl_surface_ = nullptr;
  EGLContext egl_context_ = EGL_NO_CONTEXT;

  // input devices
  wl_seat *seat_ = nullptr;
  static EventPointerDelegate& event_pointer_delegate_;
    
  bool SetupEGL();

  void AnnounceRegistryInterface(struct wl_registry* wl_registry,
                                 uint32_t name,
                                 const char* interface,
                                 uint32_t version);

  void UnannounceRegistryInterface(struct wl_registry* wl_registry,
                                   uint32_t name);

  bool StopRunning();

  // |flutter::FlutterApplication::RenderDelegate|
  bool OnApplicationContextMakeCurrent() override;

  // |flutter::FlutterApplication::RenderDelegate|
  bool OnApplicationContextClearCurrent() override;

  // |flutter::FlutterApplication::RenderDelegate|
  bool OnApplicationPresent() override;

  // |flutter::FlutterApplication::RenderDelegate|
  uint32_t OnApplicationGetOnscreenFBO() override;

  static EventPointerDelegate& GetEventPointerDelegate()
  {
    return event_pointer_delegate_;    
  }

  static void PointerEnter(void *data, struct wl_pointer *wl_pointer,
    uint32_t serial, struct wl_surface *surface, 
    wl_fixed_t surface_x, wl_fixed_t surface_y)
  {
    GetEventPointerDelegate().OnEnter(surface_x, surface_y);
  }

  static void PointerLeave(void *data,
    struct wl_pointer *wl_pointer,
    uint32_t serial, struct wl_surface *surface)
  {
    GetEventPointerDelegate().OnLeave();
  }

  static void PointerMotion(void *data,
    struct wl_pointer *wl_pointer, uint32_t time,
    wl_fixed_t surface_x, wl_fixed_t surface_y)
  {
    GetEventPointerDelegate().OnMotion(time, surface_x, surface_y);
  }

  static void PointerButton(void *data,
    struct wl_pointer *wl_pointer,
    uint32_t serial, uint32_t time,
    uint32_t button, uint32_t state)
  {
    GetEventPointerDelegate().OnButton(time, button, state);
  }

  static void PointerAxis(void *data,
    struct wl_pointer *wl_pointer,
    uint32_t time, uint32_t axis, wl_fixed_t value)
  {
    GetEventPointerDelegate().OnAxis(time, axis, value);
  }

  FLWAY_DISALLOW_COPY_AND_ASSIGN(WaylandDisplay);
};

}  // namespace flutter
