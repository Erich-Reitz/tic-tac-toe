#include "Game.hpp"
#include "Config.hpp"

Game::Game() {
    SDL_Point size = {1280, 720};
    /** TODO: Fix order dependency */
    this->window = std::make_unique<Window>("TicTacToe", size, &sharedContext);
    this->sharedContext.window = this->window.get();
    this->sharedContext.config = new tt::Config();
    this->board = std::make_unique<TicTacToeBoard>(&sharedContext);
}

void Game::Update() {
    this->window->Update();
    if (this->sharedContext.gameState == GameState::PLAYING) {
        this->board->Update();
    }
}

void Game::HandleInput() {
}

void Game::Render() {
    this->window->BeginDraw();
    this->board->Render(this->window->Renderer());
    this->window->EndDraw();
}

Window *Game::GetWindow() {
    return this->window.get();
}