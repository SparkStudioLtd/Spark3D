#include "pch.h"
#include "Core/Graphics/Graphics.h"

class ModelLoader {
public:
	static GPUMesh* loadMesh(GPUContext* context, std::string file);
};
