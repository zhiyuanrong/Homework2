#include "coins.hpp"
#include <istream>
#include <ostream>
Coins::Coins(int q, int d, int n, int p)
    : quarters(q), dimes(d), nickels(n), pennies(p) {
}

void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    dimes += coins.dimes;
    nickels += coins.nickels;
    pennies += coins.pennies;

    coins.quarters = 0;
    coins.dimes = 0;
    coins.nickels = 0;
    coins.pennies = 0;
}
bool Coins:: has_exact_change_for_coins(const Coins& coins) const{
    if(quarters >= coins.quarters && dimes >= coins.dimes && nickels >= coins.nickels && pennies >= coins.pennies){
        return true;
    }else{
        return false;
    }
}

Coins Coins::extract_exact_change(const Coins& coins){
    if(has_exact_change_for_coins(coins)){
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;
        return coins;
    }else{
        return Coins(0,0,0,0);
    }
}

int Coins::total_value_in_cents() const{
    return quarters * CENTS_PER_QUARTER +
    dimes * CENTS_PER_DIME +
    nickels * CENTS_PER_NICKEL +
    pennies;
}

void Coins::print(std::ostream& out) const{
    out<<quarters<<" quarters, "<<dimes<<" dimes, "<<nickels<<" nickels, "<<pennies<<" pennies";
}

std::ostream& operator<<(std::ostream& out, const Coins& coins){
    coins.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents){
    int quarters = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;

    int dimes = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;

    int nickels = amount_in_cents / CENTS_PER_NICKEL;
    amount_in_cents %= CENTS_PER_NICKEL;

    int pennies = amount_in_cents;

    return Coins(quarters, dimes, nickels, pennies);
}

void print_cents(int cents, std::ostream& out){
    int dollars = cents / 100;
    int remaining_cents = cents % 100;

    out << "$" << dollars << ".";
    if (remaining_cents < 10){
    out << "0" << remaining_cents;
    }else{
    out << remaining_cents;
    }
}

Coins ask_for_coins(std::istream& in, std::ostream& out){
    int q;
    int d;
    int n;
    int p;

    out << "Quarters? ";
    in >> q;

    out << "Dimes? ";
    in >> d;

    out << "Nickels? ";
    in >> n;

    out << "Pennies? ";
    in >> p;

    return Coins(q, d, n, p);
}

void coins_menu(std::istream& in, std::ostream& out){
    Coins myCoins(0, 0, 0, 0);
    int command = 0;

    while (command != 4) {
	out << "1 to deposit\n";
        out << "2 to extract\n";
        out << "3 to balance\n";
        out << "4 to exit\n";
        in >> command;

        if (command == 1) {
            Coins deposit = ask_for_coins(in, out);
            myCoins.deposit_coins(deposit);
        } else if (command == 2) {
            Coins request = ask_for_coins(in, out);
            myCoins.extract_exact_change(request);
        } else if (command == 3) {
            print_cents(myCoins.total_value_in_cents(), out);
            out << '\n';
        }
    }
}

