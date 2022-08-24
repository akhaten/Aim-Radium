#ifndef ANIMATION_DATAS_HPP
#define ANIMATION_DATAS_HPP

#include <Core/Types.hpp>

class AnimationDatas
{
    public:
        AnimationDatas(Scalar nb_frame, Scalar speed, int direction, Ra::Core::Vector3 vector);
        ~AnimationDatas();
        Scalar nb_frame;
        Scalar speed; 
        int direction;
        Ra::Core::Vector3 vector;

};

#endif // ANIMATION_DATAS_HPP