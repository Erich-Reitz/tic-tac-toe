#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "State_Menu.hpp"
#include "StateManager.hpp"
#include "TextObject.hpp"

#define M_WHITE 255, 255, 255, 255



State_Menu::State_Menu(StateManager *p_stateManager) : BaseState(p_stateManager) {};

State_Menu::~State_Menu() = default;




void State_Menu::OnCreate() {
    auto context = stateMgr->GetContext();
    auto font = context->resMgr->get_font("menu.ttf") ;
    const auto center = context->window->Center();
    const auto helloMsgPosition = SDL_Point {center.x, center.y - 150};
    helloMessage = new TextObject(helloMsgPosition, 200, 600, context, "Tic Tac Toe", font, context->config->WHITE);
    const auto startMsgPosition = SDL_Point {center.x - 175, center.y  + 50};
    startMessage = new TextObject(startMsgPosition, 100, 175, context, "Start", font, context->config->WHITE);
    const auto quitMsgPosition = SDL_Point {center.x +  175, center.y  + 50};
    quitMessage = new TextObject(quitMsgPosition, 100, 175, context, "Quit", font, context->config->WHITE);
}

void State_Menu::OnDestroy() {
    delete this->helloMessage ;
}

void State_Menu::handleClick(SDL_Point point)  {
    if (startMessage->WithinBounds(point)) {
        stateMgr->SwitchTo(StateType::Play) ;
    } else if (quitMessage->WithinBounds(point)) {
        stateMgr->GetContext()->window->SetDone();
    }
}

void State_Menu::Update() {
    auto context = stateMgr->GetContext();
    while (context->mouseClicks.size() != 0) {
        auto click = context->mouseClicks.front();
        handleClick(click);
        context->mouseClicks.pop_front();
    }
}


void State_Menu::Render() {
    const auto renderer = stateMgr->GetContext()->window->Renderer();
    this->helloMessage->Render(renderer);
    this->startMessage->Render(renderer);
    this->quitMessage->Render(renderer);
}

void State_Menu::Play() {
    stateMgr->SwitchTo(StateType::Play);
}

void State_Menu::Activate() {}

void State_Menu::Deactivate() {}

