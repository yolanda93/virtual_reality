#include "camera.h"

camera::camera()
    :m_position(0,0,0),
     m_target(0,0,-1),
     m_up(0,1,0)
{

}

QMatrix4x4* camera::projection()
{
    QMatrix4x4* proj = new QMatrix4x4();
    proj->perspective(m_fov, m_aspect_ratio, m_zmin, m_zmax);
    return proj;

}

QMatrix4x4 *camera::view()
{
    QMatrix4x4* view = new QMatrix4x4();
    view->lookAt(m_position, m_target, m_up);
    return view;
}


float camera::fov() const
{
    return m_fov;
}

void camera::setFov(float fov)
{
    m_fov = fov;
}

float camera::aspect_ratio() const
{
    return m_aspect_ratio;
}

void camera::setAspect_ratio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
}

float camera::zmin() const
{
    return m_zmin;
}

void camera::setZmin(float zmin)
{
    m_zmin = zmin;
}

float camera::zmax() const
{
    return m_zmax;
}

void camera::setZmax(float zmax)
{
    m_zmax = zmax;
}
