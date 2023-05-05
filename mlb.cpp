#include "mlb.h"
#include <QDebug>

//MLB::MLB(const QString& team)
//: teamName {team}, stadiumName {}, location {}, seatingCapacity {}, dateOpened {},
//  feetToCenter {}, metersToCenter {}, league {}, surface {}, typology {}, roofType {}, souvenirs(7)  { }


MLB::MLB(const QString& team)
    : teamName { team } { }


bool MLB::operator==(const MLB& rhs) const
{
    return this->teamName == rhs.teamName;
}


bool MLB::operator!=(const MLB& rhs) const
{
    return this->teamName != rhs.teamName;
}


void MLB::setTeamName(const QString& name)
{
    teamName = name;
}


void MLB::setStadiumName(const QString& name)
{
    stadiumName = name;
}


void MLB::setLocation(const QString& location)
{
    this->location = location;
}


void MLB::setSeatingCapacity(int capacity)
{
    seatingCapacity = capacity;
}


void MLB::setDateOpened(int date)
{
    dateOpened = date;
}


void MLB::setDistanceToCenterFT(int feet)
{
    feetToCenter = feet;
}


void MLB::setDistanceToCenterM(int meters)
{
    metersToCenter = meters;
}


void MLB::setLeague(const QString& league)
{
    if (league == "American")
    {
        this->league = League::American;
    }
    else if (league == "National")
    {
        this->league = League::National;
    }
}


void MLB::setSurface(const QString& surface)
{
    if (surface == "Grass")
    {
        this->surface = Surface::Grass;
    }
    else if (surface == "AstroTurf GameDay Grass")
    {
        this->surface = Surface::Turf;
    }
    else if (surface == "AstroTurf GameDay Grass 3D")
    {
        this->surface = Surface::Turf3D;
    }
}


void MLB::setTypology(const QString& typology)
{
    if (typology == "Contemporary")
    {
        this->typology = Typology::Contemporary;
    }
    else if (typology == "Jewel Box")
    {
        this->typology = Typology::JewelBox;
    }
    else if (typology == "Modern")
    {
        this->typology = Typology::Modern;
    }
    else if (typology == "Multipurpose")
    {
        this->typology = Typology::Multipurpose;
    }
    else if (typology == "Retro Classic")
    {
        this->typology = Typology::RetroClassic;
    }
    else if (typology == "Retro Modern")
    {
        this->typology = Typology::RetroModern;
    }
}


void MLB::setRoofType(const QString& roofType)
{
    if (roofType == "Fixed")
    {
        this->roofType = RoofType::Fixed;
    }
    else if (roofType == "Open")
    {
        this->roofType = RoofType::Open;
    }
    else if (roofType == "Retractable")
    {
        this->roofType = RoofType::Retractable;
    }
}


const QString& MLB::getTeamName() const
{
    return teamName;
}


const QString& MLB::getStadiumName() const
{
    return stadiumName;
}


const QString& MLB::getLocation() const
{
    return location;
}


int MLB::getSeatingCapacity() const
{
    return seatingCapacity;
}


int MLB::getDateOpened() const
{
    return dateOpened;
}


int MLB::getFeetToCenter() const
{
    return feetToCenter;
}


int MLB::getMetersToCenter() const
{
    return metersToCenter;
}


QString MLB::getLeague() const
{
    switch (league)
    {
        case League::American : return "American";
        case League::National : return "National";
    }
}


QString MLB::getSurface() const
 {
    switch (surface)
    {
        case Surface::Grass  : return "Grass";
        case Surface::Turf   : return "AstroTurf GameDay Grass";
        case Surface::Turf3D : return "AstroTurf GameDay Grass 3D";
    }
 }


 QString MLB::getTypology() const
 {
    switch (typology)
    {
        case Typology::Contemporary : return "Contemporary";
        case Typology::JewelBox     : return "Jewel Box";
        case Typology::Modern       : return "Modern";
        case Typology::Multipurpose : return "Multipurpose";
        case Typology::RetroClassic : return "Retro Classic";
        case Typology::RetroModern  : return "Retro Modern";
    }
 }


 QString MLB::getRoofType() const
 {
    switch (roofType)
    {
        case RoofType::Fixed       : return "Fixed";
        case RoofType::Open        : return "Open";
        case RoofType::Retractable : return "Retractable";
    }
 }

 void MLB::addSouvenir(const QString& name, float price)
 {
    souvenirs.push_back(Souvenir { name, price });
 }



void MLB::modifySouvenirName(const QString& oldName, const QString& newName)
{
    for (auto& souvenir : souvenirs)
    {
        if (oldName == souvenir.name)
        {
            souvenir.name = newName;

            break;
        }
    }
}


 void MLB::modifySouvenirPrice(const QString& name, float price)
{
    for (auto& souvenir : souvenirs)
    {
        if (name == souvenir.name)
        {
            souvenir.price = price;

            break;
        }
    }
}



void MLB::removeSouvenir(const QString& name)
{
    int count { };

    for (const auto& souvenir : souvenirs)
    {
        if (name == souvenir.name)
        {
            souvenirs.erase(souvenirs.begin() + count);
         //   souvenirs.remove(souvenir);

            break;
        }

        ++count;
    }
}


MLB::Souvenir& MLB::Souvenir::operator=(int x)
{
    if (!x)
    {
        name  = "";
        price = 0;
    }

    return *this;
}


bool MLB::Souvenir::operator==(const Souvenir& rhs)
{
    return name == rhs.name ? true : false;
}



bool MLB::Souvenir::operator!=(const Souvenir& rhs)
{
    return name != rhs.name ? true : false;
}




vector<MLB::Souvenir>& MLB::getSouvenirs()
{
    return souvenirs;
}
