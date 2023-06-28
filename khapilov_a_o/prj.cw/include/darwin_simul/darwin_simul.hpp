#pragma once
#ifndef DARWIN_SIMUL_HPP_20230503
#define DARWIN_SIMUL_HPP_20230503

#include <iostream>
#include <exception>
#include <cmath>
#include <array>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <type_traits>
#include <thread>



namespace ds {

    /// @brief Class which represents list of types
    /// @tparam Types... Types which this class is storaging
    template<class... Types>
    class TList {};

    /// @brief Base case for tSize compile-time function
    /// @return Size, which is zero
    constexpr int tSize(TList<>) {
        return 0;
    }

    /// @brief Compile-time function that finds size of TList 
    /// @tparam Head The first param of the list
    /// @tparam Tail... Other params of the list
    /// @param list List of types
    /// @return Size of list
    template<class Head, class... Tail>
    constexpr int tSize(TList<Head, Tail...> list) {
        return 1 + tSize(TList<Tail...>{});
    }


    /// @brief Base case for inTList function
    /// @return True if lhs equals to rhs
    template<class T, class Head>
    bool inTList(TList<T, Head>) {
        return std::is_same<T, Head>::value;
    }

    /// @brief Function which checks whether a type in list of types
    /// @tparam T Type to check belonging to the list
    /// @tparam Head First element of the list
    /// @tparam Tail... Other elements of the list
    /// @param list TList Object which first element is T, and others are Head and Tail...
    /// @return True if TList contains T
    template<class T, class Head, class... Tail>
    bool inTList(TList<T, Head, Tail...> list) {
        return (std::is_same<T, Head>::value || inTList(TList<T, Tail...>{}));
    }


    /// @brief Base case for indexTList function
    /// @return Index, which is zero
    template<class T, class Head>
    int indexTList(TList<T, Head>) {
        return 0;
    }

    /// @brief Function which finds index of T in list
    /// @tparam T Type which index we are looking for
    /// @tparam Head First type in list
    /// @tparam Tail... Other types in list
    /// @param list TList Object which first element is T, and others are Head and Tail...
    /// @return Index of type T in list
    template<class T, class Head, class... Tail>
    int indexTList(TList<T, Head, Tail...> list) {
        return std::is_same<T, Head>::value ? 0 : 1 + indexTList(TList<T, Tail...>{});
    }



    /// @brief Class which represents form of live, which library works with
    class Par;

    /// @brief Concept which allows user only class, derived from Par
    template <class T>
    concept ParC = std::is_base_of<Par, T>::value;

    /// @brief Class which represents form of live, which library works with
    class Par {
    public:
        
        /// @brief Default ctor
        Par() = default;

        /// @brief Ctor with common Par params
        /// @param mass_ Start mass
        /// @param x_ Start x coordinate
        /// @param y_ Start y coordinate
        /// @param viewRange_ start distance organism can see other organisms for
        Par(double mass_, double x_, double y_, double viewRange_) : startMass(mass_), mass(mass_), x(x_), y(y_), viewRange(viewRange_) {};

        /// @brief Default dtor
        virtual ~Par() = default;

        /// @return Radius of the cell based on its mass
        double radius() const {
            return 5 * std::pow(mass, 0.3333);
        }

        /// @brief Decrease mass 
        void looseMass(double loose) {
            if (loose < 0) throw std::exception("bad loose");
            mass -= loose;
        }

        /// @return Current mass of the organism
        double getMass() const {
            return mass;
        }

        /// @return Start mass of the organism
        double getStartMass() const {
            return startMass;
        }

        /// @return Current x coordinate
        double getX() const {
            return x;
        }

        /// @return Current y coordinate
        double getY() const {
            return y;
        }

        /// @brief Change organism's x coordinate by dx
        void moveX(double dx) {
            x += dx;
        }

        /// @brief Change organism's y coordinate by dy
        void moveY(double dy) {
            y += dy;
        }

        /// @brief Change organism's x coordinate to x_
        void setX(double x_) {
            x = x_;
        }

