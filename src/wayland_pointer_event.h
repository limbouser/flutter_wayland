#pragma once

#include <wayland-client.h>

namespace flutter {

class EventPointerDelegate {
  public:
    virtual void OnEnter(wl_fixed_t surface_x, wl_fixed_t surface_y) = 0;
    virtual void OnLeave() = 0;
    virtual void OnMotion(uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y) = 0;
    virtual void OnButton(uint32_t time, uint32_t button, uint32_t state) = 0;
    virtual void OnAxis(uint32_t time, uint32_t axis, wl_fixed_t value) = 0;
};

}