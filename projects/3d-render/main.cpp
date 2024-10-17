#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

struct Vec3D {
    float x, y, z;
};

// Simple 3D rotation functions (for the cube)
void rotateX(Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    float y = point.y * cosA - point.z * sinA;
    float z = point.y * sinA + point.z * cosA;
    point.y = y;
    point.z = z;
}

void rotateY(Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    float x = point.x * cosA + point.z * sinA;
    float z = -point.x * sinA + point.z * cosA;
    point.x = x;
    point.z = z;
}

void rotateZ(Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    float x = point.x * cosA - point.y * sinA;
    float y = point.x * sinA + point.y * cosA;
    point.x = x;
    point.y = y;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "3D Cube in SFML");

    // Define the original cube vertices (8 vertices)
    std::vector<Vec3D> originalVertices = {
        {-1, -1, -1}, {1, -1, -1}, {1,  1, -1}, {-1,  1, -1},  // Back face
        {-1, -1,  1}, {1, -1,  1}, {1,  1,  1}, {-1,  1,  1}   // Front face
    };

    float angleX = 0, angleY = 0, angleZ = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear window
        window.clear(sf::Color::Black);

        // Copy original vertices for transformations
        std::vector<Vec3D> vertices = originalVertices; 

        // Rotate the cube (slower rotation for better visual)
        for (auto& v : vertices) {
            rotateX(v, angleX);
            rotateY(v, angleY);
            rotateZ(v, angleZ);
        }

        // Draw edges between cube vertices (projecting 3D onto 2D)
        for (int i = 0; i < 4; ++i) {
            int next = (i + 1) % 4;
            int front = i + 4, frontNext = next + 4;

            // Back face
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(vertices[i].x * 100 + 400, vertices[i].y * 100 + 300)),
                sf::Vertex(sf::Vector2f(vertices[next].x * 100 + 400, vertices[next].y * 100 + 300))
            };
            window.draw(line, 2, sf::Lines);

            // Front face
            sf::Vertex frontLine[] = {
                sf::Vertex(sf::Vector2f(vertices[front].x * 100 + 400, vertices[front].y * 100 + 300)),
                sf::Vertex(sf::Vector2f(vertices[frontNext].x * 100 + 400, vertices[frontNext].y * 100 + 300))
            };
            window.draw(frontLine, 2, sf::Lines);

            // Connect front and back faces
            sf::Vertex sideLine[] = {
                sf::Vertex(sf::Vector2f(vertices[i].x * 100 + 400, vertices[i].y * 100 + 300)),
                sf::Vertex(sf::Vector2f(vertices[front].x * 100 + 400, vertices[front].y * 100 + 300))
            };
            window.draw(sideLine, 2, sf::Lines);
        }

        // Update the rotation angles (slow down the speed)
        angleX += 0.00005f;
        angleY += 0.00005f;
        angleZ += 0.00005f;

        // Display window
        window.display();
    }

    return 0;
}
