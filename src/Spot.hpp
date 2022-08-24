#ifndef SPOT_HPP
#define SPOT_HPP

#include <Core/Types.hpp>

#include "Animation/AnimationDatas.hpp"

class Spot
{

    public:
        Spot(Ra::Core::Vector3 position, AnimationDatas* animation_datas);
        ~Spot();
        Ra::Core::Vector3 position;
        AnimationDatas* animation_datas;
        
        

};

#endif // SPOT_HPP