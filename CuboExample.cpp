#include "CuboExample.h"
#include <engine.hpp>
#include <utility_functions.hpp>


#include "audio_stream_player.hpp"


using namespace godot;


CuboExample::CuboExample()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

CuboExample::~CuboExample()
{

}

void CuboExample::_bind_methods()
{
    //property in editor
    ClassDB::bind_method(D_METHOD("get_velocity_rotation"), &CuboExample::get_velocity_rotation);
    ClassDB::bind_method(D_METHOD("set_velocity_rotation", "velocityRotation"), &CuboExample::set_velocity_rotation);
    ClassDB::add_property("CuboExample", PropertyInfo(Variant::FLOAT, "velocityRotation"), "set_velocity_rotation", "get_velocity_rotation");

}

void CuboExample::_ready()
{
    if (Engine::get_singleton()->is_editor_hint()) return;
    UtilityFunctions::print("hola mundo Godot 3D");
    
}

void CuboExample::_process(double delta)
{
    
    if (Engine::get_singleton()->is_editor_hint()) return;
    rotate_y(velocityRotation * delta);
}

void CuboExample::set_velocity_rotation(const float velocity) {
    velocityRotation = velocity;
}

float CuboExample::get_velocity_rotation() const {
    return velocityRotation;
}
