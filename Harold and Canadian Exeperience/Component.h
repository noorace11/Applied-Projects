/**
 * @file Component.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#include "PhysicsPolygon.h"
class ContactListener;
class b2World;
class MachineComponent;


/**
 * Main component class for all components to inherit
 */
class Component
{
private:
    /// machine member variable pointer object
    MachineComponent* mMachine = nullptr;
public:

    Component() {};

    /// Copy constructor (disabled)
    Component(const Component &) = delete;

    /// Assignment operator
    void operator=(const Component &) = delete;

    virtual ~Component() = default;

    /**
     * Pure Virtual draw function for all correlated classes
     * @param graphics
     * @param a
     * @param b
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b) = 0;

    /**
     *
     * @param time
     */
    void UpdateMachineTime(double time);

    /**
     * Pure Virtual update function
     * @param elapsed
     */
    virtual void Update(double elapsed) = 0;

    /**
     * Pure Virtual reset function
     */
    virtual void Reset() = 0;

    /**
     * Pure virtual set position function
     * @param a
     * @param b
     */
    virtual void SetPosition(double a, double b) = 0;

    /**
     * Pure virtual get position function
     * @return
     */
    virtual wxPoint GetPosition() = 0;

    /**
     * Install this component into the physics system world.
     * @param world Physics system world
     * @param contact contact listener contact
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) = 0;

    /**
     * Get the current time of the machine.
     * @return The current time of the machine.
     */
    double GetTime();


    /**
     * Set the parent machine of this component.
     * @param machine The parent machine.
     */
    void SetMachine(MachineComponent* machine) { mMachine = machine; }

    /**
     * Get the parent machine of this component.
     * @return The parent machine.
     */
    MachineComponent* GetMachine();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
