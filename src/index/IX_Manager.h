# ifndef IX_MANAGER
# define IX_MANAGER

# include "../utils/pagedef.h"
# include "btree_set.h"

template<typename T> 
class Entry{
public:
  RID_t rid;
  T val;

  Entry(RID_t r, const T& v){
    rid = r;
    val = v;
  }
  friend bool operator< (const Entry &a, const Entry &b) {
    return a.val < b.val;
  }
};

template<typename T> 
class IX_IndexScan;

template<typename T> 
class IX_Manager{
    std::string tablePath;
    stx::btree_set<Entry<T>> btree;

public:  
    void createIndex();
    void destroyIndex();
    void openIndex();
    void closeIndex();

    void insertEntry(RID_t rid, const T& data);
    void deleteEntry(RID_t rid, const T& data);

    IX_Manager(std::string m_name, char** c_name, uint8_t columnCnt, std::string m_path);

    IX_IndexScan<T>* indexScan;
};

template<typename T> 
class IX_IndexScan { 
    stx::btree_set<Entry<T>>& btree;
    CompOp compOp;

    IX_IndexScan(stx::btree_set<Entry<T>>& b): btree(b){}  
public: 
    typename stx::btree_set<Entry<T>>::iterator iter, lowerBound, upperBound;                                                                
    void openScan(const T& data, CompOp m_compOp);           
    int getNextEntry(RID_t& rid);                   
    //void closeScan();   
    friend IX_Manager<T>;                           
};



#endif