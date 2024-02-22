/**
 * @file Conveyor.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSink.h"
#include <b2_world_callbacks.h>


/**
 * Conveyor Component class
 */
class Conveyor : public Component, public RotationSink, public b2ContactListener
{
private:
    /// speed member variable
    double mSpeed = 0.0;
    /// rotation member variable
    double mRotation = 0.0;
    /// conveyor physics polygon object
    cse335::PhysicsPolygon mConveyorPolygon;
    /// radius member variable
    double mRadius = 0.0;
public:
    /// Default constructor (disabled)
    Conveyor() = delete;

    /**
     * Constructor
     * @param imageDir
     */
    Conveyor(std::wstring imageDir);

    /// Copy constructor (disabled)
    Conveyor(const Conveyor &) = delete;

    /// Assignment operator
    void operator=(const Conveyor &) = delete;


    /**
     * Draw function from Component class
     * @param graphics
     * @param a
     * @param b
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b) override;

    /**
     * Update
     * @param elapsed
     */
    void Update(double elapsed) override;

    /**
     * Set position function from component class
     * @param a
     * @param b
     */
    void SetPosition(double a, double b) override;

    /**
     * Reset
     */
    void Reset() override;

    /**
     * Get position from component class
     * @return
     */
    wxPoint GetPosition() override {return wxPoint(mConveyorPolygon.GetPosition().m_x, mConveyorPolygon.GetPosition().m_y);}

    /**
     * Getting shaft position that is connecting Hamster with the conveyor
     * @return
     */
    wxPoint GetShaftPosition();

    /**
     * Install physics function from component class
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

    /**
     * Setting rotation
     * @param rotation
     * @param speed
     */
    void SetRotation(double rotation, double speed) override ;
    /**
     * Pre solve contact
     * @param contact
     * @param oldManifold
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    /**
     * Getting radius
     * @return radius
     */
    double GetRadius(){return mRadius;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
