/**
 * @file Hamster.cpp
 * @author Noor M.
 */

#include "pch.h"

#include "Hamster.h"
#include "ContactListener.h"


/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};


Hamster::Hamster(std::wstring imagesDir)
{
    mImage = imagesDir;
    mHamsterBox.BottomCenteredRectangle(HamsterCageSize);
    mHamsterWheel.CenteredSquare(HamsterWheelSize);

    mHamsterBox.SetImage(mImage + HamsterCageImage);
    mHamsterWheel.SetImage(mImage + HamsterWheelImage);

    for(int i = 0; i < 4; i++)
    {
        mRunningHamsterList[i].CenteredSquare(HamsterSize);
        mRunningHamsterList[i].SetImage(mImage + HamsterImages[i]);
    }
}

void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    mHamsterBox.Draw(graphics);
    graphics->PushState();
    graphics->Translate(a, b);
    graphics->Translate(WheelCenter.m_x, WheelCenter.m_y);

    if(mInitialRun || mCurrentRun)
    {
        mHamsterWheel.DrawPolygon(graphics, 0, 0, mRotationAmount);
        mRotationNumber = int((abs(mRotationAmount * HamsterSpeed) * 4)) % 4;

        if(mRotationNumber == 4)
        {
            mRotationNumber = 2;
            mRunningHamsterList[mRotationNumber].SetImage(mImage + HamsterImages[mRotationNumber]);
        }
        else
        {
            if(mRotationNumber == 0)
            {
                mRotationNumber = 1;
            }
            mRunningHamsterList[mRotationNumber].SetImage(mImage + HamsterImages[mRotationNumber]);
        }
    }
    else
    {
        mHamsterWheel.DrawPolygon(graphics, 0, 0, mRotationAmount);
        mRunningHamsterList[mRotationNumber].SetImage(mImage + HamsterImages[0]);
    }


    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }

    // Draw the running image
    mRunningHamsterList[mRotationNumber].DrawPolygon(graphics, 0, 0, 0);

    graphics->PopState();

}


void Hamster::Update(double elapsed)
{
    if(mInitialRun || mCurrentRun)
    {
        mRotationAmount += -mSpeed * elapsed;
        mSource.SetRotation(mRotationAmount, -mSpeed);
    }
}

void Hamster::Reset()
{
    mCurrentRun = false;
    mRotationNumber = 0;

}

wxPoint Hamster::GetShaftPosition()
{
    return wxPoint(mHamsterBox.GetPosition().m_x + HamsterShaftOffset.m_x,
                   mHamsterBox.GetPosition().m_y + HamsterShaftOffset.m_y);
}

void Hamster::SetPosition(double a, double b)
{
    mHamsterBox.SetInitialPosition(a, b);
    mPosition.x = a;
    mPosition.y = b;
}
/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    // Turn the hamster on
    mCurrentRun = true;
}

void Hamster::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
    mHamsterBox.InstallPhysics(world);
    contact->Add(mHamsterBox.GetBody(), this);
}

void Hamster::SetInitiallyRunning(bool run)
{
    mInitialRun = run;
}