#ifndef PLAYER3_H
#define PLAYER3_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/tile_map.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include "map.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

class Player3 : public Node2D {
    GDCLASS(Player3, Node2D);

private:
    TileMap* ground_tile_map;
    CharacterBody2D* selected_tank;
    Map* map_cpp_node;
    Node2D* player3;
    Array path;
    int path_index;
    float speed;

public:
    Player3();
    ~Player3();

    void _ready();
    void _process(double delta);
    void _input(const Ref<InputEvent>& event);
    void handle_left_click();
    void handle_right_click();

protected:
    static void _bind_methods();
};

#endif // PLAYER2_H