/**
 * @file RotationSink.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
class RotationSource;
class Component;


/**
 * Rotation sink class for sinks
 */
class RotationSink
{
private:
    ///rotation member variable
    double mRotation = 0.0;

    /// radius member variable
    double mRadius = 0.0;
public:
    /**
     * Constructor
     */
    RotationSink();

    /// Copy constructor (disabled)
    RotationSink(const RotationSink &) = delete;

    /// Assignment operator
    void operator=(const RotationSink &) = delete;

    /**
     * Pure virtual Set rotation function
     * @param rotation
     * @param speed
     */
    virtual void SetRotation(double rotation, double speed) = 0;


    /**
     * Getting radius
     * @return radius
     */
    double GetRadius(){return mRadius;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
