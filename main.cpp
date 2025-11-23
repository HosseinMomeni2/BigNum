#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

///this class includes a vector that contains digits of the big int
class bignum
{
    vector<unsigned int> num;
    int size; ///it's good to store the size of the number

public:

    ///constructor creates the vector and sets the size
    explicit bignum(int size = 50)
    {
        this->num = vector<unsigned int>(size, 0);
        this->size = size;
    }

    ///this operator returns a specific digit
    unsigned int& operator[](int index)
    {
        return this->num[index];
    }

    ///operator= should be available for :
    ///1. a big num
    ///2.  a string
    ///3. a const char*
    ///4. an integer (included in the template)
    bignum& operator=(const bignum& n)
    {
        this->num = n.num;
        return *this;
    }
    bignum& operator=(string& n)
    {
        this->num = vector<unsigned int>(this->size);

        std::reverse(n.begin(), n.end());

        int m = std::min((int)this->size, (int)n.size());
        for(int i=0; i<m; i++)
        {
            this->num[i] = n[i] - '0' ;
        }

        return *this;
    }
    bignum& operator=(const char* n_charStar)
    {
        string s = n_charStar;
        *this = s;

        return *this;
    }
    template<typename T> bignum& operator=(T n)
    {
        this->num = vector<unsigned int>(this->size);
        int i=0;
        while(n)
        {
            this->num[i] = n%10;
            n /= 10;
            i++;
        }

        return *this;
    }

    ///operator+ should be available for :
    ///1. bigNum
    ///2. int (included in template)
    ///
    /// note :
    /// it's only accepted to add numbers in "string" or "char*" format by converting them to "bigNum"
    bignum operator+ (const bignum& n)
    {
        bignum res(max(this->size, n.size) + 1);

        for(int i=0; i<min((int)this->size, (int)n.size); i++)
        {
            res.num[i] += this->num[i];
            res.num[i] += n.num[i];

            while(res.num[i] > 10)
            {
                res.num[i] -= 10;
                res.num[i+1] ++;
            }
        }
        for(int i=min((int)this->size, (int)n.size); i<max((int)this->size, (int)n.size); i++)
        {
            res.num[i] += (this->size > n.size ? this->num[i] : n.num[i]);
            while(res.num[i] > 10)
            {
                res.num[i] -= 10;
                res.num[i+1] ++;
            }
        }

        return res;
    }
    template<typename T>
    bignum operator+ (T a)
    {
        bignum left_side;
        left_side = a;

        return *this + left_side;
    }


    ///there is a print function but using "cout << bigNum" is recommended
    void print(string end = "")
    {
        int indextemp;
        for(int x = this->num.size()-1; x>=0; x--)
        {
            if(this->num[x] != 0)
            {
                indextemp = x;
                break;
            }
        }

        for(int i=indextemp; i>=0; i--) cout << this->num[i]; cout << end;
    }
    friend ostream& operator<<(ostream& os, const bignum& n)
    {
        int indextemp;
        for(int x = n.num.size()-1; x>=0; x--)
        {
            if(n.num[x] != 0)
            {
                indextemp = x;
                break;
            }
        }
        for(int i=indextemp; i>=0; i--) os << n.num[i];

        return os;
    }
};


int main() {

    ///tests      git:
    bignum t1, t2;
//    string s = "1265124512368";
    t1 = "111";
    t2 = 13;
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t1 + t2;
//    t = t + 12 + 1 + 2;
//    cout << t << endl;
//    t = 12341;
//    cout << t << endl;



    return 0;
}
