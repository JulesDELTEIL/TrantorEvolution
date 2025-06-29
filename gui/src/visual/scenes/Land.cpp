/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include <cstdlib>
#include <ctime>

#include "maths.hpp"
#include "map_tools.h"
#include "visual/AScene.hpp"
#include "visual/scenes/Land.hpp"
#include "visual/visual.hpp"

namespace gui {
namespace visual {

Land::Land(std::reference_wrapper<network::Client> client) : AScene(core::DEFAULT_VIEW),
    _client(client), _loading(core::DEFAULT_VIEW), _hud(std::ref(_teams))
{
    std::srand(std::time({}));
    _tile.sprite.setOrigin({TILE_SIZE / 2, 0.0f});
    _tile.texture.loadFromFile(BIOME_TEXTURE_PATH);
    _tile.sprite.setTexture(_tile.texture);
    _net = std::thread(&Land::askResources, this);
}

Land::~Land()
{
    if (_net_running) {
        _net_running = false;
        _net.join();
    }
}

void Land::display(sf::RenderTarget& render)
{
    if (!_map_set) {
        render.setView(_camera);
        _loading.draw(render);
        return;
    }
    _backgroud.drawBackground(render);
    render.setView(_camera);
    clearResources();
    moveToDest();
    drawEdge(render, -1);
    drawEdge(render, false);
    for (auto& tileY : _tiles) {
        for (auto& tileX : tileY.second) {
            tileX.second.tile->draw(render, _clock);
            for (auto& resource : tileX.second.resources)
                resource.second->draw(render);
            if (tileX.second.incantation_objects != nullptr)
                tileX.second.incantation_objects->draw(render);
        }
    }
    for (auto& trantor : _trantorians)
        trantor.second->draw(render, _clock);
    for (const auto& egg: _eggs)
        egg.second->draw(render);
    drawEdge(render, true);
    _backgroud.drawWaterfall(render, _map_size);
    _hud.display(render, _clock);
}


void Land::event(const core::Engine& engine, const network::NetEventPack& net_pack)
{
    if (!_map_set) {
        loadingEvents(net_pack);
        return;
    }
    viewEvent(engine.events);
    checkHudEvent(engine, net_pack);
    switch (static_cast<int>(net_pack.event)) {
        case network::TILE:
            updateTile(net_pack.pack);
            break;
        case network::NEW:
            addTrantorian(net_pack.pack);
            break;
        case network::PPOS:
            posTrantorian(net_pack.pack);
            break;
        case network::TIME:
            _time_unit_speed = net_pack.pack[0].getSize_t();
            break;
        case network::PGET:
            trantorCollect(net_pack.pack);
            break;
        case network::PINC:
            trantorStartIncantation(net_pack.pack);
            break;
        case network::PEINC:
            trantorEndIncantation(net_pack.pack);
            break;
        case network::PEGG:
            trantorLayingAnEgg(net_pack.pack);
            break;
        case network::ELAID:
            trantorLaidAnEgg(net_pack.pack);
            break;
        case network::ENEW:
            eggHatching(net_pack.pack);
            break;
        case network::PDEAD:
            removeTrantorian(net_pack.pack);
            break;
        case network::PINV:
            updateInventory(net_pack.pack);
            break;
        case network::PLVL:
            _trantorians.at(net_pack.pack[0].getSize_t())->lvl = net_pack.pack[1].getSize_t();
            break;
    }
}

void Land::loadingEvents(const network::NetEventPack& net_pack)
{
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _map_size = sf::Vector2f(net_pack.pack[0].getFloat(), net_pack.pack[1].getFloat());
            break;
        case network::BIOME:
            addTile(net_pack.pack);
            break;
        case network::TEAMS:
            _teams.push_back({net_pack.pack[0].getString(), RANDOM_COLOR, {}});
            break;
        case network::NEW:
            addTrantorian(net_pack.pack);
            break;
        case network::TILE:
            updateTile(net_pack.pack);
            break;
        case network::TIME:
            _time_unit_speed = net_pack.pack[0].getSize_t();
            break;
    }
}

biome_e Land::getCenterTileType(const sf::Vector2f &map_center)
{
    for (const auto& tileY : _tiles) {
        for (const auto& tileX : tileY.second) {
            sf::Vector2f tile_top = tileX.second.tile->getPos();
            sf::Vector2f tile_bot = GET_TILE_BOT(tile_top);
            sf::Vector2f tile_left = GET_TILE_LEFT(tile_top);
            sf::Vector2f tile_right = GET_TILE_RIGHT(tile_top);
            if (hitTriangle(sf::Vector2f(map_center), tile_top, tile_bot, tile_left) ||
                hitTriangle(sf::Vector2f(map_center), tile_top, tile_bot, tile_right)) {
                return tileX.second.tile->getBiome();
            }
        }
    }
    return EMPTY;
}

void Land::updateAmbiantSound()
{
    sf::Vector2f camera_center = _camera.getCenter();
    biome_e biome = getCenterTileType(camera_center);

    if (biome == EMPTY || biome == last_song_biome)
        return;
    biome_song.playSong(song_map.at(biome));
    last_song_biome = biome;
}

void Land::viewEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::E)
            return zoom(0.9);
        if (event.key.code == sf::Keyboard::A)
            return zoom(1.1);
        if (event.key.code == sf::Keyboard::D)
            move(MOV_FACTOR, 0);
        if (event.key.code == sf::Keyboard::Q)
            move(-MOV_FACTOR, 0);
        if (event.key.code == sf::Keyboard::S)
            move(0, MOV_FACTOR);
        if (event.key.code == sf::Keyboard::Z)
            move(0, -MOV_FACTOR);
        updateAmbiantSound();
    }
    if (_selected_tr != -1 && _trantorians.find(_selected_tr) != _trantorians.end()) {
        _camera.setCenter(_trantorians.at(_selected_tr)->actual_pos);;
    }
}

