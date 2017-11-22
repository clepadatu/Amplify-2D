#pragma once
#include "GL/glew.h"
#include "../maths/mat4.h"
#include "renderable2d.h"

namespace Erebos{
	namespace graphics{

		class Renderer2D
		{
		protected:
			virtual void submit(const Renderable2D& renderable);
			virtual void flush()=0;
		};




	}
}