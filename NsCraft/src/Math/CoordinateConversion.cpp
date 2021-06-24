#include "CoordinateConversion.h"
#include "Vector2.h"
#include "Vector3.h"

namespace CoordinateConversion {
    Vector2 chunkToWorld(const Vector2& chunkCoords, const Vector2& localCoords, int chunkWidth) {
        return chunkCoords * chunkWidth + localCoords;
    }

    Vector3 chunkToWorld(const Vector3& chunkCoords, const Vector3& localCoords, int chunkWidth) {
        return chunkCoords * chunkWidth + localCoords;
    }

    std::pair<Vector2, Vector2> worldToChunk(const Vector2& worldCoords, int chunkWidth) {
        Vector2 chunkPosition;
        chunkPosition.x = floor((float)worldCoords.x / (float)chunkWidth);
        chunkPosition.y = floor((float)worldCoords.y / (float)chunkWidth);

        auto localPosition = worldCoords - chunkPosition * chunkWidth;

        return { chunkPosition, localPosition };
    }

    std::pair<Vector3, Vector3> worldToChunk(const Vector3& worldCoords, int chunkWidth) {
        Vector3 chunkPosition;
        chunkPosition.x = floor((float)worldCoords.x / (float)chunkWidth);
        chunkPosition.y = floor((float)worldCoords.y / (float)chunkWidth);
        chunkPosition.z = floor((float)worldCoords.z / (float)chunkWidth);

        auto localPosition = worldCoords - chunkPosition * chunkWidth;

        return { chunkPosition, localPosition };
    }
}