void Land::askResources(void)
{
    _net_running = true;
    float ms_to_wait = 0;

    while (!_map_set)
        std::this_thread::yield();
    ms_to_wait = (_map_size.x * _map_size.y) * 10;
    while (_net_running) {
        for (size_t y = 0; y < _map_size.y; ++y) {
            for (size_t x = 0; x < _map_size.x; ++x) {
                _client.get().sendData("bct " + std::to_string(x) + " " + std::to_string(y));
            }
        }
        for (const auto& trantor : _trantorians) {
            std::string id =  std::to_string(trantor.first);
            _client.get().sendData("pin " + id);
            _client.get().sendData("plv " + id);
        }
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(ms_to_wait));
    }
}

void Land::drawEdge(sf::RenderTarget& render, int bottom)
{
    sf::Vector2f pos;
    int mx = -1;
    int my = -1;

    _tile.sprite.setTextureRect(TEXTURE_RECT.at(SEA));
    if (bottom) {
        my = _map_size.y;
        mx = _map_size.x;
    }
    if (bottom == -1) {
        pos = MAP_POS(CENTER_MAP(_map_size.y), -1, -1);
        _tile.sprite.setPosition(pos);
        render.draw(_tile.sprite);
        return;
    }
    for (int y = 0; y <= _map_size.y + bottom; ++y) {
        pos = MAP_POS(CENTER_MAP(_map_size.y), mx, y);
        _tile.sprite.setPosition(pos);
        render.draw(_tile.sprite);
    }
    for (int x = 0; x <= _map_size.x + bottom; ++x) {
        pos = MAP_POS(CENTER_MAP(_map_size.y), x, my);
        _tile.sprite.setPosition(pos);
        render.draw(_tile.sprite);
    }
}

void Land::addTile(const network::NetPack& pack)
{
    static int index = 0;
    sf::Vector2f pos = {0, 0};
    biome_e type = static_cast<biome_e>(pack[2].getInt());

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    _tiles[x][y].tile = std::make_unique<Tile>(std::ref(_tile), pos, type);
    for (size_t i = 2; i < NB_MAP_ARG; ++i) {
        _tiles[x][y].resources[static_cast<resource_e>(i - 2)] =
            std::make_shared<ResourceNode>(pos, static_cast<resource_e>(i - 2), 0);
            _tiles[x][y].tile->updateResource(static_cast<resource_e>(i - 2), 0);
    }
    index += 1;
    _loading.loadingPercent(static_cast<float>(index) / (_map_size.x * _map_size.y));
    if (index >= (_map_size.x * _map_size.y)) {
        _map_set = true;
        _hud.setLaunch(_trantorians.size(), _time_unit_speed);
    }
}

void Land::updateTile(const network::NetPack& pack)
{
    sf::Vector2f pos = {0.0f, 0.0f};

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    for (size_t i = 2; i < NB_MAP_ARG; ++i) {
        _tiles[x][y].resources.at(static_cast<resource_e>(i - 2))->updateQuantity(pack[i].getSize_t());
        _tiles[x][y].tile->updateResource(static_cast<resource_e>(i - 2), pack[i].getSize_t());
    }
}

void Land::clearResources(void)
{
    for (ClearTile& to_clear : _clear_resources) {
        if (_clock.getElapsedTime().asMilliseconds() >= to_clear.time) {
            _tiles[to_clear.tile.x][to_clear.tile.y].resources[to_clear.type]->lowerQuantity(1);
            _tiles[to_clear.tile.x][to_clear.tile.y].tile->lowerResource(to_clear.type, 1);
        }
    }
}

void Land::addTrantorian(const network::NetPack& pack)
{
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    int tId = 0;
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    std::shared_ptr<Trantorian> newT = nullptr;

    for (auto& team : _teams) {
        if (!team.name.compare(pack[5].getString())) {
            newT = std::make_shared<Trantorian>(pos, sf::Vector2i(x, y),
                pack[4].getSize_t(), tId, team.color);
            team.trantorians[pack[0].getSize_t()] = newT;
            _tiles[x][y].trantorians[pack[0].getSize_t()] = newT;
            _trantorians[pack[0].getSize_t()] = newT;
        }
        tId += 1;
    }
}

