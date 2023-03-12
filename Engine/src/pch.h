//Disable warnings
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4267)
//C++ Headers
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <any>
#include <sstream>
#include <map>
#include <filesystem>


//C++ Namespaces
namespace fs = std::filesystem;

//Thirdparty headers
#define GLM_ENABLE_EXPERIMENTAL
#include "Thirdparty/glm/glm.hpp"
#include "Thirdparty/glm/gtc/type_ptr.hpp"
#include "Thirdparty/glm/gtc/matrix_transform.hpp"
#include "Thirdparty/glm/gtc/quaternion.hpp"
#include "Thirdparty/glm/gtc/matrix_inverse.hpp"
#include "Thirdparty/glm/detail/type_quat.hpp"
#include "Thirdparty/glm/gtx/quaternion.hpp"

#include "Thirdparty/glad/glad.h"
#include "Thirdparty/GLFW/glfw3.h"

#include "Thirdparty/assimp/Importer.hpp"
#include "Thirdparty/assimp/scene.h"
#include "Thirdparty/assimp/postprocess.h"

#include "Thirdparty/imgui/imgui.h"
#include "Thirdparty/imgui/imgui_impl_glfw.h"
#include "Thirdparty/imgui/imgui_impl_opengl3.h"