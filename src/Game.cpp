#include "Game.hpp"
#include "Config.hpp"

Game::Game() {
    SDL_Point size = {1280, 720};
    /** TODO: Fix order dependency */
    this->window = std::make_unique<Window>("TicTacToe", size, &sharedContext);
    this->sharedContext.window = this->window.get();
    this->sharedContext.config = new Config();
    this->sharedContext.resMgr = new Resource_Manager();
    this->stateMgr = std::make_unique<StateManager>(&sharedContext);
}

void Game::Update() {
    UpdateWindowAndState();
    UpdateAndPrintFPS();
}



void Game::UpdateWindowAndState() {
    window->Update();
    stateMgr->Update();
}

void Game::UpdateAndPrintFPS() {
    frameCount++;
    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 scale = 1;
    if (currentFrameTime - lastFPSTime >= 1000 / scale) {
        fps = frameCount * scale;
        frameCount = 0;
        lastFPSTime = currentFrameTime;
        std::cout << "FPS: " << fps << std::endl;
    }
}

void Game::HandleInput() {
}

void Game::Render() {
    this->window->BeginDraw();
    this->stateMgr->Render();
    this->window->EndDraw();
}

Window *Game::GetWindow() {
    return this->window.get();
}