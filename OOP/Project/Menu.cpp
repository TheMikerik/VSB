#include <string>
#include <iostream>

#include "Drink.h"
#include "Pizza.h"
#include "Menu.h"

Menu::Menu(){
    this->stuff_in_menu = 0;
    this->drinks_count = 0;
    this->pizzas_count = 0;
}
Menu::~Menu(){
}



void Menu::AddDrink(std::string nam, int cst, int prof){
    if ( SeekDrinkName(nam) ){
        std::cout << " (x) " << nam << " is already in menu!! " << std::endl;
        return;
    }
    else if ( this->drinks_count > DRI ){
        std::cout << " (x) Cannot add more drinks" << std::endl;
        return;
    }
    else {
    this->drinks[drinks_count] = new Drink(nam, cst, prof);
    std::cout << "     " << drinks[drinks_count]->GetDrinkName() << " drink was added"<< std::endl;
    this->drinks_count++;
    }
}
void Menu::AddPizza(std::string nam, int cst, int prof){
    if ( SeekPizzaName(nam) ){
        std::cout << " (x) " << nam << " pizza is already in menu!!" << std::endl;
        return;
    }
    else if ( this->pizzas_count > PIZ ){
        std::cout << " (x) Cannot add more pizzas" << std::endl;
        return;
    }
    else {
    this->pizzas[pizzas_count] = new Pizza(nam, cst, prof);
    std::cout << "     " << pizzas[pizzas_count]->GetPizzaName() << " pizza was added"<< std::endl;
    this->pizzas_count++;
    }
}
void Menu::RemoveDrink(int id){
    if ( drinks_count < 1 ){
        std::cout << "     You have removed all drinks" << std::endl;
        return;
    }
    else if ( id > drinks[drinks_count]->GetStaticID()){
        std::cout << "     Drink with ID " << id << " have never existed" << std::endl;
    }
    else if ( this->GetDrink(id) == nullptr ){
        return;
    }
    else if ( id < drinks[drinks_count]->GetStaticID()){
        int i = this->GetDrinkIndex(id);
        this->GetDrink(id)->~Drink();
        drinks[i] = nullptr;

        while (i<this->drinks_count){
            drinks[i] = drinks[i+1];
            i++;
        }
        this->drinks_count--;
        std::cout << "     Drink with ID " << id << " have been deleted" << std::endl;
    }
}
void Menu::RemovePizza(int id){
    if ( pizzas_count < 1 ){
        std::cout << "     You have removed all pizzas" << std::endl;
        return;
    }
    else if ( id > pizzas[pizzas_count]->GetStaticID()){
        std::cout << "     Pizza with ID " << id << " have never existed" << std::endl;
    }
    else if ( this->GetPizza(id) == nullptr ){
        return;
    }
    else if ( id < pizzas[pizzas_count]->GetStaticID()){
        int i = this->GetPizzaIndex(id);
        this->GetPizza(id)->~Pizza();
        pizzas[i] = nullptr;

        while (i<this->pizzas_count){
            pizzas[i] = pizzas[i+1];
            i++;
        }
        this->pizzas_count--;
        std::cout << "     Pizza with ID " << id << " have been deleted" << std::endl;
    }
}


Drink* Menu::GetDrink(int id){
    for (int i=0; i<this->drinks_count; i++){
        if ( drinks[i]->GetDrinkID() == id ){
            return drinks[i];
        }
    }
    std::cout << "     This drink was already deleted" << std::endl;
    return nullptr;
}
Pizza* Menu::GetPizza(int id){
    for (int i=0; i<this->pizzas_count; i++){
        if ( pizzas[i]->GetPizzaID() == id ){
            return pizzas[i];
        }
    }
    std::cout << "     This pizza was already deleted" << std::endl;
    return nullptr;
}
bool Menu::SeekDrinkName(std::string nam){
    for (int i=0; i<this->drinks_count; i++){
        if ( drinks[i]->GetDrinkName() == nam ){
            return true;
        }
    }
    return false;
}
bool Menu::SeekPizzaName(std::string nam){
    for (int i=0; i<this->pizzas_count; i++){
        if ( pizzas[i]->GetPizzaName() == nam ){
            return true;
        }
    }
    return false;
}
int Menu::GetDrinksCount(){
    return this->drinks_count;
}
int Menu::GetPizzasCount(){
    return pizzas_count;
}
int Menu::GetDrinkIndex(int id){
    for (int i=0; i<this->drinks_count; i++){
        if ( drinks[i]->GetDrinkID() == id ){
            return i;
        }
    }
    std::cout << "This drink was not found" << std::endl;
    return -1;
}
int Menu::GetPizzaIndex(int id){
    for (int i=0; i<this->pizzas_count; i++){
        if ( pizzas[i]->GetPizzaID() == id ){
            return i;
        }
    }
    std::cout << "This pizza was not found" << std::endl;
    return -1;
}

void Menu::PrintWholeMenu(){
    std::cout << "\nLets print whole menu:" << std::endl;
    std::cout << "  Pizzas:" << std::endl;
    for( int i=0; i < pizzas_count; i++){
        std::cout << "     Pizza with ID " << pizzas[i]->GetPizzaID() << " is " << pizzas[i]->GetPizzaName() << std::endl;
    }
    std::cout << "  Drinks:" << std::endl;
    for( int i=0; i < drinks_count; i++){
        std::cout << "     Drink with ID " << drinks[i]->GetDrinkID() << " is " << drinks[i]->GetDrinkName() << std::endl;
    }    
}
void Menu::DeletionDrinks(){
    int input;
    std::cout << "\nLets delete some drinks\nType ID of the drink that you wanna delete:     (type '-1' to stop)" << std::endl;
    std::cin >> input;
    while ( input != -1){
        this->RemoveDrink(input);
        std::cin >> input;
    }
}
void Menu::DeletionPizzas(){
    int input;
    std::cout << "\nLets delete some pizzas\nType ID of the pizza that you wanna delete:     (type '-1' to stop)" << std::endl;
    std::cin >> input;
    while ( input != -1){
        this->RemovePizza(input);
        std::cin >> input;
    }
}