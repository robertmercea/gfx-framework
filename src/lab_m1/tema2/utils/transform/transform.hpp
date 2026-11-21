#pragma once

#include "glm/ext/matrix_float4x4.hpp"

namespace tema2 {
namespace transform {

inline glm::mat4 translate(float translateX, float translateY, float translateZ) {
    return glm::transpose(
        glm::mat4(
            1, 0, 0, translateX,
            0, 1, 0, translateY,
            0, 0, 1, translateZ,
            0, 0, 0, 1
        )
    );
}

inline glm::mat4 scale(float scaleX, float scaleY, float scaleZ) {
    return glm::transpose(
        glm::mat4(
            scaleX, 0, 0, 0,
            0, scaleY, 0, 0,
            0, 0, scaleZ, 0,
            0, 0, 0, 1
        )
    );
}

inline glm::mat4 rotateOZ(float radians) {
    return glm::transpose(
        glm::mat4(
            cos(radians), -sin(radians), 0, 0,
            sin(radians),  cos(radians), 0, 0,
            0,             0,            1, 0,
            0,             0,            0, 1
        )
    );
}

inline glm::mat4 rotateOY(float radians) {
    return glm::transpose(
        glm::mat4(
             cos(radians), 0, sin(radians), 0,
             0,            1, 0,            0,
            -sin(radians), 0, cos(radians), 0,
             0,            0, 0,            1
        )
    );
}

inline glm::mat4 rotateOX(float radians) {
    return glm::transpose(
        glm::mat4(
            1, 0,             0,            0,
            0, cos(radians), -sin(radians), 0,
            0, sin(radians),  cos(radians), 0,
            0, 0,             0,            1
        )
    );
}

} // namespace transform
} // namespace tema2
