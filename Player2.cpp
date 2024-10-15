#include "Player2.h"
#include "Map.h"
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/classes/tile_map.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

using namespace godot;

Player2::Player2() {
    ground_tile_map = nullptr;
    selected_tank = nullptr;
    player2 = nullptr;
    map_cpp_node = nullptr;
    path_index = -1;
}

Player2::~Player2() {}

void Player2::_ready() {
    map_cpp_node = Object::cast_to<Map>(get_parent()->get_parent());
    ground_tile_map = Object::cast_to<TileMap>(get_parent());
    player2 = this;

    if (!map_cpp_node) {
        UtilityFunctions::print("Error: Nodo 'map_cpp_node' no encontrado.");
    }
    else {
        UtilityFunctions::print("map_cpp_node asignado correctamente.");
    }

    UtilityFunctions::print("Player1 encontrado: ", player2 != nullptr);
    //UtilityFunctions::print("Ground TileMap encontrado: ", ground_tile_map != nullptr);
    set_process(true);
}

void Player2::_process(double delta) {
    if (selected_tank) {
        Vector2 mouse_position = get_global_mouse_position();
        Sprite2D* turret = cast_to<Sprite2D>(selected_tank->find_child("Turret"));

        if (turret) {
            turret->look_at(mouse_position);
        }

        if (path.size() > 0 && path_index >= 0) {
            Vector2i cell_position = path[path_index];
            Vector2 local_position = ground_tile_map->map_to_local(cell_position);
            Vector2 target_position = ground_tile_map->to_global(local_position);
            Vector2 current_position = selected_tank->get_global_position();
            Vector2 direction = (target_position - current_position).normalized();
            float speed = 800.0f;
            selected_tank->set_velocity(direction * speed);
            selected_tank->move_and_slide();
            if (current_position.distance_to(target_position) < 5.0) {
                path_index--;
            }
        }
    }
}

/*void Player2::_process(double delta) {
    if (selected_tank) {
        Vector2 mouse_position = get_global_mouse_position();
        Sprite2D* turret = cast_to<Sprite2D>(selected_tank->find_child("Turret"));
        if (turret) {
            turret->look_at(mouse_position);
        }
        if (path.size() > 0 && path_index >= 0) {
            Vector2i cell_position = path[path_index];
            Vector2 local_position = ground_tile_map->map_to_local(cell_position);
            Vector2 target_position = ground_tile_map->to_global(local_position);
            Vector2 current_position = selected_tank->get_global_position();
            Vector2 direction = (target_position - current_position).normalized();
            float target_rotation = direction.angle();
            float current_rotation = selected_tank->get_rotation();
            float rotation_speed = 2.0f;
            float new_rotation = current_rotation + Math::lerp_angle(current_rotation, target_rotation, static_cast<float>(rotation_speed * delta));
            selected_tank->set_rotation(new_rotation);
            float speed = 800.0f;
            selected_tank->set_velocity(direction * speed);
            selected_tank->move_and_slide();
            if (current_position.distance_to(target_position) < 5.0f) {
                path_index--;
            }
        }
    }
}*/

void Player2::_bind_methods() {
    ClassDB::bind_method(D_METHOD("handle_left_click"), &Player2::handle_left_click);
    ClassDB::bind_method(D_METHOD("handle_right_click"), &Player2::handle_right_click);
}

void Player2::_input(const Ref<InputEvent>& event) {
    Ref<InputEventMouseButton> mouse_event = event;
    if (mouse_event.is_valid()) {
        if (mouse_event->is_pressed()) {
            if (mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) {
                handle_left_click();
            }
            else if (mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_RIGHT) {
                handle_right_click();
            }
        }
    }
}

void Player2::handle_left_click() {
    Vector2 mouse_position = get_global_mouse_position();
    std::vector<CharacterBody2D*> tanks;
    tanks.push_back(cast_to<CharacterBody2D>(player2->find_child("Tank1")));
    tanks.push_back(cast_to<CharacterBody2D>(player2->find_child("Tank2")));
    CharacterBody2D* clicked_tank = nullptr;

    for (CharacterBody2D* tank : tanks) {
        if (tank) {
            Vector2 tank_position = tank->get_global_position();
            CollisionShape2D* tank_shape = cast_to<CollisionShape2D>(tank->find_child("CollisionShape2D"));
            if (tank_shape) {
                Ref<RectangleShape2D> rect_shape = tank_shape->get_shape();
                if (rect_shape.is_valid()) {
                    Vector2 size = rect_shape->get_size();
                    Rect2 rect(tank_position - size * 0.5, size);
                    if (rect.has_point(mouse_position)) {
                        clicked_tank = tank;
                        break;
                    }
                }
            }
        }
    }

    if (clicked_tank) {
        selected_tank = clicked_tank;
        UtilityFunctions::print("Tanque seleccionado: ", selected_tank->get_name());
    }
    else {
        selected_tank = nullptr;
        UtilityFunctions::print("No hay tanque seleccionado.");
    }
}

/*void Player2::handle_right_click() {
    if (selected_tank && map_cpp_node && ground_tile_map) {
        Vector2 mouse_position = get_global_mouse_position();
        Vector2 tank_global_position = selected_tank->get_global_position();
        Vector2i grid_position = ground_tile_map->local_to_map(ground_tile_map->to_local(mouse_position));
        Vector2i tank_grid_position = ground_tile_map->local_to_map(ground_tile_map->to_local(tank_global_position));
        UtilityFunctions::print("Posición del ratón en celdas: ", grid_position);
        UtilityFunctions::print("Posición del tanque en celdas: ", tank_grid_position);
        Array path = map_cpp_node->bfsPath(tank_grid_position, grid_position);
        if (path.size() > 0) {
            UtilityFunctions::print("Camino encontrado.");
            for (int i = path.size() - 1; i >= 0; --i) {
                Vector2i current_cell = path[i];
                UtilityFunctions::print("Tanque movido a celda: ", current_cell);
                Vector2 local_pos = ground_tile_map->map_to_local(current_cell);
                Vector2 global_pos = ground_tile_map->to_global(local_pos);
                selected_tank->set_global_position(global_pos);
            }
            UtilityFunctions::print("Camino completo en celdas: ", path);
        }
        else {
            UtilityFunctions::print("No hay camino disponible para el tanque.");
        }
    }
    else {
        UtilityFunctions::print("Error: ground_tile_map, map_cpp_node o selected_tank no están disponibles.");
    }
}*/

void Player2::handle_right_click() {
    if (selected_tank && map_cpp_node && ground_tile_map) {
        Vector2 mouse_position = get_global_mouse_position();
        Vector2 tank_global_position = selected_tank->get_global_position();
        Vector2i grid_position = ground_tile_map->local_to_map(ground_tile_map->to_local(mouse_position));
        Vector2i tank_grid_position = ground_tile_map->local_to_map(ground_tile_map->to_local(tank_global_position));
        UtilityFunctions::print("Posición del ratón en celdas: ", grid_position);
        UtilityFunctions::print("Posición del tanque en celdas: ", tank_grid_position);
        path = map_cpp_node->movementPlayer1(tank_grid_position, grid_position);
        if (path.size() > 0) {
            UtilityFunctions::print("Camino encontrado.");
            path_index = path.size() - 1;
        }
        else {
            UtilityFunctions::print("No hay camino disponible para el tanque.");
        }
    }
}