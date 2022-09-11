#pragma once

#include <memory>
#include "ComponentPool.h"

namespace Flameberry {
    class Registry;

    template<typename T, typename... ComponentTypes>
    class scene_view_iterator
    {
    private:
        using value_type = std::tuple<ComponentTypes*...>;
        using reference_type = value_type&;
    public:
        scene_view_iterator(const Registry& registry, const utils::sparse_set::const_iterator& entityIdIterator, const utils::sparse_set::const_iterator& cend);

        scene_view_iterator& operator++();
        scene_view_iterator operator++(int);
        bool operator==(const scene_view_iterator& other);
        bool operator!=(const scene_view_iterator& other);
        reference_type operator*() { return *_ComponentTuple; }
    private:
        const Registry& _Registry;
        utils::sparse_set::const_iterator _EntityIdIterator;
        utils::sparse_set::const_iterator _End;
        std::shared_ptr<value_type> _ComponentTuple;
    };

    template<typename... ComponentTypes>
    class SceneView
    {
    public:
        using iterator = scene_view_iterator<SceneView, ComponentTypes...>;
    public:
        SceneView(const Registry& registry, const std::shared_ptr<ComponentPool>& componentPool);

        iterator begin();
        iterator end();
    private:
        bool m_Null = false;
        const Registry& m_Registry;
        std::shared_ptr<ComponentPool> m_ComponentPool;
    };
}

#include "Registry.h"

namespace Flameberry {
    static void print_transform(const TransformComponent& comp)
    {
        FL_LOG(
            "Transform component is\nposition: {0}, {1}, {2}\nrotation: {3}, {4}, {5}\nscale: {6}, {7}, {8}",
            comp.translation.x,
            comp.translation.y,
            comp.translation.z,
            comp.rotation.x,
            comp.rotation.y,
            comp.rotation.z,
            comp.scale.x,
            comp.scale.y,
            comp.scale.z
        );
    }

    template<typename T, typename... ComponentTypes>
    scene_view_iterator<T, ComponentTypes...>::scene_view_iterator(const Registry& registry, const utils::sparse_set::const_iterator& entityIdIterator, const utils::sparse_set::const_iterator& cend)
        : _Registry(registry), _EntityIdIterator(entityIdIterator), _End(cend)
    {
        if (_EntityIdIterator != _End)
            _ComponentTuple = std::make_shared<value_type>(_Registry.GetComponent<ComponentTypes>(entity_handle{ *_EntityIdIterator }) ...);
    }

    template<typename T, typename... ComponentTypes>
    scene_view_iterator<T, ComponentTypes...>& scene_view_iterator<T, ComponentTypes...>::operator++()
    {
        while ((++_EntityIdIterator) != _End && !_Registry.Has<ComponentTypes...>(entity_handle{ *_EntityIdIterator }));
        if (_EntityIdIterator != _End)
            (*_ComponentTuple) = std::make_tuple<ComponentTypes*...>(_Registry.GetComponent<ComponentTypes>(entity_handle{ *_EntityIdIterator }) ...);
        return *this;
    }

    template<typename T, typename... ComponentTypes>
    scene_view_iterator<T, ComponentTypes...> scene_view_iterator<T, ComponentTypes...>::operator++(int)
    {
        scene_view_iterator iterator = *this;
        ++(*this);
        return iterator;
    }

    template<typename T, typename... ComponentTypes>
    bool scene_view_iterator<T, ComponentTypes...>::operator==(const scene_view_iterator<T, ComponentTypes...>& other)
    {
        return _EntityIdIterator == other._EntityIdIterator;
    }

    template<typename T, typename... ComponentTypes>
    bool scene_view_iterator<T, ComponentTypes...>::operator!=(const scene_view_iterator<T, ComponentTypes...>& other)
    {
        return !(*this == other);
    }

    // ------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------

    template<typename... ComponentTypes>
    SceneView<ComponentTypes...>::SceneView(const Registry& registry, const std::shared_ptr<ComponentPool>& componentPool)
        : m_Registry(registry), m_ComponentPool(componentPool)
    {
        if (!componentPool)
            m_Null = true;
    }

    template<typename... ComponentTypes>
    typename SceneView<ComponentTypes...>::iterator SceneView<ComponentTypes...>::begin()
    {
        const auto& entityIdSet = m_ComponentPool->GetEntityIdSet();
        if (m_Null)
            return iterator(m_Registry, entityIdSet.cend(), entityIdSet.cend());

        for (utils::sparse_set::iterator it = entityIdSet.begin(); it != entityIdSet.end(); it++)
        {
            if (m_Registry.Has<ComponentTypes...>(*it))
                return iterator(m_Registry, utils::sparse_set::const_iterator(it.get()), entityIdSet.cend());
        }
        m_Null = true;
        return iterator(m_Registry, entityIdSet.cend(), entityIdSet.cend());
    }

    template<typename... ComponentTypes>
    typename SceneView<ComponentTypes...>::iterator SceneView<ComponentTypes...>::end()
    {
        return iterator(m_Registry, m_ComponentPool->GetEntityIdSet().cend(), m_ComponentPool->GetEntityIdSet().cend());
    }
}