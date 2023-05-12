#include <iostream>

namespace geo2d {

    /**
     * \brief Class that contains coordinates in decart R^2 coordinates system.
     */
    class Coordinates {
    public:
        // It's nessasary for complicity version.
        using Coordinate = float;
        static constexpr std::size_t dimension = 2;

    public:
        constexpr Coordinates();
        ~Coordinates();

        Coordinates(const Coordinates&);
        Coordinates& operator=(const Coordinates&);

        constexpr Coordinates(std::initializer_list<Coordinate> il);

        /**
         * \brief Get coordinate per axis.
         * \tparam n Number of coordinate axis.
         * \return Coordinate per axis.
         */
        template<std::size_t n>
        constexpr const Coordinate& get() const;
        constexpr const Coordinate& get(const std::size_t n) const;

        /**
         * \brief Set coordinate value per axis.
         * \tparam n Number of coordinate axis.
         * \param value Value to set.
         */
        template<std::size_t n>
        constexpr void set(const Coordinate& value);
        constexpr void set(const std::size_t n, const Coordinate& value);
    };

} // geo2d