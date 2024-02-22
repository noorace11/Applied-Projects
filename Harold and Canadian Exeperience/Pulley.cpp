/**
 * @file Pulley.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Pulley.h"




Pulley::Pulley(double radius)
{
    mRadius = radius;
    mPulleyPolygon.CenteredSquare(20);
    mSource.SetComponent(this);

}

void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    graphics->PushState();
    if(mSink != nullptr)
    {
        DrawBelt(graphics);
    }
    graphics->Translate(mPosition.x, mPosition.y);
    mPulleyPolygon.DrawPolygon(graphics, 0, 0, mRotation);
    graphics->PopState();
}


void Pulley::SetPosition(double a, double b)
{
    mPosition.x = a;
    mPosition.y = b;
}

void Pulley::SetRotation(double rotation, double speed)
{
    mRotation = rotation;
    mSpeed = speed;
    mSource.SetRotation(rotation, speed);
}

void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mSink = pulley;

}

void Pulley::Update(double elapsed)
{
    mRotation += -mSpeed * elapsed;

    if(mSink != nullptr)
    {
        mSink->SetRotation(mRotation, mSpeed);
    }
}

void Pulley::Reset()
{
    mRotation = 0.0;
    mSpeed = 0.0;
}


void Pulley::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
}



/**
 * Draw the belt.
 *
 * This function also animates the belts.
 * @param graphics The graphics context to draw to.
 */
void Pulley::DrawBelt(std::shared_ptr<wxGraphicsContext> graphics)
{
        wxPoint locSource = GetPosition();
        wxPoint locSink = mSink->GetPosition();

        if(locSource == locSink)
        {
            return;
        }

        graphics->PushState();

        wxPen pen(*wxBLACK, 2);
        graphics->SetPen(pen);

        graphics->StrokeLine(locSource.x, locSource.y - 8, locSink.x, locSink.y - 8);
        graphics->StrokeLine(locSource.x, locSource.y + 8, locSink.x, locSink.y + 8);

        graphics->PopState();
}

