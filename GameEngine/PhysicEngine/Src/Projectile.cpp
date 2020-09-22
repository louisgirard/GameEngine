#include <PhysicEngine/Header/Projectile.h>
#include <GL\glew.h>
#include <GL\freeglut_std.h>

namespace PhysicEngine {
    Projectile::Projectile()
    {
        _type = Projectile::Types::Bullet;
        _launched = false;
        setParticle();
    }

    Vector3 Projectile::getPosition()
    {
        return _particle.getPosition();
    }

    void Projectile::changeType(Types p_type)
    {
        _type = p_type;
        setParticle();
        _launched = false;
    }

    void Projectile::launch()
    {
        _launched = true;
    }

    void Projectile::move(float p_dt)
    {
        if(_launched)
            _particle.integrate(p_dt);
    }

    void Projectile::draw()
    {
        glTranslatef(_particle.getPosition()._x, _particle.getPosition()._y, _particle.getPosition()._z);     
        glutWireSphere(_size, 20, 16);
    }

    void Projectile::setParticle()
    {
        //Z-axis Velocity needs to be negative to see the projectile going away from the camera
        switch (_type) {
        case Types::Bullet:
            _particle.setMass(1.f);
            _particle.setVelocity(0.f, 0.f, -80.f);
            _particle.setAcceleration(0.f, -10.f, 0.f);
            _size = 10.f;
            glColor3f(100.f, 100.f, 100.f);
            break;
        case Types::Canonball:
            _particle.setMass(10.f);
            _particle.setVelocity(0.f, 60.f, -140.f);
            _particle.setAcceleration(0.f, -20.f, 0.f);
            _size = 40.f;
            glColor3f(100.f, 100.f, 100.f);
            break;
        case Types::Laser:
            _particle.setMass(.5f);
            _particle.setVelocity(0.f, 0.f, -170.f);
            _particle.setAcceleration(0.f, 0.f, 0.f);
            _size = 5.f;
            glColor3f(100.f, 0.f, 0.f);
            break;
        case Types::Fireball:
            _particle.setMass(2.f);
            _particle.setVelocity(0.f, 0.f, -80.f);
            _particle.setAcceleration(0.f, 5.f, 0.f);
            _size = 20.f;
            glColor3f(100.f, 100.f, 0.f);
        }
        _particle.setPosition(0.f, 0.f, -50.f);
    }
}