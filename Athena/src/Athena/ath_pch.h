#pragma once

// stl
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data structures
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// libraries
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// own unchangeble headers
#include "Log.h"

#ifdef ATH_PLATFORM_WINDOWS
    #include <Windows.h>
#endif