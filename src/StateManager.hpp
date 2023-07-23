#pragma once
#include <vector>
#include <unordered_map>
#include <functional>

#include "Shared_Context.hpp"
#include "BaseState.hpp"


enum class StateType { MainMenu, Play };

// State container.
using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
// Type container.
using TypeContainer = std::vector<StateType>;
// State factory.
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager {
  public:
    StateManager(SharedContext *p_shared);
    ~StateManager();

    void Update();
    void Render();

    void ProcessRequests();

    SharedContext *GetContext();
    bool HasState(const StateType &p_type);

    void SwitchTo(const StateType &p_type);
    void Remove(const StateType &p_type);
  private:
    // Methods.
    void CreateState(const StateType &p_type);
    void RemoveState(const StateType &p_type);

    template<class T>
    void RegisterState(const StateType &p_type) {
        m_stateFactory[p_type] = [this]() -> BaseState* {
            return new T(this);
        };
    }

    // Members.
    SharedContext *m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};