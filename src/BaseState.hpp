#pragma once



class StateManager;

class BaseState {
    friend class StateManager;
  public:
    BaseState(StateManager *p_stateManager)
        :stateMgr(p_stateManager), m_transparent(false),
         m_transcendent(false) {}
    virtual ~BaseState() {}

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

    void SetTransparent(const bool &p_transparent) {
        m_transparent = p_transparent;
    }
    bool IsTransparent()const {
        return m_transparent;
    }
    void SetTranscendent(const bool &p_transcendence) {
        m_transcendent = p_transcendence;
    }
    bool IsTranscendent()const {
        return m_transcendent;
    }

    StateManager *GetStateManager() {
        return stateMgr;
    }
  protected:
    StateManager *stateMgr;
    bool m_transparent;
    bool m_transcendent;

};