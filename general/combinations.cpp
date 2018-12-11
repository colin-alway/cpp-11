// g++ -std=c++11 combinations.cpp -o combinations
//
/*
 * https://en.wikipedia.org/wiki/Combination
 * 
 * track k index numbers of the elements selected, starting with {0 .. k−1} (zero-based) 
 * as the first allowed k-combination and then repeatedly moving to the next allowed 
 * k-combination by incrementing the last index number if it is lower 
 * than n-1 (zero-based) or the last index number x that is less than the 
 * index number following it minus one if such an index exists and resetting the 
 * index numbers after x to {x+1, x+2, ...}
 * 
 * https://www.codeproject.com/Articles/4675/Combinations-in-C
 * 
 * https://gist.github.com/rg3/731626
 *      recursive algorithm
 */
// combinations indexer
//
#include <iostream>
#include <vector>

/*
if (id0 > id1) {
    id0 ^= id1;
    id1 ^= id0;
    id0 ^= id1;
}
*/              

class CombIndexer {
protected:
    unsigned int last_index_;
    std::vector<unsigned int> index_;
    
public:
    CombIndexer(unsigned int set_size, unsigned int comb) : last_index_(set_size - 1)
    {
        if (comb > set_size) {
            comb = set_size;
        }
        index_.resize(comb);
    }
    
    unsigned int set_size() const {
        return last_index_ + 1;
    }
    
    // get all combination indexes
    std::vector< std::vector<unsigned int> > indexes() {
        std::vector< std::vector<unsigned int> > results;
        
        // initialse indexes
        for (int id = 0; id < index_.size(); ++id) {
            index_[id] = id;
        }
        
        // make first array
        results.push_back(index_);
        
        // loop
        int this_id = index_.size() - 1;
        while (true) {
            
            if (index_[this_id] >= last_index_) {
                this_id--;
            }
            if (this_id < 0) {
                break;
            }

            index_[this_id]++;
            results.push_back(index_);
            

            //break;
        }
        
        return results;
    }
};


int main()
{
    CombIndexer comb = CombIndexer(6, 3);

    std::vector< std::vector<unsigned int> > indexes = comb.indexes();
    for (auto aa = indexes.begin(); aa != indexes.end(); ++aa) {
        for (auto bb : *aa) {
            std::cout << " " << bb;
        }
        std::cout << std::endl;
    }
    
    return 0;
}
