#include <algorithm>

#include "StateManager.hpp"
#include "State_Play.hpp"
#include "State_Menu.hpp"

StateManager::StateManager(SharedContext *p_shared)
    : m_shared(p_shared) {
    RegisterState<State_Menu>(StateType::MainMenu);
    RegisterState<State_Play>(StateType::Play);
    this->CreateState(StateType::MainMenu);
}

StateManager::~StateManager() {
    for (auto &itr : m_states) {
        itr.second->OnDestroy();
        delete itr.second;
    }
}

void StateManager::Update() {
    if (m_states.empty()) {
        return;
    }
    if (m_states.back().second->IsTranscendent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTranscendent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->Update();
        }
    } else {
        m_states.back().second->Update();
    }
}

void StateManager::HandleInput() {
    if (m_states.empty()) {
        return;
    }
    if (m_states.back().second->IsTranscendent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTranscendent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->HandleInput();
        }
    } else {
        m_states.back().second->HandleInput();
    }
}

void StateManager::Render() {
    if (m_states.empty()) {
        return;
    }
    if(m_states.back().second->IsTransparent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while(itr != m_states.begin()) {
            if(itr != m_states.end()) {
                if(!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for(; itr != m_states.end(); ++itr) {
            itr->second->Render();
        }
    } else {
        m_states.back().second->Render();
    }
}

SharedContext *StateManager::GetContext() {
    return m_shared;
}

bool StateManager::HasState(const StateType &p_type) {
    for (auto itr = m_states.begin();
            itr != m_states.end(); ++itr) {
        if (itr->first == p_type) {
            auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), p_type);
            if (removed == m_toRemove.end()) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void StateManager::ProcessRequests() {
    while (m_toRemove.begin() != m_toRemove.end()) {
        RemoveState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::SwitchTo(const StateType &p_type) {
    for (auto itr = m_states.begin();
            itr != m_states.end(); ++itr) {
        if (itr->first == p_type) {
            m_states.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState *tmp_state = itr->second;
            m_states.erase(itr);
            m_states.emplace_back(tmp_type, tmp_state);
            tmp_state->Activate();
            return;
        }
    }
    // State with p_type wasn't found.
    if (!m_states.empty()) {
        m_states.back().second->Deactivate();
    }
    CreateState(p_type);
    m_states.back().second->Activate();
}

void StateManager::Remove(const StateType &p_type) {
    m_toRemove.push_back(p_type);
}

// Private methods.

void StateManager::CreateState(const StateType &p_type) {
    auto newState = m_stateFactory.find(p_type);
    if (newState == m_stateFactory.end()) {
        return;
    }
    BaseState *state = newState->second();
    m_states.emplace_back(p_type, state);
    state->OnCreate();
}

void StateManager::RemoveState(const StateType &p_type) {
    for (auto itr = m_states.begin();
            itr != m_states.end(); ++itr) {
        if (itr->first == p_type) {
            itr->second->OnDestroy();
            delete itr->second;
            m_states.erase(itr);
            return;
        }
    }
}