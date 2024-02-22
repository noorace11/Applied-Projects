/**
 * @file MachineSystem.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#include "IMachineSystem.h"
class MachineComponent;
class ActualMachine1Factory;
class ActualMachine2Factory;


/**
 * Machine System class that inherits from the interface machine class
 */
class MachineSystem : public IMachineSystem
{
private:
    /// flag member variable
    int mFlag = 0;
    /// machine number member variable
    int mMachineNumber = 1;
    ///location member variable
    wxPoint mLocation = wxPoint(0,0);
    /// current time member variable
    int mCurrentTime = 0;
    /// current frame member variable
    int mCurrentFrame = 0;
    /// frame rate member variable
    double mFrameRate = 30.0;
    ///Machine object pointer
    std::shared_ptr<MachineComponent> mMachineComponent;
    /// directory member variable
    std::wstring mDirectory;
    /// machine 1 factory member variable
    std::shared_ptr<ActualMachine1Factory> mMachine;

public:
    /**
     * Constructor
     * @param name
     */
    MachineSystem(std::wstring name);

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;


    virtual ~MachineSystem() {}

    /**
     * Setting location
     * @param location
     */
    void SetLocation(wxPoint location) override {mLocation = location;}

    /**
     * Getting location
     * @return
     */
    wxPoint GetLocation() override {return mLocation;}

    /**
     * Draw Machine
     * @param graphics
     */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Setting machine number
     * @param machineNumber
     */
    void SetMachineNumber(int machineNumber) override;
    /**
     * Getting machine number
     * @return machine number entered
     */
    int GetMachineNumber() override {return mMachineNumber;}

    /**
     * Setting machine frame
     * @param frame
     */
    void SetMachineFrame(int frame) override;

    /**
     * Setting frame rate
     * @param rate
     */
    void SetFrameRate(double rate) override { mFrameRate = rate;}

    /**
     * Getting frame rate
     * @return
     */
    double GetFrameRate() {return mFrameRate;}

    /**
     * Getting machine time based on frames
     * @return
     */
    double GetMachineTime() override {return mCurrentFrame/mFrameRate;}

    /**
     * Setting flag
     * @param flag
     */
    void SetFlag(int flag) override {mFlag = flag;}




};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