        /// @brief Change organism's y coordinate to y_
        void setY(double y_) {
            y = y_;
        }

        /// @return True if organism is going to die
        bool isDead() {
            return killerNumber;
        }

        /// @brief Lhs organism makes rhs organism dead and gain mass by the end of the turn
        ///
        /// Lhs organism makes rhs organism dead and gain mass by the end of
        /// the turn in inverse proportion to number of killers of this organism
        void eat(Par* rhs) {
            if (this == rhs) throw std::exception("Form of live cannot eat itself");
            victim = rhs;
            ++rhs->killerNumber;
        }

        /// @brief Makes organism look dead for user
        void die() {
            ++killerNumber;
        }

        /// @return True is organism has victim
        bool hasVictim() {
            return victim;
        }

        /// @brief Write main params of an organism to ostrm
        /// @param ostrm Output stream
        void writeTo(std::ostream& ostrm) const {
            ostrm << startMass << ' ' << mass << ' ' << x << ' ' << y << ' ' << viewRange << ' ';
        }

        /// @brief Read main params of an organism from istrm
        /// @param istrm Input stream
        void readFrom(std::istream& istrm) {
            istrm >> startMass >> mass >> x >> y >> viewRange;
        }

        /// @brief Main class which represents simulation
        /// @tparam Types... Types of organisms that can be added to simulation
        template<ParC... Types>
        friend class DarwinSimulator;

        double viewRange = 10;

    private:

        double startMass = 0;
        double mass = 1;

        double x = 0, y = 0;

        Par* victim = nullptr;
        int killerNumber = 0;
    };

    /// @brief Operator which writes organism to ostrm
    /// @param ostrm Output stream
    /// @param p Organism we are writing to ostrm
    /// @return ostrm Output stream
    std::ostream& operator<<(std::ostream& ostrm, const Par& p) {
        p.writeTo(ostrm);
        return ostrm;
    }

    /// @brief Operator which reads organism from istrm
    /// @param istrm Input stream
    /// @param p Organism we are reading from istrm
    /// @return istrm Input stream
    std::istream& operator>>(std::istream& istrm, Par& p) {
        p.readFrom(istrm);
        return istrm;
    }



    /// @brief Comparator which helps sorting organisms firstly by x, then by y if x coordinates are equal
    auto cmp = [](const Par* lhs, const Par* rhs) { return (lhs->getX() == rhs->getX()) ? (lhs->getY() < rhs->getY()) : (lhs->getX() < rhs->getX()); };

    /// @brief Base case of writeArrOfMultisetTo
    template<int dim, ParC Head>
    void writeArrOfMultisetTo(std::array<std::multiset<Par*, decltype(cmp)>, dim>& arr, TList<Head>, std::ostream& ostrm, int i = 0) {
        ostrm << arr[i].size() << std::endl;
        for (auto el : arr[i]) {
            ostrm << *reinterpret_cast<Head*>(el) << std::endl;
        }
    }

    /// @brief Write structure we are working with to ostrm
    /// @tparam dim Size of array
    /// @tparam Head Type we are working with currently
    /// @tparam Tail... Types we will have to work later
    /// @param arr Main structure of library that we are writing to ostrm
    /// @param list List of Head and Tail...
    /// @param ostrm Output stream
    /// @param i Index of type we are working with to get element of array
    template<int dim, ParC Head, ParC... Tail>
    void writeArrOfMultisetTo(std::array<std::multiset<Par*, decltype(cmp)>, dim>& arr, TList<Head, Tail...> list, std::ostream& ostrm, int i = 0) {
        ostrm << arr[i].size() << std::endl;
        for (auto el : arr[i]) {
            ostrm << *reinterpret_cast<Head*>(el) << std::endl;
        }
        writeArrOfMultisetTo(arr, TList<Tail...>{}, ostrm, i + 1);
    }


    /// @brief Base case of readArrOfMultisetFrom
    template<int dim, ParC Head>
    void readArrOfMultisetFrom(std::array<std::multiset<Par*, decltype(cmp)>, dim>& arr, TList<Head>, std::istream& istrm, int i = 0) {
        int size = 0;
        istrm >> size;
        for (int j = 0; j < size; ++j) {
            Head var = Head();
            istrm >> var;
            arr[i].insert(reinterpret_cast<Par*>(new Head(var)));
        }
    }

