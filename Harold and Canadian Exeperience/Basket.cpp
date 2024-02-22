/**
 * @file Basket.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Basket.h"
#include <b2_contact.h>
#include "ContactListener.h"


/// The size of the basket in centimeters
const double BasketSize = 40;

/// Delay between when the ball hits the basket
/// and when it is shot out
const double BasketDelay = 1.0;

/// The direction we shoot the ball out of the basket
const wxPoint2DDouble BasketShot = wxPoint2DDouble(3, 5);


Basket::Basket(std::wstring imagesDir)
{
    mBasketPolygon.CenteredSquare(BasketSize);
    mBasketPolygon.SetImage(imagesDir + L"/basket.png");

    mBase.BottomCenteredRectangle(wxSize(30,5));
    mLeftWall.BottomCenteredRectangle(5,32);
    mRightWall.BottomCenteredRectangle(5,32);


    mBase.SetInitialPosition(-30,3);
    mLeftWall.SetInitialPosition(-47,5);
    mRightWall.SetInitialPosition(-13,5);


}
void Basket::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    mBasketPolygon.Draw(graphics);
}


void Basket::Update(double elapsed)
{
    if(mCountDown > 0)
    {
        mCountDown -= elapsed;
        auto contact = mBase.GetBody()->GetContactList();
        while(contact != nullptr)
        {
            if(contact->contact->IsTouching())
            {
                contact->other->SetLinearVelocity(b2Vec2(1, 11));
            }
            contact = contact->next;
        }
    }
}

void Basket::Reset()
{

}

void Basket::SetPosition(double a, double b)
{
    mBasketPolygon.SetInitialPosition(a,b);
    mPosition.x = a;
    mPosition.y = b;
}
void Basket::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
    mBasketPolygon.InstallPhysics(world);
    mBase.InstallPhysics(world);
    mLeftWall.InstallPhysics(world);
    mRightWall.InstallPhysics(world);
    contact->Add(mBasketPolygon.GetBody(), this);
}
void Basket::PreSolve(b2Contact *contact, const b2Manifold *oldmanifold)
{
    contact->SetEnabled(false);
}


void Basket::BeginContact(b2Contact *contact)
{
    mCountDown = BasketDelay;
}
