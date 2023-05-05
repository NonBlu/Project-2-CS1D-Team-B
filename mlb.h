#pragma once

#include <QString>
#include <vector>

using std::vector;

/**
 * @brief Enum class for team Leagus
 */
enum class League : unsigned char
{
    American = 1, National
};


/**
 * @brief Enum class stadiums playing surface
 */
enum class Surface : unsigned char
{
    Grass = 1, Turf, Turf3D
};


/**
 * @brief Enum class for a stadiums typology
 */
enum class Typology : unsigned char
{
    Contemporary = 1, JewelBox,     Modern,
    Multipurpose,     RetroClassic, RetroModern

};


/**
 * @brief Enum class for a stadiums roof type
 */
enum class RoofType : unsigned char
{
    Fixed = 1, Open, Retractable
};


/** ******************************************************
 * @class MLB
 * @brief class for storing and accessing all MLB info
 ********************************************************/
class MLB
{
  public:

    friend class StadiumManager;
    friend class AdminPage;

    struct Souvenir
    {
        Souvenir() : name { }, price { } {}

        Souvenir(const QString& name, float price)
            : name { name }, price { price } { }

        /**
         * @brief overloaded asignment operator.
         * @details for handling being set to 0.
         * @return A souvenir with values set to "" & 0.
         */
        Souvenir& operator=(int);

        /**
         * @brief Overloaded equality operator.
         * @param [in] rhs Reference to another Souvenir.
         * @return True if the names match, false otherwise.
         */
        bool operator==(const Souvenir& rhs);

        /**
         * @brief overloaded inequality operator.
         * @param [in] rhs Reference to another souvenir.
         * @return True if the name is not equal, false otherwise.
         */
        bool operator!=(const Souvenir& rhs);

        QString name;   /**< Name of the souvenir  */
        float   price;  /**< Price of the souvenir */
    };

    /**
     * @brief Defalt constructor
     * @param [in] team Name of the team
     * @details sets the teams name if provided
     * and all other values to a default of none.
     */
    MLB(const QString& team = "");


     MLB(const MLB& other)     = default;
     MLB(MLB&& other) noexcept = default;
     ~MLB() = default;

     MLB& operator=(const MLB& rhs)     = default;
     MLB& operator=(MLB&& rhs) noexcept = default;

    /**
     * @brief Overloaded equality operator
     * @param [in] rhs another MLB object to compare
     * @details compares the the teams name
     */
    bool operator==(const MLB& rhs) const;

    /**
     * @brief Overloaded inequality operator
     * @param [in] rhs Another MLB object to compare
     * @details compares the the teams name
     */
    bool operator!=(const MLB& rhs) const;


    // Mutators

    /**
     * @brief Method to set team name
     * @param [in] name Name of the team
     */
    void setTeamName(const QString& name);

    /**
     * @brief Method to set the Stadium name
     * @param [in] name Name of the stadium
     */
    void setStadiumName(const QString& name);

    /**
     * @brief Method to set the stadiums location
     * @param [in] location Location of the stadium
     */
    void setLocation(const QString& location);

    /**
     * @brief Method to set the seating capacity
     * @param [in] capacity Seating capacity for stadium
     */
    void setSeatingCapacity(int capacity);

    /**
     * @brief Method to set the date opened
     * @param [in] date Date the stadium opened
     */
    void setDateOpened(int date);

    /**
     * @brief Method to set distance to center in feet
     * @param [in] feet Number of feet to the center
     */
    void setDistanceToCenterFT(int feet);

    /**
     * @brief Method to set distance to center in meters
     * @param [in] meters Number of meters to center
     */
    void setDistanceToCenterM(int meters);

    /**
     * @brief Method to set the teams league
     * @param [in] league The teams league
     */
    void setLeague(const QString& league);

    /**
     * @brief Method to set the playing surface
     * @param [in] surface The stadiums playing surface
     */
    void setSurface(const QString& surface);

    /**
     * @brief Method to the typology
     * @param [in] typology The stadiums typology
     */
    void setTypology(const QString& typology);

    /**
     * @brief Method to set the stadiums roof type
     * @param [in] roofType The stadiums roof type
     */
    void setRoofType(const QString& roofType);

    /**
     * @brief Method to add a souvenir for the stadium
     * @param [in] name Name of the souvenir
     * @parem [in] price Price of the souvenir
     */
    void addSouvenir(const QString& name, float price);

    /**
     * @brief Method to remove a souvenir from a stadium
     * @param [in] name Name of the souvenir to remove
     */
    void removeSouvenir(const QString& name);

    /**
     * @brief Method Method to modify a souvenirs name
     * @param [in] oldName Current name of the souvenir
     * @param [in] newName New name for the souvenir
     */
    void modifySouvenirName(const QString& oldName, const QString& newName);

    /**
     * @brief Method to modify the price of a souvenir
     * @param [in] name Name of the souvenir to modify
     * @param [in] newPrice New price to update the souvenir with
     */
    void modifySouvenirPrice(const QString& name, float newPrice);



    // Accessors

    /**
     * @brief Method to get a teams name
     * @return The name of the team
     */
    const QString& getTeamName() const;

    /**
     * @brief Method to get a stadiums name
     * @return The name of the stadium
     */
    const QString& getStadiumName() const;

     /**
     * @brief Method to get the stadiums location
     * @return The location of the stadium
     */
    const QString& getLocation() const;

    /**
     * @brief Method to get a stadiums seating capacity
     * @return The stadiums seating capacity
     */
    int getSeatingCapacity() const;

    /**
     * @brief Method to get the Date the stadium opened
     * @return The date the stadium opened
     */
    int getDateOpened() const;

    /**
     * @brief Method to get the distance to center (Feet)
     * @return The feet to the center of the stadium
     */
    int getFeetToCenter() const;

    /**
     * @brief Method to get the distance to center (Meters)
     * @return The meters to the center of the stadium
     */
    int getMetersToCenter() const;

    /**
     * @brief Method to get the teams league
     * @return The teams league
     */
    QString getLeague()   const;

    /**
     * @brief Method to get the the playing surface
     * @return The stadiums playing surface
     */
    QString getSurface()  const;

    /**
     * @brief Method to the stadiums typology
     * @return The stadiums typology
     */
    QString getTypology() const;

    /**
     * @brief Method to get the stadiums roog type
     * @return The stadiums roof type
     */
    QString getRoofType() const;

    vector<Souvenir>& getSouvenirs();

 private:
    QString  teamName;         /**< Name of the teams             */
    QString  stadiumName;      /**< Name of the stadium           */
    QString  location;         /**< Location of the stadium       */
    int      seatingCapacity;  /**< Stadiums seating capacity     */
    int      dateOpened;       /**< Date the stadium opened       */
    int      feetToCenter;     /**< Distance to center in feet    */
    int      metersToCenter;   /**< Distance to center in meters  */
    League   league;           /**< The teams league              */
    Surface  surface;          /**< The stadiums playing surface  */
    Typology typology;         /**< The stadiums typology         */
    RoofType roofType;         /**< The stadiums roof type        */

    vector<Souvenir> souvenirs;  /**< container of souvenirs  */
};
