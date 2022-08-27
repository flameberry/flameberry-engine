#include "Scene.h"
#include "Core/Core.h"

namespace Flameberry {
    Entity Scene::CreateEntity()
    {
        if (m_FreeEntities.size())
        {
            uint64_t id = m_FreeEntities.back();
            m_Entities[id] = Entity{ id };
            m_FreeEntities.pop_back();
            return Entity{ id };
        }
        m_Entities.emplace_back(m_Entities.size());
        return m_Entities.back();
    }

    void Scene::DestroyEntity(Entity& entity)
    {
        for (auto& commandPool : m_ComponentPools)
        {
            if (commandPool->GetComponentAddress(entity.entityId))
                commandPool->RemoveEntityId(entity.entityId);
        }
        m_Entities[entity.entityId].SetValidity(false);
        entity.SetValidity(false);
        m_FreeEntities.push_back(entity.entityId);
    }
}