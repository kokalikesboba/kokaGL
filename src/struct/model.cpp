#include "model.h"
#include "parser/obj.h"

#include <SFML/Graphics.hpp>

Model::Model() {
};

void Model::InitFromOBJ(std::string dirName) {
    ObjParse(dirName, *this);
};
