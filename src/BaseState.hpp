#pragma once



class StateManager;

class BaseState {
    friend class StateManager;
  public:
    BaseState(StateManager *p_stateManager);
    virtual ~BaseState() {}

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

    void SetTransparent(const bool &p_transparent);
    bool IsTransparent()const ; 
    void SetTranscendent(const bool &p_transcendence);
    bool IsTranscendent()const ;


  protected:
    StateManager *stateMgr;
    bool m_transparent;
    bool m_transcendent;

};