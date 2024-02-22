/**
 * @file Conveyor.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Conveyor.h"
#include "ContactListener.h"
#include <b2_contact.h>


/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

Conveyor::Conveyor(std::wstring imageDir)
{
    mConveyorPolygon.SetImage(imageDir + ConveyorImageName);
    mConveyorPolygon.BottomCenteredRectangle(ConveyorSize);
}

void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    mConveyorPolygon.Draw(graphics);
}

void Conveyor::SetPosition(double a, double b)
{
    mConveyorPolygon.SetInitialPosition(a, b);
}

void Conveyor::SetRotation(double rotation, double speed)
{
    mSpeed = speed;

}

void Conveyor::Update(double elapsed)
{
    auto contact = mConveyorPolygon.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-mSpeed, 0));
        }

        contact = contact->next;
    }
}

void Conveyor::Reset()
{
    mSpeed = 0.0;
    mRotation = 0.0;
}

void Conveyor::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
    mConveyorPolygon.InstallPhysics(world);
    contact->Add(mConveyorPolygon.GetBody(), this);
}

wxPoint Conveyor::GetShaftPosition()
{
    return wxPoint(mConveyorPolygon.GetPosition().m_x + ConveyorShaftOffset.m_x,
                   mConveyorPolygon.GetPosition().m_y + ConveyorShaftOffset.m_y);
}

void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}