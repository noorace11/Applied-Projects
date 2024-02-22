/**
 * @file RotationSource.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#include "RotationSink.h"
class Component;

/**
 * Rotation source class for source
 */
class RotationSource
{
private:
    /// rotation member variable
    double mRotation = 0.0;

    /// rotation vector for sinks to connect to source
    std::vector<std::shared_ptr<RotationSink>> mRotationVector;

    /// The component that this source is attached to.
    Component* mComponent = nullptr;
public:
    /**
     * Constructor
     */
    RotationSource();

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator
    void operator=(const RotationSource &) = delete;

    /**
     * Setting component
     * @param comp
     */
    void SetComponent(Component *comp){mComponent = comp;}
    /**
     * Getting component
     * @return component
     */
    Component * GetComponent(){return mComponent;}

    /**
     * Setting rotation
     * @param rotation
     * @param speed
     */
    void SetRotation(double rotation, double speed);
    /**
     * Adding sink to source for rotation
     * @param sink
     */
    void AddSink(std::shared_ptr<RotationSink> sink);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