    /// @brief Read structure we are working with from istrm
    /// @tparam dim Size of array
    /// @tparam Head Type we are working with currently
    /// @tparam Tail... Types we will have to work later
    /// @param arr Main structure of library that we are reading from istrm
    /// @param list Of Head and Tail...
    /// @param istrm Input stream
    /// @param i Index of type we are working with to put element to array
    template<int dim, ParC Head, ParC... Tail>
    void readArrOfMultisetFrom(std::array<std::multiset<Par*, decltype(cmp)>, dim>& arr, TList<Head, Tail...>, std::istream& istrm, int i = 0) {
        int size = 0;
        istrm >> size;
        for (int j = 0; j < size; ++j) {
            Head var = Head();
            istrm >> var;
            arr[i].insert(reinterpret_cast<Par*>(new Head(var)));
        }
        readArrOfMultisetFrom(arr, TList<Tail...>{}, istrm, i + 1);
    }

    /// @brief Class which is used to give user more or less comfortable form of data, which is used in DarwinSimulator class
    /// @tparam Types... Types of organisms which simulation works with
    template<ParC... Types>
    class TArray {
    public:
        /// @brief Ctor, which converts class-data to user-data
        /// @param inpArr Class-used data
        TArray(std::array < std::vector<Par*>, tSize(TList<Types...>{}) >& inpArr) : data(inpArr) {};

        /// @tparam T Type of organisms user wants to use
        /// @return Vector of T*
        template<ParC T>
        const std::vector<T*> getByType() const {
            int ind = indexTList(TList<T, Types...>{});
            int size = data[ind].size();
            std::vector<T*> retVec(size);
            for (int i = 0; i < size; ++i) {
                retVec[i] = reinterpret_cast<T*>(data[ind][i]);
            }
            return retVec;
        }

        /// @tparam T Type of organisms user wants to add to object
        /// @param newVec Vector of T
        template<ParC T>
        void putByType(const std::vector<T>& newVec) {
            int size = data[indexTList(TList<T, Types...>{})].size();
            std::vector<Par*>& vecToChange = data[size];
            for (auto& el : vecToChange) delete el;
            int newSize = newVec.size();
            vecToChange.resize(newSize);
            for (int i = 0; i < newSize; ++i) {
                vecToChange[i] = new Par(newVec[i]);
            }
        }
    private:
        constexpr static TList<Types...> list;
        std::array < std::vector<Par*>, tSize(list) >& data;
    };


    /// @brief Base function that lets user change state corresponding to seen organisms' states
    /// @tparam T Type of organism which state is updating
    /// @tparam Types... Types of visible organisms
    /// @param myOrg Ptr to organism which state is updating
    /// @param visible Organisms which myOrg can see
    /// @param dt_ Simulation's time step
    template<ParC T, ParC... Types>
    void calculations(T* myOrg, const TArray<Types...>& visible, double dt_) {};

    /// @brief Base function that lets user change its coordinates
    /// @tparam T Type of organism which state is updating
    /// @param myOrg Ptr to organism which coordinates is updating
    /// @param dt_ Simulation's time step
    template<ParC T>
    void move(T* myOrg, double dt_) {};

    /// @brief Function that handles collision of two organisms
    /// @tparam T1 Type of lhs organism
    /// @tparam T2 Type of rhs organism
    /// @param lhs Ptr to lhs organism
    /// @param rhs Ptr to rhs organism
    template<ParC T1, ParC T2>
    void collision(T1* lhs, T2* rhs) {};

    /// @brief Function that lets user add organism's children to simulation
    /// @tparam T Type of reproducing organism and its children
    /// @param myOrg Reproducing organism
    /// @param childs Vector which user can add organisms to
    template<ParC T>
    void reproduction(T* myOrg, std::vector<T>& childs) {};

