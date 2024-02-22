/**
 * @file Goal.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#include "PhysicsPolygon.h"
#include "Component.h"
#include <b2_world_callbacks.h>

/**
 * Basketball Goal.
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// score member variable
    int mScore = 0;

    /// polygon object for the goal image
    cse335::Polygon mGoalImage;

    /// physics polygon object for goal post
    cse335::PhysicsPolygon mPost;

    /// physics polygon object for goal
    cse335::PhysicsPolygon mGoal;

    /// image member variable
    std::wstring mImage;

    /// position member variable
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;
public:
    /// Default constructor (disabled)
    Goal() = delete;

    /// Copy constructor (disabled)
    Goal(const Goal &) = delete;

    /// Assignment operator
    void operator=(const Goal &) = delete;

    /**
     * Constructor
     * @param imagesDir
     */
    Goal(std::wstring imagesDir);

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
     * Update function from component class
     * @param elapsed
     */
    void Update(double elapsed) override;

    /**
     * Reset function from component class
     */
    void Reset() override;

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
    wxPoint GetPosition() override {return wxPoint(mPost.GetPosition().m_x, mPost.GetPosition().m_y);}

    /**
     * Install physics function from component class
     * @param world
     * @param contact
     */
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact) override;

    /**
     * Begin contact
     * @param contact
     */
    void BeginContact(b2Contact *contact) override;
    /**
     * presolve contact
     * @param contact
     * @param oldManifold
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;



};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
