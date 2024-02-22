/**
 * @file Curtains.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Curtains.h"
#include "MachineComponent.h"


/// Height of our curtains in pixels
const double CurtainHeight = 500;

/// Total width of the curtains in pixels
const double CurtainWidth = 750;

/// Image to draw
const std::wstring LeftCurtain = L"/curtain1.png";

/// Image to draw
const std::wstring RightCurtain = L"/curtain2.png";

/// Image to draw
const std::wstring CurtainRod = L"/curtain-rod.png";

/// Number of seconds to open the curtains
const double CurtainOpenTime = 2.0;

/// Minimum scaling factor for when the curtains are open
const double CurtainMinScale = 0.2;


Curtains::Curtains(std::wstring imageDir)
{
    mRod.BottomCenteredRectangle(CurtainWidth, CurtainHeight);
    mRod.SetImage(imageDir + CurtainRod);

    mRightCurtain.BottomCenteredRectangle(CurtainWidth, CurtainHeight);
    mRightCurtain.SetImage(imageDir + RightCurtain);

    mLeftCurtain.BottomCenteredRectangle(CurtainWidth, CurtainHeight);
    mLeftCurtain.SetImage(imageDir + LeftCurtain);

    mRightCurtain.Rectangle(-CurtainWidth / 2, 0, CurtainWidth / 2, CurtainHeight);
    mLeftCurtain.Rectangle(-CurtainWidth / 2, 0, CurtainWidth / 2, CurtainHeight);
}



void Curtains::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    graphics->PushState();

    auto machine = GetMachine();
    auto time = machine->GetMachineTime();

    double scale = time / CurtainOpenTime;
    scale = std::min(scale, 1.0);

    mRod.DrawPolygon(graphics, a + 50, b - 60, 0);
    graphics->PopState();

    double movementFactor = scale * (CurtainWidth / 2);


    const double minWidthScale = 0.3;
    double widthScaleFactor = std::max(1.0 - scale, minWidthScale);

// Initial position adjustments
    double initialLeftCurtainX = a + (CurtainWidth / 2) - (movementFactor * widthScaleFactor) - 700;
    double initialRightCurtainX = a + (CurtainWidth / 2) + movementFactor - 350 ;


    graphics->PushState();
    graphics->Translate(initialLeftCurtainX, b - 70);
    graphics->Scale(widthScaleFactor, 1.0);
    mLeftCurtain.Draw(graphics);
    graphics->PopState();


    graphics->PushState();
    graphics->Translate(initialRightCurtainX, b - 70);
    graphics->Scale(widthScaleFactor, 1.0);
    mRightCurtain.Draw(graphics);
    graphics->PopState();
}


void Curtains::Update(double elapsed)
{
}

void Curtains::Reset()
{
    mIsOpening = false;
    mAnimationProgress = 0.0;
}

void Curtains::SetPosition(double a, double b)
{
    mLeftCurtain.SetInitialPosition(a, b);
    mRightCurtain.SetInitialPosition(a, b);
}

wxPoint Curtains::GetPosition()
{
    return  wxPoint(mRightCurtain.GetPosition().m_x, -mRightCurtain.GetPosition().m_y),
    wxPoint(mLeftCurtain.GetPosition().m_x, mLeftCurtain.GetPosition().m_y);

}

void Curtains::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
}