    /// @brief Function that lets user add some organisms to simulation
    /// @tparam Types... Types of organisms that can be added to simulation
    /// @param organisms Object in which organisms can be added to
    /// @param massLeft Simulation's parameter which shows user what is the total mass they can add
    /// @param wid Width of the simulation's scene
    /// @param high Height of the simulation's scene
    /// @param dt_ Simulation's time step
    /// @warning If user will add more than allowed mass, exeption will be thrown
    template<ParC... Types>
    void spawn(TArray<Types...>& organisms, double massLeft, double wid, double high, double dt_) {};



    /// @brief Main class which represents simulation
    /// @tparam Types... Types of organisms that can be added to simulation
    template<ParC... Types>
    class DarwinSimulator {
    public:
        /// @brief Number of organism types
        constexpr static int simulDim = tSize(TList<Types...>{});

        /// @brief Empty ctor
        DarwinSimulator();

        /// @brief Main ctor
        /// @param dt_ Simulation's time step
        /// @param w_ Width of the simulation's scene
        /// @param h_ Height of the simulation's scene
        /// @param totalMass_ Maximal mass of simulation's organisms'
        DarwinSimulator(double dt_, double w_, double h_, double totalMass_);

        /// @brief Empty dtor
        ~DarwinSimulator();

        /// @brief Method, which adds organism to simulation
        /// @tparam T Type of organism
        /// @param inp Input organism
        template<ParC T>
        void addAlive(const T& inp);

        /// @brief Getter of organisms by type
        /// @tparam T Type which user wants to get organisms of
        /// @return Vector of organisms
        template<ParC T>
        std::vector<T*> get();

        /// @return Width of scene
        double getWidth();

        /// @return Height of scene
        double getHeight();

        /// @return update time step
        double getTimeStep();

        /// @brief Method that updates simulation for dt seconds
        void update();

        /// @brief Method that updates simulation some times
        /// @param times Number of times simulation updates
        void update(int times);

        /// @brief Function that writes simulation's state to output stream
        /// @param ostrm Output stream
        void writeTo(std::ostream& ostrm);

        /// @brief Read simulation's state from input stream
        /// @param istrm Input stream
        void readFrom(std::istream& istrm);

    private:

        /// @brief Base case for set method
        template<ParC Head>
        inline void set(TList<Head>, int i = 0) {
            calculations_fs[i] = [this](Par* p, const TArray<Types...>& arr, double dt_) {
                calculations(reinterpret_cast<Head*>(p), arr, dt_);
            };
            move_fs[i] = [](Par* p, double dt_) {
                move(reinterpret_cast<Head*>(p), dt_);
            };
            reproduction_fs[i] = [](Par* p, std::vector<Par*>& readyChildren) {
                std::vector<Head> children;
                reproduction(reinterpret_cast<Head*>(p), children);
                readyChildren.resize(children.size());
                for (int j = 0; j < children.size(); ++j) {
                    readyChildren[j] = reinterpret_cast<Par*>(new Head(children[j]));
                }
            };
        }

        /// @brief Method, that collects user-redefined functions which handle one organism
        /// @tparam Head Type corresponding to which functions are added
        /// @tparam Tail... Types that will be added later
        /// @param i Index of type we are working with to add functions to arrays
        template<ParC Head, ParC... Tail>
        inline void set(TList<Head, Tail...> list, int i = 0) {
            calculations_fs[i] = [this](Par* p, const TArray<Types...>& arr, double dt_) {
                calculations(reinterpret_cast<Head*>(p), arr, dt_);
            };
            move_fs[i] = [](Par* p, double dt_) {
                move(reinterpret_cast<Head*>(p), dt_);
            };
            reproduction_fs[i] = [](Par* p, std::vector<Par*>& readyChildren) {
                std::vector<Head> children;
                reproduction(reinterpret_cast<Head*>(p), children);
                readyChildren.resize(children.size());
                for (int j = 0; j < children.size(); ++j) {
                    readyChildren[j] = reinterpret_cast<Par*>(new Head(children[j]));
                }
            };
            set(TList<Tail...>{}, i + 1);
        }

