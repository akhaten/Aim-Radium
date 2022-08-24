#include "Animation/AnimationDatas.hpp"

AnimationDatas::AnimationDatas(Scalar nb_frame, Scalar speed, int direction, Ra::Core::Vector3 vector)
{
    this->nb_frame = nb_frame;
    this->speed = speed;
    this->direction = direction;
    this->vector = vector;
}