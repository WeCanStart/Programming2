namespace geo2d {

    /**
     * \brief Polygon is a part of square with holes.
     * \details Polygon is a type of figure primitive. It's closed polyline with the inner holes.
     */
    class Polygon : public Figure {
    private:
        using PolylineType = Polyline<true>; // Closed polyline.
        using PolylinesContainer = std::vector<PolylineType>;

    public:
        constexpr Polygon();
        ~Polygon();

        Polygon(const Polygon&);
        Polygon& operator=(const Polygon&);

        /**
         * \brief Construct from initializer list.
         * First item in il is a outer, all others are inners.
         * \param il Initializer list, if it empty, outer is a default polyline,
         * else first item is a outer, all others are inners.
         */
        Polygon(std::initializer_list<PolylineType> il);

        void WriteTo(std::ostream& ostream) const override;
        void ReadFrom(std::istream& istream) override;

        /**
         * \brief Outer getter.
         * \return Reference to outer.
         */
        constexpr PolylineType& Outer();

        /**
         * \brief Const version of outer getter.
         * \return Const reference to outer.
         */
        constexpr const PolylineType& Outer() const;

        /**
         * \brief Inners getter.
         * \return Reference to inners collection.
         */
        constexpr PolylinesContainer& Inners();

        /**
         * \brief Const version of inners getter.
         * \return Const reference to inners collection.
         */
        constexpr const PolylinesContainer& Inners() const;

        /**
         * \brief Clear polygon.
         */
        void Clear();
    };

} // geo2d