void Land::removeTrantorian(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    if (_trantorians.find(id) == _trantorians.end())
        return;
    std::shared_ptr<Trantorian> trantor = _trantorians.at(id);

    _tiles[trantor->map_pos.x][trantor->map_pos.y].trantorians.erase(id);
    _teams.at(_trantorians.at(id)->team).trantorians.erase(id);
    _trantorians.erase(id);
    trantor = nullptr;
}

void Land::trantorCollect(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    if (_trantorians.find(id) == _trantorians.end())
        return;
    sf::Vector2i tile_pos = _trantorians.at(id)->map_pos;
    resource_e type = static_cast<resource_e>(pack[1].getInt());

    _trantorians.at(id)->collect(_tiles[tile_pos.x][tile_pos.y].resources.at(type), ACT_TIME(7.0f) / 2, _clock);
    _clear_resources.push_back({ACT_TIME(7.0f) + _clock.getElapsedTime().asMilliseconds(), type, tile_pos});
}

void Land::trantorStartIncantation(const network::NetPack& pack)
{
    int x = pack[0].getInt();
    int y = pack[1].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    
    _tiles[x][y].incantation_objects = std::make_shared<IncantationObject>(pos);
    for (size_t index = 3; index < pack.size(); index++) {
        _trantorians.at(pack[index].getSize_t())->startIncantation(_tiles[x][y].incantation_objects, ACT_TIME(7.0f) / 2, _clock);
    }
}

void Land::trantorEndIncantation(const network::NetPack& pack)
{
    int x = pack[0].getInt();
    int y = pack[1].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    
    for (const auto &trantor : _tiles[x][y].trantorians) {
        trantor.second->endIncantation(pos, ACT_TIME(7.0f) / 2, _clock);
    }
}

void Land::trantorLayingAnEgg(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    
    if (_trantorians.find(id) == _trantorians.end())
        return;
    _trantorians.at(id)->layAnEgg();
}

void Land::trantorLaidAnEgg(const network::NetPack& pack)
{
    size_t egg_id = pack[0].getSize_t();
    size_t id = pack[1].getSize_t();
    if (_trantorians.find(id) == _trantorians.end() ||
        _eggs.find(egg_id) == _eggs.end())
        return;
    sf::Vector2f egg_pos = _trantorians.at(id)->getBodyPos(0);
    egg_pos.x += 5;
    
    _trantorians.at(id)->laidAnEgg();
    _eggs.emplace(egg_id, std::make_shared<Egg>(egg_pos));
}

void Land::eggHatching(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();

    if (_eggs.find(id) == _eggs.end())
        return;
    _eggs.at(id)->hatch();
}

void Land::posTrantorian(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    if (_trantorians.find(id) == _trantorians.end())
        return;
    std::shared_ptr<Trantorian> trantor = _trantorians.at(id);
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos;

    if (trantor->map_pos.x != x || trantor->map_pos.y != y) {
        pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
        trantor->changeTile(pos, ACT_TIME(7.0f), _clock);
        _tiles[trantor->map_pos.x][trantor->map_pos.y].trantorians.erase(id);
        trantor->map_pos = {x, y};
        _tiles[x][y].trantorians[id] = trantor;
    }
}

void Land::updateInventory(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();

    if (_trantorians.find(id) == _trantorians.end())
        return;
    _trantorians.at(id)->updateInventory(
        pack[3].getSize_t(), pack[4].getSize_t(), pack[5].getSize_t(),
        pack[6].getSize_t(), pack[7].getSize_t(), pack[8].getSize_t(),
        pack[9].getSize_t()
    );
}

void Land::checkHudEvent(const core::Engine& engine, const network::NetEventPack& net_pack)
{
    _hud.event(engine.events, net_pack);
    if (engine.events.type == sf::Event::KeyPressed) {
        if (engine.events.key.code == sf::Keyboard::Escape)
            _selected_tr = -1;
    }
    if (engine.events.type == sf::Event::MouseButtonPressed) {
        if (engine.events.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mpos = sf::Mouse::getPosition(engine.window);
            _selected_tr = _hud.hitHudTeamInfo(mpos);
            if (_selected_tr != -1);
            else {
                hitTile(engine.window.mapPixelToCoords(mpos, _camera));
                _selected_tr = -1;
                _hud.clearTrantorInfo();
            }
        }
    }
}

bool Land::hitTile(const sf::Vector2f& mpos)
{
    for (const auto& tileY : _tiles) {
        for (const auto& tileX : tileY.second) {
            sf::Vector2f tile_top = tileX.second.tile->getPos();
            sf::Vector2f tile_bot = GET_TILE_BOT(tile_top);
            sf::Vector2f tile_left = GET_TILE_LEFT(tile_top);
            sf::Vector2f tile_right = GET_TILE_RIGHT(tile_top);
            if (hitTriangle(mpos, tile_top, tile_bot, tile_left) ||
                hitTriangle(mpos, tile_top, tile_bot, tile_right)) {
                _hud.changeTileInfo(tileX.second.tile);
                _hud.updateInfo(_clock);
                return true;
            }
        }
    }
    return true;
}

} // visual
} // gui
