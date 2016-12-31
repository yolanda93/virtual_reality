#ifndef CAMERA_H
#define CAMERA_H


class camera
{
public:
    camera();

    float fov() const;
    void setFov(float fov);

    float aspect_ratio() const;
    void setAspect_ratio(float aspect_ratio);

    float zmin() const;
    void setZmin(float zmin);

    float zmax() const;
    void setZmax(float zmax);

protected:
    void view();
    void projection();

private:
    float m_fov, m_aspect_ratio, m_zmin, m_zmax;
};

#endif // CAMERA_H
