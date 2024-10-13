#pragma once

#ifndef VSTESTGDNATIVE_H
#define VSTESTGDNATIVE_H

#include <node.hpp>

namespace godot {

	class VSTestGDnative : public Node {
		GDCLASS(VSTestGDnative, Node)

	protected:
		static void _bind_methods();

	public:
		VSTestGDnative();
		~VSTestGDnative();

		void _process(double delta) override;

		void _ready() override;

	};

}

#endif