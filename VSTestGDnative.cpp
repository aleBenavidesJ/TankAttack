#include "VSTestGDnative.h"

#include <utility_functions.hpp>
#include <engine.hpp>

using namespace godot;


VSTestGDnative::VSTestGDnative()
{
	if (Engine::get_singleton()->is_editor_hint()) return;
}

VSTestGDnative::~VSTestGDnative()
{
	if (Engine::get_singleton()->is_editor_hint()) return;
}

void VSTestGDnative::_bind_methods()
{
	if (Engine::get_singleton()->is_editor_hint()) return;
}

void VSTestGDnative::_ready()
{
	if (Engine::get_singleton()->is_editor_hint()) return;

	/*UtilityFunctions::print("hola mundo  visual studio");
	UtilityFunctions::print("hola mundo  visual studio");
	UtilityFunctions::print("hola mundo  visual studio");
	UtilityFunctions::print("hola mundo  visual studio");*/
	
}

void VSTestGDnative::_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint()) return;


}


