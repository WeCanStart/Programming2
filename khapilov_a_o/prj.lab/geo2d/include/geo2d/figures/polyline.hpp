namespace geo2d {

    /**
     * \brief Polyline is a Sequential connected points in plain.
     * \details Simple figure is a collection of sequential connected coordinates.
     * It may be open or closed. If it's closed, last and first points are connected too.
     * \tparam closed Bool parameter. If it's true, figure has edge
     * that is ended at first and last points.
     */
    template<
        bool closed_ = true,
    >
    class Polyline : public Figure {
    public:
        static constexpr bool closed = closed_;

    public:
        constexpr Polyline();
        ~Polyline();

        Polyline(const Polyline&);
        Polyline& operator=(const Polyline&);

        /**
         * \brief Construct from range.
         * \tparam Iterator Type of iterators.
         * \param begin Iterator from range begin.
         * \param end Iterator from range end.
         */
        template<std::input_iterator Iterator>
        Polyline(const Iterator& begin, const Iterator& end);

        /**
         * \brief Polyline supported initializer list constructor.
         * \param il initializer list
         */
        Polyline(std::initializer_list<Coordinates> il);

        void WriteTo(std::ostream& ostream) const override;
        void ReadFrom(std::istream& istream) override;

        // ВНИМАНИЕ! это минимальный интерфейс. он специально сделан эквивалентным std::vector.

        /**
         * \brief Доступ к точкам по индексу
         * \param i Индекс точки.
         * \return i-тая точка.
         */
        [[nodiscard]] Coordinates& operator[](const std::size_t i);
        [[nodiscard]] const Coordinates& operator[](const std::size_t i) const;

        /**
         * \return Текущее количество точек.
         */
        [[nodiscard]] constexpr const std::size_t& size() const;

        /**
         * \brief Вставляет точку на i-ое место.
         * \param i Индекс точки, которая будет добавлена.
         * \param value Точка, которую надо добавить.
         */
        void insert(const std::size_t i, const Coordinates& value);

        /**
         * \brief Удаляет точку из Polyline
         * \param i индекс удаляемого элемента
         */
        void remove(const std::size_t i);
    };

} // geo2d