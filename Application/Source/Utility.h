#include <MatrixStack.h>
#include <Mtx44.h>
#include "Vertex.h"
#pragma once
Position operator*(const Mtx44& lhs, const Position& rhs);