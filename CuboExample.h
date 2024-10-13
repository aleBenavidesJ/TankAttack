#ifndef CUBOEXAMPLE_H
#define CUBOEXAMPLE_H

#pragma once

#include <mesh_instance3d.hpp>

#include <packed_scene.hpp>

namespace godot {

    class CuboExample : public MeshInstance3D {
        GDCLASS(CuboExample, MeshInstance3D)

    protected:
        static void _bind_methods();

    public:
        CuboExample();
        ~CuboExample();

        void _process(double delta) override;

        void set_velocity_rotation(const float velocity);

        float get_velocity_rotation() const;

        void _ready() override;



    //EXPORT
    private:
        float velocityRotation{ 1 };
       
        




    };

}

#endif

