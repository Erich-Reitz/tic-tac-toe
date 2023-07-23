#include "BaseState.hpp"
#include "StateManager.hpp"

BaseState::BaseState(StateManager *p_stateManager)
    :stateMgr(p_stateManager), m_transparent(false),
     m_transcendent(false) {}


void BaseState::SetTransparent(const bool &p_transparent) {
    m_transparent = p_transparent;
}

void BaseState::SetTranscendent(const bool &p_transcendence) {
    m_transcendent = p_transcendence;
}


bool BaseState::IsTransparent() const {
    return m_transparent;
}


bool BaseState::IsTranscendent() const {
    return m_transcendent;
}

