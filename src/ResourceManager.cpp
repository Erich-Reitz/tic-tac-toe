#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <optional>
#include <filesystem>
namespace fs = std::filesystem;

struct FileNode {
    std::string path;
    std::string resName;
} typedef FileNode;

std::vector<FileNode> loadDirFileNames(std::string path);

Resource_Manager::Resource_Manager() {
    load_fonts();
}

Resource_Manager::~Resource_Manager() {
    for (auto &font : fonts) {
        TTF_CloseFont( font.second );
    }
}


std::unordered_map<std::string, TTF_Font *> Resource_Manager::get_fonts() {
    return fonts;
}

TTF_Font *Resource_Manager::get_font(std::string fontName) {
    return fonts.at(fontName);
}

std::optional<TTF_Font *> load_ttf_font_from_file(const FileNode &file, int ptrSize) {
    TTF_Font *font = TTF_OpenFont( file.path.c_str(), ptrSize);
    if (font == nullptr) {
        return {};
    }
    return font;
}

void Resource_Manager::load_fonts() {
    std::vector<FileNode> files = loadDirFileNames("assets/fonts/");
    for (const auto &file : files) {
        if (const auto font = load_ttf_font_from_file(file, 50).value_or(nullptr)) {
            std::cout << "Loaded font: " << file.resName << std::endl;
            fonts[file.resName] = font;
        } else {
            std::cout << "Error loading font: " << TTF_GetError()  << std::endl;
        }
    }
}


std::vector<FileNode> loadDirFileNames(std::string path) {
    std::vector<FileNode> files;
    // load all files in path
    for (auto &entry : fs::directory_iterator(path)) {
        FileNode file;
        file.path = entry.path().string();
        file.resName = entry.path().filename().string();
        files.push_back(file);
    }
    return files;
}