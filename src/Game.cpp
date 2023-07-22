#include "Game.hpp"
#include "Config.hpp"

Game::Game() {
    SDL_Point size = {1280, 720};
    /** TODO: Fix order dependency */
    this->window = std::make_unique<Window>("TicTacToe", size, &sharedContext);
    this->sharedContext.window = this->window.get();
    this->sharedContext.config = new tt::Config();
    this->stateMgr = std::make_unique<StateManager>(&sharedContext);
    this->stateMgr->SwitchTo(StateType::Play);
}

void Game::Update() {
    // Update the window and the state manager
    UpdateWindowAndState();
    // Update FPS and print it every second
    UpdateAndPrintFPS();
    // Optionally, use the deltaTime for smooth movement or time-based updates
    // UpdateObjects(deltaTime);
}



void Game::UpdateWindowAndState() {
    window->Update();
    stateMgr->Update();
}

void Game::UpdateAndPrintFPS() {
    // Calculate FPS
    frameCount++;
    Uint32 currentFrameTime = SDL_GetTicks();
    if (currentFrameTime - lastFPSTime >= 1000) { // Every 1000ms (1 second)
        fps = frameCount;
        frameCount = 0;
        lastFPSTime = currentFrameTime;
        // Optionally, you can print or display the FPS value somewhere
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