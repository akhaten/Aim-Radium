#include "Spot.hpp"

Spot::Spot(Ra::Core::Vector3 position, AnimationDatas* animation_datas)
{
    this->position = position;
    this->animation_datas = animation_datas;
}