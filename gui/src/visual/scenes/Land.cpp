/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include <cstdlib>
#include <ctime>

#include "maths.hpp"
#include "visual/scenes/Land.hpp"
#include "visual/visual.hpp"

namespace gui {
namespace visual {

Land::Land(std::reference_wrapper<network::Client> client) : AScene(core::DEFAULT_VIEW), _client(client)
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
    _backgroud.drawBackground(render);
    render.setView(_camera);
    clearResources();
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
    drawEdge(render, true);
    _backgroud.drawWaterfall(render, _map_size);
    _hud.display(render, _clock);
}


void Land::event(const core::Engine& engine, const network::NetEventPack& net_pack)
{
    viewEvent(engine.events);
    checkHudEvent(engine, net_pack);
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _map_size = sf::Vector2f(net_pack.pack[0].getFloat(), net_pack.pack[1].getFloat());
            break;
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
        case network::PDEAD:
            removeTrantorian(net_pack.pack);
            break;
        case network::TEAMS:
            _teams[net_pack.pack[0].getString()] = {};
            break;
        case network::BIOME:
            addTile(net_pack.pack);
            break;
    }
}

void Land::viewEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::D)
            move(10, 0);
        if (event.key.code == sf::Keyboard::Q)
            move(-10, 0);
        if (event.key.code == sf::Keyboard::S)
            move(0, 10);
        if (event.key.code == sf::Keyboard::Z)
            move(0, -10);
        if (event.key.code == sf::Keyboard::E)
            zoom(0.9);
        if (event.key.code == sf::Keyboard::A)
            zoom(1.1);
    }
}

void Land::askResources(void)
{
    _net_running = true;
    float last_check = 0;

    while (_net_running) {
        float time_to_asked = (_map_size.x * _map_size.y) * 10;
        if (time_to_asked > 60000)
            time_to_asked = 60000;
        if (_clock.getElapsedTime().asMilliseconds() > last_check + time_to_asked) {
            for (size_t y = 0; y < _map_size.y; ++y) {
                for (size_t x = 0; x < _map_size.x; ++x) {
                    _client.get().sendData("bct " + std::to_string(x) + " " + std::to_string(y));
                }
            }
            last_check = _clock.getElapsedTime().asMilliseconds();
        }
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
    if (index >= (_map_size.x * _map_size.y))
        _map_set = true;
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
            _tiles[to_clear.tile.x][to_clear.tile.y].resources[to_clear.type]->updateQuantity(0);
        }
    }
}

void Land::addTrantorian(const network::NetPack& pack)
{
    int x = pack[1].getInt();
    int y = pack[2].getInt();
    sf::Vector2f pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    std::shared_ptr<Trantorian> newT = std::make_shared<Trantorian>(pos, sf::Vector2i(x, y), pack[4].getSize_t(), pack[5].getString());

    _teams[pack[5].getString()].push_back(newT);
    _tiles[x][y].trantorians[pack[0].getSize_t()] = newT;
    _trantorians[pack[0].getSize_t()] = newT;
}

void Land::removeTrantorian(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
    std::shared_ptr<Trantorian> trantor = _trantorians.at(id);

    _tiles[trantor->map_pos.x][trantor->map_pos.y].trantorians.erase(id);
    _trantorians.erase(id);
    trantor = nullptr;
}

void Land::trantorCollect(const network::NetPack& pack)
{
    sf::Vector2i tile_pos = _trantorians.at(pack[0].getSize_t())->map_pos;
    resource_e type = static_cast<resource_e>(pack[1].getInt());

    _trantorians.at(pack[0].getSize_t())->collect(_tiles[tile_pos.x][tile_pos.y].resources, ACT_TIME(7.0f) / 2, _clock);
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

void Land::posTrantorian(const network::NetPack& pack)
{
    size_t id = pack[0].getSize_t();
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

void Land::checkHudEvent(const core::Engine& engine, const network::NetEventPack& net_pack)
{
    _hud.event(engine.events, net_pack);
    if (engine.events.type == sf::Event::MouseButtonPressed) {
        if (engine.events.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mpos = engine.window.mapPixelToCoords(sf::Mouse::getPosition(engine.window), _camera);
            if (hitTile(mpos))
                _hud.changeStatus(HudType_e::TILE_INFO);
            else
                _hud.changeStatus(HudType_e::NO_INFO);
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
                _hud.updateInfo();
                return true;
            }
        }
    }
    return true;
}

} // visual
} // gui
