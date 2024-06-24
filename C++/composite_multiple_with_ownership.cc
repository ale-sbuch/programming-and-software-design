#include <iostream>
#include <string>
#include <vector>
/*
Una fabbrica di biciclette deve modellare i manufatti che crea: ruote, biciclette, partendo da componenti semplici: raggi delle ruote, cerchione, telaio.
Il costo della bici, o il suo peso sono la somma delle componenti. Permettere all'azienda con un software adeguato di modellare il processo di produzione della bici e tracciare costo o peso dei prodotti.
*/

// Classe Base, l'interfaccia di qualsiasi componente, oltre che della composta
// Classe Foglia che un elemento singolo, non scomponibile
// Classe Composta che aggrega elementi in modo ricorsivo


// Classe Base.
class BikeComponentBase {
 protected:
    const std::string name;
 public:
    BikeComponentBase(const std::string& name_) : name(name_) { }
    virtual const std::string& GetName() const {
        return name;
    }
    virtual float GetPrice() const = 0;
    virtual float GetWeight() const = 0;
    virtual ~BikeComponentBase() { }
};

// Classe Foglia
class BikeComponent : public BikeComponentBase {
 protected:
    const float price;
    const float weight;

 public:
    // Costruttore
    BikeComponent(const std::string& name_, const float price_, const float weight_) :
        BikeComponentBase(name_), price(price_), weight(weight_) {}
    // Metodi
    // virtual const std::string& GetName() const {
        return name;
    };
    virtual float GetPrice() const {
        return price;
    };
    virtual float GetWeight() const {
        return weight;
    };
    virtual ~BikeComponent() { }
};

// Classe composta
class BikeComposite : public BikeComponentBase {
 protected:
    std::vector<const BikeComponentBase*> components;

 public:
    BikeComposite(const std::string& name_) : BikeComponentBase(name_) { }
    void AddComponent(const BikeComponentBase* component) {
        components.push_back(component);
    }
    virtual float GetPrice() const {
        float sum = 0.0f;
        for (const auto& component : components) {
            sum += component->GetPrice();
        }
        return sum;
    }

    virtual float GetWeight() const {
        float sum = 0.0f;
        for (const auto& component : components) {
            sum += component->GetWeight();
        }
        return sum;
    }

    virtual ~BikeComposite() {
        for (const auto& component : components) {
            delete component;
        }
    }
};

class AWheel : public BikeComposite {
 public:
    AWheel() : BikeComposite("ruota_anteriore") {
        BikeComponent* raggi = new BikeComponent("raggi ruota anteriore", 30, 100);
        BikeComponent* cerchione = new BikeComponent("cerchione ruota anteriore", 50, 200);
        this->AddComponent(raggi);
        this->AddComponent(cerchione);
    }
    virtual ~AWheel() {}
};

class PWheel : public BikeComposite {
 public:
    PWheel() : BikeComposite("ruota_posteriore") {
        BikeComponent* raggi = new BikeComponent("raggi ruota posteriore", 50, 120);
        BikeComponent* cerchione = new BikeComponent("cerchione ruota anteriore", 70, 250);
        this->AddComponent(raggi);
        this->AddComponent(cerchione);
    }
    virtual ~PWheel() {}
};

class Bike : public BikeComposite {
 public:
    Bike() : BikeComposite("bike") {
        BikeComponentBase* a_ruota = new AWheel();
        BikeComponentBase* p_ruota = new PWheel();
        BikeComponentBase* telaio = new BikeComponent("telaio", 300, 1000);
        BikeComponentBase* cambio = new BikeComponent("cambio", 100, 100);
        this->AddComponent(telaio);
        this->AddComponent(cambio);
        this->AddComponent(a_ruota);
        this->AddComponent(p_ruota);
    }
    virtual ~Bike() { }
}

int main() {
    Bike bici;
    std::cout << bici.GetName() << " costa ";
    std::cout << bici.GetPrice() << " pesa " << bici.GetWeight() << std::endl;
    return 0;
}