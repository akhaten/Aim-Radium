#ifndef ANIMATION_HPP
#define ANIMATION_HPP

// include the Engine/entity/component/system/animation interface
#include <Engine/FrameInfo.hpp>
#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/System.hpp>

#include <Core/Animation/KeyFramedValueController.hpp>
#include <Core/Animation/KeyFramedValueInterpolators.hpp>
#include <Core/Asset/BlinnPhongMaterialData.hpp>


#include <Engine/Rendering/RenderObjectManager.hpp>

#include "AnimationDatas.hpp"


class Animation : 
    public Ra::Engine::Scene::TriangleMeshComponent
{
  public:
    /*!
     * Constructor from an existing core mesh
     * \warning Moves the mesh and takes its ownership
     */
    inline Animation( const std::string& name,
                                       Ra::Engine::Scene::Entity* entity,
                                       Ra::Core::Geometry::TriangleMesh&& mesh ) :
        Ra::Engine::Scene::TriangleMeshComponent( name,
                                                  entity,
                                                  std::move( mesh ),
                                                  new Ra::Core::Asset::BlinnPhongMaterialData {} ),
        m_transform( 0_ra, Ra::Core::Transform::Identity() ) {

        //! [Creating the color KeyFrames]
        auto colors = new Ra::Core::Animation::KeyFramedValue<Ra::Core::Utils::Color>(
            0_ra, Ra::Core::Utils::Color::Green() );
        
        
        // //! [Attach the color KeyFrames to a controller of the Render object material]
        m_colorController.m_value = colors;
        m_ro = getRoMgr()->getRenderObject( m_roIndex );
        auto material = dynamic_cast<Ra::Engine::Data::BlinnPhongMaterial*>( m_ro->getMaterial().get() );
        m_colorController.m_updater = [colors, material]( const Scalar& t ) {
            auto C = colors->at( t, Ra::Core::Animation::linearInterpolate<Ra::Core::Utils::Color> );
            material->m_kd = C;
            material->needUpdate();
        };
        //! [Attach the color KeyFrames to a controller]
        //! [Creating the color KeyFrames]

    }

    void configure(AnimationDatas* datas)
    {

        // reset m_transform
        m_transform = Ra::Core::Animation::KeyFramedValue<Ra::Core::Transform>(0_ra, Ra::Core::Transform::Identity());
        
        auto nb_frame = datas->nb_frame;
        auto speed = datas->speed;
        auto direction = datas->direction;
        auto vector = datas->vector;
        
        Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
        

        for(Scalar t = 1_ra; t < 2*nb_frame; t+=1_ra){

            if (t == nb_frame){
                direction = -direction;
            }

            m_transform.insertKeyFrame(t, transform_t);
            transform_t.translate(speed * direction * vector.normalized());
            
        }

    }

    /// This function uses the keyframes to update the geometry to time \p t.
    void update( Scalar t ) {
        //! [Fetch transform from KeyFramedValue
        transformer = m_transform.at( t, Ra::Core::Animation::linearInterpolate<Ra::Core::Transform> );
        //! [Fetch transform from KeyFramedValue]
        m_ro->setLocalTransform( transformer );
        //! [Update color from KeyFramedValue]
        m_colorController.updateKeyFrame( t );
        //! [Update color from KeyFramedValue]
    }

    /// The render object to animate
    std::shared_ptr<Ra::Engine::Rendering::RenderObject> m_ro;

    /// The Keyframes for the render object's tranform.
    Ra::Core::Animation::KeyFramedValue<Ra::Core::Transform> m_transform;

    /// The Keyframes for the render object's color.
    Ra::Core::Animation::KeyFramedValueController m_colorController;

    Ra::Core::Transform transformer;


};

#endif // ANIMATION_HPP