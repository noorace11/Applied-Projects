/**
 * @file MachineAdapter.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
#include <machine-api.h>
#include "Drawable.h"
#include "MainFrame.h"

class Timeline;

/**
 * Adapter class for Machine to Canadian Experience
 */
class MachineAdapter : public Drawable
{
private:
    /// IMachine system pointer
    std::shared_ptr<IMachineSystem> mMachine;
    /// The start frame of the machine.
    int mStartFrame = 1;

    /// The end frame of the machine.
    int mEndFrame = 1;

    /// current frame member variable
    int mFrameCurrent = 0;

    /// Timeline pointer object
    Timeline *mTimeline;

public:
    /// Default constructor (disabled)
    MachineAdapter() = delete;

    /// Copy constructor (disabled)
    MachineAdapter(const MachineAdapter &) = delete;

    /// Assignment operator
    void operator=(const MachineAdapter &) = delete;

    /**
     * Constructor
     * @param resourcesDir
     */
    MachineAdapter(std::wstring  resourcesDir);

    /**
     * Drawing machines
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Setting actors
     * @param actor
     */
    void SetActor(Actor *actor) override;

    /**
     * Git test
     * @param pos
     * @return false to stop machine movement
     */
    bool HitTest(wxPoint pos) override {return false;}

    /**
     * Setting timeline
     * @param timeline
     */
    void SetTimeline(Timeline *timeline) override;

    /**
     * Setting framerate
     * @param rate
     */
    void SetFrameRate(double rate);

    /**
     * Settting a frame
     * @param frame
     */
    void SetFrame(double frame);

    /**
     * Empty setkeyframe avoiding virtual function issues
     */
    void SetKeyframe() override {}
    /**
     * Empty getkeyframe avoiding virtual function issues
     */
    void GetKeyframe() override {}

    /**
     * Setting frame to start
     * @param timeFrame
     */
    void SetStartTime(int timeFrame){mStartFrame = timeFrame;}

    /**
     * Getting frame to start at time
     * @return
     */
    int GetStartTime(){return mStartFrame;}

    /**
     * Setting frame to end
     * @param timeFrame
     */
    void SetEndTime(int timeFrame){mEndFrame = timeFrame;}

    /**
     * Setting machine number
     * @param machineNum
     */
    void SetMachineNumber(int machineNum){mMachine->SetMachineNumber(machineNum);}

    /**
     * Getting machine number
     * @return
     */
    int GetMachineNumber(){return mMachine->GetMachineNumber();}

    /**
     * Opening dialog for machines
     * @param parent
     */
    void OpenDialogMachine(wxWindow *parent);


};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
