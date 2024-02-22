/**
 * @file MachineComponent.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINECOMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINECOMPONENT_H
#include "Component.h"
class b2World;
class ContactListener;


/**
 * Machine class to connect to all components
 */
class MachineComponent
{
private:
    /// machine number member variable
    int mMachineNumber = 0;

    /// time member variable
    double mTime = 0.0f;

    /// vector holding components
    std::vector<std::shared_ptr<Component>> mComponentVector;

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// Gravity in meters per second per second
    const float Gravity = -9.8f;

    /// Number of velocity update iterations per step
    const int VelocityIterations = 6;

    /// Number of position update iterations per step
    const int PositionIterations = 2;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;
public:
    /// Copy constructor (disabled)
    MachineComponent(const MachineComponent &) = delete;

    /// Assignment operator
    void operator=(const MachineComponent &) = delete;

    MachineComponent() {}

    ~MachineComponent() {}

    /**
     * Add component function to push to vector
     * @param components
     */
    void AddComponent(std::shared_ptr<Component> components);

    /**
     * Draw function
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Update function
     * @param elapsed
     */
    void Update(double elapsed);

    /**
     * Reset function
     */
    void Reset();

    /**
     * Set the current time
     * @param time The current time in seconds
     */
    void SetMachineTime(double time) { mTime = time; }

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() { return mTime; }




};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINECOMPONENT_H
