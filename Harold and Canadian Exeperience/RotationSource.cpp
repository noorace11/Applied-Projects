/**
 * @file RotationSource.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "RotationSource.h"
#include "Component.h"

RotationSource::RotationSource()
{

}

void RotationSource::SetRotation(double rotation, double speed)
{
    for(auto rotations : mRotationVector)
    {
        rotations->SetRotation(rotation, speed);
    }
}

void RotationSource::AddSink(std::shared_ptr<RotationSink> sink)
{
    mRotationVector.push_back(sink);
}

