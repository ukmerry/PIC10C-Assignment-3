// Description:
//     An incomplete implementation of iterators for a RingQueue class.
//
// Notes:
//     The project DOES compile but there is no meaningful output
//
// Your job:
//     To complete this set of classes so that the output produced by 'main'
//     (below), matches the sample file provided at the end of this file.


#include <iostream>

// Forward declaration
template <typename ItemType, int MAX_SIZE>
class RingQueue;



template <typename ItemType, int MAX_SIZE>
class RingQueue{
public:
  // Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator.
  // This is needed if one plans to turn this home-made iterator into one of
  // the special categories of iterators (e.g., input, output, forward, etc.).
  class iterator;
  
  
  
  // Aliases.
  typedef ItemType* pointer;
  typedef ItemType& reference;
  
  
  
public:
  // Definition of RingQueue<ItemType,MAX_SIZE>::iterator
  class iterator{
  private:
    // A link to the parent container
    RingQueue* parent;
    
    // The position within the RingQueue is determined by how far ahead we
    // are from the begining of the queue.
    int offset;
    
  private:  // Private constructor???
    iterator(RingQueue* _parent, int _offset = 0 )
    : parent(_parent), offset(_offset) { }
    
    
    // It is quite common for Containers and their iterators to be friends.
    // After all, they should work closely together.
    friend class RingQueue<ItemType,MAX_SIZE>;
    
    
  public:
    reference operator*() {
      //compute the correct index in buffer(array), that is (offset + begin_index) % capacity
      //then we can locate the address of our value
      //return the reference of our value
      return parent->buffer[(offset + parent->begin_index) % MAX_SIZE] ;
    }
    
    iterator& operator++(){
      offset++; //move the iterator to the right
      return *this;
    }
    
    iterator operator++( int unused ){
      offset++; //move the iterator to the right
      return *this;
    }
    
    bool operator==( const iterator& rhs ) const {
      return offset == rhs.offset; //compare their index, if they are the same, return true
    }
    
    bool operator!=( const iterator& rhs ) const {
      return offset != rhs.offset; //compare their index, if they are not the same, return true
    }
    
  }; // end of iterator class
  
  
  
  /**
   class const_iterator{
   private:
   RingQueue* parent;
   int offset;
   
   private:
   // Only RingQueue objects can create const_iterators...
   const_iterator();
   
   public:
   // ... however, const_iterators can be 'copied'.
   const_iterator( const const_iterator& );
   
   friend class RingQueue<ItemType,MAX_SIZE>;
   };
   */
  
  
  
  // Friendship goes both ways here.
  friend class iterator;
  // friend class const_iterator;  // not implemented... try it if you want.
  
  
  
private:
  // A fixed-size static array with constant capacity that represents the
  // RingQueue
  ItemType buffer[MAX_SIZE];
  
  // The starting index. It changes according to a very specific set of rules
  // (below).
  int begin_index;
  
  // The actual size of the RingQueue. Not to be confused with its capacity.
  int ring_size;
  
  
  
  // A helper function that computes the index of 'the end' of the RingQueue
  int end_index() const {
    // Replace the line(s) below with your code.
    return (begin_index + ring_size) % MAX_SIZE;
  }
  
  
  
public:
  // Constructor
  RingQueue() : begin_index(0), ring_size(0) { }
  
  // Accessors. Note: 'back()' is not considered part of the array.
  ItemType front() const {
    if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // Feel free to throw instead...
    
    
    return buffer[begin_index];
  }
  
  ItemType back() const {
    if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // Feel free to throw instead...
    
    
    return buffer[end_index()];
  }
  
  
  
  // Mutators
  void push_back( const ItemType& value ){
    
    //set the value in the array[endpoint]
    buffer[end_index()] = value;
    
    //check if the ring_size reaches the capacity
    if (ring_size < MAX_SIZE)
      ring_size++; //if no, increment ring size
    else
      //if yes, check if the begin_index reaches the capacity
      if (begin_index < MAX_SIZE)
        begin_index++; //if no, increment begin_index
      else
        begin_index = 0; //if yes, reset begin_index to 0
    
    return;
  }
  
  void pop_front(){
    
    //check if the begin_index reaches the capacity
    if (begin_index < MAX_SIZE)
      begin_index++; //if no, increment begin_index
    else
      begin_index = 0; //if yes, reset begin_index to 0
    
    //decrement ring_size whenever ring_size > 0
    if (ring_size > 0)
      ring_size--;
    
    return;
  }
  
  
  // Functions that return iterators
  iterator begin() {
    return iterator(this,0);
  }
  
  iterator end() {
    return iterator(this,MAX_SIZE-1);
  }
  
  
  // Miscellaneous functions
  size_t size() const {
    return ring_size;
  }
  
  // Debugging functions
  void dump_queue() const {
    std::cout << "Raw queue...\n";
    for ( size_t i = 0 ; i < MAX_SIZE ; ++i )
      std::cout << "Val: " << buffer[i] << ", at: " << buffer + i << '\n';
    std::cout << '\n';
    return;
  }
  
};




int main(){
  RingQueue<int,7> rq;
  rq.dump_queue();
  
  for ( int i = 0 ; i < 8 ; ++i )
    rq.push_back(i+1);
  
  rq.dump_queue();
  rq.pop_front();
  
  std::cout << "Queue via size:\n";
  
  // RingQueue<int,7>::iterator it = rq.begin() ;
  auto it = rq.begin() ;
  for ( size_t i = 0 ; i < rq.size() ; ++i ) {
    std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
    ++it;
  }
  std::cout << '\n';
  
  
  
  std::cout << "Queue via iterators:\n";
  for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
  std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
  }
  std::cout << '\n';
  
  
  rq.dump_queue();
  
  return 0;
}



/**
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 The output of your program [once the missing code is added] should look more
 or less like the output below.
 
 Note: It is dependent on the device where this driver is executed. However,
 it should be clear that the difference between consecutive memory addresses
 is equal to the number reported by 'size_of( int )'.
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
 Raw queue...
 Val: 2, at: 0x7ffcdeeaab40
 Val: 0, at: 0x7ffcdeeaab44
 Val: 4198285, at: 0x7ffcdeeaab48
 Val: 0, at: 0x7ffcdeeaab4c
 Val: 0, at: 0x7ffcdeeaab50
 Val: 0, at: 0x7ffcdeeaab54
 Val: 0, at: 0x7ffcdeeaab58
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 
 Queue via size:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Queue via iterators:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 */
