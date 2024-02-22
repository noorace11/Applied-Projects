/**
 * @file MachineSystem.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "MachineSystem.h"
#include "ActualMachine1Factory.h"
#include "ActualMachine2Factory.h"
#include "MachineComponent.h"


MachineSystem::MachineSystem(std::wstring name) : mDirectory(name)
{
    ActualMachine1Factory machine(mDirectory);
    mMachineComponent = machine.Create();
    mMachineComponent->Reset();

}

void MachineSystem::SetMachineFrame(int frame)
{
    if(frame < mCurrentFrame)
    {
        mCurrentFrame = 0;
        mMachineComponent->Reset();
    }

    for( ; mCurrentFrame < frame;  mCurrentFrame++)
    {
        mMachineComponent->Update(1.0 / mFrameRate);
    }
    mMachineComponent->SetMachineTime(mCurrentFrame/mFrameRate);
}

void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(1.5, -1.5);
    mMachineComponent->Draw(graphics);
    graphics->PopState();
}


void MachineSystem::SetMachineNumber(int machineNumber)
{
    mMachineNumber = machineNumber;

    if(GetMachineNumber() == 1)
    {
        ActualMachine1Factory machine1(mDirectory);
        mMachineComponent = machine1.Create();
        mMachineComponent->Reset();

    }
    else if (GetMachineNumber() == 2)
    {
        ActualMachine2Factory machine2(mDirectory);
        mMachineComponent = machine2.Create();
        mMachineComponent->Reset();
    }

}