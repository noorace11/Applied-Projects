/**
 * @file Body.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H
#include "PhysicsPolygon.h"
#include "Component.h"
#include "RotationSink.h"

/**
 * Body component class inheriting from class component
 */
class Body : public Component, public RotationSink
{
private:
    /// speed member variable
    double mSpeed = 0.0;
    ///rotation member variable
    double mRotation = 0.0;
    /// color member variable
    wxColour mColor;

    /// image member variable
    std::wstring mImage;

    /// physics polygon object for body
    cse335::PhysicsPolygon mBodyPolygon;

    /// radius member variable
    double mRadius = 0.0;

public:

    /// Copy constructor (disabled)
    Body(const Body &) = delete;

    /// Assignment operator
    void operator=(const Body &) = delete;

    Body();

    /**
     * Adding point
     * @param a
     * @param b
     */
    void AddPoint(double a, double b);

    /**
     * Setting image of physics polygon
     * @param image
     */
    void SetImage(std::wstring image){mBodyPolygon.SetImage(image);}

    /**
     * Drawing body
     * @param graphics
     * @param a
     * @param b
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b) override;

    /**
     * Setting position
     * @param a
     * @param b
     */
    void SetPosition(double a, double b) override;

    /**
     * Update
     * @param elapsed
     */
    void Update(double elapsed) override;

    /**
     * Setting speed
     * @param speed
     */
    void SetSpeed(double speed){mSpeed = speed;}

    /**
     * Setting rotation
     * @param rotation
     * @param speed
     */
    void SetRotation(double rotation, double speed) override;
    /**
     * Setting color
     * @param color
     */
    void SetColor(wxColour color){mColor = color;}

    /**
     * Rectangle function to call physics polygon on appropriate object
     * @param a
     * @param b
     * @param width
     * @param height
     */
    void Rectangle(int a, int b, int width, int height);

    /**
     * Bottom Centered Rectangle function to call physics polygon on appropriate object
     * @param width
     * @param height
     */
    void BottomCenteredRectangle(int width, int height);

    /**
     * Circle function to call physics polygon on appropriate object
     * @param radius
     */
    void Circle(double radius){mBodyPolygon.Circle(radius);}

    /**
     * SetDynamic function to call the physics polygon setdynamic
     */
    void SetDynamic(){mBodyPolygon.SetDynamic();}

    /**
     * Settting kinematic for physics polygon
     */
    void SetKinematic(){mBodyPolygon.SetKinematic();}

    /**
     * SetPhysics function to call appropriate Setphysics stnadards on object
     * @param a
     * @param b
     * @param c
     */
    void SetPhysics(double a, double b, double c){mBodyPolygon.SetPhysics(a, b, c);}

    /**
     * Reset
     */
    void Reset() override {};

    /**
     * Getting position
     * @return polygon position
     */
    wxPoint GetPosition() override {return wxPoint(mBodyPolygon.GetPosition().m_x, mBodyPolygon.GetPosition().m_y);}

    /**
     * InstallPhysics to apply physics on the physics object
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override ;

    /**
     * Getting radius
     * @return radius
     */
    double GetRadius(){return mRadius;}

    /**
     * Set initial rotation for domino
     * @param rotation
     */
    void SetInitialRotation(double rotation){mBodyPolygon.SetInitialRotation(rotation);}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
