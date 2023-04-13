#include "pizzeria.hpp"

int main(){
    std::cout << "Lets create 3 differen pizzerias." << std::endl;

    std::cout << "    First one will be Vegan Pizzeria." << std::endl;
    std::cout << "    Second one will be Tomatoe Pizzeria." << std::endl;
    std::cout << "    Third one will be Italiano Pizzeria." << std::endl;
    Pizzeria* vegan = new Pizzeria("Vegan Pizzeria");
    Pizzeria* tomatoe = new Pizzeria("Tomatoe Pizzeria");
    Pizzeria* italiano = new Pizzeria("Italiano Pizzeria");
    std::cout << "  ---> " << vegan->GetPizzeriasCount() << " pizzerias has been generated." << std::endl;

    std::cout << "Lets add 5 pizzas into Vegan pizzerias menu" << std::endl;

    std::cout << "  ---> Added" << std::endl;

}