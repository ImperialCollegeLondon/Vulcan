#include "Capital_Firm.hpp"


#include "Capital_Firm.hpp"


class Capital_Good{

    public:
    Capital_Good(Capital_Firm_Agent *  seller_pointer, int seller_price, int seller_quantity);
    Capital_Good(Capital_Good&);
    ~Capital_Good();

    int GetPrice() const {return price;}
    Capital_Firm_Agent * GetSeller() {return pSeller;}

    protected:
    int price;
    int quantity;
    Capital_Firm_Agent *  pSeller;




};