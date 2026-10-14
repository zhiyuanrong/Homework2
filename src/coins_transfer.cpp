#include "coins.hpp"
#include <iostream>
using namespace std;
int main(){
	Coins piggyBank(50,50,50,50);
	Coins pocket(8,3,6,8);
	cout<<piggyBank<<endl;
	cout<<pocket<<endl;
	Coins chips = coins_required_for_cents(149);
        pocket.extract_exact_change(chips);
        cout << chips << endl;

        Coins transfer = coins_required_for_cents(405);
        Coins moved = piggyBank.extract_exact_change(transfer);
        cout << moved << endl;
	pocket.deposite_coins(moved);

        Coins sofa(10, 10, 10, 10);
        piggyBank.deposite_coins(sofa);
        cout << sofa << endl;
        cout << piggyBank << endl;

        print_cents(piggyBank.total_value_in_cents(), cout);
        cout << endl;
}
