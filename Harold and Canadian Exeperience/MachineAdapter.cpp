/**
 * @file MachineAdapter.cpp
 * @author Noor M.
 */

#include "pch.h"
#include <machine-api.h>
#include "MachineAdapter.h"
#include "Timeline.h"



MachineAdapter::MachineAdapter(std::wstring resourcesDir) : Drawable(resourcesDir)
{
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();

}

void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.6f;

    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);

    mMachine->SetLocation(wxPoint(0, 0));

    mMachine->DrawMachine(graphics);


    double currentFrame = mTimeline->GetCurrentFrame();
    mFrameCurrent = currentFrame;
    double frameRate = mTimeline->GetFrameRate();


    if(currentFrame >= mStartFrame && currentFrame <= mEndFrame)
    {
        SetFrame(currentFrame);
    }
    SetFrameRate(frameRate);

    graphics->PopState();
}

void MachineAdapter::SetActor(Actor *actor)
{
    Drawable::SetActor(actor);
}


void MachineAdapter::SetTimeline(Timeline *timeline)
{
    mTimeline = timeline;
}

void MachineAdapter::SetFrameRate(double rate)
{
    mMachine->SetFrameRate(rate);
}


void MachineAdapter::SetFrame(double frame)
{
    mMachine->SetMachineFrame(mFrameCurrent - mStartFrame);
}

void MachineAdapter::OpenDialogMachine(wxWindow *parent)
{
    MachineDialog dlg(parent, mMachine);
    dlg.ShowModal();
}