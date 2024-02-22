/**
 * @file Pulley.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#include "Component.h"
#include "RotationSink.h"
#include "RotationSource.h"
#include "Polygon.h"


/**
 * Pulley component class
 */
class Pulley : public Component, public RotationSink, public RotationSource
{
private:
    /// radius member variable
    double mRadius = 0.0;
    /// rotation member variable
    double mRotation = 0.0;
    /// speed member variable
    double mSpeed = 0.0;
    /// position member variable
    wxPoint mPosition = wxPoint(0,0);
    /// pulley polygon object
    cse335::Polygon mPulleyPolygon;

    /// image member variable
    std::wstring mImage;

    /// rotation source object
    RotationSource mSource;

    /// pulley pointer to get the sink of the pulley source
    std::shared_ptr<Pulley> mSink;
public:
    /// Default constructor (disabled)
    Pulley() = delete;

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    /// Assignment operator
    void operator=(const Pulley &) = delete;

    /**
     * Constructor
     * @param radius
     */
    Pulley(double radius);
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
     * Setting image of physics polygon
     * @param image
     */
    void SetImage(std::wstring image){mPulleyPolygon.SetImage(image);}

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
    * get position function
    * @return
    */
    wxPoint GetPosition() override { return mPosition; }

    /**
     * Install physics function from component class
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

    /**
     * Driving the pulley
     * @param pulley
     */
    void Drive(std::shared_ptr<Pulley> pulley);

    /**
     * Setting rotation
     * @param rotation
     * @param speed
     */
    void SetRotation(double rotation, double speed) override ;

    /**
     * Getting rotation source object to spin wheel
     * @return
     */
    RotationSource *GetSource(){return &mSource;}

    /**
     * Getting radius
     * @return
     */
    double GetRadius(){return mRadius;}

    void DrawBelt(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
