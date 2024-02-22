/**
 * @file Basket.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#include "Component.h"
#include <b2_world_callbacks.h>


/**
 * Challenge task Basket class
 */
class Basket : public Component, public b2ContactListener
{
private:
    /// position
    wxPoint mPosition = wxPoint(0,0);
    /// physics polygon object of basket
    cse335::PhysicsPolygon mBasketPolygon;
    /// physics polygon object of basket base
    cse335::PhysicsPolygon mBase;
    /// physics polygon object of basket left wall
    cse335::PhysicsPolygon mLeftWall;
    /// physics polygon object of basket right wall
    cse335::PhysicsPolygon mRightWall;
    /// countdown
    double mCountDown = 0.0;


public:
    /**
     * Constructor
     * @param imagedDir
     */
    Basket(std::wstring imagedDir);
    /// Copy constructor (disabled)
    Basket(const Basket &) = delete;
    /// Assignment operator (disabled)
    void operator=(const Basket &) = delete;
    /**
    * Drawing basket
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
     * @return polygon position
     */
    wxPoint GetPosition() override {return wxPoint(mBasketPolygon.GetPosition().m_x, mBasketPolygon.GetPosition().m_y);}

    /**
     * Installing physics to component
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

    /**
     * Setting action on contact
     * @param contact
     */
    void BeginContact(b2Contact *contact) override;
    /**
     * Presolve contact
     * @param contact
     * @param oldManifold
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKET_H
