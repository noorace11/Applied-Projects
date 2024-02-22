/**
 * @file Curtains.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CURTAINS_H
#define CANADIANEXPERIENCE_MACHINELIB_CURTAINS_H
#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"


/**
 * Challenge task Curtains class
 */
class Curtains : public Component
{
private:
    /// left curtain physics polygon object
    cse335::PhysicsPolygon mLeftCurtain;
    /// right curtain physics polygon object
    cse335::PhysicsPolygon mRightCurtain;
    /// rod polygon object
    cse335::Polygon mRod;
    /// image member variable
    std::wstring mImage;
    /// is opening boolean
    bool mIsOpening = false;
    /// animation progress of curtains to reset
    double mAnimationProgress = 0.0;
public:
    /// Default constructor (disabled)
    Curtains() = delete;

    /// Copy constructor (disabled)
    Curtains(const Curtains &) = delete;

    /// Assignment operator
    void operator=(const Curtains &) = delete;

    /**
     * Constructor
     * @param imageDir
     */
    Curtains(std::wstring imageDir);
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
     * Reset
     */
    void Reset() override;
    /**
     * Setting position
     * @param a
     * @param b
     */
    void SetPosition(double a, double b) override;
    /**
     * Getting position
     * @return position of physics polygon objects
     */
    wxPoint GetPosition() override;

    /**
    * Install physics function from component class
    * @param world
     * @param contact
    */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CURTAINS_H
