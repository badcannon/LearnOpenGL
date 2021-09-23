#include "../utils/shader.hpp"

class Coord
{
private:
    float vertices[20],indices[20];
    unsigned int VAO,VBO,EBO;
public:
    Coord();
    void Draw();
};
