/**
 * @file HamsterAndConveyorFactory.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H

class MachineComponent;
class Hamster;
class Conveyor;
class Body;


/**
 * Hamster and Conveyor factory to merge hamster and conveyor with pulley
 */
class HamsterAndConveyorFactory
{
private:
    /// The machine we are adding these components to
    std::shared_ptr<MachineComponent> mMachine;

    /// The directory for the images
    std::wstring mImagesDir;

    /// The hamster wheel
    std::shared_ptr<Hamster> mHamster;

    /// The conveyor
    std::shared_ptr<Conveyor> mConveyor;
public:
    /**
     * Constructor
     * @param machine The Machine to add the components to
     * @param imagesDir Directory containing the images
     */
    HamsterAndConveyorFactory(std::shared_ptr<MachineComponent> machine, std::wstring imagesDir) :
        mMachine(machine), mImagesDir(imagesDir) {}

    /// Default constructor (disabled)
    HamsterAndConveyorFactory() = delete;

    /// Copy constructor (disabled)
    HamsterAndConveyorFactory(const HamsterAndConveyorFactory &) = delete;

    /// Assignment operator
    void operator=(const HamsterAndConveyorFactory &) = delete;

    /**
     * Creates a new Hamster and Conveyor object.
     * @param hamsterPosition The position where the hamster will be created.
     * @param conveyorPosition The position where the conveyor will be created.
     */
    void Create(wxPoint2DDouble hamsterPosition, wxPoint2DDouble conveyorPosition);

    /**
     * Add a ball onto the conveyor belt for the just created hamster
     * conveyor belt combination.
     * @param placement Placement left (negative) to right (positive)
     * @return Ball object
     */
    std::shared_ptr<Body> AddBall(double placement);

    /**
     * Get the constructed Hamster object
     * @return Hamster object
     */
    std::shared_ptr<Hamster> GetHamster() {return mHamster;}

    /**
     * Get the constructed Conveyor object
     * @return Conveyor object
     */
    std::shared_ptr<Conveyor> GetConveyor() {return mConveyor;}


};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
