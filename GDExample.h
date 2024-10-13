#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <sprite2d.hpp>

namespace godot {

	class GDExample : public Sprite2D {
		GDCLASS(GDExample, Sprite2D)

	protected:
		static void _bind_methods();

	public:
		GDExample();
		~GDExample();

		void _process(double delta) override;

		void _ready() override;


	private:
		double time_passed{ 0 };
		double time_emit{ 0 };
		double amplitude{ 1 };
		double speed{ 0 };

	public:
		void set_amplitude(const double p_amplitude);
		double get_amplitude() const;
	};

}

#endif

