/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineAdapter.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
        std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    auto machine1 = std::make_shared<Actor>(L"MachineAdaptation1");
    machine1->SetPosition(wxPoint(900,300));
    auto machineAdaptation1 = std::make_shared<MachineAdapter>(resourcesDir);
    machine1->AddDrawable(machineAdaptation1);
    machine1->SetRoot(machineAdaptation1);
    machineAdaptation1->SetMachineNumber(1);
    machineAdaptation1->SetTimeline(picture->GetTimeline());
    machineAdaptation1->SetStartTime(7);
    machineAdaptation1->SetEndTime(250);
    picture->AddActor(machine1);
    picture->SetMachine1(machineAdaptation1);


    auto machine2 = std::make_shared<Actor>(L"MachineAdaptation2");
    machine2->SetPosition(wxPoint(900,700));
    auto machineAdaptation2 = std::make_shared<MachineAdapter>(resourcesDir);
    machine2->AddDrawable(machineAdaptation2);
    machine2->SetRoot(machineAdaptation2);
    machineAdaptation2->SetMachineNumber(2);
    machineAdaptation2->SetTimeline(picture->GetTimeline());
    machineAdaptation2->SetStartTime(45);
    machineAdaptation2->SetEndTime(280);
    picture->AddActor(machine2);
    picture->SetMachine2(machineAdaptation2);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);

    return picture;
}

