#ifndef MAP_H
#define MAP_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/tile_map.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <vector>
#include <unordered_map>

namespace godot {

    struct Vector2iHash {
        std::size_t operator()(const Vector2i& vec) const {
            return std::hash<int>()(vec.x) ^ std::hash<int>()(vec.y);
        }
    };

    class Map : public Node2D {
        GDCLASS(Map, Node2D)

    private:
        Vector2i map_size;
        TileMap* ground_tile_map;
        std::vector<std::vector<std::vector<int>>> adjacency_matrix;

    public:
        static void _bind_methods();
        void _ready();
        void fill_adjacency_matrix();
        void print_adjacency_matrix();
        bool is_valid_position(const Vector2i& pos);
        bool is_connected(const Vector2i& from, const Vector2i& to);
        TypedArray<Vector2i> randomMovement(const Vector2i& start, const Vector2i& goal);
        TypedArray<Vector2i> movementPlayer1(const Vector2i& start, const Vector2i& goal);
        TypedArray<Vector2i> movementPlayer2(const Vector2i& start, const Vector2i& goal);
        TypedArray<Vector2i> bfsPath(const Vector2i& start, const Vector2i& goal);
        TypedArray<Vector2i> dijkstraPath(const Vector2i& start, const Vector2i& goal);
    };

}

#endif
