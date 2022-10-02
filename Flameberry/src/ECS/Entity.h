#pragma once

#include "Component.h"

#define MAX_ENTITIES 1000

namespace Flameberry {
    class entity_handle
    {
    public:
        entity_handle() = default;
        entity_handle(uint64_t entityId) : handle(entityId), validity(true) {}
        entity_handle(uint64_t entityId, bool validity) : handle(entityId), validity(validity) {}

        inline bool is_valid() const { return validity; }
        inline void set_validity(bool val) { validity = val; }

        // Returns the entity handle i.e. a unique uint64_t value
        inline uint64_t get() const { return handle; }
        inline void set_handle(uint64_t entity_handle) { handle = entity_handle; }

        bool operator==(const entity_handle& entity)
        {
            return handle == entity.get() && validity;
        }
        bool operator!=(const entity_handle& entity)
        {
            return !(*this == entity);
        }
    private:
        uint64_t handle;
        bool validity;
    };
}