/**
 * @file Hamster.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "Polygon.h"
#include <b2_world_callbacks.h>
#include "RotationSource.h"

/**
 * Hamster component class
 */
class Hamster : public Component, public RotationSource, public b2ContactListener
{
private:
    /// speed member variable
    double mSpeed = 1.0;
    /// rotation member variable
    double mRotationAmount = 0.0;
    /// rotation number variable for hamster type
    int mRotationNumber = 0;
    /// position member variable
    wxPoint mPosition = wxPoint(0,0);
    /// Hamster cage physics polygon object
    cse335::PhysicsPolygon mHamsterBox;
    /// Hamster wheel physics polygon object
    cse335::Polygon mHamsterWheel;
    /// array for Hamster images
    std::array<cse335::Polygon, 4> mRunningHamsterList;
    /// initial running boolean
    bool mInitialRun = false;
    /// currently running boolean
    bool mCurrentRun = false;
    /// image member variable
    std::wstring mImage;
    ///rotation source object
    RotationSource mSource;
public:
    /// Default constructor (disabled)
    Hamster() = delete;

    /// Copy constructor (disabled)
    Hamster(const Hamster &) = delete;

    /// Assignment operator
    void operator=(const Hamster &) = delete;

    /**
     * Constructor
     * @param imagesDir
     */
    Hamster(std::wstring imagesDir);

     /**
     * Draw function from Component class
     * @param graphics
     * @param a
     * @param b
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b) override;

    /**
     * Update Machine time
     * @param time
     */
    void UpdateMachineTime(double time);

    /**
     * Reset function from component class
     */
    void Reset() override;

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
     * Get position from component class
     * @return
     */
    wxPoint GetPosition() override {return mPosition;}

    /**
     * Install physics function from component class
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

    /**
     * Get shaft position for hamster moving shaft
     * @return
     */
    wxPoint GetShaftPosition();

    /**
     * Setting speed
     * @param speed
     */
    void SetSpeed(double speed){mSpeed = speed;};


    void BeginContact(b2Contact *contact) override;

    /**
     * setting inital running
     * @param run
     */
    void SetInitiallyRunning(bool run);

    /**
     * Getting source object
     * @return source object
     */
    RotationSource *GetSource(){return &mSource;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
