#include "stock.hpp"

using namespace std;

int main()
{
    Stock misys("Misys", 340.0);
    Stock ibm("IBM", 245.0);
    Stock tpsa("TPSA", 95.0);

    // rejestracja inwestorow zainteresowanych powiadomieniami o zmianach kursu spolek
    
    std::shared_ptr<Investor> Kamil = std::make_shared<Investor>("Kamil");
    misys.register_observer(Kamil);
    ibm.register_observer(Kamil);
    Kamil.reset();

    // zmian kursow
    misys.set_price(360.0);
    ibm.set_price(210.0);
    tpsa.set_price(45.0);

    ibm.deregister_observer(Kamil);

    misys.set_price(380.0);
    ibm.set_price(230.0);
    tpsa.set_price(15.0);
}
