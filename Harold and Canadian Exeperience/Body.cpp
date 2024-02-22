/**
 * @file Body.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Body.h"
#include "ContactListener.h"

/// Image to draw
const std::wstring BodyImage = L"/floor.png";


Body::Body()
{

}


void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    mBodyPolygon.Draw(graphics);
}

void Body::Rectangle(int a, int b, int width, int height)
{
    mBodyPolygon.Rectangle(a, b, width, height);
}

void Body::BottomCenteredRectangle(int width, int height)
{
    mBodyPolygon.BottomCenteredRectangle(width, height);
}

void Body::Update(double elapsed)
{

}

void Body::SetRotation(double rotation, double speed)
{
    mBodyPolygon.SetAngularVelocity(speed);
}

void Body::SetPosition(double a, double b)
{
    mBodyPolygon.SetInitialPosition(a, b);
}

void Body::AddPoint(double a, double b)
{
    mBodyPolygon.AddPoint(a, b);

}

void Body::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
    mBodyPolygon.InstallPhysics(world);
}