        /// @brief Base-base case for set1d function
        /// @tparam T First organism's last type
        /// @tparam Head Second organism's last type
        /// @param i First type's index
        /// @param j Second type's index
        template<ParC T, ParC Head>
        inline void set1d(TList<T>, TList<Head>, int i = 0, int j = 0) {
            collision_fs[i][j] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<T, Head>);
            collision_fs[j][i] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<Head, T>);
        }

        /// @brief Base-main method, that collects user-redefined functions which handle two organisms
        /// @tparam T First organism's last type
        /// @tparam Head Second organism's type
        /// @tparam Tail... Second organism's types that will be used later
        /// @param i First type's index
        /// @param j Second type's index
        template<ParC T, ParC Head, ParC... Tail>
        inline void set1d(TList<T>, TList<Head, Tail...>, int i = 0, int j = 0) {
            collision_fs[i][j] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<T, Head>);
            collision_fs[j][i] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<Head, T>);
            set1d(TList<T>{}, TList<Tail...>{}, i, j + 1);
        }

        /// @brief Main-base method, that collects user-redefined functions which handle two organisms
        /// @tparam Head Start type to use for first organism
        /// @param i Index for arrays, which is simmetrical in this case for two organisms
        template<ParC Head>
        inline void set2d(TList<Head>, int i = 0) {
            collision_fs[i][i] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<Head, Head>);
        }

        /// @brief Main-main method, that collects user-redefined functions which handle two organisms
        /// @tparam Head Start type to use for first organism
        /// @tparam Tail... Other types to add functions 
        /// @param i Index for arrays, which is simmetrical in this case for two organisms
        /// 
        /// **Explanation of logic**
        /// Function table here looks like
        /// . . . . .
        /// . . . . .
        /// . . . . .
        /// . . . . .
        /// . . . . .
        /// Firstly left-top element will be filled,
        /// then two lines (top without left-top, left without left-top),
        /// now 4x4 part of table is unfilled.
        /// This process continues until right-bottom element fills
        template<ParC Head, ParC... Tail>
        inline void set2d(TList<Head, Tail...>, int i = 0) {
            collision_fs[i][i] = reinterpret_cast<void(*)(Par*, Par*)>(&collision<Head, Head>);
            set1d(TList<Head>{}, TList<Tail...>{}, i, i + 1);
            set2d(TList<Tail...>{}, i + 1);
        }

        /// @brief Function that finds every visible organism to current one
        /// @param myOrg Iterator of multiset of organisms
        /// @return Array of vectors of organisms
        /// @todo Rewrite return to TArray
        std::array < std::vector<Par*>, tSize(TList<Types...>{}) > getVisible(const std::multiset<Par*, decltype(cmp)>::iterator& myOrg) {
            std::array < std::vector<Par*>, tSize(TList<Types...>{}) > retArr;

            Par* leftAl = new Par;
            Par* rightAl = new Par;

            leftAl->setX((*myOrg)->getX() - (*myOrg)->viewRange);
            rightAl->setX((*myOrg)->getX() + (*myOrg)->viewRange);

            for (int i = 0; i < retArr.size(); ++i) {
                retArr[i].clear();
                auto first = alives[i].lower_bound(leftAl); //not sure
                auto last = alives[i].upper_bound(rightAl); //not sure
                for (auto iter = first; iter != last; ++iter) {
                    if (*iter == *myOrg) {
                        continue;
                    }
                    if (((*iter)->getX() - (*myOrg)->getX()) * ((*iter)->getX() - (*myOrg)->getX()) + ((*iter)->getY() - (*myOrg)->getY()) * ((*iter)->getY() - (*myOrg)->getY()) <= (*myOrg)->viewRange * (*myOrg)->viewRange) {
                        retArr[i].push_back(*iter);
                    }
                }
            }

            delete leftAl;
            delete rightAl;

            return retArr;
        }

        /// @brief Function that removes organism from sistem by its iterator
        /// @param i Index related to organism's type
        /// @param it Iterator to organism's ptr
        void die(int i, std::multiset<Par*, decltype(cmp)>::iterator& it) {
            std::multiset<Par*, decltype(cmp)>::iterator tmp = it;
            tmp = it;
            ++tmp;
            deathNote.push_back(*it);
            alives_upd[i].erase(it);
            it = tmp;
        }

        /// @brief Function that distribute mass of organism between its killers
        /// @param par Ptr to dying organism
        void kill(Par* par) {
            if (!par->victim) throw std::exception("This form of live has no victim");
            par->mass += 0.5 * par->victim->getMass() / par->victim->killerNumber;
            par->victim = nullptr;
        }

    private:
        double dt = 0.01;
        double w = 100;
        double h = 100;
        double totalMass = 0;

        std::array<std::thread, simulDim> threads;

        std::array < std::multiset<Par*, decltype(cmp)>, simulDim > alives;
        std::array < std::multiset<Par*, decltype(cmp)>, simulDim > alives_upd;

        std::vector<Par*> deathNote;

        /// @brief Array with calculations functions
        std::array < std::function<void(Par*, const TArray<Types...>&, double)>, simulDim> calculations_fs;
        /// @brief Array with move functions
        std::array < std::function<void(Par*, double)>, simulDim> move_fs;
        /// @brief Table with collision functions
        std::array < std::array < std::function<void(Par*, Par*)>, simulDim>, simulDim> collision_fs;
        /// @brief Array with reproduction functions
        std::array < std::function<void(Par*, std::vector<Par*>&)>, simulDim> reproduction_fs;
        /// @brief Array with spawn functions
        std::function<void(TArray<Types...>&, double, double, double, double)> spawn_f;
    };

    template<ParC... Types>
    DarwinSimulator<Types...>::DarwinSimulator() {
        spawn_f = [](TArray<Types...>& alives, double massLeft, double wid, double high, double dt) {
            spawn(alives, massLeft, wid, high, dt);
        };
        set(TList<Types...>{});
        set2d(TList<Types...>{});
    }

    template<ParC... Types>
    DarwinSimulator<Types...>::DarwinSimulator(
        double dt_, double w_, double h_, double totalMass_) :
        dt(dt_), w(w_), h(h_), totalMass(totalMass_) {
        spawn_f = [](TArray<Types...>& alives, double massLeft, double wid, double high, double dt) {
            spawn(alives, massLeft, wid, high, dt);
        };
        set(TList<Types...>{});
        set2d(TList<Types...>{});
    }

    template<ParC... Types>
    DarwinSimulator<Types...>::~DarwinSimulator() {
        for (int i = 0; i != alives.size(); ++i) {
            for (auto j = alives[i].begin(); j != alives[i].end(); ++j) {
                delete* j;
            }
        }
    }

    template<ParC... Types>
    template<ParC T>
    void DarwinSimulator<Types...>::addAlive(const T& inp) {
        T* myOrg = new T;
        *myOrg = inp;
        totalMass += inp.getMass();
        if (!inTList(TList<T, Types...>{})) {
            throw std::invalid_argument("Imposible to add this form of live");
        }
        alives[indexTList(TList<T, Types...>{})].insert(reinterpret_cast<Par*>(myOrg)); //спорно
        alives_upd[indexTList(TList<T, Types...>{})].insert(reinterpret_cast<Par*>(myOrg));
    }

    template<ParC... Types>
    template<ParC T>
    std::vector<T*> DarwinSimulator<Types...>::get() {
        std::vector<T*> tmp;
        for (auto al = alives[indexTList(TList<T, Types...>{})].begin(); al != alives[indexTList(TList<T, Types...>{})].end(); ++al) {
            tmp.push_back(reinterpret_cast<T*>(*al));
        }
        return tmp;
    }

    template<ParC... Types>
    void DarwinSimulator<Types...>::update() {

        for (int i = 0; i != simulDim; ++i) {
            threads[i] = std::thread([this, i] {
                for (auto prev_it = alives[i].begin(); prev_it != alives[i].end(); ++prev_it) {
                    Par* el = *prev_it;
                    auto cur_it = std::find(alives_upd[i].begin(), alives_upd[i].end(), el);
                    alives_upd[i].erase(cur_it);
                    std::array<std::vector<Par*>, simulDim> visible = getVisible(prev_it);
                    TArray<Types...> closest(visible);
                    calculations_fs[i](el, closest, dt);
                    alives_upd[i].insert(el);
                }
            });
        }

        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        for (int i = 0; i != simulDim; ++i) {
            auto j = alives_upd[i].begin();
            while (j != alives_upd[i].end()) {
                if ((*j)->getMass() <= 0.2 * (*j)->getStartMass()) {
                    die(i, j);
                }
                else {
                    ++j;
                }
            }
        }
        alives = alives_upd;

        for (int i = 0; i != simulDim; ++i) {
            for (auto prev_it = alives[i].begin(); prev_it != alives[i].end(); ++prev_it) {
                Par* el = *prev_it;
                auto cur_it = std::find(alives_upd[i].begin(), alives_upd[i].end(), el);
                alives_upd[i].erase(cur_it);
                move_fs[i](el, dt);
                alives_upd[i].insert(el);
            }
        }

        for (int i = 0; i != simulDim; ++i) {
            auto j = alives_upd[i].begin();
            while (j != alives_upd[i].end()) {
                if ((*j)->getMass() <= 0.2 * (*j)->getStartMass()) {
                    die(i, j);
                }
                else {
                    ++j;
                }
            }
        }
        alives = alives_upd;

        std::array < std::array<std::vector<std::vector<bool>>, simulDim>, simulDim > isInteracted;
        for (int i = 0; i < simulDim; ++i) {
            for (int j = 0; j < simulDim; ++j) {
                isInteracted[i][j] = std::vector<std::vector<bool>>(alives[i].size(), std::vector<bool>(alives[j].size(), false));
            }
        }
        for (int i = 0; i < simulDim; ++i) {
            for (int j = 0; j < alives[i].size(); ++j) {
                isInteracted[i][i][j][j] = true;
            }
        }
        for (int i = 0; i != simulDim; ++i) {
            for (auto first_prev_it = alives[i].begin(); first_prev_it != alives[i].end(); ++first_prev_it) {
                Par* first_el = *first_prev_it;
                for (int k = 0; k != simulDim; ++k) {

                    Par first_seen = *first_el;
                    first_seen.moveX(-first_seen.radius());
                    Par last_seen = *first_el;
                    last_seen.moveX(last_seen.radius());
                    auto begin = alives[k].lower_bound(&first_seen);
                    auto end = alives[k].upper_bound(&last_seen);

                    auto first_cur_it = std::find(alives_upd[i].begin(), alives_upd[i].end(), first_el);
                    alives_upd[i].erase(first_cur_it);
                    for (auto second_prev_it = begin; second_prev_it != end; ++second_prev_it) {
                        Par* second_el = *second_prev_it;
                        if ((first_el->getX() - second_el->getX()) * (first_el->getX() - second_el->getX()) + (first_el->getY() - second_el->getY()) * (first_el->getY() - second_el->getY()) > (first_el->radius() + second_el->radius()) * (first_el->radius() + second_el->radius())) continue;
                        if (isInteracted[i][k][std::distance(alives[i].begin(), first_prev_it)][std::distance(alives[k].begin(), second_prev_it)]) continue;
                        isInteracted[k][i][std::distance(alives[k].begin(), second_prev_it)][std::distance(alives[i].begin(), first_prev_it)] = true;

                        auto second_cur_it = std::find(alives_upd[k].begin(), alives_upd[k].end(), second_el);
                        alives_upd[k].erase(second_cur_it);
                        collision_fs[i][k](first_el, second_el);
                        alives_upd[k].insert(second_el);
                    }
                    alives_upd[i].insert(first_el);
                }
            }
        }
        alives = alives_upd;

        for (int i = 0; i < simulDim; ++i) {
            for (auto j = alives_upd[i].begin(); j != alives_upd[i].end(); ++j) {
                if ((*j)->hasVictim()) {
                    kill(*j);
                }
            }
        }

        for (int i = 0; i != simulDim; ++i) {
            std::multiset<Par*, decltype(cmp)>::iterator j = alives_upd[i].begin();
            while (j != alives_upd[i].end()) {
                if ((*j)->isDead() || ((*j)->getMass() <= 0.2 * (*j)->getStartMass())) {
                    die(i, j);
                }
                else {
                    ++j;
                }
            }
        }
        alives = alives_upd;

        for (int i = 0; i != simulDim; ++i) {
            for (auto j = alives[i].begin(); j != alives[i].end(); ++j) {
                std::vector<Par*> newAlives;
                reproduction_fs[i](*j, newAlives);
                for (int k = 0; k < newAlives.size(); ++k) {
                    alives_upd[i].insert(newAlives[k]);
                }
            }
        }
        alives = alives_upd;

        for (int i = 0; i != simulDim; ++i) {
            std::multiset<Par*, decltype(cmp)>::iterator j = alives_upd[i].begin();
            while (j != alives_upd[i].end()) {
                if ((*j)->getMass() <= 0.2 * (*j)->getStartMass()) {
                    die(i, j);
                }
                else {
                    ++j;
                }
            }
        }
        alives = alives_upd;

        std::array<std::vector<Par*>, simulDim> newAlivesVec;
        TArray<Types...> newAlives(newAlivesVec);
        double massLeft = totalMass;
        for (int i = 0; i < simulDim; ++i) {
            for (auto j = alives_upd[i].begin(); j != alives_upd[i].end(); ++j) {
                massLeft -= (*j)->getMass();
            }
        }
        if (massLeft < 0) throw std::exception("mass");
        spawn_f(newAlives, massLeft, w, h, dt);
        for (int i = 0; i < simulDim; ++i) {
            for (int j = 0; j < newAlivesVec[i].size(); ++j) {
                alives_upd[i].insert(newAlivesVec[i][j]);
            }
        }
        alives = alives_upd;

        for (auto el : deathNote) {
            delete el;
        }
        deathNote.clear();
    }

    template<ParC... Types>
    void DarwinSimulator<Types...>::update(int times) {
        for (int i = 0; i < times; ++i) {
            update();
        }
    }

    template<ParC... Types>
    void DarwinSimulator<Types...>::writeTo(std::ostream& ostrm) {
        ostrm << dt << ' ' << w << ' ' << h << ' ' << totalMass << std::endl;
        writeArrOfMultisetTo(alives_upd, TList<Types...>{}, ostrm);
    }

    template<ParC... Types>
    void DarwinSimulator<Types...>::readFrom(std::istream& istrm) {
        istrm >> dt >> w >> h >> totalMass;
        for (int i = 0; i != alives.size(); ++i) {
            for (auto j = alives[i].begin(); j != alives[i].end(); ++j) {
                delete* j;
            }
        }
        readArrOfMultisetFrom(alives_upd, TList<Types...>{}, istrm);
    }

    template<ParC... Types>
    double DarwinSimulator<Types...>::getWidth() {
        return w;
    }

    template<ParC... Types>
    double DarwinSimulator<Types...>::getHeight() {
        return h;
    }

    template<ParC... Types>
    double DarwinSimulator<Types...>::getTimeStep() {
        return dt;
    }

    /// @brief Operator which writes simulation to ostrm
    /// @tparam Types... Types of organisms in simulation
    /// @param ostrm Output stream
    /// @param simul Simulation we are writing to stream
    /// @return Output stream
    template<class... Types>
    std::ostream& operator<<(std::ostream& ostrm, DarwinSimulator<Types...>& simul) {
        simul.writeTo(ostrm);
        return ostrm;
    }

    /// @brief Operator which reads simulation from istrm
    /// @tparam Types... Types of organisms in simulation
    /// @param istrm Input stream
    /// @param simul Simulation we are reading from stream
    /// @return Input stream
    template<class... Types>
    std::istream& operator>>(std::istream& istrm, DarwinSimulator<Types...>& simul) {
        simul.readFrom(istrm);
        return istrm;
    }

}

#endif