/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** Land.cpp
*/

#include <iostream> // test purpose (to delete)

#include <cstdlib>
#include <ctime>

#include "maths.hpp"
#include "visual/scenes/Land.hpp"
#include "visual/visual.hpp"

namespace gui {
namespace visual {

Land::Land() : AScene(core::DEFAULT_VIEW)
{
    std::srand(std::time({}));
    _tile.sprite.setOrigin({TILE_SIZE / 2, 0.0f});
    _tile.texture.loadFromFile(BIOME_TEXTURE_PATH);
    _tile.sprite.setTexture(_tile.texture);
}

void Land::display(sf::RenderTarget& render)
{
    render.setView(_camera);
    clearResources();
    for (auto& tileY : _tiles) {
        for (auto& tileX : tileY.second) {
            tileX.second.tile->draw(render, _clock);
            for (auto& resource : tileX.second.resources)
                resource.second->draw(render);
        }
    }
    for (auto& trantor : _trantorians)
        trantor.second->draw(render, _clock);
    // render.setView(render.getDefaultView());
    _hud.display(render, _clock);
}

void Land::event(const core::Engine& engine, const network::NetEventPack& net_pack)
{
    viewEvent(engine.events);
    checkHudEvent(engine);
    switch (static_cast<int>(net_pack.event)) {
        case network::MSIZE:
            _map_size = sf::Vector2f(net_pack.pack[0].getFloat(), net_pack.pack[1].getFloat());
            break;
        case network::TILE:
            if (!_map_set && _map_size.y != -1)
                loadTile(net_pack.pack);
            else
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
        case network::PDEAD:
            removeTrantorian(net_pack.pack);
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

void Land::loadTile(const network::NetPack& pack)
{
    static int index = 0;
    sf::Vector2f pos = {0, 0};
    biome_e type = EMPTY;

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    type = readBiomeType(pack);
    _tiles[x][y].tile = std::make_unique<Tile>(std::ref(_tile), pos, type);
    for (size_t i = 2; i < NB_MAP_ARG; ++i)
        _tiles[x][y].resources[static_cast<resource_e>(i - 2)] =
            std::make_shared<ResourceNode>(pos, static_cast<resource_e>(i - 2), pack[i].getSize_t());
    index += 1;
    if (index >= (_map_size.x * _map_size.y))
        _map_set = true;
}

biome_e Land::readBiomeType(const network::NetPack& pack)
{
    int biome_pack[NB_RESOURCES] = {};

    for (short i = 2; i < NB_RESOURCES + 2; ++i)
        biome_pack[i - 2] = pack[i].getInt();
    for (short b = 0; b < NB_BIOMES; ++b)
        for (short i = 0; i < NB_RESOURCES; ++i) {
            if (biome_distributions[b].biome_start[i] != biome_pack[i])
                break;
            else if (i + 1 == NB_RESOURCES)
                return static_cast<biome_e>(b);
        }
    return biome_e::EMPTY;
}

void Land::updateTile(const network::NetPack& pack)
{
    sf::Vector2f pos = {0.0f, 0.0f};

    int x = pack[0].getInt();
    int y = pack[1].getInt();
    pos = MAP_POS(CENTER_MAP(_map_size.y), x, y);
    for (size_t i = 2; i < NB_MAP_ARG; ++i)
        _tiles[x][y].resources.at(static_cast<resource_e>(i - 2))->updateQuantity(pack[i].getSize_t());
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

void Land::checkHudEvent(const core::Engine& engine)
{
    _hud.event(engine.events);
    if (engine.events.type == sf::Event::MouseButtonPressed) {
        if (engine.events.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mpos = sf::Mouse::getPosition(engine.window);
            mpos.x += getViewPos().x;
            mpos.y += getViewPos().y;
            if (hitTrantor(mpos))
                _hud.changeStatus(HudType_e::TRANTOR_INFO);
            else if (hitTile(mpos))
                _hud.changeStatus(HudType_e::TILE_INFO);
        }
    }
}

bool Land::hitTrantor(const sf::Vector2i&)
{
    for (const auto& trantor : _trantorians) {
        _hud.changeTrantorInfo(trantor.second);
        return true;
    }
    return false;
}

bool Land::hitTile(const sf::Vector2i& mpos)
{
    for (const auto& tileY : _tiles) {
        for (const auto& tileX : tileY.second) {
            sf::Vector2f tile_top = tileX.second.tile->getPos();
            sf::Vector2f tile_bot = GET_TILE_BOT(tile_top);
            sf::Vector2f tile_left = GET_TILE_LEFT(tile_top);
            sf::Vector2f tile_right = GET_TILE_RIGHT(tile_top);
            if (hitTriangle(sf::Vector2f(mpos), tile_top, tile_bot, tile_left) ||
                hitTriangle(sf::Vector2f(mpos), tile_top, tile_bot, tile_right)) {
                _hud.changeTileInfo(tileX.second.tile);
                return true;
            }
        }
    }
    return true;
}

} // visual
} // gui
