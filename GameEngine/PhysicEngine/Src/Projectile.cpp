#include <PhysicEngine/Header/Projectile.h>
#include <GL\glew.h>

namespace PhysicEngine {
    Projectile::Projectile()
    {
        _type = Projectile::Types::Bullet;
        _launched = false;
        _size = 10.f;
    }

    Vector3 Projectile::getPosition()
    {
        return _particle.getPosition();
    }

    void Projectile::changeType(Types p_type)
    {
        _type = p_type;
        _launched = false;
    }

    void Projectile::launch()
    {
        setParticle();
        _launched = true;
    }

    void Projectile::integrate(float p_dt)
    {
        _particle.integrate(p_dt);
    }

    void Projectile::draw()
    {
    }

    void Projectile::setParticle()
    {
        //Z-axis Velocity needs to be negative to see the projectile going away from the camera
        switch (_type) {
        case Types::Bullet:
            _particle.setMass(1.f);
            _particle.setVelocity(0.f, 0.f, -20.f);
            _particle.setAcceleration(0.f, -1.f, 0.f);
            _size = 10.f;
            break;
        case Types::Canonball:
            _particle.setMass(20.f);
            _particle.setVelocity(0.f, 40.f, -40.f);
            _particle.setAcceleration(0.f, -5.f, 0.f);
            _size = 70.f;
            break;
        case Types::Laser:
            _particle.setMass(.5f);
            _particle.setVelocity(0.f, 0.f, -80.f);
            _particle.setAcceleration(0.f, 0.f, 0.f);
            _size = 5.f;
            break;
        case Types::Fireball:
            _particle.setMass(2.f);
            _particle.setVelocity(0.f, 0.f, -20.f);
            _particle.setAcceleration(0.f, .5f, 0.f);
            _size = 20.f;
        }
        _particle.setPosition(0.f, 0.f, -50.f);
    }

    void Projectile::drawCube()
    {
        /*glBegin(GL_QUADS);

        glColor3f(0, 1, 1);
        glVertex3f(-_size, -_size, -_size);
        glVertex3f(-_size, _size, -_size);
        glVertex3f(_size, _size, -_size);
        glVertex3f(_size, -_size, -_size);

        glColor3f(0, 0, 1);
        glVertex3f(-_size, -_size, _size);
        glVertex3f(-_size, _size, _size);
        glVertex3f(_size, _size, _size);
        glVertex3f(_size, -_size, _size);

        glColor3f(1, 0, 1);
        glVertex3f(-_size, -_size, -_size);
        glVertex3f(-_size, _size, -_size);
        glVertex3f(-_size, _size, _size);
        glVertex3f(-_size, -_size, _size);

        glColor3f(0, 1, 0);
        glVertex3f(_size, -_size, -_size);
        glVertex3f(_size, _size, -_size);
        glVertex3f(_size, _size, _size);
        glVertex3f(_size, -_size, _size);

        glColor3f(1, 1, 0);
        glVertex3f(-_size, -_size, _size);
        glVertex3f(-_size, -_size, -_size);
        glVertex3f(_size, -_size, -_size);
        glVertex3f(_size, -_size, _size);

        glColor3f(1, 0, 0);
        glVertex3f(-_size, _size, _size);
        glVertex3f(-_size, _size, -_size);
        glVertex3f(_size, _size, -_size);
        glVertex3f(_size, _size, _size);

        glEnd();*/
    }
}