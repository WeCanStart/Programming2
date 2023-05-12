namespace geo2d {

    /**
     * \brief Simple primitive. Figure with one point.
     * \details That's class implement point for 2 dimension.
     * First coordinate is x and second is y.
     */
    class Point : public Figure {
    public:
        constexpr Point();
        ~Point();

        Point(const Point&);
        Point& operator=(const Point&);

        constexpr Point(const float x, const float y);
        constexpr Point(const Coordinates& coordinates);

        void WriteTo(std::ostream& ostream) const override;
        void ReadFrom(std::istream& istream) override;

        /**
         * \brief Coordinates getter.
         * \return Reference to coordinates.
         */
        Coordinates& Coord();

        /**
         * \brief X coordinate getter.
         * \return Const reference to X coord.
         */
        constexpr const float& x() const;

        /**
         * \brief Y coordinate getter.
         * \return Const reference to Y coord.
         */
        constexpr const float& y() const;

        /**
         * \brief Set X coordinate by value.
         * \param v Value to set.
         */
        constexpr void x(const float v);

        /**
         * \brief Set Y coord by value.
         * \param v Value to set.
         */
        constexpr void y(const float v);
    };

} // geo2d