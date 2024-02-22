/**
 * @file Component.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Component.h"
#include "MachineComponent.h"



double Component::GetTime()
{
    return mMachine->GetMachineTime();
}


MachineComponent* Component::GetMachine()
{
    if(mMachine != nullptr)
    {
        return mMachine;
    }
}
