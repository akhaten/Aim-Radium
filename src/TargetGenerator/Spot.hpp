#ifndef SPOT_HPP
#define SPOT_HPP

#include <Core/Types.hpp>



#include <QCursor>

namespace Ra {
namespace Gui {

class Spot
{

    public:
        
        ~Spot();
        void add_target(Core::Vector3 coord);
        void make_target(unsigned int index);
        
        

    protected:

    private:
        std::vector<Core::Vector3> coords;

};
}
}

#endif // SPOT_HPP