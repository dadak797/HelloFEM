#pragma once

#include "ObjectBase.h"
#include "TransformMatrix.h"

#include "Vector.h"

class Node : public ObjectBase
{
    using Coordinate = Vector<StaticAllocator<double, 3>>;

private:
    Coordinate m_Crd;  // Coordinate of Node

};