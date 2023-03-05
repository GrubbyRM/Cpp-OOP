#include <iostream>
#include <memory>
#include <string>

class Ship {
private:
    int id_;
    std::string name_;
    int speed_;
    int maxCrew_;
    int capacity_;
    size_t crew_;

public:
    int getId() const { return id_; }

    std::string getName() const { return name_; }

    int getSpeed() const { return speed_; }

    int getMaxCrew() const { return maxCrew_; }

    int getCapacity() const { return capacity_; }

    size_t getCrew() const { return crew_; }

    Ship();

    // rule of 5
    //  1. copy constructor
    Ship(const Ship& s)
            : id_(s.id_)
            , name_(s.name_)
            , speed_(s.speed_)
            , maxCrew_(s.maxCrew_)
            , capacity_(s.capacity_)
            , crew_(s.crew_)
    {
    }
    // 2. Assignment operator
    Ship& operator=(const Ship& s)
    {
        id_ = s.id_;
        name_ = s.name_;
        speed_ = s.speed_;
        maxCrew_ = s.maxCrew_;
        capacity_ = s.capacity_;
        crew_ = s.crew_;
        return *this;
    }
    // 3. Destructor
    ~Ship();
    // 4. Move constructor
    Ship(Ship&& s) noexcept
            : id_(s.id_)
            , name_(s.name_)
            , speed_(s.speed_)
            , maxCrew_(s.maxCrew_)
            , capacity_(s.capacity_)
            , crew_(s.crew_)
    {
    }
    // 5. move assignment
    Ship& operator=(Ship&& s) noexcept
    {
        id_ = s.id_;
        name_ = s.name_;
        speed_ = s.speed_;
        maxCrew_ = s.maxCrew_;
        capacity_ = s.capacity_;
        crew_ = s.crew_;
        return *this;
    }
    // end rule of 5

    Ship(int id, std::string name, int speed, int maxCrew, int capacity, size_t crew)
            : id_(id)
            , name_(name)
            , speed_(speed)
            , maxCrew_(maxCrew)
            , capacity_(capacity)
            , crew_(crew)
    {
    }

    void setName(const std::string& name)
    {
        name_ = name;
    }

    Ship& operator+=(const int a)
    {
        crew_ += a;
        return *this;
    }

    Ship& operator-=(const int a)
    {
        crew_ -= a;
        return *this;
    }
};

class Cargo {
public:
    virtual ~Cargo() { }
    virtual size_t getPrice() const = 0;

    virtual std::string getName() const = 0;

    virtual size_t getAmmont() const = 0;

    virtual size_t getBasePrice() const = 0;
};

class Fruit : public Cargo {
private:
    int bestBefore_;
    std::string name_;
    int amount_;
    size_t basePrice_;

public:
    Fruit(int bestBefore, std::string name, int amount, size_t basePrice)
            : bestBefore_(bestBefore)
            , name_(name)
            , amount_(amount)
            , basePrice_(basePrice)
    {
    }

    virtual ~Fruit() override { }

    Fruit& operator--()
    {
        bestBefore_--;
        return *this;
    }

    size_t getPrice() const override
    {
        return getBasePrice() * bestBefore_;
    }

    std::string getName() const override { return name_; }

    size_t getAmmont() const override { return amount_; }

    size_t getBasePrice() const override { return basePrice_; };
};

class Alcohol : public Cargo {
private:
    std::string name_;
    int amount_;
    size_t basePrice_;
    int power_;

public:
    Alcohol(std::string name, int amount, size_t basePrice, int power)
            : name_(name)
            , amount_(amount)
            , basePrice_(basePrice)
            , power_(power)
    {
    }
    virtual ~Alcohol() override { }

    size_t getPrice() const override
    {
        return power_ * getBasePrice();
    }

    std::string getName() const override { return name_; }

    size_t getAmmont() const override { return amount_; }

    size_t getBasePrice() const override { return basePrice_; }
};

void price(std::shared_ptr<Cargo>& c)
{
    std::cout << c->getName();
    std::cout << c->getPrice() << '\n';
}

class Item : public Cargo {
private:
    std::string name_;
    int amount_;
    size_t basePrice_;

public:
    enum itemType_ {
        COMMON = 1,
        RARE = 2,
        EPIC = 3,
        LEGENDARY = 4
    } a_;

    Item(itemType_ a, std::string name, int amount, size_t basePrice)
            : a_(a)
            , name_(name)
            , amount_(amount)
            , basePrice_(basePrice)
    {
    }

    virtual ~Item() override { }

    size_t getPrice() const override
    {
        return getBasePrice() * a_;
    }

    std::string getName() const override { return name_; }

    size_t getAmmont() const override { return amount_; }

    size_t getBasePrice() const override { return basePrice_; }
};

int main()
{
    Item Gold(Item::LEGENDARY, "Złoto", 10, 20);
    std::cout << Gold.getPrice() << '\n';
    std::cout << '\n';

    Alcohol Wodka("Wodka", 5, 100, 40);
    std::cout << Wodka.getPrice() << '\n';
    std::cout << '\n';

    Fruit Apple(15, "Jabłko", 10, 1);
    std::cout << Apple.getPrice() << '\n';
    std::cout << '\n';

    std::shared_ptr<Cargo> cargo1 = std::make_shared<Item>(Item::RARE, "Srebro", 5, 10);
    std::shared_ptr<Cargo> cargo2 = std::make_shared<Alcohol>("Piwo", 4, 5, 6);
    std::shared_ptr<Cargo> cargo3 = std::make_shared<Fruit>(10, "Gruszka", 5, 5);

    std::cout << "Cargo1 price: " << cargo1->getPrice() << '\n';
    std::cout << "Cargo2 price: " << cargo2->getPrice() << '\n';
    std::cout << "Cargo3 price: " << cargo3->getPrice() << '\n';
    std::cout << '\n';
    price(cargo1);
    price(cargo2);
    price(cargo3);

    return 0;
}
// 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got